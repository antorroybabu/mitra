#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace mitra::recommendation {

struct Interest final {
    double score{0.0};
    std::int64_t updated_at_ms{0};
};

class SparseInterestModel final {
public:
    void update(const std::string& topic, double delta, std::int64_t now_ms) {
        if (topic.empty()) return;
        auto& interest = interests_[topic];
        interest.score = std::clamp(interest.score + delta, -1.0, 1.0);
        interest.updated_at_ms = now_ms;
    }

    [[nodiscard]] const Interest* find(const std::string& topic) const {
        const auto it = interests_.find(topic);
        return it == interests_.end() ? nullptr : &it->second;
    }

    void decay(double factor, std::int64_t now_ms) {
        factor = std::clamp(factor, 0.0, 1.0);
        for (auto& [_, interest] : interests_) {
            interest.score *= factor;
            interest.updated_at_ms = now_ms;
        }
    }

private:
    std::unordered_map<std::string, Interest> interests_;
};

} // namespace mitra::recommendation
