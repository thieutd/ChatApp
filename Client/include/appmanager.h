#ifndef APPSTATEMANAGER_H
#define APPSTATEMANAGER_H

#include "appstate.h"

#include <QObject>
#include <QPointer>
#include <QStateMachine>

class BackendManager;
class LoginDialog;
class MainWindow;
class QFinalState;
class QRestReply;

class AppManager : public QObject
{
    Q_OBJECT
public:
    explicit AppManager(QObject* parent = nullptr);
    ~AppManager();

    void start();
    AppState getCurrentState() const;

signals:
    void stateChanged(AppState newState);
    void finished();

private:
    void setupStates();
    void setupTransitions();
    void setupConnections();
    void setupLoginDialogConnections();
    void setupMainWindowConnections();
    void createLoginDialog();
    void cleanupLoginDialog();
    void createMainWindow();
    void cleanupMainWindow();

    BackendManager* backendManager;
    QThread* backendManagerThread;

    QPointer<MainWindow> mainWindow;
    QPointer<LoginDialog> loginDialog;

    QStateMachine stateMachine;
    QState* initializatingState;
    QState* authCheckState;
    QState* loginState;
    QState* mainState;
    QState* loggedOutState;
    QFinalState* finalState;
};

#endif // APPSTATEMANAGER_H
