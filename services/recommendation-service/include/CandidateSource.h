#pragma once

#include "CandidateGenerator.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

class CandidateSource {
public:
    virtual ~CandidateSource() = default;
    virtual std::vector<Candidate> fetch(std::uint64_t user_id, std::size_t limit) = 0;
};

} // namespace mitra::recommendation
