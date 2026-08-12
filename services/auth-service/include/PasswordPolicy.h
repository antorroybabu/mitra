#pragma once
#include <string_view>
namespace mitra::auth { inline bool valid_password(std::string_view p) noexcept { if(p.size()<12||p.size()>128)return false; bool upper=false,lower=false,digit=false,symbol=false; for(unsigned char c:p){upper|=c>='A'&&c<='Z';lower|=c>='a'&&c<='z';digit|=c>='0'&&c<='9';symbol|=c<33||c>126||(!((c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9')));} return upper&&lower&&digit&&symbol; } }
