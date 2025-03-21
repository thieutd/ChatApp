#include "restclients/authstrategy.h"

#include <QNetworkRequestFactory>
#include <QThread>

BasicAuthStrategy::BasicAuthStrategy(QString username, QString password)
    : username(std::move(username))
    , password(std::move(password))
{}

constexpr AuthType BasicAuthStrategy::type() const
{
    return AuthType::Basic;
}

void BasicAuthStrategy::apply(QNetworkRequestFactory &requestFactory) const
{
    requestFactory.setUserName(username);
    requestFactory.setPassword(password);
}

void BasicAuthStrategy::unapply(QNetworkRequestFactory &requestFactory) const
{
    requestFactory.clearUserName();
    requestFactory.clearPassword();
}

JwtAuthStrategy::JwtAuthStrategy(QByteArray token)
    : token(std::move(token))
{}

JwtAuthStrategy::~JwtAuthStrategy()
{
    qDebug() << QThread::currentThread() << "JwtAuthStrategy::~JwtAuthStrategy()";
}

void JwtAuthStrategy::apply(QNetworkRequestFactory &requestFactory) const
{
    requestFactory.setBearerToken(token);
}

void JwtAuthStrategy::unapply(QNetworkRequestFactory &requestFactory) const
{
    requestFactory.clearBearerToken();
}
