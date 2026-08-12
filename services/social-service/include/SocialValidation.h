#pragma once
#include <cstddef>
#include <string_view>
namespace mitra::social {
inline bool valid_username(std::string_view v) noexcept { if(v.size()<3||v.size()>64)return false; for(unsigned char c:v) if(!((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c=='_'||c=='.')) return false; return true; }
inline bool valid_post(std::string_view v) noexcept { return !v.empty() && v.size()<=5000; }
inline bool valid_page_size(std::size_t n) noexcept { return n>0&&n<=100; }
}
