#pragma once

#include <cstdint>
#include <deque>
#include <unordered_set>

namespace mitra::recommendation {

class EventDeduplicator final {
public:
    explicit EventDeduplicator(std::size_t capacity = 100000) : capacity_(capacity) {}

    bool accept(std::uint64_t event_id) {
        if (event_id == 0 || seen_.contains(event_id)) return false;
        seen_.insert(event_id);
        order_.push_back(event_id);
        while (order_.size() > capacity_) {
            seen_.erase(order_.front());
            order_.pop_front();
        }
        return true;
    }

private:
    std::size_t capacity_;
    std::unordered_set<std::uint64_t> seen_;
    std::deque<std::uint64_t> order_;
};

} // namespace mitra::recommendation
