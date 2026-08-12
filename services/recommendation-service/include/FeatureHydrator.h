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
    double age_seconds{0.0};
};

struct HydratedFeature final {
    std::uint64_t content_id{0};
    std::uint64_t creator_id{0};
    RankingFeatures features;
    double age_seconds{0.0};
};

class FeatureHydrator final {
public:
    static std::vector<HydratedFeature> hydrate(
        const std::vector<std::uint64_t>& candidate_ids,
        const std::vector<FeatureRecord>& records) {
        std::unordered_map<std::uint64_t, const FeatureRecord*> index;
        index.reserve(records.size());
        for (const auto& record : records) index.emplace(record.content_id, &record);

        std::vector<HydratedFeature> result;
        result.reserve(candidate_ids.size());
        for (const auto id : candidate_ids) {
            const auto it = index.find(id);
            if (it == index.end()) continue;
            const auto& record = *it->second;
            result.push_back({record.content_id, record.creator_id,
                              record.features, record.age_seconds});
        }
        return result;
    }
};

} // namespace mitra::recommendation
