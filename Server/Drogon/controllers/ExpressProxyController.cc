#include "ExpressProxyController.h"
#include "models/User.h"
#include "utilities/HttpResponseUtil.h"

using namespace server::api;

Task<HttpResponsePtr> ExpressProxy::Forward(HttpRequestPtr req)
{
    static const auto express_config = app().getCustomConfig()["express"];
    static const auto host = express_config.get("host", "localhost").asString();
    static const auto api_key = express_config.get("api_key", "").asString();

    const auto client = HttpClient::newHttpClient(host);
    const auto new_req = HttpRequest::newHttpRequest();
    new_req->setPath(req->path());
    new_req->setMethod(req->method());
    new_req->setBody(std::string{req->body()});
    for (const auto &[key, value] : req->headers())
    {
        new_req->addHeader(key, value);
    }

    const auto id = req->getAttributes()->get<drogon_model::postgres::User::PrimaryKeyType>("id");
    const auto role = req->getAttributes()->get<std::string>("role");
    new_req->addHeader("X-User-Id", std::to_string(id));
    new_req->addHeader("X-User-Role", role);
    new_req->addHeader("X-Api-Key", api_key);

    try
    {
        auto result = co_await client->sendRequestCoro(std::move(req));
        auto response = HttpResponse::newHttpResponse();
        response->setBody(std::string{result->body()});

        co_return response;
    }
    catch (const HttpException &e)
    {
        LOG_ERROR << e.what();
        co_return utilities::NewJsonErrorResponse<HttpErrorCode::kInternalServerError>();
    }

}