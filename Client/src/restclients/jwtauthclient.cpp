#include "restclients/jwtauthclient.h"
#include "appsettings.h"
#include "restclients/authstrategy.h"

#include <QJsonObject>
#include <QRestAccessManager>
#include <QThread>

JwtAuthClient::JwtAuthClient(QObject *parent)
    : RestClientBase(parent)
{}

JwtAuthClient::~JwtAuthClient()
{
    qDebug() << QThread::currentThread() << "JwtAuthClient::~JwtAuthClient()";
}

void JwtAuthClient::login(const QString &username, const QString &password)
{
    auto request = requestFactory.createRequest("login");
    QJsonObject json{{"username", username}, {"password", password}};

    restAccessManager->post(request, QJsonDocument(json), this, [this](QRestReply &reply) {
        if (reply.isHttpStatusSuccess()) {
            auto jsonOpt = reply.readJson();
            Q_ASSERT(jsonOpt.has_value() && "Json is empty");
            auto json = jsonOpt.value();

            // Extract tokens from response
            auto accessToken = json["access_token"].toString().toUtf8();
            auto expiry = json["access_expiration"].toInteger();
            refreshToken = json["refresh_token"].toString();

            emit loggedIn();
            emit accessTokenChanged(AuthStrategyFactory::create<AuthType::Jwt>(
                                        std::move(accessToken)),
                                    QDateTime::fromSecsSinceEpoch(expiry));
        } else {
            defaultFailedRequestEmitter(*this, &JwtAuthClient::loginFailed, std::move(reply));
        }
    });
}

void JwtAuthClient::logout()
{
    auto request = requestFactory.createRequest("logout");
    QJsonObject json{{"refresh_token", refreshToken}};

    restAccessManager->post(request, QJsonDocument(json), this, [this](QRestReply &reply) {
        if (reply.isHttpStatusSuccess()) {
            refreshToken.clear();
            emit loggedOut();
        } else {
            defaultFailedRequestEmitter(*this, &JwtAuthClient::logoutFailed, std::move(reply));
        }
    });
}

void JwtAuthClient::refresh()
{
    auto request = requestFactory.createRequest("refresh");
    QJsonObject json{{"refresh_token", refreshToken}};

    restAccessManager->post(request, QJsonDocument(json), this, [this](QRestReply &reply) {
        if (reply.isHttpStatusSuccess()) {
            auto jsonOpt = reply.readJson();
            Q_ASSERT(jsonOpt.has_value() && "Json is empty");
            auto json = jsonOpt.value();
            
            // Create new auth strategy with refreshed token
            auto accessToken = json["access_token"].toString().toUtf8();
            auto expiry = json["access_expiration"].toInteger();
            emit accessTokenChanged(AuthStrategyFactory::create<AuthType::Jwt>(
                                        std::move(accessToken)),
                                    QDateTime::fromSecsSinceEpoch(expiry));
        } else {
            defaultFailedRequestEmitter(*this, &JwtAuthClient::refreshFailed, std::move(reply));
        }
    });
}

void JwtAuthClient::registerUser(const QString &username, const QString &password)
{
    auto request = requestFactory.createRequest("register");
    QJsonObject json{{"username", username}, {"password", password}};

    restAccessManager->post(request, QJsonDocument(json), this, [this](QRestReply &reply) {
        if (reply.isHttpStatusSuccess()) {
            emit registered();
        } else {
            defaultFailedRequestEmitter(*this, &JwtAuthClient::registerFailed, std::move(reply));
        }
    });
}

bool JwtAuthClient::load()
{
    if (auto refreshTokenOpt = AppSettings::getInstance().getRefreshToken();
        refreshTokenOpt.has_value()) {
        refreshToken = refreshTokenOpt.value();
        return true;
    }
    return false;
}

void JwtAuthClient::save()
{
    AppSettings::getInstance().setRefreshToken(refreshToken);
}
