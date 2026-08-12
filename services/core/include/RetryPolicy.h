#pragma once
#include <algorithm>
#include <chrono>
#include <cstddef>
namespace mitra::core { struct RetryPolicy { std::size_t max_attempts{3}; std::chrono::milliseconds base_delay{50}; [[nodiscard]] std::chrono::milliseconds delay(std::size_t attempt) const noexcept { const auto n=std::min(attempt,max_attempts); return base_delay * (1ULL<<std::min<std::size_t>(n,10)); } }; }
