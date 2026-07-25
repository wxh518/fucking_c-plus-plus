#pragma once

#include <atomic>

template<typename T>
class RefCount {
public:
  RefCount() = default;
  RefCount(const RefCount&) = delete;
  RefCount& operator=(const RefCount&) = delete;

  void AddRef() {
    count_++;
  }

  void Release() {
    count_--;
    if (count_ == 0) {
      delete static_cast<T*>(this);
    }
  }

  int use_count() const {
    return count_;
  }

private:
  ~RefCount() = default;
  friend T;

private:
  std::atomic<int> count_{0};
};