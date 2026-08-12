#pragma once

#include "BehaviorEvent.h"
#include "SparseInterestModel.h"

#include <string>
#include <string_view>

namespace mitra::recommendation {

class InterestUpdater final {
public:
    void apply(SparseInterestModel& model, const behavior::BehaviorEvent& event,
               std::string_view topic, std::int64_t now_ms) const {
        if (topic.empty()) return;

        double delta = 0.0;
        switch (event.type) {
            case behavior::EventType::completion: delta = 0.40; break;
            case behavior::EventType::like: delta = 0.30; break;
            case behavior::EventType::bookmark: delta = 0.35; break;
            case behavior::EventType::follow: delta = 0.25; break;
            case behavior::EventType::click: delta = 0.08; break;
            case behavior::EventType::view: delta = 0.05; break;
            case behavior::EventType::skip: delta = -0.15; break;
            case behavior::EventType::dislike: delta = -0.35; break;
            case behavior::EventType::not_interested: delta = -0.60; break;
            case behavior::EventType::mute_topic: delta = -0.80; break;
            case behavior::EventType::report: delta = -1.00; break;
            default: break;
        }
        model.update(std::string(topic), delta, now_ms);
    }
};

} // namespace mitra::recommendation
