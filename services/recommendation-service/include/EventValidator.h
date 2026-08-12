#pragma once

#include "EventTypes.h"

#include <cstdint>

namespace mitra::recommendation {

struct ValidationResult final {
    bool valid{false};
    const char* reason{"invalid event"};
};

inline ValidationResult validate(const BehaviorEvent& event, std::int64_t now_ms) noexcept {
    if (event.event_id == 0) return {false, "event_id is required"};
    if (event.user_id == 0) return {false, "user_id is required"};
    if (event.content_id == 0) return {false, "content_id is required"};
    if (event.occurred_at_ms <= 0) return {false, "occurred_at_ms is required"};
    if (now_ms > 0 && event.occurred_at_ms > now_ms + 300000) {
        return {false, "event timestamp is too far in the future"};
    }
    if (now_ms > 0 && event.occurred_at_ms < now_ms - 30LL * 24 * 60 * 60 * 1000) {
        return {false, "event is too old"};
    }
    return {true, "ok"};
}

} // namespace mitra::recommendation
