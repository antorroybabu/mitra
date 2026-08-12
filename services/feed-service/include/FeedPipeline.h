#pragma once

#include "../../recommendation-service/include/CandidateGenerator.h"
#include "../../recommendation-service/include/DiversityReranker.h"
#include "../../recommendation-service/include/Ranker.h"
#include "../../recommendation-service/include/TopK.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::feed {

struct FeedCandidate final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    recommendation::RankingFeatures features;
};

inline std::vector<DiversityItem> build_feed(
    const std::vector<std::vector<recommendation::Candidate>>& sources,
    const std::vector<FeedCandidate>& hydrated,
    std::size_t candidate_limit,
    std::size_t top_k) {
    const auto candidates = recommendation::merge_candidates(sources, candidate_limit);

    std::vector<recommendation::RankedCandidate> ranked;
    ranked.reserve(candidates.size());
    for (const auto& candidate : candidates) {
        const auto it = std::find_if(hydrated.begin(), hydrated.end(),
            [&](const auto& item) { return item.content_id == candidate.content_id; });
        if (it == hydrated.end()) continue;
        ranked.push_back({it->content_id, it->features, 0.0});
    }

    recommendation::rank(ranked);

    std::vector<DiversityItem> diverse;
    diverse.reserve(std::min(top_k, ranked.size()));
    for (const auto& item : ranked) {
        const auto it = std::find_if(hydrated.begin(), hydrated.end(),
            [&](const auto& candidate) { return candidate.content_id == item.content_id; });
        if (it != hydrated.end()) {
            diverse.push_back({item.content_id, it->creator_id, item.score});
        }
    }

    return recommendation::diversify(diverse, top_k);
}

} // namespace mitra::feed
