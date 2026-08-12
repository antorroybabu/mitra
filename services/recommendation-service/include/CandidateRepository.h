#pragma once
#include "CandidateIndex.h"
#include "FollowGraph.h"
#include <cstddef>
#include <cstdint>
#include <vector>
namespace mitra::recommendation {
class CandidateRepository final {
public:
 CandidateRepository(const CandidateIndex& index,const FollowGraph& graph):index_(index),graph_(graph){}
 std::vector<Candidate> following(std::uint64_t user,std::size_t per_creator,std::size_t limit) const {
  std::vector<Candidate> out;
  for(std::uint64_t creator=1; creator<1000000 && out.size()<limit; ++creator){
   if(!graph_.follows(user,creator)) continue;
   auto items=index_.by_creator(creator,per_creator);
   out.insert(out.end(),items.begin(),items.end());
  }
  return out;
 }
private: const CandidateIndex& index_; const FollowGraph& graph_;
};
}
