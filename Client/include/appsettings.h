#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>
#include <QLocale>
#include <shared_mutex>

class AppSettings
{
public:
    static AppSettings &getInstance();

    std::optional<QUrl> getServerUrl() const;
    void setServerUrl(const QUrl &url);

    std::optional<QString> getAccessToken() const;
    void setAccessToken(const QString &accessToken);

    std::optional<QString> getRefreshToken() const;
    void setRefreshToken(const QString &refreshToken);

    std::optional<QDateTime> getAccessTokenExpiry() const;
    void setRefreshTokenExpiry(const QDateTime &expiry);

    std::optional<QString> getUsername() const;
    void setUsername(const QString &username);

    std::optional<QString> getPassword() const;
    void setPassword(const QString &password);

    std::optional<quint64> getUserId() const;
    void setUserId(quint64 userId);

    void setTempValue(const QString &key, const QVariant &value);
    std::optional<QVariant> getTempValue(const QString &key) const;
    template<typename T>
    std::optional<T> getTempValue(const QString &key) const;

    void setLanguage(QLocale::Language language);
    QLocale::Language getLanguage();

    void clear();
    void commit();

private:
    AppSettings();
    ~AppSettings() = default;
    AppSettings(const AppSettings &) = delete;
    AppSettings &operator=(const AppSettings &) = delete;
    AppSettings(AppSettings &&) = delete;
    AppSettings &operator=(AppSettings &&) = delete;

private:
    QSettings settings;
    QVariantMap tempSettings;
    mutable std::shared_mutex mutex;
};

template<typename T>
inline std::optional<T> AppSettings::getTempValue(const QString &key) const
{
    if (auto valueOpt = getTempValue(key); valueOpt.has_value() && valueOpt->canConvert<T>()) {
        return valueOpt->value<T>();
    }
    return std::nullopt;
}

#endif // APPSETTINGS_H
