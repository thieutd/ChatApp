#ifndef APPRESTCLIENTMANAGER_H
#define APPRESTCLIENTMANAGER_H

#include "appstate.h"

#include <QNetworkRequestFactory>
#include <QObject>

class JwtAuthClient;
class UserClient;
class TestClient;
class RestClientManager;
class QNetworkAccessManager;
class RestClientManager;
class QRestReply;
class MessageClient;

class BackendManager : public QObject
{
    Q_OBJECT
public:
    explicit BackendManager(QObject *parent = nullptr);
    ~BackendManager() override;

    JwtAuthClient *getAuthClient() const;
    UserClient *getUserClient() const;
    TestClient *getTestClient() const;
    MessageClient *getMessageClient() const;

    void initialize();
    void clearData();
    void loadStoredAuth();
    void setUrl(const QUrl &url);
    void setNetworkRequestFactory(QNetworkRequestFactory factory);
    std::shared_ptr<const QRestReply> makeSharedRestReply(const QRestReply &reply);

public slots:
    void onUrlChange(const QUrl &url);
    void onApplicationStateChanged(AppState newState);

signals:
    void initialized();
    void dataCleared();
    void authenticationSucceeded();
    void authenticationCleared();
    void authenticationFailed(const QString &error);
    void crossThreadRestReplySignal(const QObject *receiver,
                                    const char *method,
                                    const std::shared_ptr<const QRestReply> &reply);

private:
    std::optional<QNetworkRequestFactory> requestFactory;
    RestClientManager *restClientManager;
};

#endif // APPRESTCLIENTMANAGER_H
