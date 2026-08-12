#pragma once

#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include <vector>

namespace mitra::recommendation {

struct DiversityItem final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    double score{0.0};
};

// Greedy bounded reranking: limits repeated creators while preserving score
// order as much as possible. This is intentionally deterministic.
inline std::vector<DiversityItem> diversify(
    const std::vector<DiversityItem>& ranked,
    std::size_t limit,
    std::size_t max_items_per_creator = 2) {
    std::vector<DiversityItem> result;
    if (limit == 0 || max_items_per_creator == 0) return result;
    result.reserve(limit);

    struct CreatorCountHash {
        std::size_t operator()(std::uint64_t value) const noexcept {
            value ^= value >> 30;
            value *= 0xbf58476d1ce4e5b9ULL;
            value ^= value >> 27;
            value *= 0x94d049bb133111ebULL;
            return static_cast<std::size_t>(value ^ (value >> 31));
        }
    };

    std::unordered_set<std::uint64_t, CreatorCountHash> seen_creators;
    for (const auto& item : ranked) {
        if (result.size() >= limit) break;
        if (seen_creators.count(item.creator_id) >= max_items_per_creator) continue;
        seen_creators.insert(item.creator_id);
        result.push_back(item);
    }
    return result;
}

} // namespace mitra::recommendation
