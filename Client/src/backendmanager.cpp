#include "backendmanager.h"
#include "appsettings.h"
#include "restclients/authstrategy.h"
#include "restclients/jwtauthclient.h"
#include "restclients/messageclient.h"
#include "restclients/restclientmanager.h"
#include "restclients/testclient.h"
#include "restclients/userclient.h"
#include "sqliteasyncdatabase.h"

#include <ClientModels_all_include.gen.h>
#include <QRestReply>
#include <QTimer>
#include <QxOrm.h>

const QString authPath = QString::fromLatin1("auth");
const QString userPath = QString::fromLatin1("users");
const QString testPath = QString::fromLatin1("test");
const QString messagePath = QString::fromLatin1("messages");
const QString databasePath = QString::fromLatin1("sqlite.db");

QFuture<AsyncDatabase::Result> initializeDatabase(AsyncDatabase &asyncDatabase)
{
    return asyncDatabase.open(databasePath).then([](AsyncDatabase::Result &&result) {
        return result.and_then([]() -> AsyncDatabase::Result {
            auto qxSingleton = qx::QxSqlDatabase::getSingleton();
            auto db = qxSingleton->getDatabase();

            auto hasFullTable = [tables = db.tables()]() -> bool {
                return [&tables]<typename... Tables>() -> bool {
                    return (tables.contains(Tables::table_name()) && ...);
                }.operator()<User, Room, RoomMembership, Message>();
            };

            if (hasFullTable()) {
                return {};
            }

            QFile schemaFile{":/schemas/sqlite_db_create.sql"};
            if (!schemaFile.open(QIODevice::ReadOnly)) {
                return std::unexpected(QSqlError{QStringLiteral("Failed to open schema file")});
            }

            QTextStream schemaStream{&schemaFile};
            while (!schemaStream.atEnd()) {
                const QString query = schemaStream.readLine();
                if (!query.isEmpty()) {
                    QSqlQuery sqlQuery{db};
                    if (!sqlQuery.exec(query)) {
                        return std::unexpected(sqlQuery.lastError());
                    }
                }
            }
            return {};
        });
    });
}

BackendManager::BackendManager(QObject *parent)
    : QObject(parent)
    , restClientManager(nullptr)
{}

BackendManager::~BackendManager()
{
    qDebug() << QThread::currentThread() << "BackendManager::~BackendManager()";
}

JwtAuthClient *BackendManager::getAuthClient() const
{
    Q_ASSERT_X(restClientManager, Q_FUNC_INFO, "Rest client manager must be initialized");
    if (!restClientManager) {
        return nullptr;
    }
    return restClientManager->getClient<JwtAuthClient>(authPath);
}

UserClient *BackendManager::getUserClient() const
{
    Q_ASSERT_X(restClientManager, Q_FUNC_INFO, "Rest client manager must be initialized");
    if (!restClientManager) {
        return nullptr;
    }
    return restClientManager->getClient<UserClient>(userPath);
}

TestClient *BackendManager::getTestClient() const
{
    Q_ASSERT_X(restClientManager, Q_FUNC_INFO, "Rest client manager must be initialized");
    if (!restClientManager) {
        return nullptr;
    }
    return restClientManager->getClient<TestClient>(testPath);
}

MessageClient *BackendManager::getMessageClient() const
{
    Q_ASSERT_X(restClientManager, Q_FUNC_INFO, "Rest client manager must be initialized");
    if (!restClientManager) {
        return nullptr;
    }
    return restClientManager->getClient<MessageClient>(messagePath);
}

