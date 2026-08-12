#pragma once

#include "CandidateGenerator.h"
#include "FeatureHydrator.h"
#include "FeedSafety.h"
#include "Freshness.h"
#include "Ranker.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
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
        if (request.candidate_budget == 0 || request.output_limit == 0 ||
            request.max_per_creator == 0) return {};

        const auto candidates = merge_candidates(sources, request.candidate_budget);
        std::vector<std::uint64_t> ids;
        ids.reserve(candidates.size());
        for (const auto& candidate : candidates) ids.push_back(candidate.content_id);

        auto hydrated = FeatureHydrator::hydrate(ids, records);
        std::vector<RecommendationCandidate> ranked;
        ranked.reserve(hydrated.size());

        for (const auto& item : hydrated) {
            if (item.creator_id == 0) continue;
            if (safety.blocked_content.contains(item.content_id) ||
                safety.reported_content.contains(item.content_id) ||
                safety.blocked_users.contains(item.creator_id) ||
                safety.muted_creators.contains(item.creator_id)) continue;

            auto features = item.features;
            features.freshness_score = freshness_score(
                item.age_seconds, request.freshness_half_life_seconds);
            ranked.push_back({item.content_id, item.creator_id,
                              features, score_candidate(features)});
        }

        std::stable_sort(ranked.begin(), ranked.end(),
            [](const auto& a, const auto& b) {
                if (a.score != b.score) return a.score > b.score;
                return a.content_id < b.content_id;
            });

        std::unordered_map<std::uint64_t, std::size_t> creator_counts;
        creator_counts.reserve(request.output_limit * 2);

        std::vector<RecommendationCandidate> result;
        result.reserve(request.output_limit);
        for (const auto& item : ranked) {
            if (result.size() >= request.output_limit) break;
            auto& count = creator_counts[item.creator_id];
            if (count >= request.max_per_creator) continue;
            ++count;
            result.push_back(item);
        }
        return result;
    }
};

} // namespace mitra::recommendation
