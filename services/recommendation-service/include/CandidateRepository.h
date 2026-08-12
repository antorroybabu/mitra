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
  if(limit==0) return out;
  const auto* creators=graph_.creators(user);
  if(!creators) return out;
  out.reserve(std::min(limit, creators->size()*per_creator));
  for(const auto creator:*creators){
   if(out.size()>=limit) break;
   auto items=index_.by_creator(creator,per_creator);
   const auto remaining=limit-out.size();
   if(items.size()>remaining) items.resize(remaining);
   out.insert(out.end(),items.begin(),items.end());
  }
  return out;
 }
private: const CandidateIndex& index_; const FollowGraph& graph_;
};
}