void BackendManager::initialize()
{
    if (restClientManager) {
        return;
    }
    // database initialization
    auto sqliteAsyncDatabase = new SqliteAsyncDatabase{};
    auto sqlFuture = initializeDatabase(*sqliteAsyncDatabase);

    if (!requestFactory) {
        requestFactory = QNetworkRequestFactory{};
    }
    restClientManager = new RestClientManager(this);

    QUrl url = requestFactory->baseUrl();
    if (!url.isValid()) {
        if (const auto urlOpt = AppSettings::getInstance().getServerUrl()) {
            url = *urlOpt;
        }
    }

    restClientManager->addClient(new TestClient, testPath)
        .addClient(new JwtAuthClient, authPath)
        .addClient(new UserClient, userPath)
        .addClient(new MessageClient, messagePath)
        .setRequestFactory(requestFactory.value())
        .setUrl(url);

    // connect internal signals
    JwtAuthClient *authClient = getAuthClient();
    UserClient *userClient = getUserClient();
    MessageClient *messageClient = getMessageClient();

    connect(authClient,
            &JwtAuthClient::accessTokenChanged,
            this,
            [this, authClient, userClient, messageClient](const auto &authStrategySharedPtr,
                                                          const QDateTime &expiry) {
                authClient->save();
                restClientManager->setAuthStrategy(authStrategySharedPtr);
                userClient->setAuthStrategy(authStrategySharedPtr);
                messageClient->setAuthStrategy(authStrategySharedPtr);
                userClient->fetchSelf();
                messageClient->openConnection();

                QTimer::singleShot(expiry.secsTo(QDateTime::currentDateTime()),
                                   authClient,
                                   &JwtAuthClient::refresh);
            });

    connect(authClient, &JwtAuthClient::loggedOut, this, [this]() { emit authenticationCleared(); });

    connect(authClient, &JwtAuthClient::refreshFailed, this, [this](const AuthRequestError &error) {
        QString errorMsg = errorVariantToString(error);
        emit authenticationFailed(errorMsg);
    });

    // Check if the database initialization was successful
    sqlFuture.waitForFinished();
    if (sqlFuture.isCanceled() || !sqlFuture.result().has_value()) {
        QString errorMsg = QString("Failed to initialize database: %1")
                               .arg(sqlFuture.isCanceled() ? "canceled"
                                                           : sqlFuture.result().error().text());
        qFatal() << errorMsg;
    }

    restClientManager->setAsyncDatabase(sqliteAsyncDatabase);
    userClient->setAsyncDatabase(sqliteAsyncDatabase);

    emit initialized();
}

void BackendManager::clearData()
{
    delete restClientManager;
    restClientManager = nullptr;
    if (QFile::exists(databasePath)) {
        bool success = QFile::remove(databasePath);
        Q_ASSERT(success);
    }
    emit dataCleared();
}

void BackendManager::loadStoredAuth()
{
    auto authClient = getAuthClient();
    auto userClient = getUserClient();
    Q_ASSERT_X(authClient, Q_FUNC_INFO, "Auth client must be initialized");
    if (!authClient) {
        return;
    }
    connect(
        userClient,
        &UserClient::fetched,
        this,
        [this]() { emit authenticationSucceeded(); },
        Qt::SingleShotConnection);

    if (authClient->load()) {
        authClient->refresh();
    } else {
        emit authenticationCleared();
    }
}

void BackendManager::setUrl(const QUrl &url)
{
    restClientManager->setUrl(url);
}

void BackendManager::setNetworkRequestFactory(QNetworkRequestFactory factory)
{
    this->requestFactory = std::move(factory);
}

std::shared_ptr<const QRestReply> BackendManager::makeSharedRestReply(const QRestReply &reply)
{
    QNetworkReply *networkReply = reply.networkReply();
    networkReply->setParent(nullptr);
    return {new QRestReply{networkReply}, [](QRestReply *reply) {
                delete reply->networkReply();
                delete reply;
            }};
}

void BackendManager::onUrlChange(const QUrl &url)
{
    setUrl(url);
}

void BackendManager::onApplicationStateChanged(AppState newState)
{
    if (newState == AppState::Initializing) {
        initialize();
    } else if (newState == AppState::AuthCheck) {
        loadStoredAuth();
    } else if (newState == AppState::LoggedOut) {
        clearData();
    }
}
