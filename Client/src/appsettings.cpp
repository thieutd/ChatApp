#include "appsettings.h"

#include <optional>
#include <QDateTime>
#include <QSettings>
#include <QString>
#include <QUrl>

AppSettings &AppSettings::getInstance()
{
    static AppSettings instance;
    return instance;
}

std::optional<QUrl> AppSettings::getServerUrl() const
{
    std::shared_lock lock(mutex);
    if (settings.contains("server_url")) {
        return settings.value("server_url").toUrl();
    }
    return std::nullopt;
}

void AppSettings::setServerUrl(const QUrl &url)
{
    std::unique_lock lock(mutex);
    settings.setValue("server_url", url);
}

std::optional<QString> AppSettings::getAccessToken() const
{
    std::shared_lock lock(mutex);
    if (settings.contains("access_token")) {
        return settings.value("access_token").toString();
    }
    return std::nullopt;
}

void AppSettings::setAccessToken(const QString &accessToken)
{
    std::unique_lock lock(mutex);
    settings.setValue("access_token", accessToken);
}

std::optional<QString> AppSettings::getRefreshToken() const
{
    std::shared_lock lock(mutex);
    if (settings.contains("refresh_token")) {
        return settings.value("refresh_token").toString();
    }
    return std::nullopt;
}

void AppSettings::setRefreshToken(const QString &refreshToken)
{
    std::unique_lock lock(mutex);
    settings.setValue("refresh_token", refreshToken);
}

std::optional<QDateTime> AppSettings::getAccessTokenExpiry() const
{
    std::shared_lock lock(mutex);
    if (settings.contains("access_token_expiry")) {
        return settings.value("access_token_expiry").toDateTime();
    }
    return std::nullopt;
}

void AppSettings::setRefreshTokenExpiry(const QDateTime &expiry)
{
    std::unique_lock lock(mutex);
    settings.setValue("access_token_expiry", expiry);
}

std::optional<QString> AppSettings::getUsername() const
{
    std::shared_lock lock(mutex);
    if (settings.contains("username")) {
        return settings.value("username").toString();
    }
    return std::nullopt;
}

void AppSettings::setUsername(const QString &username)
{
    std::unique_lock lock(mutex);
    settings.setValue("username", username);
}

std::optional<QString> AppSettings::getPassword() const
{
    std::shared_lock lock(mutex);
    if (settings.contains("password")) {
        return settings.value("password").toString();
    }
    return std::nullopt;
}

void AppSettings::setPassword(const QString &password)
{
    std::unique_lock lock(mutex);
    settings.setValue("password", password);
}

std::optional<quint64> AppSettings::getUserId() const
{
    return getTempValue<quint64>("user_id");
}

void AppSettings::setUserId(quint64 userId)
{
    setTempValue("user_id", userId);
}

void AppSettings::setTempValue(const QString &key, const QVariant &value)
{
    std::unique_lock lock(mutex);
    tempSettings[key] = value;
}

std::optional<QVariant> AppSettings::getTempValue(const QString &key) const
{
    std::shared_lock lock(mutex);
    if (tempSettings.contains(key)) {
        return tempSettings[key];
    }
    return std::nullopt;
}

void AppSettings::setLanguage(QLocale::Language language)
{
    std::unique_lock lock(mutex);
    settings.setValue("language", language);
}

QLocale::Language AppSettings::getLanguage()
{
    {
        std::shared_lock lock(mutex);
        if (settings.contains("language")) {
            return static_cast<QLocale::Language>(settings.value("language").toInt());
        }
    }
    setLanguage(QLocale::Language::English);
    return QLocale::Language::English;
}

void AppSettings::clear()
{
    std::unique_lock lock(mutex);
    settings.clear();
    tempSettings.clear();
}

void AppSettings::commit()
{
    std::unique_lock lock(mutex);
    settings.sync();
}

AppSettings::AppSettings()
    : settings("settings.ini", QSettings::IniFormat)
{}
