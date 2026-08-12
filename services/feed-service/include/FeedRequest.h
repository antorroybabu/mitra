#pragma once
#include "FeedCursor.h"
#include <cstddef>
#include <cstdint>
#include <optional>
namespace mitra::feed { struct FeedRequest{std::uint64_t user_id{};std::size_t limit{20};std::optional<FeedCursor> after;}; inline bool valid(const FeedRequest&q)noexcept{return q.user_id>0&&q.limit>0&&q.limit<=100;} }
