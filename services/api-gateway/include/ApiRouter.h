#pragma once
#include <string_view>
namespace mitra::api { enum class Method{get,post,put,del}; struct Route{Method method;std::string_view path;}; constexpr Route routes[]={{Method::post,"/v1/auth/login"},{Method::post,"/v1/auth/logout"},{Method::get,"/v1/feed"},{Method::post,"/v1/posts"},{Method::post,"/v1/posts/{id}/like"},{Method::post,"/v1/users/{id}/follow"}}; }
