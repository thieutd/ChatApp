#ifndef HTTPSTATUSCODE_H
#define HTTPSTATUSCODE_H

#include <QLatin1StringView>
#include <QMetaEnum>

namespace HttpStatusCode {
Q_NAMESPACE

// Src/qthttpserver/src/httpserver/qhttpserverresponder.h
enum Code {
    // 1xx: Informational
    Continue = 100,
    SwitchingProtocols,
    Processing,

    // 2xx: Success
    Ok = 200,
    Created,
    Accepted,
    NonAuthoritativeInformation,
    NoContent,
    ResetContent,
    PartialContent,
    MultiStatus,
    AlreadyReported,
    IMUsed = 226,

    // 3xx: Redirection
    MultipleChoices = 300,
    MovedPermanently,
    Found,
    SeeOther,
    NotModified,
    UseProxy,
    // 306: not used, was proposed as "Switch Proxy" but never standardized
    TemporaryRedirect = 307,
    PermanentRedirect,

    // 4xx: Client Error
    BadRequest = 400,
    Unauthorized,
    PaymentRequired,
    Forbidden,
    NotFound,
    MethodNotAllowed,
    NotAcceptable,
    ProxyAuthenticationRequired,
    RequestTimeout,
    Conflict,
    Gone,
    LengthRequired,
    PreconditionFailed,
    PayloadTooLarge,
    UriTooLong,
    UnsupportedMediaType,
    RequestRangeNotSatisfiable,
    ExpectationFailed,
    ImATeapot,
    MisdirectedRequest = 421,
    UnprocessableEntity,
    Locked,
    FailedDependency,
    UpgradeRequired = 426,
    PreconditionRequired = 428,
    TooManyRequests,
    RequestHeaderFieldsTooLarge = 431,
    UnavailableForLegalReasons = 451,

    // 5xx: Server Error
    InternalServerError = 500,
    NotImplemented,
    BadGateway,
    ServiceUnavailable,
    GatewayTimeout,
    HttpVersionNotSupported,
    VariantAlsoNegotiates,
    InsufficientStorage,
    LoopDetected,
    NotExtended = 510,
    NetworkAuthenticationRequired,
    NetworkConnectTimeoutError = 599,
};
Q_ENUM_NS(Code)

// Src/qthttpserver/src/httpserver/qhttpserverhttp1protocolhandler.cpp
const QLatin1StringView toString(Code code);

} // namespace HttpStatusCode

#endif // HTTPSTATUSCODE_H
