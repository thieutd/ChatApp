#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "httpstatuscode.h"

#include <QJsonDocument>
#include <QNetworkReply>
#include <QRestReply>
#include <QSqlError>

#include <ClientModels_all_include.model_view.gen.h>

using UserIdType = std::invoke_result_t<decltype(&User::getid), User>;

/*
 * 
 * Declaration
 * 
 */

struct NetworkError;
struct HttpError;
struct ResponseDataError;
struct QueryError;

// Request error variants
using RequestErrorVariant = std::variant<NetworkError, HttpError, ResponseDataError, QueryError>;

// Rest Client defined errors
using AuthRequestError = std::variant<NetworkError, HttpError, ResponseDataError>;
using UserRequestError = RequestErrorVariant;

// Readable string conversion helpers
template<typename T>
struct RequestErrorTraits
{
    static constexpr bool isError = false;
    static constexpr std::string_view name = "Unknown Error";
};

template<typename T>
concept RequestErrorType = RequestErrorTraits<T>::isError;

template<RequestErrorType Error>
constexpr std::string_view errorType()
{
    return RequestErrorTraits<Error>::name;
}

template<RequestErrorType Error>
QString errorToString(const Error &error)
{
    return error.toString();
}

template<RequestErrorType... RequestErrorAlternatives>
QString errorVariantToString(const std::variant<RequestErrorAlternatives...> &error);

/*
 * 
 * Definitions
 * 
 */

// Error types definition
struct NetworkError
{
    QNetworkReply::NetworkError errorCode;
    QString errorString;

    NetworkError(const QNetworkReply &reply);
    explicit NetworkError(const QRestReply &reply);

    QString toString() const;
};

struct HttpError
{
    HttpStatusCode::Code errorCode;
    QString errorString;
    std::variant<QJsonDocument, QString> errorData;

    explicit HttpError(QRestReply &&reply);

    QString toString() const;
};

struct ResponseDataError
{
    QString errorString;

    std::variant<QJsonDocument, QString> body;

    ResponseDataError(QString errStr, QRestReply &&reply);
    template<typename T>
        requires std::is_constructible_v<decltype(body), T>
    ResponseDataError(QString errStr, T &&body)
        : errorString(std::move(errStr))
        , body(std::forward<T>(body))
    {}

    QString toString() const;
};

struct QueryError
{
    QSqlError::ErrorType type;
    QString errorString;
    QString nativeErrorCode;

    QueryError(const QSqlError &error);

    QString toString() const;
};

// Error traits specialization
template<>
struct RequestErrorTraits<NetworkError>
{
    static constexpr bool isError = true;
    static constexpr std::string_view name = "Network Error";
};

template<>
struct RequestErrorTraits<HttpError>
{
    static constexpr bool isError = true;
    static constexpr std::string_view name = "HTTP Error";
};

template<>
struct RequestErrorTraits<ResponseDataError>
{
    static constexpr bool isError = true;
    static constexpr std::string_view name = "Response Data Error";
};

template<>
struct RequestErrorTraits<QueryError>
{
    static constexpr bool isError = true;
    static constexpr std::string_view name = "Query Error";
};

template<RequestErrorType... RequestErrorAlternatives>
QString errorVariantToString(const std::variant<RequestErrorAlternatives...> &errorVariant)
{
    return std::visit(
        [](auto &&error) {
            return QString("%1: %2").arg(errorType<std::remove_cvref_t<decltype(error)>>().data(),
                                         errorToString(error));
        },
        errorVariant);
}

#endif // TYPEDEFS_H
