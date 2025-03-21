#ifndef AUTHSTRATEGY_H
#define AUTHSTRATEGY_H

#include <QByteArray>
#include <QString>

class QNetworkRequestFactory;

enum class AuthType { Basic, Jwt };

class AuthStrategy
{
public:
    virtual ~AuthStrategy() = default;
    virtual constexpr AuthType type() const = 0;
    virtual void apply(QNetworkRequestFactory &requestFactory) const = 0;
    virtual void unapply(QNetworkRequestFactory &requestFactory) const = 0;
};

class BasicAuthStrategy : public AuthStrategy
{
public:
    BasicAuthStrategy(QString username, QString password);
    constexpr AuthType type() const override;
    void apply(QNetworkRequestFactory &requestFactory) const override;
    void unapply(QNetworkRequestFactory &requestFactory) const override;

private:
    QString username;
    QString password;
};

class JwtAuthStrategy : public AuthStrategy
{
public:
    explicit JwtAuthStrategy(QByteArray token);
    ~JwtAuthStrategy() override;
    constexpr AuthType type() const override { return AuthType::Jwt; }
    void apply(QNetworkRequestFactory &requestFactory) const override;
    void unapply(QNetworkRequestFactory &requestFactory) const override;

private:
    QByteArray token;
};

#endif // AUTHSTRATEGY_H
