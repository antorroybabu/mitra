#pragma once

#include "CandidateGenerator.h"
#include "DiversityReranker.h"
#include "FeatureHydrator.h"
#include "TopK.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

class RecommendationEngine final {
public:
    static std::vector<DiversityItem> recommend(
        const std::vector<std::vector<Candidate>>& sources,
        const std::vector<FeatureRecord>& records,
        std::size_t candidate_budget,
        std::size_t output_limit,
        std::size_t max_per_creator = 2) {
        const auto candidates = merge_candidates(sources, candidate_budget);

        std::vector<std::uint64_t> ids;
        ids.reserve(candidates.size());
        for (const auto& candidate : candidates) ids.push_back(candidate.content_id);

        auto ranked = FeatureHydrator::hydrate(ids, records);
        rank(ranked);

        std::vector<ScoredItem<std::uint64_t>> scored;
        scored.reserve(ranked.size());
        for (const auto& item : ranked) {
            scored.push_back({item.content_id, item.score});
        }
        const auto top = top_k(std::move(scored), output_limit * 4 + 1);

        std::vector<DiversityItem> diverse;
        diverse.reserve(top.size());
        for (const auto& item : top) {
            diverse.push_back({item.item, 0, item.score});
        }
        return diversify(diverse, output_limit, max_per_creator);
    }
};

} // namespace mitra::recommendation
