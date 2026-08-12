#pragma once
#include <algorithm>
#include <cstddef>
#include <cstdint>
namespace mitra::feed { struct CachePolicy{std::int64_t ttl_seconds{30};std::size_t max_items{100};}; inline bool cacheable(std::size_t n,const CachePolicy&p)noexcept{return n>0&&n<=p.max_items&&p.ttl_seconds>0;} }
