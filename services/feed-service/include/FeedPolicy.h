#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <unordered_set>
#include <vector>

namespace mitra::feed {

struct FeedPolicy final {
    std::size_t page_size{20};
    std::size_t max_page_size{100};
    std::size_t max_items_per_creator{2};
    bool exclude_seen{true};
};

struct FeedRequest final {
    std::uint64_t user_id{0};
    std::optional<std::int64_t> after_created_at_ms;
    std::optional<std::uint64_t> after_item_id;
};

inline bool valid(const FeedRequest& request, const FeedPolicy& policy) noexcept {
    return request.user_id != 0 && policy.page_size > 0 &&
           policy.page_size <= policy.max_page_size;
}

} // namespace mitra::feed
