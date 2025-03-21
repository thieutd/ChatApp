#ifndef RESTCLIENTBASE_H
#define RESTCLIENTBASE_H

#include "irestclient.h"
#include "typedefs.h"

#include <QNetworkRequestFactory>
#include <QPointer>

class QRestAccessManager;

class RestClientBase : public IRestClient
{
    Q_OBJECT
    // IRestClient interface
public:
    IRestClient &setBaseUrl(const QUrl &url) override;
    IRestClient &setRestAccessManager(QRestAccessManager &restAccessManager) override;
    IRestClient &setRequestFactory(QNetworkRequestFactory requestFactory) override;
    void initializeFromManager(IRestClientManager &manager, const QString &path) override;

protected:
    explicit RestClientBase(QObject *parent = nullptr);

protected:
    QNetworkRequestFactory requestFactory;
    QPointer<QRestAccessManager> restAccessManager;
};

template<typename T, typename F>
    requires std::is_base_of_v<IRestClient, T> && std::is_member_function_pointer_v<F>
             && std::invocable<F, T, NetworkError> && std::invocable<F, T, HttpError>
void defaultFailedRequestEmitter(T &client, F &&signal, QRestReply &&reply)
{
    if (reply.hasError()) {
        (client.*signal)(NetworkError(std::move(reply)));
    } else {
        (client.*signal)(HttpError(std::move(reply)));
    }
}

#endif // RESTCLIENTBASE_H
