#pragma once
#include "CandidateGenerator.h"
#include <cstdint>
#include <unordered_map>
#include <vector>
namespace mitra::recommendation {
struct IndexedContent final { std::uint64_t content_id{0}; std::uint64_t creator_id{0}; std::int64_t created_at_ms{0}; std::vector<std::string> topics; };
class CandidateIndex final {
public:
 void upsert(IndexedContent item){ if(item.content_id) items_[item.content_id]=std::move(item); }
 void erase(std::uint64_t id){ items_.erase(id); }
 [[nodiscard]] const IndexedContent* get(std::uint64_t id) const { auto it=items_.find(id); return it==items_.end()?nullptr:&it->second; }
 [[nodiscard]] std::vector<Candidate> by_creator(std::uint64_t creator,std::size_t limit) const { std::vector<Candidate> out; for(const auto& [id,item]:items_) if(item.creator_id==creator){ out.push_back({id,1.0}); if(out.size()>=limit) break; } return out; }
private: std::unordered_map<std::uint64_t,IndexedContent> items_;
};
}
