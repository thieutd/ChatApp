#ifndef TESTCLIENT_H
#define TESTCLIENT_H

#include "restclientbase.h"

class TestClient : public RestClientBase
{
    Q_OBJECT
public:
    explicit TestClient(QObject *parent = nullptr);
    ~TestClient() override;

    void test(const QNetworkRequest &request);

signals:
    void testFinished(const QRestReply &reply);
};

#endif // TESTCLIENT_H
