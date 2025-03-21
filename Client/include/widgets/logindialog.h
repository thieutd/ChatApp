#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "AppManager.h"
#include "typedefs.h"

#include <QDialog>

namespace Ui {
class LoginDialog;
}
class QRestReply;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

public slots:
    void onServerTestFinished(const QRestReply &reply);
    void onLoggedIn();
    void onRegistered();
    void onLoggedOut();
    void onApplicationStateChanged(AppState newState);

    void onLoginFailed(const AuthRequestError &error);
    void onRegisterFailed(const AuthRequestError &error);
    void onLogoutFailed(const AuthRequestError &error);

signals:
    void serverTestRequested(const QUrl &url);
    void loginRequested(const QUrl &url, const QString &username, const QString &password);
    void registerRequested(const QUrl &url, const QString &username, const QString &password);
    void logoutRequested();

private slots:
    void on_serverTestButton_clicked();
    void on_authActionButton_clicked();
    void on_authModeChanged(int id);

private:
    void setupAuthRadioButtonGroup();
    void setupConnections();
    void updateAuthState(bool isAuthenticated);

    void load();
    void save();
    QUrl getUrl() const;
    std::pair<QString, QString> getUserNameAndPassword() const;
    bool validateAuthInputs();

    void handleLogin();
    void handleRegister();
    void handleLogout();

private:
    bool authenticated;
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
