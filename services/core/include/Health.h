#pragma once
#include <atomic>
namespace mitra::core {
class Health final { public: void set_ready(bool value) noexcept { ready_.store(value, std::memory_order_release); } [[nodiscard]] bool ready() const noexcept { return ready_.load(std::memory_order_acquire); } private: std::atomic_bool ready_{false}; };
}
