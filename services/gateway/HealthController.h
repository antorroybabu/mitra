#pragma once

#include <drogon/HttpController.h>

class HealthController : public drogon::HttpController<HealthController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthController::health, "/health", drogon::Get);
    ADD_METHOD_TO(HealthController::ready, "/ready", drogon::Get);
    METHOD_LIST_END

    drogon::HttpResponsePtr health();
    drogon::HttpResponsePtr ready();
};
