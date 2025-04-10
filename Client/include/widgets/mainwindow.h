#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "appstate.h"
#include "typedefs.h"

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void onApplicationStateChanged(AppState newState);
    void onMessageReceived(const QString &message, const UserIdType &userId);
    // void onMessageSent(const QUuid &messageId);
    // void onMessageDelivered(const QUuid &messageId);

signals:
    void loginDialogRequested();
    void sendMessageRequested(const QString &message, const QUuid &messageId);

protected:
    void changeEvent(QEvent *event) override;

private:
    void updateAuthState(bool isAuthenticated);
    bool sendMessage();
    void insertMessage(const QString &message, const UserIdType &userId);

    void ChangeLanguage(QLocale::Language language);

private slots:
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionSession_triggered();
    void on_actionExit_triggered();

    void on_sendMessagePushButton_clicked();
    void on_messageLineEdit_returnPressed();

    void on_actionEnglish_triggered();
    void on_actionVietnamese_triggered();

    void on_fileAddButton_clicked();

private:
    std::optional<UserIdType> userId;
    bool authenticated;
    Ui::MainWindow *ui;
    QStandardItemModel model;
    QTranslator translator;
    QTranslator qtTranslator;
};
#endif // MAINWINDOW_HPP
