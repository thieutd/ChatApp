#include "AppManager.h"
#include "BackendManager.h"
#include "appsettings.h"
#include "config.h"
#include "restclients/jwtauthclient.h"
#include "restclients/messageclient.h"
#include "restclients/testclient.h"
#include "widgets/logindialog.h"
#include "widgets/mainwindow.h"

#include <QFinalState>
#include <QMessageBox>
#include <QRestReply>
#include <QSignalTransition>
#include <QThread>

class AuthFailureTransition : public QSignalTransition
{
    Q_OBJECT
public:
    AuthFailureTransition(QObject *sender, const char *signal, QState *sourceState = nullptr)
        : QSignalTransition(sender, signal, sourceState)
    {}

    ~AuthFailureTransition() override
    {
        qDebug() << QThread::currentThread() << "AuthFailureTransition::~AuthFailureTransition()";
    }

private:
    bool eventTest(QEvent *event) override
    {
        QStateMachine::SignalEvent *signalEvent = dynamic_cast<QStateMachine::SignalEvent *>(event);
        if (!signalEvent) {
            return false;
        }

        if (!QSignalTransition::eventTest(event)) {
            return false;
        }

        const QList<QVariant> &arguments = signalEvent->arguments();
        Q_ASSERT(arguments.size() == 1 && "AuthFailureTransition expects a single argument");
        if (arguments.size() != 1) {
            qWarning() << "Expected 1 argument, got" << arguments.size();
            return false;
        }

        QVariant arg = arguments.at(0);
        Q_ASSERT(arg.typeId() == QMetaType::QString
                 && "AuthFailureTransition expects a QString argument");
        if (!arg.canConvert<QString>()) {
            qWarning() << "Argument is not a QString";
            return false;
        }

        QString error = arg.toString();
        QMessageBox::critical(nullptr,
                              tr("Authentication Error"),
                              tr("%1: Authentication failed: %2")
                                  .arg(senderObject()->metaObject()->className(), error));

        return true;
    }
};

AppManager::AppManager(QObject *parent)
    : QObject(parent)
    , backendManager(new BackendManager)
    , backendManagerThread(new QThread(this))
    , mainWindow(nullptr)
    , loginDialog(nullptr)
{
    QNetworkRequestFactory requestFactory;
    QHttpHeaders headers;
    headers.append(QHttpHeaders::WellKnownHeader::UserAgent, Client::UserAgent);
    requestFactory.setCommonHeaders(headers);

    backendManager->setNetworkRequestFactory(std::move(requestFactory));
    backendManagerThread->setObjectName("BackendManager Thread");
    backendManager->moveToThread(backendManagerThread);

    QEventLoop loop;
    connect(backendManagerThread, &QThread::started, &loop, &QEventLoop::quit);
    backendManagerThread->start();

    setupStates();
    setupTransitions();
    setupConnections();
    loop.exec();
}

AppManager::~AppManager()
{
    qDebug() << QThread::currentThread() << "AppManager::~AppManager()";
    stateMachine.stop();
    cleanupLoginDialog();
    cleanupMainWindow();

    backendManagerThread->quit();
    AppSettings::getInstance().commit();
    backendManagerThread->wait();

    emit finished();
}

AppState AppManager::getCurrentState() const
{
    if (stateMachine.configuration().contains(initializatingState)) {
        return AppState::Initializing;
    } else if (stateMachine.configuration().contains(authCheckState)) {
        return AppState::AuthCheck;
    } else if (stateMachine.configuration().contains(loginState)) {
        return AppState::Login;
    } else if (stateMachine.configuration().contains(mainState)) {
        return AppState::Main;
    } else if (stateMachine.configuration().contains(loggedOutState)) {
        return AppState::LoggedOut;
    } else if (stateMachine.configuration().contains(finalState)) {
        return AppState::Final;
    }

    return AppState::Unknown;
}

void AppManager::start()
{
    stateMachine.start();
}

void AppManager::setupStates()
{
    // Create states
    initializatingState = new QState(&stateMachine);
    authCheckState = new QState(&stateMachine);
    loginState = new QState(&stateMachine);
    mainState = new QState(&stateMachine);
    loggedOutState = new QState(&stateMachine);
    finalState = new QFinalState(&stateMachine);

    // Set initial state
    stateMachine.setInitialState(initializatingState);
}

