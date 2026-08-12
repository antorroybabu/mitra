#pragma once

#include <cstdint>
#include <optional>

namespace mitra::feed {

struct FeedCursor final {
    std::int64_t created_at_ms{0};
    std::uint64_t item_id{0};
};

struct FeedQuery final {
    std::uint64_t user_id{0};
    std::uint32_t limit{20};
    std::optional<FeedCursor> after;
};

[[nodiscard]] inline bool valid(const FeedQuery& query) noexcept {
    return query.user_id != 0 && query.limit > 0 && query.limit <= 100;
}

} // namespace mitra::feed
