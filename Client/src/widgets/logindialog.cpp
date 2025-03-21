#include "widgets/logindialog.h"
#include "appsettings.h"
#include "httpstatuscode.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QRestReply>
#include <QThread>

enum AuthAction { Login, Register, Logout };

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
    , authenticated(false)
{
    ui->setupUi(this);
    setupAuthRadioButtonGroup();
    setupConnections();
    load();
    updateAuthState(authenticated);
}

LoginDialog::~LoginDialog()
{
    qDebug() << QThread::currentThread() << "LoginDialog::~LoginDialog()";
    delete ui;
}

void LoginDialog::setupAuthRadioButtonGroup()
{
    ui->authModeSelectionButtonGroup->setId(ui->loginRadioButton, Login);
    ui->authModeSelectionButtonGroup->setId(ui->registerRadioButton, Register);
    ui->authModeSelectionButtonGroup->button(Login)->setChecked(true);
}

void LoginDialog::setupConnections()
{
    connect(ui->authModeSelectionButtonGroup, QOverload<int>::of(&QButtonGroup::idClicked),
            this, &LoginDialog::on_authModeChanged);
}

void LoginDialog::on_authModeChanged(int id)
{
    switch (id) {
    case Login:
        ui->authActionButton->setText(tr("Login"));
        break;
    case Register:
        ui->authActionButton->setText(tr("Register"));
        break;
    case Logout:
        ui->authActionButton->setText(tr("Logout"));
        break;
    default:
        Q_ASSERT_X(false, Q_FUNC_INFO, "Unknown auth action");
    }
}

bool LoginDialog::validateAuthInputs()
{
    auto url = getUrl();
    if (!url.isValid()) {
        QString errorMsg = tr("Please enter a valid server URL");
        QMessageBox::warning(this, tr("Invalid URL"), errorMsg);
        return false;
    }

    auto [username, password] = getUserNameAndPassword();
    if (username.isEmpty() || password.isEmpty()) {
        QString errorMsg = tr("Please enter both username and password");
        QMessageBox::warning(this, tr("Missing Credentials"), errorMsg);
        return false;
    }

    return true;
}

void LoginDialog::handleLogin()
{
    auto url = getUrl();
    auto [username, password] = getUserNameAndPassword();
    emit loginRequested(url, username, password);
    ui->authActionButton->setEnabled(false);
}

void LoginDialog::handleRegister()
{
    auto url = getUrl();
    auto [username, password] = getUserNameAndPassword();
    emit registerRequested(url, username, password);
    ui->authActionButton->setEnabled(false);
}

void LoginDialog::handleLogout()
{
    emit logoutRequested();
}

void LoginDialog::onLoginFailed(const AuthRequestError &error)
{
    QString errorMsg = errorVariantToString(error);
    QMessageBox::critical(this, tr("Login Failed"), errorMsg);
    ui->authActionButton->setEnabled(true);
}

void LoginDialog::onRegisterFailed(const AuthRequestError &error)
{
    QString errorMsg = errorVariantToString(error);
    QMessageBox::critical(this, tr("Registration Failed"), errorMsg);
    ui->authActionButton->setEnabled(true);
}

void LoginDialog::onLogoutFailed(const AuthRequestError &error)
{
    QString errorMsg = errorVariantToString(error);
    QMessageBox::critical(this, tr("Logout Failed"), errorMsg);
    ui->authActionButton->setEnabled(true);
}

void LoginDialog::updateAuthState(bool isAuthenticated)
{
    authenticated = isAuthenticated;
    ui->usernameLineEdit->setEnabled(!isAuthenticated);
    ui->passwordLineEdit->setEnabled(!isAuthenticated);
    ui->loginRadioButton->setEnabled(!isAuthenticated);
    ui->registerRadioButton->setEnabled(!isAuthenticated);

    if (isAuthenticated) {
        on_authModeChanged(Logout);
    } else {
        on_authModeChanged(ui->authModeSelectionButtonGroup->checkedId());
    }
}

void LoginDialog::onServerTestFinished(const QRestReply &reply)
{
    if (reply.isHttpStatusSuccess()) {
        QMessageBox::information(this,
                                 tr("Server Test Succeeded"),
                                 QRestReply(reply.networkReply()).readText());
    } else if (reply.hasError()) {
        QString errorMsg = tr("Server test failed, Network error: %1 (%2)")
                            .arg(reply.errorString(), QString::number(reply.error()));
        QMessageBox::warning(this, tr("Server Test Failed"), errorMsg);
    } else {
        auto code = HttpStatusCode::Code(reply.httpStatus());
        QString errorMsg = tr("Server test failed, HTTP error: %1 (%2)")
                            .arg(HttpStatusCode::toString(code),
                                 QString::number(reply.httpStatus()));
        QMessageBox::warning(this, tr("Server Test Failed"), errorMsg);
    }
    ui->serverTestButton->setEnabled(true);
}

void LoginDialog::onLoggedIn()
{
    save();
    QMessageBox::information(nullptr, tr("Login Successful"), tr("Login successful"));
    accept();
}

void LoginDialog::onRegistered()
{
    save();
    QMessageBox::information(nullptr, tr("Registration Successful"), tr("Registration successful"));
    handleLogin(); // Auto-login after registration
}

void LoginDialog::onLoggedOut()
{
    accept();
}

void LoginDialog::onApplicationStateChanged(AppState newState)
{
    bool isAuthenticated = (newState == AppState::Main);
    if (isAuthenticated != authenticated) {
        updateAuthState(isAuthenticated);
    }
}

void LoginDialog::load()
{
    if (auto serverUrlOpt = AppSettings::getInstance().getServerUrl()) {
        auto url = *serverUrlOpt;
        ui->uriSchemeComboBox->setCurrentText(url.scheme());
        ui->uriAuthorityLineEdit->setText(url.authority());
    }
    if (auto usernameOpt = AppSettings::getInstance().getUsername()) {
        ui->usernameLineEdit->setText(*usernameOpt);
    }
}

void LoginDialog::save()
{
    AppSettings::getInstance().setUsername(getUserNameAndPassword().first);
    AppSettings::getInstance().setServerUrl(getUrl());
}

QUrl LoginDialog::getUrl() const
{
    return {ui->uriSchemeComboBox->currentText() + ui->uriAuthorityLineEdit->text()};
}

std::pair<QString, QString> LoginDialog::getUserNameAndPassword() const
{
    return {ui->usernameLineEdit->text(), ui->passwordLineEdit->text()};
}

void LoginDialog::on_serverTestButton_clicked()
{
    ui->serverTestButton->setEnabled(false);
    emit serverTestRequested(getUrl());
}

void LoginDialog::on_authActionButton_clicked()
{
    if (authenticated) {
        handleLogout();
        return;
    }

    if (!validateAuthInputs()) {
        return;
    }

    switch (ui->authModeSelectionButtonGroup->checkedId()) {
    case Login:
        handleLogin();
        break;
    case Register:
        handleRegister();
        break;
    }
}
