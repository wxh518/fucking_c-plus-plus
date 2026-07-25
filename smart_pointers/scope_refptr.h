#pragma once

#include "ref_count.h"

template<typename T>
class ScopeRefPtr {
public:
ScopeRefPtr(T* ptr = nullptr) : ptr_(ptr) {
    if (ptr_) {
      ptr_->AddRef();
    }
  }

  ~ScopeRefPtr() {
    if (ptr_) {
      ptr_->Release();
    }
  }

  ScopeRefPtr(const ScopeRefPtr& other) : ptr_(other.ptr_) {
    if (ptr_) {
      ptr_->AddRef();
    }
  }

  ScopeRefPtr& operator=(const ScopeRefPtr& other) {
    if (this == &other) {
      return *this;
    }

    if (other.ptr_) {
      other.ptr_->AddRef();
    }

    if (ptr_) {
      ptr_->Release();
    }

    ptr_ = other.ptr_;
    return *this;
  }

  ScopeRefPtr(ScopeRefPtr&& other) : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  ScopeRefPtr& operator=(ScopeRefPtr&& other) {
    if (this == &other) {
      return *this;
    }

    if (ptr_) {
      ptr_->Release();
    }

    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
  }

  T* get() const {
    return ptr_;
  }

  T* operator ->() const {
    return ptr_;
  }

  operator bool() const {
    return ptr_ != nullptr;
  }

  int use_count() const {
    return ptr_ ? ptr_->use_count() : 0;
  }

  void reset(T* ptr = nullptr) {
    if (ptr_) {
      ptr_->Release();
    }
    ptr_ = ptr;
    if (ptr_) {
      ptr_->AddRef();
    }
  }

private:
  T* ptr_ = nullptr;
};