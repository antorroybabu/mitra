#pragma once
#include "CandidateGenerator.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace mitra::recommendation {
struct FreshContent final { std::uint64_t content_id{0}; std::int64_t created_at_ms{0}; };
class FreshContentIndex final {
public:
 void add(FreshContent item){ if(item.content_id) items_.push_back(item); }
 [[nodiscard]] std::vector<Candidate> recent(std::size_t limit) const {
  auto items=items_; std::stable_sort(items.begin(),items.end(),[](const auto&a,const auto&b){ if(a.created_at_ms!=b.created_at_ms)return a.created_at_ms>b.created_at_ms; return a.content_id>b.content_id; });
  if(items.size()>limit) items.resize(limit); std::vector<Candidate> out; out.reserve(items.size()); for(const auto& item:items) out.push_back({item.content_id,1.0}); return out;
 }
private: std::vector<FreshContent> items_;
};
}
