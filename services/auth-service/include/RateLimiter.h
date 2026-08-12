#pragma once
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <mutex>
#include <unordered_map>
namespace mitra::auth { class RateLimiter final { struct Bucket{double tokens;std::chrono::steady_clock::time_point last;}; public: RateLimiter(double capacity=20,double refill_per_sec=1):capacity_(capacity),refill_(refill_per_sec){} bool allow(std::uint64_t key){std::lock_guard l(mu_);auto now=std::chrono::steady_clock::now();auto&b=buckets_[key];if(b.last.time_since_epoch().count()==0){b.tokens=capacity_;b.last=now;}double sec=std::chrono::duration<double>(now-b.last).count();b.tokens=std::min(capacity_,b.tokens+sec*refill_);b.last=now;if(b.tokens<1)return false;--b.tokens;return true;} private:double capacity_,refill_;std::mutex mu_;std::unordered_map<std::uint64_t,Bucket>buckets_;}; }
