#pragma once
#include "CandidateGenerator.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace mitra::recommendation {
class TopicIndex final {
public:
 void add(std::string topic,std::uint64_t content_id){ if(!topic.empty()&&content_id) index_[std::move(topic)].insert(content_id); }
 void remove(const std::string& topic,std::uint64_t content_id){ auto it=index_.find(topic); if(it!=index_.end()) it->second.erase(content_id); }
 [[nodiscard]] std::vector<Candidate> query(const std::vector<std::string>& topics,std::size_t limit) const {
  std::unordered_set<std::uint64_t> ids;
  for(const auto& topic:topics){ auto it=index_.find(topic); if(it==index_.end()) continue; for(auto id:it->second){ if(ids.size()>=limit) break; ids.insert(id); } if(ids.size()>=limit) break; }
  std::vector<Candidate> out; out.reserve(ids.size()); for(auto id:ids) out.push_back({id,1.0}); return out;
 }
private: std::unordered_map<std::string,std::unordered_set<std::uint64_t>> index_;
};
}
