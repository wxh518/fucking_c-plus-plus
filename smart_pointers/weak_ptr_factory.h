#pragma once

#include "scope_refptr.h"

namespace base {

struct Flag : public RefCount<Flag> {
  bool is_valid = false;
};

template<typename T>
class WeakPtr {
public:
  WeakPtr() : flag_(nullptr) {}

  WeakPtr(const ScopeRefPtr<Flag>& flag, T* ptr) : flag_(flag), ptr_(ptr) {}

  WeakPtr(const WeakPtr& other) : flag_(other.flag_), ptr_(other.ptr_) {}

  WeakPtr& operator=(const WeakPtr& other) {
    if (this == &other) {
      return *this;
    }
    flag_ = other.flag_;
    ptr_ = other.ptr_;
    return *this;
  }

  WeakPtr(WeakPtr&& other) : flag_(std::move(other.flag_)), ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  WeakPtr& operator=(WeakPtr&& other) {
    if (this == &other) {
      return *this;
    }
    flag_ = std::move(other.flag_);
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
  }

  bool expired() const {
    return !flag_ || !flag_->is_valid;
  }

  operator bool() const {
    return !expired();
  }

  int use_count() const {
    return flag_ ? flag_->use_count() : 0;
  }

  void reset() {
    flag_.reset();
    ptr_ = nullptr;
  }

  T* get() const {
    return expired() ? nullptr : ptr_;
  }

private:
  ScopeRefPtr<Flag> flag_;
  T* ptr_ = nullptr;
};

template<typename T>
class WeakPtrFactory {
public:
  WeakPtrFactory(T* ptr) : flag_(new Flag()), ptr_(ptr) {
    flag_->is_valid = true;
  }

  ~WeakPtrFactory() {
    flag_->is_valid = false;
  }

  WeakPtr<T> GetWeakPtr() {
    return WeakPtr<T>(flag_, ptr_);
  }

private:
  ScopeRefPtr<Flag> flag_;
  T* ptr_ = nullptr;
};

}  // namespace base