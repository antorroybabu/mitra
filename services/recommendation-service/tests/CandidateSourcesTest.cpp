#include "../include/CandidateSources.h"

#include <cassert>

int main() {
    using namespace mitra::recommendation;

    SourceBudget budget;
    budget.following = 2;
    budget.interest = 2;
    budget.trending = 1;
    budget.fresh = 1;
    budget.exploration = 1;

    const std::vector<Candidate> following{{1, 1.0}, {2, 0.9}, {3, 0.8}};
    const std::vector<Candidate> interest{{2, 1.0}, {4, 0.7}};
    const std::vector<Candidate> trending{{5, 0.8}};
    const std::vector<Candidate> fresh{{6, 0.7}};
    const std::vector<Candidate> exploration{{7, 0.6}};

    const auto result = CandidateSources::collect(
        following, interest, trending, fresh, exploration, budget, 10);

    assert(result.size() == 7);
    assert(result[0].content_id == 1);
    assert(result[1].content_id == 2);
    for (std::size_t i = 0; i < result.size(); ++i) {
        for (std::size_t j = i + 1; j < result.size(); ++j) {
            assert(result[i].content_id != result[j].content_id);
        }
    }
    return 0;
}
