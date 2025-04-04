#include "widgets/mainwindow.h"
#include "./ui_mainwindow.h"
#include "appsettings.h"
#include "widgets/messagedelegate.h"
#include "ClientModels_all_include.model_view.gen.h"

#include <QStandardItemModel>
#include <QThread>
#include <QTimer>
#include <QUuid>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , authenticated(false)
{
    ChangeLanguage(AppSettings::getInstance().getLanguage());
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

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }

    QMainWindow::changeEvent(event);
}

// void MainWindow::onMessageSent(const QUuid &messageId) {}

// void MainWindow::onMessageDelivered(const QUuid &messageId) {}

void MainWindow::updateAuthState(bool isAuthenticated)
{
    authenticated = isAuthenticated;
    ui->sendMessagePushButton->setEnabled(isAuthenticated);
    ui->fileAddButton->setEnabled(isAuthenticated);
    if (!isAuthenticated) {
        ui->sendMessagePushButton->setToolTip(tr("Please authenticate first"));
        ui->fileAddButton->setToolTip(tr("Please authenticate first"));
    } else {
        ui->sendMessagePushButton->setToolTip(tr("Send message"));
        ui->fileAddButton->setToolTip(tr("Add file"));
    }

    if (isAuthenticated) {
        userId = AppSettings::getInstance().getUserId();
        Q_ASSERT(userId.has_value());
        while (!userId.has_value()) {
            QEventLoop loop;
            QTimer::singleShot(100, &loop, &QEventLoop::quit);
            loop.exec();
            userId = AppSettings::getInstance().getUserId();
        }
        // // MessageDelegate *delegate = new MessageDelegate(*userId, this);
        // model_view::User_model userModel;
        // userModel.qxFetchAll();
        // ui->messageListView->setItemDelegate(userModel);
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

void MainWindow::ChangeLanguage(QLocale::Language language)
{
    switch (language) {
        using enum QLocale::Language;
    case English: {
        qApp->removeTranslator(&translator);
        bool result = translator.load(":/translations/ChatClient_en_US.qm");
        Q_ASSERT(result && "Failed to load translator");
        qApp->installTranslator(&translator);
        AppSettings::getInstance().setLanguage(English);
        break;
    }
    case Vietnamese: {
        qApp->removeTranslator(&translator);
        bool result = translator.load(":/translations/ChatClient_vi_VN.qm");
        Q_ASSERT(result && "Failed to load translator");
        qApp->installTranslator(&translator);
        AppSettings::getInstance().setLanguage(Vietnamese);
        break;
    }
    default: {
        Q_ASSERT(true && "Invalid language");
    }
    }
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
    if (!ui->sendMessagePushButton->isEnabled()) {
        QMessageBox::warning(this, tr("Not Authenticated"), tr("You are not authenticated"));
    }
    sendMessage();
}

void MainWindow::on_messageLineEdit_returnPressed()
{
    sendMessage();
}

void MainWindow::on_actionEnglish_triggered()
{
    ChangeLanguage(QLocale::Language::English);
}

void MainWindow::on_actionVietnamese_triggered()
{
    ChangeLanguage(QLocale::Language::Vietnamese);
}


void MainWindow::on_fileAddButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)");
}

