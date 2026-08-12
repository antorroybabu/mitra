#pragma once
#include "InterestProfile.h"
#include "TopicIndex.h"
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>
namespace mitra::recommendation {
class InterestCandidateSource final {
public:
 static std::vector<Candidate> query(const InterestProfile& profile,const TopicIndex& index,std::vector<std::string> topics,std::size_t limit){
  std::stable_sort(topics.begin(),topics.end(),[&](const auto&a,const auto&b){ const auto* x=profile.get(a); const auto* y=profile.get(b); return (x?x->score:0.0)>(y?y->score:0.0); });
  return index.query(topics,limit);
 }
};
}
