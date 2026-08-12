#pragma once

#include "EventTypes.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace mitra::recommendation {

class EventStore {
public:
    virtual ~EventStore() = default;
    virtual bool append(const BehaviorEvent& event) = 0;
    virtual std::vector<BehaviorEvent> recent_for_user(
        std::uint64_t user_id, std::size_t limit) = 0;
};

} // namespace mitra::recommendation
