#pragma once
#include <cstddef>
#include <string_view>
namespace mitra::media { enum class Kind{image,video,audio}; struct UploadPolicy{std::size_t max_bytes{100ULL*1024*1024};}; inline bool allowed(Kind k,std::size_t bytes,std::string_view mime,const UploadPolicy&p)noexcept{if(bytes==0||bytes>p.max_bytes||mime.empty())return false; if(k==Kind::image)return mime.rfind("image/",0)==0; if(k==Kind::video)return mime.rfind("video/",0)==0; return k==Kind::audio&&mime.rfind("audio/",0)==0;} }
