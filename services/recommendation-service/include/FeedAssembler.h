#pragma once

#include "FeedSafety.h"
#include "Freshness.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

struct AssemblyItem final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    double base_score{0.0};
    double age_seconds{0.0};
};

inline std::vector<SafetyItem> assemble_feed(
    std::vector<AssemblyItem> candidates,
    const SafetyContext& safety,
    std::size_t limit,
    double freshness_half_life_seconds = 86400.0) {
    for (auto& item : candidates) {
        const double fresh = freshness_score(item.age_seconds, freshness_half_life_seconds);
        item.base_score = 0.85 * item.base_score + 0.15 * fresh;
    }

    std::stable_sort(candidates.begin(), candidates.end(),
        [](const auto& a, const auto& b) {
            if (a.base_score != b.base_score) return a.base_score > b.base_score;
            if (a.age_seconds != b.age_seconds) return a.age_seconds < b.age_seconds;
            return a.content_id < b.content_id;
        });

    std::vector<SafetyItem> ranked;
    ranked.reserve(candidates.size());
    for (const auto& item : candidates) {
        ranked.push_back({item.content_id, item.creator_id, item.base_score});
    }
    return filter_safe(ranked, safety, limit);
}

} // namespace mitra::recommendation
