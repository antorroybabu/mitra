#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include <vector>

namespace mitra::recommendation {

struct PolicyContext final {
    std::unordered_set<std::uint64_t> seen_content;
    std::unordered_set<std::uint64_t> blocked_creators;
    std::unordered_set<std::uint64_t> muted_creators;
    std::unordered_set<std::uint64_t> reported_content;
    std::size_t max_per_creator{2};
    std::size_t limit{20};
};

struct PolicyItem final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    double score{0.0};
};

inline std::vector<PolicyItem> apply_policy(
    const std::vector<PolicyItem>& ranked, const PolicyContext& ctx) {
    std::vector<PolicyItem> out;
    out.reserve(std::min(ctx.limit, ranked.size()));
    std::unordered_set<std::uint64_t> creators;
    creators.reserve(ctx.limit * 2 + 1);

    for (const auto& item : ranked) {
        if (out.size() >= ctx.limit) break;
        if (ctx.seen_content.contains(item.content_id)) continue;
        if (ctx.reported_content.contains(item.content_id)) continue;
        if (ctx.blocked_creators.contains(item.creator_id)) continue;
        if (ctx.muted_creators.contains(item.creator_id)) continue;
        if (creators.count(item.creator_id) >= ctx.max_per_creator) continue;
        creators.insert(item.creator_id);
        out.push_back(item);
    }
    return out;
}

} // namespace mitra::recommendation
