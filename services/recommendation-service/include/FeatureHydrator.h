#pragma once

#include "Ranker.h"

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace mitra::recommendation {

struct FeatureRecord final {
    std::uint64_t content_id{0};
    RankingFeatures features;
};

class FeatureHydrator final {
public:
    static std::vector<RankedCandidate> hydrate(
        const std::vector<std::uint64_t>& candidate_ids,
        const std::vector<FeatureRecord>& records) {
        std::unordered_map<std::uint64_t, RankingFeatures> index;
        index.reserve(records.size());
        for (const auto& record : records) {
            index.emplace(record.content_id, record.features);
        }

        std::vector<RankedCandidate> result;
        result.reserve(candidate_ids.size());
        for (const auto id : candidate_ids) {
            const auto it = index.find(id);
            if (it != index.end()) {
                result.push_back({id, it->second, 0.0});
            }
        }
        return result;
    }
};

} // namespace mitra::recommendation
