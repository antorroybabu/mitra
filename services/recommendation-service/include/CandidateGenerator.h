#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include <utility>
#include <vector>

namespace mitra::recommendation {

struct Candidate final {
    std::uint64_t content_id{0};
    double source_score{0.0};
};

// Merges bounded candidate lists and removes duplicate content IDs.
// The caller controls source-specific budgets before invoking this function.
inline std::vector<Candidate> merge_candidates(
    const std::vector<std::vector<Candidate>>& sources,
    std::size_t max_candidates) {
    std::vector<Candidate> result;
    result.reserve(std::min(max_candidates, std::size_t{1024}));
    std::unordered_set<std::uint64_t> seen;

    for (const auto& source : sources) {
        for (const auto& candidate : source) {
            if (result.size() >= max_candidates) {
                return result;
            }
            if (seen.insert(candidate.content_id).second) {
                result.push_back(candidate);
            }
        }
    }
    return result;
}

} // namespace mitra::recommendation
