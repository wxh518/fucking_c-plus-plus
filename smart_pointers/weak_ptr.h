#pragma once
#include "shared_ptr.h"

template<typename T>
class WeakPtr
{
public:
  WeakPtr() : cb_(nullptr) {}
  ~WeakPtr() {
    release();
  }
  WeakPtr(const WeakPtr& other) : cb_(other.cb_) {
    if (cb_) {
      cb_->weak_count_++;
    }
  }
  WeakPtr& operator=(const WeakPtr& other) {
    if (this == &other) {
      return *this;
    }

    if (other.cb_) {
      other.cb_->weak_count_++;
    }
    
    release();

    cb_ = other.cb_;
    return *this;
  }
  WeakPtr& operator=(const SharedPtr<T>& other) {
    if (other.cb_) {
      other.cb_->weak_count_++;
    }
    release();
    cb_ = other.cb_;
    return *this;
  }
  WeakPtr(const SharedPtr<T>& other) : cb_(other.cb_) {
    if (cb_) {
      cb_->weak_count_++;
    }
  }
  WeakPtr(WeakPtr&& other) : cb_(other.cb_) {
    other.cb_ = nullptr;
  }
  WeakPtr& operator=(WeakPtr&& other) {
    if (this == &other) {
      return *this;
    }
    
    release();

    cb_ = other.cb_;
    other.cb_ = nullptr;
    return *this;
  }
  bool expired() const {
    return cb_ == nullptr || cb_->strong_count_ == 0;
  }
  int use_count() const {
    return cb_ ? cb_->strong_count_.load() : 0;
  }
  void release() {
    if (cb_) {
      cb_->weak_count_--;
      if (cb_->weak_count_.load() == 0 && cb_->strong_count_.load() == 0) {
        delete cb_;
        cb_ = nullptr;
      }
    }
  }

  void reset() {
    release();
    cb_ = nullptr;
  }

  SharedPtr<T> lock() const {
    if (expired()) {
      return SharedPtr<T>(nullptr, 0);
    }
    return SharedPtr<T>(cb_, 0);
  }
    
private:
  control_block<T>* cb_ = nullptr;
};
