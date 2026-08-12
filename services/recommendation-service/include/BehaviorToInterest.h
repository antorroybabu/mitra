#pragma once

#include "SparseInterestModel.h"
#include "../../behavior-service/include/BehaviorEvent.h"

namespace mitra::recommendation {

inline double signal_for(behavior::EventType type) noexcept {
    switch (type) {
        case behavior::EventType::completion: return 0.18;
        case behavior::EventType::like: return 0.12;
        case behavior::EventType::bookmark: return 0.15;
        case behavior::EventType::follow: return 0.14;
        case behavior::EventType::share: return 0.16;
        case behavior::EventType::view: return 0.04;
        case behavior::EventType::impression: return 0.01;
        case behavior::EventType::click: return 0.03;
        case behavior::EventType::skip: return -0.06;
        case behavior::EventType::dislike: return -0.20;
        case behavior::EventType::not_interested: return -0.30;
        case behavior::EventType::mute_creator: return -0.35;
        case behavior::EventType::mute_topic: return -0.30;
        case behavior::EventType::report: return -0.50;
        default: return 0.0;
    }
}

inline void apply_event(SparseInterestModel& model,
                        const behavior::BehaviorEvent& event,
                        const std::string& topic) {
    model.update(topic, signal_for(event.type), event.occurred_at_ms);
}

} // namespace mitra::recommendation
