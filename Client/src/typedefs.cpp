#include "typedefs.h"

NetworkError::NetworkError(const QNetworkReply &reply)
{
    errorCode = reply.error();
    errorString = reply.errorString();
}

NetworkError::NetworkError(const QRestReply &reply)
    : NetworkError(*reply.networkReply())
{}

QString NetworkError::toString() const
{
    return QString("%1 (code: %2)").arg(errorString, QString::number(errorCode));
}

HttpError::HttpError(QRestReply &&reply)
{
    errorCode = HttpStatusCode::Code(reply.httpStatus());
    errorString = HttpStatusCode::toString(errorCode);

    if (auto jsonOpt = reply.readJson(); jsonOpt) {
        errorData = std::move(*jsonOpt);
    } else {
        errorData = reply.readText();
    }
}

template<class... Ts>
struct overloads : Ts...
{
    using Ts::operator()...;
};

QString HttpError::toString() const
{
    QString code = QString::number(std::underlying_type_t<HttpStatusCode::Code>(errorCode));
    QString errorDataStr = std::visit(overloads{[](const QJsonDocument &doc) {
                                                    return QString(
                                                        doc.toJson(QJsonDocument::Compact));
                                                },
                                                [](const QString &str) { return str; }},
                                      errorData);
    return QString("%1 (code: %2, data: %3)").arg(errorString, code, errorDataStr);
}

QueryError::QueryError(const QSqlError &error)
{
    type = error.type();
    errorString = error.text();
    nativeErrorCode = error.nativeErrorCode();
}

QString QueryError::toString() const
{
    return QString("%1 (code: %2, native code: %3)")
        .arg(errorString, QString::number(type), nativeErrorCode);
}

ResponseDataError::ResponseDataError(QString errStr, QRestReply &&reply)
    : errorString(std::move(errStr))
{
    if (auto jsonOpt = reply.readJson(); jsonOpt) {
        body = std::move(*jsonOpt);
    } else {
        body = reply.readText();
    }
}

QString ResponseDataError::toString() const
{
    QString bodyStr = std::visit(overloads{[](const QJsonDocument &doc) {
                                               return QString(doc.toJson(QJsonDocument::Compact));
                                           },
                                           [](const QString &str) { return str; }},
                                 body);
    return QString("%1 (body: %2)").arg(errorString, bodyStr);
}
