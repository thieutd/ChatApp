#ifndef AUTHSTRATEGY_INL
#define AUTHSTRATEGY_INL

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

template<AuthType authType, typename... Args>
std::shared_ptr<AuthStrategy> AuthStrategyFactory::create(Args &&...args)
{
    if constexpr (authType == AuthType::Basic) {
        static_assert(std::is_constructible_v<BasicAuthStrategy, Args...>,
                      "Invalid arguments for BasicAuthStrategy");
        return std::make_shared<BasicAuthStrategy>(std::forward<Args>(args)...);
    } else if constexpr (authType == AuthType::Jwt) {
        static_assert(std::is_constructible_v<JwtAuthStrategy, Args...>,
                      "Invalid arguments for JwtAuthStrategy");
        return std::make_shared<JwtAuthStrategy>(std::forward<Args>(args)...);
    } else {
        static_assert(true, "Unsupported AuthType");
    }
}

#endif // AUTHSTRATEGY_INL
