#include "restclients/restclientbase.h"
#include "restclients/irestclientmanager.h"
#include <QRestAccessManager>

IRestClient &RestClientBase::setBaseUrl(const QUrl &url)
{
    this->requestFactory.setBaseUrl(url);
    return *this;
}

IRestClient &RestClientBase::setRestAccessManager(QRestAccessManager &restAccessManager)
{
    this->restAccessManager = &restAccessManager;
    return *this;
}

IRestClient &RestClientBase::setRequestFactory(QNetworkRequestFactory requestFactory)
{
    this->requestFactory = std::move(requestFactory);
    return *this;
}

void RestClientBase::initializeFromManager(IRestClientManager &manager, const QString &path)
{
    restAccessManager = &manager.getRestAccessManager();
    requestFactory = manager.getRequestFactory();
    if (const auto urlFuncOpt = manager.getResolveUrlFunc()) {
        requestFactory.setBaseUrl((*urlFuncOpt)(path));
    }
}

RestClientBase::RestClientBase(QObject *parent)
    : IRestClient(parent)
{}
