#ifndef IRESTCLIENTMANAGER_H
#define IRESTCLIENTMANAGER_H

#include <QObject>

class AuthStrategy;
class QRestAccessManager;
class AsyncDatabase;
class QNetworkRequestFactory;

class IRestClientManager : public QObject
{
    Q_OBJECT
public:
    explicit IRestClientManager(QObject *parent = nullptr);
    virtual QRestAccessManager &getRestAccessManager() = 0;
    virtual const QNetworkRequestFactory &getRequestFactory() const = 0;
    virtual const std::shared_ptr<const AuthStrategy> getAuthStrategy() const = 0;
    virtual const AsyncDatabase *getAsyncDatabase() const = 0;
    virtual const std::optional<const std::function<QUrl(const QString &)>> getResolveUrlFunc() const
        = 0;

    // https://forum.qt.io/post/391476
    // Use an alias to prevent MOC from wrongly parsing std::function<QUrl(const QString &)> as std::function<const QUrl(QString &)>
    using ResolveUrlFuncType = const std::function<QUrl(const QString &)>;
signals:
    void authStrategyChanged(const std::shared_ptr<const AuthStrategy> &authStrategy);
    void asyncDatabaseChanged(AsyncDatabase *asyncDatabase);
    void resolveUrlFuncChanged(ResolveUrlFuncType resolveUrlFunc);
};

#endif // IRESTCLIENTMANAGER_H
