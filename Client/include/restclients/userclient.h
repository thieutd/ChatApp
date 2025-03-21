#ifndef USERCLIENT_H
#define USERCLIENT_H

#include "restclientbase.h"
#include "typedefs.h"

class AuthStrategy;
class AsyncDatabase;

class UserClient : public RestClientBase
{
    Q_OBJECT
public:
    explicit UserClient(QObject *parent = nullptr);
    ~UserClient() override;

    void setAuthStrategy(std::shared_ptr<const AuthStrategy> authStrategy);
    void setAsyncDatabase(AsyncDatabase* asyncDatabase);

    void fetchSelf();

public slots:
    void onAuthStrategyChanged(std::shared_ptr<const AuthStrategy> authStrategy);
    void onAsyncDatabaseChanged(AsyncDatabase *asyncDatabase);

signals:
    void fetched();
    void fetchFailed(const UserRequestError &error);

private:
    QPointer<AsyncDatabase> asyncDatabase;
    std::shared_ptr<const AuthStrategy> authStrategy;
};

#endif // USERCLIENT_H
