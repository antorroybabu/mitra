#pragma once

#include "CandidateGenerator.h"
#include "FeatureHydrator.h"
#include "RecommendationPolicy.h"
#include "Ranker.h"
#include "TopK.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

class RecommendationPipeline final {
public:
    static std::vector<PolicyItem> run(
        const std::vector<std::vector<Candidate>>& sources,
        const std::vector<FeatureRecord>& features,
        const PolicyContext& policy) {
        const auto candidates = merge_candidates(sources, policy.limit * 20 + 1);
        std::vector<std::uint64_t> ids;
        ids.reserve(candidates.size());
        for (const auto& candidate : candidates) ids.push_back(candidate.content_id);

        auto ranked = FeatureHydrator::hydrate(ids, features);
        rank(ranked);

        std::vector<ScoredItem<std::uint64_t>> scored;
        scored.reserve(ranked.size());
        for (const auto& item : ranked) {
            scored.push_back({item.content_id, item.score});
        }
        const auto top = top_k(std::move(scored), policy.limit * 4 + 1);

        std::vector<PolicyItem> policy_items;
        policy_items.reserve(top.size());
        for (const auto& item : top) {
            std::uint64_t creator = 0;
            for (const auto& record : features) {
                if (record.content_id == item.item) {
                    creator = record.creator_id;
                    break;
                }
            }
            policy_items.push_back({item.item, creator, item.score});
        }
        return apply_policy(policy_items, policy);
    }
};

} // namespace mitra::recommendation
