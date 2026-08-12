#pragma once

#include "CandidateGenerator.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

struct ExplorationPolicy final {
    double exploration_ratio{0.10};
    std::size_t minimum_exploration{2};
    std::size_t maximum_exploration{10};
};

inline std::size_t exploration_budget(std::size_t limit, const ExplorationPolicy& policy) noexcept {
    const auto proportional = static_cast<std::size_t>(limit * std::clamp(policy.exploration_ratio, 0.0, 1.0));
    return std::min(policy.maximum_exploration,
                    std::max(policy.minimum_exploration, proportional));
}

inline std::vector<Candidate> select_exploration(
    const std::vector<Candidate>& candidates,
    std::size_t budget) {
    const auto count = std::min(budget, candidates.size());
    return std::vector<Candidate>(candidates.begin(), candidates.begin() + count);
}

} // namespace mitra::recommendation