void AppManager::setupTransitions()
{
    // Starting -> Auth Check
    initializatingState->addTransition(backendManager, &BackendManager::initialized, authCheckState);
    // Auth Check -> Main (on successful auth)
    authCheckState->addTransition(backendManager,
                                  &BackendManager::authenticationSucceeded,
                                  mainState);
    // Auth Check -> Login (on auth cleared)
    authCheckState->addTransition(backendManager,
                                  &BackendManager::authenticationCleared,
                                  loginState);
    // Auth Check -> Login (on auth failure)
    auto authFailureTransition = new AuthFailureTransition(backendManager,
                                                           SIGNAL(authenticationFailed(QString)),
                                                           authCheckState);
    authFailureTransition->setTargetState(loginState);

    authCheckState->addTransition(authFailureTransition);

    // Login -> Main
    loginState->addTransition(backendManager, &BackendManager::authenticationSucceeded, mainState);

    // Main -> Login (on logout)
    mainState->addTransition(backendManager, &BackendManager::authenticationCleared, loggedOutState);
    // LoggedOut -> initializating (on data cleared)
    loggedOutState->addTransition(backendManager, &BackendManager::dataCleared, initializatingState);

    // Main -> Login (on auth failure)
    authFailureTransition = new AuthFailureTransition(backendManager,
                                                      SIGNAL(authenticationFailed(QString)),
                                                      mainState);
    mainState->addTransition(authFailureTransition);
}

void AppManager::setupConnections()
{
    connect(backendManagerThread, &QThread::finished, backendManager, &BackendManager::deleteLater);

    connect(this,
            &AppManager::stateChanged,
            backendManager,
            &BackendManager::onApplicationStateChanged);

    connect(initializatingState, &QState::entered, this, [this]() {
        emit stateChanged(AppState::Initializing);
    });

    connect(initializatingState, &QState::exited, this, [this]() {
        createMainWindow();
        qDebug() << "Exited initializing state";
    });

    connect(authCheckState, &QState::entered, backendManager, [this]() {
        qDebug() << "Entered auth check state";
        emit stateChanged(AppState::AuthCheck);
    });

    connect(loginState, &QState::entered, this, [this]() {
        qDebug() << "Entered login state";
        emit stateChanged(AppState::Login);
        createLoginDialog();
    });

    connect(loginState, &QState::exited, this, [this]() { qDebug() << "Exited login state"; });

    connect(mainState, &QState::entered, this, [this]() {
        qDebug() << "Entered main state";
        emit stateChanged(AppState::Main);
    });

    connect(loggedOutState, &QState::entered, this, [this]() {
        qDebug() << "Entered logged out state";
        emit stateChanged(AppState::LoggedOut);
        cleanupLoginDialog();
        cleanupMainWindow();
        AppSettings::getInstance().clear();
    });

    connect(finalState, &QState::entered, this, [this]() {
        qDebug() << "Entered final state";
        emit stateChanged(AppState::Final);
        cleanupLoginDialog();
        cleanupMainWindow();
    });

    connect(finalState, &QState::exited, this, [this]() { qDebug() << "Exited final state"; });

    connect(&stateMachine, &QStateMachine::stopped, this, [this]() {
        qDebug() << "State machine finished";
    });

    connect(backendManager,
            &BackendManager::crossThreadRestReplySignal,
            this,
            [](const QObject *receiver,
               const char *method,
               const std::shared_ptr<const QRestReply> &replyPtr) {
                const QRestReply &reply = *replyPtr;
                QMetaObject::invokeMethod(const_cast<QObject *>(receiver),
                                          method,
                                          Qt::DirectConnection,
                                          Q_ARG(const QRestReply &, reply));
            });
}

void AppManager::createMainWindow()
{
    if (!mainWindow) {
        mainWindow = new MainWindow();
        setupMainWindowConnections();
        mainWindow->setWindowTitle(Client::AppName);
        mainWindow->onApplicationStateChanged(getCurrentState());
        mainWindow->show();
    }
}

void AppManager::cleanupMainWindow()
{
    if (mainWindow) {
        mainWindow->deleteLater();
        mainWindow = nullptr;
    }
}

