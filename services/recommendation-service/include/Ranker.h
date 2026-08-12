#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

struct RankingFeatures final {
    double interest_score{0.0};
    double creator_affinity{0.0};
    double quality_score{0.0};
    double engagement_score{0.0};
    double freshness_score{0.0};
    double negative_feedback{0.0};
};

struct RankedCandidate final {
    std::uint64_t content_id{0};
    RankingFeatures features;
    double score{0.0};
};

inline double score_candidate(const RankingFeatures& f) noexcept {
    return 0.30 * f.interest_score +
           0.20 * f.creator_affinity +
           0.15 * f.quality_score +
           0.15 * f.engagement_score +
           0.20 * f.freshness_score -
           0.35 * f.negative_feedback;
}

inline void rank(std::vector<RankedCandidate>& candidates) {
    for (auto& candidate : candidates) {
        candidate.score = score_candidate(candidate.features);
    }
    std::stable_sort(candidates.begin(), candidates.end(),
        [](const auto& a, const auto& b) {
            if (a.score != b.score) return a.score > b.score;
            return a.content_id < b.content_id;
        });
}

} // namespace mitra::recommendation
