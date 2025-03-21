#ifndef JWTAUTHCLIENT_H
#define JWTAUTHCLIENT_H

#include "restclientbase.h"
#include "typedefs.h"

class JwtAuthStrategy;

class JwtAuthClient : public RestClientBase
{
    Q_OBJECT
public:
    explicit JwtAuthClient(QObject *parent = nullptr);
    ~JwtAuthClient() override;

    void login(const QString &username, const QString &password);
    void logout();
    void refresh();
    void registerUser(const QString &username, const QString &password);

    bool load();
    void save();

signals:
    void loggedIn();
    void loggedOut();
    void registered();
    void accessTokenChanged(const std::shared_ptr<const JwtAuthStrategy> &authStrategy,
                            const QDateTime &expiry);

    void loginFailed(const AuthRequestError &error);
    void logoutFailed(const AuthRequestError &error);
    void registerFailed(const AuthRequestError &error);
    void refreshFailed(const AuthRequestError &error);

private:
    QString refreshToken;
};

#endif // JWTAUTHCLIENT_H
