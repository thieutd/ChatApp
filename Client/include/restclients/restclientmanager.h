#ifndef RESTCLIENTMANAGER_H
#define RESTCLIENTMANAGER_H

#include "irestclientmanager.h"

#include <QNetworkRequestFactory>
#include <QPointer>
#include <QRestAccessManager>

class RestClientBase;

class RestClientManager : public IRestClientManager
{
    Q_OBJECT
public:
    explicit RestClientManager(QObject *parent = nullptr);
    ~RestClientManager() override;

    RestClientManager &addClient(RestClientBase *client, QString path);
    RestClientManager &setUrl(const QUrl &url, const bool isSubdomain = false);
    RestClientManager &setAuthStrategy(std::shared_ptr<const AuthStrategy> authStrategy);
    RestClientManager &setAsyncDatabase(AsyncDatabase *asyncDatabase);
    RestClientManager &setAutoDeleteReplies(const bool autoDelete);
    RestClientManager &setRequestFactory(QNetworkRequestFactory requestFactory);

    bool autoDeleteReplies() const;
    RestClientBase *getClient(const QString &path) const;
    template<typename T>
        requires std::is_base_of_v<RestClientBase, T>
    T *getClient(const QString &path) const;

    // IRestClientManager interface
public:
    QRestAccessManager &getRestAccessManager() override;
    const QNetworkRequestFactory &getRequestFactory() const override;
    const std::shared_ptr<const AuthStrategy> getAuthStrategy() const override;
    const AsyncDatabase *getAsyncDatabase() const override;
    const std::optional<const std::function<QUrl(const QString &)>> getResolveUrlFunc()
        const override;

private:
    QNetworkAccessManager *networkAccessManager;
    QRestAccessManager *restAccessManager;
    std::unordered_map<QString, RestClientBase *> clients;
    std::shared_ptr<const AuthStrategy> authStrategy;
    AsyncDatabase *asyncDatabase;
    QNetworkRequestFactory requestFactory;
    std::function<QUrl(const QString &)> resolveUrlFunc;
};

template<class T>
    requires std::is_base_of_v<RestClientBase, T>
inline T *RestClientManager::getClient(const QString &path) const
{
    if (clients.contains(path)) {
        return qobject_cast<T *>(clients.at(path));
    }
    return nullptr;
}

#endif // RESTCLIENTMANAGER_H
