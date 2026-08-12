#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace mitra::social {
struct FeedRow { std::uint64_t id{}; std::uint64_t author_id{}; std::string body; };
class MySqlSocialRepository final {
public:
  virtual ~MySqlSocialRepository() = default;
  virtual bool create_user(std::uint64_t id, const std::string& username, const std::string& display_name)=0;
  virtual bool create_post(std::uint64_t id, std::uint64_t author_id, const std::string& body)=0;
  virtual bool follow(std::uint64_t follower_id, std::uint64_t following_id)=0;
  virtual bool like(std::uint64_t user_id, std::uint64_t post_id)=0;
  virtual bool bookmark(std::uint64_t user_id, std::uint64_t post_id)=0;
  virtual std::vector<FeedRow> feed(std::uint64_t user_id, std::uint64_t limit)=0;
};
}
