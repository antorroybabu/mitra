#pragma once

#include <cstdint>
#include <string>

namespace mitra::behavior {

enum class EventType {
    impression,
    click,
    view,
    completion,
    skip,
    like,
    dislike,
    comment,
    share,
    bookmark,
    follow,
    unfollow,
    search,
    profile_view,
    not_interested,
    mute_creator,
    mute_topic,
    report
};

struct BehaviorEvent final {
    std::string event_id;
    std::uint64_t user_id{0};
    std::uint64_t content_id{0};
    EventType type{EventType::impression};
    std::int64_t occurred_at_ms{0};
    std::uint32_t schema_version{1};
};

} // namespace mitra::behavior
