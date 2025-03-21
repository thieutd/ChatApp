#ifndef MESSAGECLIENT_H
#define MESSAGECLIENT_H

#include "restclientbase.h"
#include "typedefs.h"

#include <QWebSocket>

class AuthStrategy;
class AsyncDatabase;

class MessageClient : public RestClientBase
{
    Q_OBJECT
public:
    explicit MessageClient(QObject *parent = nullptr);
    ~MessageClient() override;

    void setAuthStrategy(std::shared_ptr<const AuthStrategy> authStrategy);
    void setAsyncDatabase(AsyncDatabase* asyncDatabase);

    void openConnection();
    void closeConnection();
    void sendMessage(const QString &message, const QUuid &messageId);

signals:
    void messageReceived(const QString &message, const UserIdType userId);

public slots:
    void onAuthStrategyChanged(std::shared_ptr<const AuthStrategy> authStrategy);
    void onAsyncDatabaseChanged(AsyncDatabase *asyncDatabase);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket *webSocket;
    QPointer<AsyncDatabase> asyncDatabase;
    std::shared_ptr<const AuthStrategy> authStrategy;
};

#endif // MESSAGECLIENT_H
