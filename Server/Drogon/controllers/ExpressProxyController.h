#pragma once

#include <drogon/orm/RestfulController.h>

namespace server::api
{
using namespace drogon;

class ExpressProxy : public HttpController<ExpressProxy>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ExpressProxy::Forward, "/rooms", "AuthenticationCoroFilter", Get, Post, Patch, Delete, Options);
    METHOD_LIST_END

    Task<HttpResponsePtr> Forward(HttpRequestPtr req);
};

} // namespace server::api
