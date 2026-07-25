#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QDebug>
#include "shared_ptr.h"
#include "weak_ptr.h"
#include "scope_refptr.h"
#include "weak_ptr_factory.h"
#include <memory>

class Test : public RefCount<Test> {
public:
  Test() {
      qDebug() << "Test constructor: ";
  }
private:
  ~Test() {
      qDebug() << "Test destructor: ";
  }

private:
  friend class RefCount<Test>;
};

class Test2 {
public:
  Test2() {
      qDebug() << "Test2 constructor: ";
  }
  ~Test2() {
      qDebug() << "Test2 destructor: ";
  }

  base::WeakPtr<Test2> GetWeakPtr() {
    return weak_ptr_factory_.GetWeakPtr();
  }

private:
  base::WeakPtrFactory<Test2> weak_ptr_factory_{this};
};

void TestStdSharedPtr() {
  std::shared_ptr<int> ptr;
  {
    ptr = std::make_shared<int>(1);
    qDebug() << "std ptr count: " << ptr.use_count();
    {
        std::shared_ptr<int> ptr2 = ptr;
        qDebug() << "std ptr2 count: " << ptr2.use_count();
    }
    qDebug() << "std ptr count: " << ptr.use_count();
  }
  ptr.reset();
  qDebug() << "std ptr count: " << ptr.use_count();
}

void TestSharedPtr() {
  SharedPtr<int> ptr(nullptr);
  {
    ptr = SharedPtr<int>(new int(1));
    qDebug() << "ptr count: " << ptr.use_count();
    {
      SharedPtr<int> ptr2 = ptr;
      qDebug() << "ptr2 count: " << ptr2.use_count();
    }
    qDebug() << "ptr count: " << ptr.use_count();
  }
  ptr.reset();
  qDebug() << "ptr count: " << ptr.use_count();
}

void TestScopeRefPtr() {
  ScopeRefPtr<Test> ptr(nullptr);
  {
    ptr = ScopeRefPtr<Test>(new Test());
    qDebug() << "ptr count: " << ptr.use_count();
    {
      ScopeRefPtr<Test> ptr2 = ptr;
      qDebug() << "ptr2 count: " << ptr2.use_count();
    }
    qDebug() << "ptr count: " << ptr.use_count();
  }
  ptr.reset();
  qDebug() << "ptr count: " << ptr.use_count();

  // Test* test = new Test();
  // delete test;
}

void TestStdWeakPtr() {
  std::weak_ptr<int> ptr;
  qDebug() << "ptr count begin: " << ptr.use_count();
  {
    std::shared_ptr<int> ptr2 = std::make_shared<int>(1);
    ptr = ptr2;
    qDebug() << "std ptr2 count: " << ptr2.use_count();
    qDebug() << "std ptr count: " << ptr.use_count();
    std::weak_ptr<int> ptr3 = ptr;
    qDebug() << "std ptr3 count: " << ptr3.use_count();
    ptr2.reset(); 
    qDebug() << "std ptr3 count2: " << ptr3.use_count();
    qDebug() << "std ptr count: " << ptr.use_count();
  }
  qDebug() << "std ptr count: " << ptr.use_count();
  if (std::shared_ptr<int> ptr4 = ptr.lock()) {
    qDebug() << "std ptr4 count: " << ptr4.use_count();
  } else {
    qDebug() << "std ptr4 is expired";
  }
}

void TestWeakPtr() {
  WeakPtr<int> ptr;
  qDebug() << "ptr count begin: " << ptr.use_count();
  {
    SharedPtr<int> ptr2 = SharedPtr<int>(new int(1));
    ptr = ptr2;
    qDebug() << "ptr2 count: " << ptr2.use_count();
    qDebug() << "ptr count: " << ptr.use_count();
    WeakPtr<int> ptr3 = ptr;
    qDebug() << "ptr3 count: " << ptr3.use_count();
    ptr2.reset(); 
    qDebug() << "ptr3 count2: " << ptr3.use_count();
    qDebug() << "ptr count: " << ptr.use_count();
  }
  qDebug() << "ptr count: " << ptr.use_count();
  {
    SharedPtr<int> ptr4 = ptr.lock();
    if (ptr4) {
      qDebug() << "ptr4 count: " << ptr4.use_count();
    } else {
      qDebug() << "ptr4 is expired";
    }
  }
  qDebug() << "ptr count end: " << ptr.use_count();
}

void TestWeakPtrFactory() {
  base::WeakPtr<Test2> ptr;
  qDebug() << "ptr count begin: " << ptr.use_count();
  {
    SharedPtr<Test2> ptr2 = SharedPtr<Test2>(new Test2());
    ptr = ptr2->GetWeakPtr();
    qDebug() << "ptr2 count: " << ptr2.use_count();
    qDebug() << "ptr count: " << ptr.use_count();
    base::WeakPtr<Test2> ptr3 = ptr;
    qDebug() << "ptr3 count: " << ptr3.use_count();
    ptr2.reset(); 
    qDebug() << "ptr3 count2: " << ptr3.use_count();
    qDebug() << "ptr count: " << ptr.use_count();
  }
  qDebug() << "ptr count: " << ptr.use_count();
  {
    if (ptr) {
      qDebug() << "ptr4 count: " << ptr.use_count();
    } else {
      qDebug() << "ptr4 is expired";
    }
  }
  qDebug() << "ptr count end: " << ptr.use_count();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.show();

    TestStdSharedPtr();
    TestSharedPtr();
    TestScopeRefPtr();

    TestStdWeakPtr();
    TestWeakPtr();
    TestWeakPtrFactory();

    qDebug() << "Hello VSCode Qt...";
    return app.exec();
}
