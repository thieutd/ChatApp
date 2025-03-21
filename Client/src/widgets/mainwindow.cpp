#include "widgets/mainwindow.h"
#include "./ui_mainwindow.h"
#include "appsettings.h"
#include "widgets/messagedelegate.h"

#include <QStandardItemModel>
#include <QThread>
#include <QTimer>
#include <QUuid>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authenticated(false)
{
    ui->setupUi(this);
    ui->messageListView->setModel(&model);
    updateAuthState(authenticated);
}

MainWindow::~MainWindow()
{
    qDebug() << QThread::currentThread() << "MainWindow::~MainWindow()";
    delete ui;
}

void MainWindow::onApplicationStateChanged(AppState newState)
{
    if (newState == AppState::AuthCheck) {
        statusBar()->showMessage(tr("Checking authentication..."));
    } else if (newState == AppState::Login) {
        statusBar()->showMessage(tr("Logging in..."));
    } else if (newState == AppState::Main) {
        statusBar()->showMessage(tr("Logged in"), 3000);
    } else if (newState == AppState::LoggedOut) {
        QApplication::setQuitOnLastWindowClosed(false);
    } else if (newState == AppState::Final) {
        statusBar()->showMessage(tr("Exiting..."));
    } else {
        statusBar()->clearMessage();
    }

    if (bool isAuthenticated = (newState == AppState::Main); isAuthenticated != authenticated) {
        updateAuthState(isAuthenticated);
    }
}

void MainWindow::onMessageReceived(const QString &message, const UserIdType &userId)
{
    insertMessage(message, userId);
}

// void MainWindow::onMessageSent(const QUuid &messageId) {}

// void MainWindow::onMessageDelivered(const QUuid &messageId) {}

void MainWindow::updateAuthState(bool isAuthenticated)
{
    authenticated = isAuthenticated;
    ui->sendMessagePushButton->setEnabled(isAuthenticated);

    if (isAuthenticated) {
        userId = AppSettings::getInstance().getUserId();
        Q_ASSERT(userId.has_value());
        while (!userId.has_value()) {
            QEventLoop loop;
            QTimer::singleShot(100, &loop, &QEventLoop::quit);
            loop.exec();
            userId = AppSettings::getInstance().getUserId();
        }
        MessageDelegate *delegate = new MessageDelegate(*userId, this);
        ui->messageListView->setItemDelegate(delegate);
    }
}

bool MainWindow::sendMessage()
{
    if (!userId.has_value()) {
        return false;
    }

    QString message = ui->messageLineEdit->text();
    if (message.isEmpty()) {
        return false;
    }
    ui->messageLineEdit->clear();

    QUuid messageId = QUuid::createUuid();
    emit sendMessageRequested(message, messageId);

    insertMessage(message, *userId);

    return true;
}

void MainWindow::insertMessage(const QString &message, const UserIdType &userId)
{
    QStandardItem *item = new QStandardItem(message);
    item->setData(userId, Qt::UserRole);
    model.appendRow(item);
}

void MainWindow::on_actionAbout_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionSession_triggered()
{
    emit loginDialogRequested();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_sendMessagePushButton_clicked()
{
    sendMessage();
}

void MainWindow::on_messageLineEdit_returnPressed()
{
    sendMessage();
}
