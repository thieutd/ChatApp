#include "restclients/restclientmanager.h"
#include "asyncdatabase.h"
#include "restclients/restclientbase.h"

#include <ranges>

RestClientManager::RestClientManager(QObject *parent)
    : IRestClientManager(parent)
    , asyncDatabase(nullptr)
    , networkAccessManager(new QNetworkAccessManager(this))
    , restAccessManager(new QRestAccessManager(networkAccessManager, this))
{}

RestClientManager::~RestClientManager()
{
    qDebug() << QThread::currentThread() << "RestClientManager::~RestClientManager()";
    for (auto &client : clients | std::views::values) {
        delete client;
    }
    clients.clear();
    delete asyncDatabase;
    asyncDatabase = nullptr;
}

RestClientManager &RestClientManager::addClient(RestClientBase *client, QString path)
{
    Q_ASSERT_X(!clients.contains(path), "RestClientManager", "Client path must be unique");
    Q_ASSERT_X(QPointer(client).isNull() == false, "RestClientManager", "Client must not be null");
    client->setParent(this);
    client->setRestAccessManager(*restAccessManager);
    clients.insert({std::move(path), client});
    return *this;
}

RestClientManager &RestClientManager::setUrl(const QUrl &url, const bool isSubdomain)
{
    if (isSubdomain) {
        resolveUrlFunc = [url](const QString &path) -> QUrl {
            QUrl newUrl(url);
            newUrl.setAuthority(QString("%1.%2").arg(path, url.authority()));
            return newUrl;
        };
    } else {
        resolveUrlFunc = [url](const QString &path) -> QUrl { return url.resolved(path); };
    }
    for (const auto &[path, client] : clients) {
        client->setBaseUrl(resolveUrlFunc(path));
    }
    emit resolveUrlFuncChanged(resolveUrlFunc);
    return *this;
}

RestClientManager &RestClientManager::setAuthStrategy(
    std::shared_ptr<const AuthStrategy> newAuthStrategy)
{
    authStrategy = std::move(newAuthStrategy);
    emit authStrategyChanged(authStrategy);
    return *this;
}

RestClientManager &RestClientManager::setAsyncDatabase(AsyncDatabase *newAsyncDatabase)
{
    if (newAsyncDatabase == asyncDatabase) {
        return *this;
    }
    if (asyncDatabase) {
        delete asyncDatabase;
    }
    asyncDatabase = newAsyncDatabase;
    asyncDatabase->setParent(this);
    emit asyncDatabaseChanged(asyncDatabase);
    return *this;
}

RestClientManager &RestClientManager::setAutoDeleteReplies(const bool autoDelete)
{
    networkAccessManager->setAutoDeleteReplies(autoDelete);
    return *this;
}

RestClientManager &RestClientManager::setRequestFactory(QNetworkRequestFactory newRequestFactory)
{
    requestFactory = std::move(newRequestFactory);
    for (const auto &client : clients | std::views::values) {
        client->setRequestFactory(requestFactory);
    }
    return *this;
}

bool RestClientManager::autoDeleteReplies() const
{
    return networkAccessManager->autoDeleteReplies();
}

RestClientBase *RestClientManager::getClient(const QString &path) const
{
    return clients.contains(path) ? clients.at(path) : nullptr;
}

QRestAccessManager &RestClientManager::getRestAccessManager()
{
    return *restAccessManager;
}

const QNetworkRequestFactory &RestClientManager::getRequestFactory() const
{
    return requestFactory;
}

const std::shared_ptr<const AuthStrategy> RestClientManager::getAuthStrategy() const
{
    return authStrategy;
}

const AsyncDatabase *RestClientManager::getAsyncDatabase() const
{
    return asyncDatabase;
}

const std::optional<const std::function<QUrl(const QString &)>> RestClientManager::getResolveUrlFunc()
    const
{
    return (resolveUrlFunc) ? std::make_optional(resolveUrlFunc) : std::nullopt;
}
