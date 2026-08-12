#pragma once

#include "EventDeduplicator.h"
#include "EventStore.h"
#include "EventValidator.h"
#include "InterestProfile.h"
#include "EventTypes.h"

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>

namespace mitra::recommendation {

class BehaviorProcessor final {
public:
    BehaviorProcessor(EventStore& store, std::size_t dedup_capacity = 100000)
        : store_(store), deduplicator_(dedup_capacity) {}

    bool process(const BehaviorEvent& event, std::string_view topic, std::int64_t now_ms) {
        const auto validation = validate(event, now_ms);
        if (!validation.valid || !deduplicator_.accept(event.event_id)) return false;
        if (!store_.append(event)) return false;

        if (!topic.empty()) {
            auto& profile = profiles_[event.user_id];
            profile.apply(std::string(topic), event_weight(event.type), now_ms);
        }
        return true;
    }

    InterestProfile* profile_for(std::uint64_t user_id) {
        const auto it = profiles_.find(user_id);
        return it == profiles_.end() ? nullptr : &it->second;
    }

private:
    EventStore& store_;
    EventDeduplicator deduplicator_;
    std::unordered_map<std::uint64_t, InterestProfile> profiles_;
};

} // namespace mitra::recommendation
