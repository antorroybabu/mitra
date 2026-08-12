#include "../include/RecommendationPipeline.h"

#include <cassert>
#include <vector>

int main() {
    using namespace mitra::recommendation;

    std::vector<std::vector<Candidate>> sources{{
        {1, 0.9}, {2, 0.8}, {1, 0.7}, {3, 0.6}
    }};

    std::vector<FeatureRecord> features{
        {1, 10, {0.9, 0.5, 0.8, 0.7, 1.0, 0.0}},
        {2, 10, {0.8, 0.4, 0.7, 0.6, 0.8, 0.0}},
        {3, 11, {0.7, 0.9, 0.9, 0.8, 0.9, 0.0}}
    };

    PolicyContext policy;
    policy.limit = 2;
    policy.max_per_creator = 1;

    const auto result = RecommendationPipeline::run(sources, features, policy);
    assert(result.size() == 2);
    assert(result[0].creator_id != result[1].creator_id);
    assert(result[0].content_id != result[1].content_id);
    return 0;
}
