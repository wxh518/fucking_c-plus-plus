#pragma once
#include <vector>

namespace base {

class QObject;
class QPointerObserver {
public:
  virtual ~QPointerObserver() = default;

  virtual void OnQObjectDestroyed(QObject* obj) = 0;
};

class QObject {
public:
  virtual ~QObject() {
    for (auto observer : observers_) {
      observer->OnQObjectDestroyed(this);
    }
    observers_.clear();
  }

  void AddObserver(QPointerObserver* observer) {
    observers_.push_back(observer);
  }
  
  void RemoveObserver(QPointerObserver* observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
  }

private:
  std::vector<QPointerObserver*> observers_;
};

template<typename T>
class QPointer : public QPointerObserver {
public:
  static_assert(std::is_base_of<QObject, T>::value, "T must be derived from QObject");
  QPointer(T* obj = nullptr) : obj_(obj) {
    if (obj_) {
      obj_->AddObserver(this);
    }
  }

  ~QPointer() {
    if (obj_) {
      obj_->RemoveObserver(this);
    }
  }

  QPointer(const QPointer& other) : obj_(other.obj_) {
    if (obj_) {
      obj_->AddObserver(this);
    }
  }

  QPointer& operator= (const QPointer& other) {
    if (this == &other) {
      return *this;
    }
    if (obj_) {
      obj_->RemoveObserver(this);
    }
    obj_ = other.obj_;
    if (obj_) {
      obj_->AddObserver(this);
    }
    return *this;
  }

  QPointer(QPointer&& other) : obj_(other.obj_) {
    if (obj_) {
      obj_->AddObserver(this);
    }
    other.clear();
  }

  QPointer& operator= (QPointer&& other) {
    if (this == &other) {
      return *this;
    }
    if (obj_) {
      obj_->RemoveObserver(this);
    }
    obj_ = other.obj_;
    if (obj_) {
      obj_->AddObserver(this);
    }
    other.clear();
    return *this;
  }

  T* data() const {
    return obj_;
  }

  void clear() {
    if (obj_) {
      obj_->RemoveObserver(this);
      obj_ = nullptr;
    }
  }

  void OnQObjectDestroyed(QObject* obj) override {
    if (obj == obj_) {
      obj_ = nullptr;
    }
  }

private:
  T* obj_ = nullptr;
};

}