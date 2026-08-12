#pragma once
#include "CandidateGenerator.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>
namespace mitra::recommendation {
class TrendingIndex final {
public:
 void record(std::uint64_t content_id,double engagement){ if(content_id) scores_[content_id]+=std::max(0.0,engagement); }
 void decay(double factor){ factor=std::clamp(factor,0.0,1.0); for(auto& [_,score]:scores_) score*=factor; }
 [[nodiscard]] std::vector<Candidate> top(std::size_t limit) const {
  std::vector<Candidate> out; out.reserve(scores_.size()); for(const auto& [id,score]:scores_) out.push_back({id,score});
  std::stable_sort(out.begin(),out.end(),[](const auto&a,const auto&b){return a.score>b.score;}); if(out.size()>limit) out.resize(limit); return out;
 }
private: std::unordered_map<std::uint64_t,double> scores_;
};
}
