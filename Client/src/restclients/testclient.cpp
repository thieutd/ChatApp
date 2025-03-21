#include "restclients/testclient.h"

#include <QRestAccessManager>
#include <QRestReply>
#include <QThread>

TestClient::TestClient(QObject *parent)
    : RestClientBase(parent)
{}

TestClient::~TestClient()
{
    qDebug() << QThread::currentThread() << "TestClient::~TestClient()";
}

void TestClient::test(const QNetworkRequest &request)
{
    restAccessManager->get(request, this, [this](QRestReply &reply) {
        emit testFinished(std::move(reply));
    });
}
