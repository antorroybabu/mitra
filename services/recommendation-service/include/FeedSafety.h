#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include <vector>

namespace mitra::recommendation {

struct SafetyContext final {
    std::unordered_set<std::uint64_t> blocked_users;
    std::unordered_set<std::uint64_t> blocked_content;
    std::unordered_set<std::uint64_t> reported_content;
    std::unordered_set<std::uint64_t> muted_creators;
};

struct SafetyItem final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    double score{0.0};
};

inline std::vector<SafetyItem> filter_safe(
    const std::vector<SafetyItem>& ranked,
    const SafetyContext& context,
    std::size_t limit) {
    std::vector<SafetyItem> result;
    result.reserve(limit);
    for (const auto& item : ranked) {
        if (result.size() >= limit) break;
        if (context.blocked_content.contains(item.content_id)) continue;
        if (context.reported_content.contains(item.content_id)) continue;
        if (context.blocked_users.contains(item.creator_id)) continue;
        if (context.muted_creators.contains(item.creator_id)) continue;
        result.push_back(item);
    }
    return result;
}

} // namespace mitra::recommendation
