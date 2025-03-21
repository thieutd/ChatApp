#include "restclients/messageclient.h"
#include "asyncdatabase.h"
#include "restclients/authstrategy.h"

#include <QJsonObject>

MessageClient::MessageClient(QObject *parent)
    : RestClientBase(parent)
    , webSocket(new QWebSocket)
{
    webSocket->setParent(this);
    connect(webSocket, &QWebSocket::connected, this, &MessageClient::onConnected);
    connect(webSocket, &QWebSocket::disconnected, this, &MessageClient::onDisconnected);
    connect(webSocket, &QWebSocket::errorOccurred, this, &MessageClient::onError);
}

MessageClient::~MessageClient()
{
    disconnect();
}

void MessageClient::setAuthStrategy(std::shared_ptr<const AuthStrategy> newAuthStrategy)
{
    this->authStrategy = std::move(newAuthStrategy);
    authStrategy->apply(requestFactory);
}

void MessageClient::setAsyncDatabase(AsyncDatabase *asyncDatabase) {
    this->asyncDatabase = asyncDatabase;
}

void MessageClient::openConnection()
{
    if (webSocket->state() == QAbstractSocket::ConnectedState) {
        return;
    }

    auto req = requestFactory.createRequest();
    auto url = requestFactory.baseUrl();
    QString wsScheme = (url.scheme() == "https") ? "wss" : "ws";

    QUrl wsUrl = QString("%1://%2/ws/chat").arg(wsScheme).arg(url.host());
    req.setUrl(wsUrl);

    webSocket->open(req);
}

void MessageClient::closeConnection()
{
    qDebug() << "Closing connection";
}

void MessageClient::sendMessage(const QString &message, const QUuid &messageId)
{
    QJsonObject json{{"type", "message"},
                     {"message", message},
                     {"message_id", messageId.toString()}};
    webSocket->sendTextMessage(QJsonDocument(json).toJson());
}

void MessageClient::onAuthStrategyChanged(std::shared_ptr<const AuthStrategy> authStrategy) {
    this->authStrategy = std::move(authStrategy);
}

void MessageClient::onAsyncDatabaseChanged(AsyncDatabase *asyncDatabase) {
    this->asyncDatabase = asyncDatabase;
}

void MessageClient::onConnected() {
    qDebug() << "Connected";
    connect(webSocket,
            &QWebSocket::textMessageReceived,
            this,
            &MessageClient::onTextMessageReceived);
}

void MessageClient::onDisconnected()
{
    qDebug() << "Disconnected";
}

void MessageClient::onTextMessageReceived(const QString &message)
{
    QJsonObject json = QJsonDocument::fromJson(message.toUtf8()).object();
    if (json["type"] != "message") {
        qDebug() << json;
        return;
    }
    QString msg = json["message"].toString();
    UserIdType id = json["sender_id"].toVariant().value<UserIdType>();
    emit messageReceived(msg, id);
}

void MessageClient::onError(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}
