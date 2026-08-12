#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <charconv>
namespace mitra::feed {
struct FeedCursor{std::int64_t created_at_ms{};std::uint64_t id{};};
inline std::string encode_cursor(FeedCursor c){return std::to_string(c.created_at_ms)+":"+std::to_string(c.id);}
inline std::optional<FeedCursor> decode_cursor(const std::string& s){auto p=s.find(':');if(p==std::string::npos)return std::nullopt;FeedCursor c{};auto a=std::from_chars(s.data(),s.data()+p,c.created_at_ms);auto b=std::from_chars(s.data()+p+1,s.data()+s.size(),c.id);if(a.ec!=std::errc{}||b.ec!=std::errc{}||a.ptr!=s.data()+p||b.ptr!=s.data()+s.size())return std::nullopt;return c;}
}
