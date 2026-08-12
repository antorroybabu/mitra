#pragma once

#include <cstdint>
#include <string_view>

namespace mitra::recommendation {

enum class EventType : std::uint8_t {
    view,
    impression,
    click,
    like,
    bookmark,
    follow,
    share,
    completion,
    skip,
    dislike,
    not_interested,
    mute_topic,
    report
};

struct BehaviorEvent final {
    std::uint64_t event_id{0};
    std::uint64_t user_id{0};
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    EventType type{EventType::impression};
    std::int64_t occurred_at_ms{0};
};

constexpr double event_weight(EventType type) noexcept {
    switch (type) {
        case EventType::completion: return 0.40;
        case EventType::bookmark: return 0.35;
        case EventType::like: return 0.30;
        case EventType::follow: return 0.25;
        case EventType::share: return 0.30;
        case EventType::click: return 0.08;
        case EventType::view: return 0.05;
        case EventType::impression: return 0.0;
        case EventType::skip: return -0.15;
        case EventType::dislike: return -0.35;
        case EventType::not_interested: return -0.60;
        case EventType::mute_topic: return -0.80;
        case EventType::report: return -1.00;
    }
    return 0.0;
}

} // namespace mitra::recommendation
