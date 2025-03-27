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

class AuthStrategyFactory
{
public:
    template<AuthType authType, typename... Args>
    static std::shared_ptr<AuthStrategy> create(Args &&...args);
};

#include "authstrategy.inl"

#endif // AUTHSTRATEGY_H
