#pragma once
#include <iostream>
#include <atomic>

template<typename T>
struct control_block
{
  control_block() {
    std::cout << "control_block constructor" << std::endl;
  }
  ~control_block() {
    std::cout << "control_block destructor" << std::endl;
  }
  std::atomic<int> strong_count_ = 0;
  std::atomic<int> weak_count_ = 0;
  T* ptr_ = nullptr;
};

template<typename T> class WeakPtr;
template<typename T>
class SharedPtr
{
public:
  explicit SharedPtr(T* ptr = nullptr) {
    if (ptr) {
      cb_ = new control_block<T>();
      cb_->strong_count_ = 1;
      cb_->ptr_ = ptr;
    }
  }
  ~SharedPtr() {
    release();
  }

  void release() {
    if (cb_ && --cb_->strong_count_ == 0) {
      delete cb_->ptr_;
      cb_->ptr_ = nullptr;
      if (cb_->weak_count_.load() == 0) {
        delete cb_;
        cb_ = nullptr;
      }
      cb_ = nullptr;
    }
  }
  SharedPtr(const SharedPtr& other) : cb_(other.cb_) {
    if (cb_) {
      cb_->strong_count_++;
    }
  }
  SharedPtr& operator=(const SharedPtr& other) {
    if (this == &other) {
      return *this;
    }

    if (other.cb_) {
      other.cb_->strong_count_++;
    }

    release();

    cb_ = other.cb_;
    return *this;
  }
  SharedPtr(SharedPtr&& other) : cb_(other.cb_) {
    other.cb_ = nullptr;
  }
  SharedPtr& operator=(SharedPtr&& other) {
    if (this == &other) {
      return *this;
    }

    release();

    cb_ = other.cb_;
    other.cb_ = nullptr;
    return *this;
  }
  T* get() const {
    return cb_ ? cb_->ptr_ : nullptr;
  }
  T& operator*() const {
    return *get();
  }
  T* operator->() const {
    return get();
  }
  explicit operator bool() const {
    return cb_ && cb_->ptr_;
  }
  int use_count() const {
    return cb_ ? cb_->strong_count_.load() : 0;
  }
  void reset() {
    release();
    cb_ = nullptr;
  }
    
private:
  SharedPtr(control_block<T>* cb, int) : cb_(cb) {
    if (cb_) {
      cb_->strong_count_++;
    }
  }

  friend class WeakPtr<T>;
  control_block<T>* cb_ = nullptr;
};
