#ifndef ASYNCDATABASE_H
#define ASYNCDATABASE_H

#include <QFuture>
#include <QObject>
#include <QSqlError>
#include <expected>

class QSqlQuery;

class AsyncDatabase : public QObject
{
    Q_OBJECT
public:
    using Result = std::expected<void, QSqlError>;
    explicit AsyncDatabase(QObject *parent = nullptr);

    virtual QFuture<Result> open(const QString &path) = 0;
    virtual QFuture<void> close() = 0;
    virtual QFuture<Result> execute(QString query) = 0;
    virtual QFuture<Result> execute(std::function<Result()> &&func) = 0;
};

#endif // ASYNCDATABASE_H
