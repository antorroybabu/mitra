#pragma once

#include "CandidateGenerator.h"
#include "FeatureHydrator.h"
#include "RecommendationPolicy.h"
#include "Ranker.h"
#include "TopK.h"

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace mitra::recommendation {

class RecommendationPipelineV2 final {
public:
    static std::vector<PolicyItem> run(
        const std::vector<std::vector<Candidate>>& sources,
        const std::vector<FeatureRecord>& features,
        const PolicyContext& policy) {
        const std::size_t candidate_budget = policy.limit * 20 + 1;
        const auto candidates = merge_candidates(sources, candidate_budget);

        auto ranked = FeatureHydrator::hydrate(ids(candidates), features);
        rank(ranked);

        std::vector<ScoredItem<std::uint64_t>> scored;
        scored.reserve(ranked.size());
        for (const auto& item : ranked) {
            scored.push_back({item.content_id, item.score});
        }

        const auto top = top_k(std::move(scored), policy.limit * 4 + 1);
        std::unordered_map<std::uint64_t, std::uint64_t> creator_by_content;
        creator_by_content.reserve(features.size());
        for (const auto& feature : features) {
            creator_by_content.emplace(feature.content_id, feature.creator_id);
        }

        std::vector<PolicyItem> policy_items;
        policy_items.reserve(top.size());
        for (const auto& item : top) {
            const auto it = creator_by_content.find(item.item);
            if (it != creator_by_content.end()) {
                policy_items.push_back({item.item, it->second, item.score});
            }
        }
        return apply_policy(policy_items, policy);
    }

private:
    static std::vector<std::uint64_t> ids(const std::vector<Candidate>& candidates) {
        std::vector<std::uint64_t> result;
        result.reserve(candidates.size());
        for (const auto& candidate : candidates) result.push_back(candidate.content_id);
        return result;
    }
};

} // namespace mitra::recommendation
