#pragma once

#include <algorithm>
#include <cmath>

namespace mitra::recommendation {

// Exponential freshness decay. Half-life is expressed in seconds.
inline double freshness_score(double age_seconds, double half_life_seconds) noexcept {
    if (age_seconds <= 0.0) return 1.0;
    if (half_life_seconds <= 0.0) return 0.0;
    return std::exp(-0.6931471805599453 * age_seconds / half_life_seconds);
}

} // namespace mitra::recommendation