void AppManager::createLoginDialog()
{
    if (!loginDialog) {
        loginDialog = new LoginDialog(mainWindow);
        setupLoginDialogConnections();
        loginDialog->onApplicationStateChanged(getCurrentState());
        loginDialog->show();
    }
}

void AppManager::cleanupLoginDialog()
{
    if (loginDialog) {
        loginDialog->deleteLater();
        loginDialog = nullptr;
    }
}

void AppManager::setupLoginDialogConnections()
{
    Q_ASSERT_X(loginDialog, Q_FUNC_INFO, "Login dialog must be initialized");
    if (!loginDialog) {
        return;
    }

    auto testClient = backendManager->getTestClient();
    auto authClient = backendManager->getAuthClient();

    // Server test connections
    connect(loginDialog,
            &LoginDialog::serverTestRequested,
            testClient,
            [testClient](const QUrl &url) { testClient->test(QNetworkRequest(url)); });

    // Login connections
    connect(loginDialog,
            &LoginDialog::loginRequested,
            authClient,
            [this, authClient](const QUrl &url, const QString &username, const QString &password) {
                backendManager->onUrlChange(url);
                authClient->login(username, password);
            });

    // Register connections
    connect(loginDialog,
            &LoginDialog::registerRequested,
            authClient,
            [this, authClient](const QUrl &url, const QString &username, const QString &password) {
                backendManager->onUrlChange(url);
                authClient->registerUser(username, password);
            });

    // Logout connection
    connect(loginDialog, &LoginDialog::logoutRequested, authClient, &JwtAuthClient::logout);

    // Auth result connections
    connect(authClient, &JwtAuthClient::loggedIn, loginDialog, &LoginDialog::onLoggedIn);
    connect(authClient, &JwtAuthClient::registered, loginDialog, &LoginDialog::onRegistered);
    connect(authClient, &JwtAuthClient::loggedOut, loginDialog, &LoginDialog::onLoggedOut);

    connect(authClient, &JwtAuthClient::loginFailed, loginDialog, &LoginDialog::onLoginFailed);
    connect(authClient, &JwtAuthClient::registerFailed, loginDialog, &LoginDialog::onRegisterFailed);
    connect(authClient, &JwtAuthClient::logoutFailed, loginDialog, &LoginDialog::onLogoutFailed);

    // Cleanup
    connect(loginDialog, &LoginDialog::accepted, [this]() { cleanupLoginDialog(); });
    connect(loginDialog, &LoginDialog::rejected, [this]() { cleanupLoginDialog(); });

    // App state change
    connect(this,
            &AppManager::stateChanged,
            loginDialog,
            &LoginDialog::onApplicationStateChanged,
            Qt::DirectConnection);

    {
        // For testing purposes
        std::vector<QMetaObject::Connection> connections;
        auto conn = connect(
            testClient, &TestClient::testFinished, backendManager, [this](const QRestReply &reply) {
                emit backendManager->crossThreadRestReplySignal(this->loginDialog,
                                                                "onServerTestFinished",
                                                                backendManager->makeSharedRestReply(
                                                                    reply));
            });
        connections.push_back(std::move(conn));
        connect(loginDialog, &LoginDialog::destroyed, [connections = std::move(connections)]() {
            for (const auto &conn : connections) {
                QObject::disconnect(conn);
            }
        });
    }
}

void AppManager::setupMainWindowConnections()
{
    Q_ASSERT_X(mainWindow, Q_FUNC_INFO, "Main window must be initialized");
    if (!mainWindow) {
        return;
    }

    auto messageClient = backendManager->getMessageClient();

    connect(this,
            &AppManager::stateChanged,
            mainWindow,
            &MainWindow::onApplicationStateChanged,
            Qt::DirectConnection);

    connect(mainWindow,
            &MainWindow::sendMessageRequested,
            messageClient,
            &MessageClient::sendMessage);

    connect(messageClient,
            &MessageClient::messageReceived,
            mainWindow,
            &MainWindow::onMessageReceived);

    //  MainWindow session button
    connect(mainWindow, &MainWindow::loginDialogRequested, this, [this]() { createLoginDialog(); });
}

#include "appmanager.moc"
