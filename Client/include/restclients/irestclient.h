#ifndef IRESTCLIENT_H
#define IRESTCLIENT_H

#include <QObject>

class QRestAccessManager;
class QNetworkRequestFactory;
class IRestClientManager;

class IRestClient : public QObject
{
    Q_OBJECT
public:
    IRestClient(QObject *parent = nullptr);

    virtual IRestClient &setBaseUrl(const QUrl &url) = 0;
    virtual IRestClient &setRestAccessManager(QRestAccessManager &restAccessManager) = 0;
    virtual IRestClient &setRequestFactory(QNetworkRequestFactory requestFactory) = 0;
    virtual void initializeFromManager(IRestClientManager &manager, const QString &path) = 0;
};



#endif // IRESTCLIENT_H
