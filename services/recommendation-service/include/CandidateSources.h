#pragma once

#include "CandidateGenerator.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

struct SourceBudget final {
    std::size_t following{100};
    std::size_t interest{100};
    std::size_t trending{50};
    std::size_t fresh{50};
    std::size_t exploration{25};
};

class CandidateSources final {
public:
    static std::vector<Candidate> collect(
        const std::vector<Candidate>& following,
        const std::vector<Candidate>& interest,
        const std::vector<Candidate>& trending,
        const std::vector<Candidate>& fresh,
        const std::vector<Candidate>& exploration,
        const SourceBudget& budget,
        std::size_t total_limit) {
        return merge_candidates({take(following, budget.following),
                                 take(interest, budget.interest),
                                 take(trending, budget.trending),
                                 take(fresh, budget.fresh),
                                 take(exploration, budget.exploration)}, total_limit);
    }

private:
    static std::vector<Candidate> take(const std::vector<Candidate>& input, std::size_t limit) {
        const auto count = std::min(limit, input.size());
        return std::vector<Candidate>(input.begin(), input.begin() + count);
    }
};

} // namespace mitra::recommendation
