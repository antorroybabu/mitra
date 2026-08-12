#pragma once
#include "CandidateRepository.h"
#include "CandidateSources.h"
#include "FreshContentIndex.h"
#include "InterestCandidateSource.h"
#include "TrendingIndex.h"
#include "TopicIndex.h"
#include <cstddef>
#include <vector>
namespace mitra::recommendation {
class UnifiedCandidateRepository final {
public:
 UnifiedCandidateRepository(const CandidateIndex& content,const FollowGraph& follows,const TopicIndex& topics,const TrendingIndex& trending,const FreshContentIndex& fresh):following_(content,follows),topics_(topics),trending_(trending),fresh_(fresh){}
 std::vector<Candidate> collect(std::uint64_t user,const InterestProfile& profile,const std::vector<std::string>& interest_topics,const SourceBudget& budget,std::size_t limit) const {
  auto following=following_.following(user,4,budget.following);
  auto interest=InterestCandidateSource::query(profile,topics_,interest_topics,budget.interest);
  auto trend=trending_.top(budget.trending);
  auto fresh=fresh_.recent(budget.fresh);
  std::vector<Candidate> exploration=fresh; if(exploration.size()>budget.exploration) exploration.resize(budget.exploration);
  return merge_candidates({following,interest,trend,fresh,exploration},limit);
 }
private: CandidateRepository following_; const TopicIndex& topics_; const TrendingIndex& trending_; const FreshContentIndex& fresh_;
};
}
