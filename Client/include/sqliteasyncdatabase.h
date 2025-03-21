#ifndef SQLITEASYNCDATABASE_H
#define SQLITEASYNCDATABASE_H

#include "asyncdatabase.h"


class SqliteAsyncDatabase : public AsyncDatabase
{
    Q_OBJECT
public:
    explicit SqliteAsyncDatabase(QObject *parent = nullptr);
    ~SqliteAsyncDatabase() override;

    QFuture<Result> open(const QString &path) override;
    QFuture<void> close() override;
    QFuture<Result> execute(QString query) override;
    QFuture<Result> execute(std::function<Result()> &&func) override;

private:
    QThreadPool *threadPool;
};

#endif // SQLITEASYNCDATABASE_H
