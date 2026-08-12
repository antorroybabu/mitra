#pragma once

#include "CandidateGenerator.h"
#include "DiversityReranker.h"
#include "FeatureHydrator.h"
#include "FeedSafety.h"
#include "Freshness.h"
#include "TopK.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

struct RecommendationRequest final {
    std::size_t candidate_budget{500};
    std::size_t output_limit{20};
    std::size_t max_per_creator{2};
    double freshness_half_life_seconds{86400.0};
};

struct RecommendationCandidate final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    RankingFeatures features;
    double score{0.0};
};

class RecommendationEngine final {
public:
    static std::vector<RecommendationCandidate> recommend(
        const std::vector<std::vector<Candidate>>& sources,
        const std::vector<FeatureRecord>& records,
        const SafetyContext& safety,
        const RecommendationRequest& request) {
        if (request.candidate_budget == 0 || request.output_limit == 0) return {};

        const auto candidates = merge_candidates(sources, request.candidate_budget);
        std::vector<std::uint64_t> ids;
        ids.reserve(candidates.size());
        for (const auto& candidate : candidates) ids.push_back(candidate.content_id);

        auto ranked = FeatureHydrator::hydrate(ids, records);
        rank(ranked);

        std::vector<SafetyItem> safe_ranked;
        safe_ranked.reserve(ranked.size());
        for (const auto& item : ranked) {
            const auto creator_id = FeatureHydrator::creator_for(item.content_id, records);
            if (creator_id == 0) continue;
            safe_ranked.push_back({item.content_id, creator_id, item.score});
        }

        auto safe = filter_safe(safe_ranked, safety, request.candidate_budget);

        std::vector<RecommendationCandidate> candidates_with_metadata;
        candidates_with_metadata.reserve(safe.size());
        for (const auto& item : safe) {
            candidates_with_metadata.push_back({item.content_id, item.creator_id, {}, item.score});
            for (const auto& record : records) {
                if (record.content_id == item.content_id) {
                    candidates_with_metadata.back().features = record.features;
                    break;
                }
            }
        }

        // Re-rank after safety filtering so the final set has deterministic ordering.
        std::stable_sort(candidates_with_metadata.begin(), candidates_with_metadata.end(),
            [](const auto& a, const auto& b) {
                if (a.score != b.score) return a.score > b.score;
                return a.content_id < b.content_id;
            });

        std::vector<RecommendationCandidate> result;
        result.reserve(request.output_limit);
        std::vector<std::size_t> creator_counts;
        (void)creator_counts;

        // Greedy creator diversity with no hidden mutation of caller-owned data.
        std::vector<std::uint64_t> creators;
        for (const auto& item : candidates_with_metadata) {
            if (result.size() >= request.output_limit) break;
            const auto count = static_cast<std::size_t>(std::count(creators.begin(), creators.end(), item.creator_id));
            if (count >= request.max_per_creator) continue;
            creators.push_back(item.creator_id);
            result.push_back(item);
        }
        return result;
    }
};

} // namespace mitra::recommendation
