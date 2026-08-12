#include "../include/BehaviorProcessor.h"

#include <cassert>
#include <unordered_map>

using namespace mitra::recommendation;

class MemoryEventStore final : public EventStore {
public:
    bool append(const BehaviorEvent& event) override {
        if (events.count(event.event_id)) return false;
        events.emplace(event.event_id, event);
        return true;
    }

    std::vector<BehaviorEvent> recent_for_user(std::uint64_t user_id, std::size_t limit) override {
        std::vector<BehaviorEvent> result;
        for (const auto& [_, event] : events) {
            if (event.user_id == user_id && result.size() < limit) result.push_back(event);
        }
        return result;
    }

    std::unordered_map<std::uint64_t, BehaviorEvent> events;
};

int main() {
    MemoryEventStore store;
    BehaviorProcessor processor(store);
    const std::int64_t now = 1'700'000'000'000;

    BehaviorEvent like{1, 42, 100, 7, EventType::like, now};
    assert(processor.process(like, "technology", now));
    assert(!processor.process(like, "technology", now));

    const auto* profile = processor.profile_for(42);
    assert(profile != nullptr);
    const auto* interest = profile->get("technology");
    assert(interest != nullptr);
    assert(interest->score > 0.0);

    BehaviorEvent future{2, 42, 101, 7, EventType::view, now + 600'000};
    assert(!processor.process(future, "technology", now));
    return 0;
}
