#include "HealthController.h"

#include <drogon/HttpResponse.h>

namespace {
drogon::HttpResponsePtr jsonStatus(const char* status) {
    Json::Value body;
    body["status"] = status;
    return drogon::HttpResponse::newHttpJsonResponse(body);
}
} // namespace

drogon::HttpResponsePtr HealthController::health() {
    return jsonStatus("ok");
}

drogon::HttpResponsePtr HealthController::ready() {
    // Phase 1 readiness is process-level. Database/cache dependency checks
    // will be added before production deployment.
    return jsonStatus("ready");
}
