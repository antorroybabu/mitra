#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace mitra::recommendation {

struct InterestValue final {
    double score{0.0};
    std::int64_t updated_at_ms{0};
};

class InterestProfile final {
public:
    explicit InterestProfile(std::size_t max_topics = 500) : max_topics_(max_topics) {}

    void apply(const std::string& topic, double delta, std::int64_t now_ms) {
        if (topic.empty()) return;
        auto& value = topics_[topic];
        value.score = std::clamp(value.score + delta, -1.0, 1.0);
        value.updated_at_ms = now_ms;
        trim_if_needed();
    }

    void decay(double factor, std::int64_t now_ms) {
        factor = std::clamp(factor, 0.0, 1.0);
        for (auto& [_, value] : topics_) {
            value.score *= factor;
            value.updated_at_ms = now_ms;
        }
        trim_if_needed();
    }

    [[nodiscard]] const InterestValue* get(const std::string& topic) const {
        const auto it = topics_.find(topic);
        return it == topics_.end() ? nullptr : &it->second;
    }

    [[nodiscard]] std::size_t size() const noexcept { return topics_.size(); }

private:
    void trim_if_needed() {
        while (topics_.size() > max_topics_) {
            auto victim = topics_.begin();
            for (auto it = topics_.begin(); it != topics_.end(); ++it) {
                if (std::abs(it->second.score) < std::abs(victim->second.score)) victim = it;
            }
            topics_.erase(victim);
        }
    }

    std::size_t max_topics_;
    std::unordered_map<std::string, InterestValue> topics_;
};

} // namespace mitra::recommendation
