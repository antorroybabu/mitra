#pragma once

#include "Ranker.h"

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace mitra::recommendation {

struct FeatureRecord final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    RankingFeatures features;
};

class FeatureHydrator final {
public:
    static std::vector<RankedCandidate> hydrate(
        const std::vector<std::uint64_t>& candidate_ids,
        const std::vector<FeatureRecord>& records) {
        std::unordered_map<std::uint64_t, FeatureRecord> index;
        index.reserve(records.size());
        for (const auto& record : records) {
            index.emplace(record.content_id, record);
        }

        std::vector<RankedCandidate> result;
        result.reserve(candidate_ids.size());
        for (const auto id : candidate_ids) {
            const auto it = index.find(id);
            if (it != index.end()) {
                auto ranked = RankedCandidate{id, it->second.features, 0.0};
                result.push_back(ranked);
            }
        }
        return result;
    }

    static std::uint64_t creator_for(
        std::uint64_t content_id,
        const std::vector<FeatureRecord>& records) {
        for (const auto& record : records) {
            if (record.content_id == content_id) return record.creator_id;
        }
        return 0;
    }
};

} // namespace mitra::recommendation
