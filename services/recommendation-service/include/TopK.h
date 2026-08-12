#pragma once

#include <algorithm>
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

namespace mitra::recommendation {

template <typename T, typename Score = double>
struct ScoredItem final {
    T item;
    Score score{};
};

template <typename T, typename Score = double>
std::vector<ScoredItem<T, Score>> top_k(std::vector<ScoredItem<T, Score>> items,
                                         std::size_t k) {
    if (k == 0 || items.empty()) return {};
    if (items.size() <= k) {
        std::stable_sort(items.begin(), items.end(),
            [](const auto& a, const auto& b) { return a.score > b.score; });
        return items;
    }

    auto cmp = [](const auto& a, const auto& b) { return a.score > b.score; };
    std::priority_queue<ScoredItem<T, Score>,
                        std::vector<ScoredItem<T, Score>>, decltype(cmp)> heap(cmp);

    for (auto& candidate : items) {
        if (heap.size() < k) {
            heap.push(std::move(candidate));
        } else if (candidate.score > heap.top().score) {
            heap.pop();
            heap.push(std::move(candidate));
        }
    }

    std::vector<ScoredItem<T, Score>> result;
    result.reserve(k);
    while (!heap.empty()) {
        auto value = heap.top();
        heap.pop();
        result.push_back(std::move(value));
    }
    std::stable_sort(result.begin(), result.end(),
        [](const auto& a, const auto& b) { return a.score > b.score; });
    return result;
}

} // namespace mitra::recommendation
