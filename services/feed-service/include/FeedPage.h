#pragma once

#include "Cursor.h"

#include <cstdint>
#include <optional>
#include <vector>

namespace mitra::feed {

struct FeedItem final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    std::int64_t created_at_ms{0};
};

struct FeedPage final {
    std::vector<FeedItem> items;
    std::optional<Cursor> next_cursor;
    bool has_more{false};
};

} // namespace mitra::feed
