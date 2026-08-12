#pragma once
#include <algorithm>
#include <cstddef>
#include <string>
namespace mitra::search { struct Query{std::string text;std::size_t limit{20};}; inline bool valid(const Query&q)noexcept{return !q.text.empty()&&q.text.size()<=256&&q.limit>0&&q.limit<=100;} }
