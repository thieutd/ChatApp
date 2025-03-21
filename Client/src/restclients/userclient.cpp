#include "restclients/userclient.h"
#include "appsettings.h"
#include "asyncdatabase.h"
#include "restclients/authstrategy.h"
#include "restclients/userclient.h"

#include "ClientModels_all_include.gen.h"
#include <QRestAccessManager>
#include <QRestReply>
#include <QxOrm.h>

UserClient::UserClient(QObject *parent)
    : RestClientBase(parent)
{}

UserClient::~UserClient()
{
    qDebug() << QThread::currentThread() << "UserClient::~UserClient()";
}

void UserClient::setAuthStrategy(std::shared_ptr<const AuthStrategy> newAuthStrategy)
{
    this->authStrategy = std::move(newAuthStrategy);
    authStrategy->apply(requestFactory);
}

void UserClient::setAsyncDatabase(AsyncDatabase* asyncDatabase)
{
    this->asyncDatabase = asyncDatabase;
}

void UserClient::fetchSelf()
{
    auto request = requestFactory.createRequest("/me");
    restAccessManager->get(request, this, [this](QRestReply &reply) {
        if (reply.isHttpStatusSuccess()) {
            auto jsonOpt = reply.readJson();
            Q_ASSERT(jsonOpt.has_value() && "Json is empty");
            if (!jsonOpt.has_value()) {
                emit fetchFailed(ResponseDataError("Json is empty", std::move(reply)));
                return;
            }

            auto json = jsonOpt.value();
            User_ptr user = std::make_shared<User>();
            user->fromJson_(json.object());
            AppSettings::getInstance().setUserId(user->getid());
            user->setlast_synced(QDateTime::currentDateTime());
            user->setcreated_at(QDateTime::fromSecsSinceEpoch(json["created_at"].toInt()));
            UserRole::enum_UserRole role = static_cast<UserRole::enum_UserRole>(
                QMetaEnum::fromType<UserRole::enum_UserRole>().keyToValue(
                    json["role"].toString().toUtf8().constData()));
            user->setrole(role);

            asyncDatabase
                ->execute([user = std::move(user)]() -> AsyncDatabase::Result {
                    qDebug() << QThread::currentThread() << "Saving user to db";
                    auto err = user->qxSave();
                    if (err.isValid()) {
                        return std::unexpected(err);
                    }
                    return {};
                })
                .then(this, [this](const AsyncDatabase::Result &result) {
                    if (result.has_value()) {
                        emit fetched();
                    } else {
                        Q_ASSERT(true
                                 && QString("Persist failed: %1")
                                        .arg(result.error().text())
                                        .toUtf8()
                                        .constData());
                        emit fetchFailed(QueryError(result.error()));
                    }
                });
        } else {
            defaultFailedRequestEmitter(*this, &UserClient::fetchFailed, std::move(reply));
        }
    });
}

void UserClient::onAuthStrategyChanged(std::shared_ptr<const AuthStrategy> authStrategy)
{
    setAuthStrategy(std::move(authStrategy));
}

void UserClient::onAsyncDatabaseChanged(AsyncDatabase *asyncDatabase)
{
    setAsyncDatabase(asyncDatabase);
}
