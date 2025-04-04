#include "sqliteasyncdatabase.h"

#include <QSqlQuery>
#include <QtConcurrent>

#include <QxOrm.h>

// REFERENCE:https://lnj.gitlab.io/post/async-databases-with-qtsql/

SqliteAsyncDatabase::SqliteAsyncDatabase(QObject *parent)
    : AsyncDatabase(parent)
    , threadPool(new QThreadPool(this))
{
    threadPool->setMaxThreadCount(1);
    threadPool->setExpiryTimeout(-1);
}

SqliteAsyncDatabase::~SqliteAsyncDatabase()
{
    qDebug() << QThread::currentThread() << "SqliteAsyncDatabase::~SqliteAsyncDatabase()";
    SqliteAsyncDatabase::close();
    threadPool->waitForDone();
}

QFuture<SqliteAsyncDatabase::Result> SqliteAsyncDatabase::open(const QString &path)
{
    return QtConcurrent::run(threadPool, [this, path]() -> Result {
        QThread::currentThread()->setObjectName("SqliteAsyncDatabase Thread");
        qDebug() << QThread::currentThread() << "Opening SqliteDB connection";
        Q_ASSERT(qx::QxSqlDatabase::isEmpty());
        auto singleton = qx::QxSqlDatabase::getSingleton();
        qInfo() << "Opening database at" << path;
        singleton->setDriverName("QSQLITE");
        singleton->setDatabaseName(path);
        auto database = singleton->getDatabase();
        if (!database.isValid()) {
            return std::unexpected(database.lastError());
        }
        return {};
    });
}

QFuture<void> SqliteAsyncDatabase::close()
{
    return QtConcurrent::run(threadPool, [this]() {
        qDebug() << QThread::currentThread() << "Closing SqliteDB connection";
        if (!qx::QxSqlDatabase::isEmpty()) {
            qx::QxSqlDatabase::clearAllDatabases();
        }
    });
}

QFuture<SqliteAsyncDatabase::Result> SqliteAsyncDatabase::execute(QString query)
{
    return QtConcurrent::run(threadPool, [query = std::move(query)]() -> Result {
        QSqlQuery q(query);
        if (!q.exec()) {
            return std::unexpected(q.lastError());
        }
        return {};
    });
}

QFuture<AsyncDatabase::Result> SqliteAsyncDatabase::execute(std::function<Result()> &&func)
{
    return QtConcurrent::run(threadPool, std::move(func));
}
