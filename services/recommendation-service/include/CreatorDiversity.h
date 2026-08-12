#pragma once

#include "FeatureHydrator.h"

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace mitra::recommendation {

struct CreatorRankedItem final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    double score{0.0};
};

inline std::vector<CreatorRankedItem> diversify_by_creator(
    const std::vector<CreatorRankedItem>& ranked,
    std::size_t limit,
    std::size_t max_per_creator = 2) {
    std::vector<CreatorRankedItem> result;
    if (limit == 0 || max_per_creator == 0) return result;

    std::unordered_map<std::uint64_t, std::size_t> counts;
    counts.reserve(limit * 2);

    for (const auto& item : ranked) {
        if (result.size() >= limit) break;
        auto& count = counts[item.creator_id];
        if (count >= max_per_creator) continue;
        ++count;
        result.push_back(item);
    }
    return result;
}

} // namespace mitra::recommendation
