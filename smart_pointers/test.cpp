#include "pch.h"
#include "D:/test/fucking_c-plus-plus/smart_pointers/shared_ptr.h"
#include "D:/test/fucking_c-plus-plus/smart_pointers/weak_ptr.h"
#include "D:/test/fucking_c-plus-plus/smart_pointers/scope_refptr.h"
#include "D:/test/fucking_c-plus-plus/smart_pointers/weak_ptr_factory.h"

TEST(TestSharedPtr, TestSharedPtrCaseConstructor) {
//   EXPECT_EQ(1, 1);
//   EXPECT_TRUE(true);
  std::shared_ptr<int> stdptr = nullptr;
  SharedPtr<int> ptr(nullptr);
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 0);
}

TEST(TestSharedPtr, TestSharedPtrCaseCopyOperator) {
  std::shared_ptr<int> stdptr = std::make_shared<int>(1);
  SharedPtr<int> ptr(new int(1));
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  {
    std::shared_ptr<int> stdptr2 = stdptr;
    SharedPtr<int> ptr2 = ptr;
    EXPECT_EQ(stdptr.use_count(), ptr2.use_count());
    EXPECT_EQ(ptr.use_count(), 2);
  }
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 1);
}

TEST(TestSharedPtr, TestSharedPtrCaseAssignmentOperator) {
  std::shared_ptr<int> stdptr;
  SharedPtr<int> ptr;
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  {
    stdptr = std::make_shared<int>(1);
    ptr = SharedPtr<int>(new int(1));
    EXPECT_EQ(stdptr.use_count(), ptr.use_count());
    EXPECT_EQ(ptr.use_count(), 1);
  }
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 1);
}

TEST(TestSharedPtr, TestSharedPtrCaseReset) {
  std::shared_ptr<int> stdptr = std::make_shared<int>(1);
  SharedPtr<int> ptr(new int(1));
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  {
    std::shared_ptr<int> stdptr2 = stdptr;
    SharedPtr<int> ptr2 = ptr;
    EXPECT_EQ(stdptr.use_count(), ptr2.use_count());
    EXPECT_EQ(ptr.use_count(), 2);
    stdptr.reset();
    ptr.reset();
    EXPECT_EQ(stdptr2.use_count(), ptr2.use_count());
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(stdptr.use_count(), ptr.use_count());
    EXPECT_EQ(ptr.use_count(), 0);
  }
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 0);
}

TEST(TestSharedPtr, TestSharedPtrCaseMoveConstructor) {
  std::shared_ptr<int> stdptr = std::make_shared<int>(1);
  SharedPtr<int> ptr(new int(1));
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 1);
  std::shared_ptr<int> stdptr2 = std::move(stdptr);
  SharedPtr<int> ptr2 = std::move(ptr);
  EXPECT_EQ(stdptr2.use_count(), ptr2.use_count());
  EXPECT_EQ(ptr2.use_count(), 1);
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 0);
}

TEST(TestSharedPtr, TestSharedPtrCaseMoveAssignmentOperator) {
  std::shared_ptr<int> stdptr = std::make_shared<int>(1);
  SharedPtr<int> ptr(new int(1));
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 1);
  std::shared_ptr<int> stdptr2;
  SharedPtr<int> ptr2;
  stdptr2 = std::move(stdptr);
  ptr2 = std::move(ptr);
  EXPECT_EQ(stdptr2.use_count(), ptr2.use_count());
  EXPECT_EQ(ptr2.use_count(), 1);
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 0);
}

TEST(TestWeakPtr, TestWeakPtrCaseConstructor) {
  std::weak_ptr<int> stdweakptr;
  WeakPtr<int> weakptr;
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());

  std::shared_ptr<int> stdptr = std::make_shared<int>(1);
  SharedPtr<int> ptr = SharedPtr<int>(new int(1));
  {
    stdweakptr = stdptr;
    weakptr = ptr;

    std::shared_ptr<int> stdptr2 = stdptr;
    SharedPtr<int> ptr2 = ptr;
    EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
    EXPECT_EQ(weakptr.use_count(), 2);
  }
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 1);
}

TEST(TestWeakPtr, TestWeakPtrCaseCopyConstructor) {
  std::weak_ptr<int> stdweakptr;
  WeakPtr<int> weakptr;
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());

  std::shared_ptr<int> stdptr = std::make_shared<int>(1);
  SharedPtr<int> ptr = SharedPtr<int>(new int(1));
  {
    stdweakptr = stdptr;
    weakptr = ptr;

    std::weak_ptr<int> stdweakptr2 = stdweakptr;
    WeakPtr<int> weakptr2 = weakptr;
    EXPECT_EQ(stdweakptr2.use_count(), weakptr2.use_count());
    EXPECT_EQ(weakptr2.use_count(), 1);
    EXPECT_EQ(weakptr.use_count(), 1);
  }
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 1);
}

TEST(TestWeakPtr, TestWeakPtrCaseAssignmentOperator) {
  std::weak_ptr<int> stdweakptr;
  WeakPtr<int> weakptr;
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());

  std::shared_ptr<int> stdptr = std::make_shared<int>(1);
  SharedPtr<int> ptr = SharedPtr<int>(new int(1));
  {
    stdweakptr = stdptr;
    weakptr = ptr;

    std::weak_ptr<int> stdweakptr2;
    WeakPtr<int> weakptr2;
    stdweakptr2 = stdweakptr;
    weakptr2 = weakptr;
    EXPECT_EQ(stdweakptr2.use_count(), weakptr2.use_count());
    EXPECT_EQ(weakptr2.use_count(), 1);
    EXPECT_EQ(weakptr.use_count(), 1);
  }
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 1);
}

TEST(TestWeakPtr, TestWeakPtrCaseReset) {
  std::weak_ptr<int> stdweakptr;
  WeakPtr<int> weakptr;
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());

  std::shared_ptr<int> stdptr = std::make_shared<int>(1);
  SharedPtr<int> ptr = SharedPtr<int>(new int(1));
  {
    stdweakptr = stdptr;
    weakptr = ptr;

    std::weak_ptr<int> stdweakptr2;
    WeakPtr<int> weakptr2;
    stdweakptr2 = stdweakptr;
    weakptr2 = weakptr;

    EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
    EXPECT_EQ(stdweakptr2.use_count(), weakptr2.use_count());
    stdweakptr2.reset();
    weakptr2.reset();
    EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
    EXPECT_EQ(stdweakptr2.use_count(), weakptr2.use_count());
    EXPECT_EQ(weakptr2.use_count(), 0);
    EXPECT_EQ(weakptr.use_count(), 1);
  }
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 1);
}

TEST(TestWeakPtr, TestWeakPtrCaseLock) {
  std::weak_ptr<int> stdweakptr;
  WeakPtr<int> weakptr;
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());

  {
    std::shared_ptr<int> stdptr = std::make_shared<int>(1);
    SharedPtr<int> ptr = SharedPtr<int>(new int(1));

    stdweakptr = stdptr;
    weakptr = ptr;

    std::shared_ptr<int> stdptr2 = stdweakptr.lock();
    SharedPtr<int> ptr2 = weakptr.lock();
    EXPECT_TRUE(stdptr2.get());
    EXPECT_TRUE(ptr2.get());
    EXPECT_EQ(stdptr2.use_count(), ptr2.use_count());
    EXPECT_TRUE(ptr2.use_count() == 2);

    std::shared_ptr<int> stdptr3;
    SharedPtr<int> ptr3;
    {
      stdptr3 = stdweakptr.lock();
      ptr3 = weakptr.lock();
      EXPECT_TRUE(stdptr3.get());
      EXPECT_TRUE(ptr3.get());
      EXPECT_EQ(stdptr3.use_count(), ptr3.use_count());
      EXPECT_TRUE(ptr3.use_count() == 3);
    }
  }
  EXPECT_TRUE(stdweakptr.lock().get() == nullptr);
  EXPECT_TRUE(weakptr.lock().get() == nullptr);

  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 0);
}

TEST(TestWeakPtr, TestWeakPtrCaseMoveConstructor) {
  std::weak_ptr<int> stdweakptr = std::make_shared<int>(1);
  WeakPtr<int> weakptr = SharedPtr<int>(new int(1));
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 0);
  std::weak_ptr<int> stdweakptr2 = std::move(stdweakptr);
  WeakPtr<int> weakptr2 = std::move(weakptr);
  EXPECT_EQ(stdweakptr2.use_count(), weakptr2.use_count());
  EXPECT_EQ(weakptr2.use_count(), 0);
  EXPECT_EQ(weakptr.use_count(), 0);

  EXPECT_EQ(stdweakptr2.lock().get(), nullptr);
  EXPECT_EQ(weakptr2.lock().get(), nullptr);
}

TEST(TestWeakPtr, TestWeakPtrCaseMoveAssignmentOperator) {
  std::weak_ptr<int> stdweakptr = std::make_shared<int>(1);
  WeakPtr<int> weakptr = SharedPtr<int>(new int(1));
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 0);

  std::weak_ptr<int> stdweakptr2;
  WeakPtr<int> weakptr2;
  stdweakptr2 = std::move(stdweakptr);
  weakptr2 = std::move(weakptr);
  EXPECT_EQ(stdweakptr2.use_count(), weakptr2.use_count());
  EXPECT_EQ(weakptr2.use_count(), 0);
  EXPECT_EQ(weakptr.use_count(), 0);

  EXPECT_EQ(stdweakptr2.lock().get(), nullptr);
  EXPECT_EQ(weakptr2.lock().get(), nullptr);
}

class TestSmartPtr : public RefCount<TestSmartPtr> {
public:
  TestSmartPtr() {}
  ~TestSmartPtr() {}

private:
  friend class RefCount<TestSmartPtr>;
};

TEST(TestScopeRefPtr, TestScopeRefPtrCaseConstructor) {
  std::shared_ptr<TestSmartPtr> stdptr = nullptr;
  ScopeRefPtr<TestSmartPtr> ptr(nullptr);
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 0);
}

TEST(TestScopeRefPtr, TestScopeRefPtrCaseCopyOperator) {
  std::shared_ptr<TestSmartPtr> stdptr = std::make_shared<TestSmartPtr>();
  ScopeRefPtr<TestSmartPtr> ptr(new TestSmartPtr());
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  {
    std::shared_ptr<TestSmartPtr> stdptr2 = stdptr;
    ScopeRefPtr<TestSmartPtr> ptr2 = ptr;
    EXPECT_EQ(stdptr.use_count(), ptr2.use_count());
    EXPECT_EQ(ptr.use_count(), 2);
  }
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 1);
}

TEST(TestScopeRefPtr, TestScopeRefPtrCaseAssignmentOperator) {
  std::shared_ptr<TestSmartPtr> stdptr;
  ScopeRefPtr<TestSmartPtr> ptr;
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  {
    stdptr = std::make_shared<TestSmartPtr>();
    ptr = ScopeRefPtr<TestSmartPtr>(new TestSmartPtr());
    EXPECT_EQ(stdptr.use_count(), ptr.use_count());
    EXPECT_EQ(ptr.use_count(), 1);
  }
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 1);
}

TEST(TestScopeRefPtr, TestScopeRefPtrCaseReset) {
  std::shared_ptr<TestSmartPtr> stdptr = std::make_shared<TestSmartPtr>();
  ScopeRefPtr<TestSmartPtr> ptr(new TestSmartPtr());
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  {
    std::shared_ptr<TestSmartPtr> stdptr2 = stdptr;
    ScopeRefPtr<TestSmartPtr> ptr2 = ptr;
    EXPECT_EQ(stdptr.use_count(), ptr2.use_count());
    EXPECT_EQ(ptr.use_count(), 2);
    stdptr.reset();
    ptr.reset();
    EXPECT_EQ(stdptr2.use_count(), ptr2.use_count());
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(stdptr.use_count(), ptr.use_count());
    EXPECT_EQ(ptr.use_count(), 0);
  }
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 0);
}

TEST(TestScopeRefPtr, TestScopeRefPtrCaseMoveConstructor) {
  std::shared_ptr<TestSmartPtr> stdptr = std::make_shared<TestSmartPtr>();
  ScopeRefPtr<TestSmartPtr> ptr(new TestSmartPtr());
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 1);
  std::shared_ptr<TestSmartPtr> stdptr2 = std::move(stdptr);
  ScopeRefPtr<TestSmartPtr> ptr2 = std::move(ptr);
  EXPECT_EQ(stdptr2.use_count(), ptr2.use_count());
  EXPECT_EQ(ptr2.use_count(), 1);
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 0);
}

TEST(TestScopeRefPtr, TestScopeRefPtrCaseMoveAssignmentOperator) {
  std::shared_ptr<TestSmartPtr> stdptr = std::make_shared<TestSmartPtr>();
  ScopeRefPtr<TestSmartPtr> ptr(new TestSmartPtr());
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 1);
  std::shared_ptr<TestSmartPtr> stdptr2;
  ScopeRefPtr<TestSmartPtr> ptr2;
  stdptr2 = std::move(stdptr);
  ptr2 = std::move(ptr);
  EXPECT_EQ(stdptr2.use_count(), ptr2.use_count());
  EXPECT_EQ(ptr2.use_count(), 1);
  EXPECT_EQ(stdptr.use_count(), ptr.use_count());
  EXPECT_EQ(ptr.use_count(), 0);
}

class Test2 {
public:
  Test2() {}
  ~Test2() {}

  base::WeakPtr<Test2> GetWeakPtr() {
    return weak_ptr_factory_.GetWeakPtr();
  }

private:
  base::WeakPtrFactory<Test2> weak_ptr_factory_{this};
};

TEST(TestWeakPtrFactory, TestWeakPtrFactoryCaseConstructor) {
  base::WeakPtr<Test2> weakptr;
  EXPECT_EQ(weakptr.use_count(), 0);

  std::shared_ptr<Test2> stdptr = std::make_shared<Test2>();
  {
    weakptr = stdptr->GetWeakPtr();

    base::WeakPtr<Test2> ptr2 = stdptr->GetWeakPtr();
    EXPECT_EQ(weakptr.use_count(), 3);
  }
  EXPECT_EQ(weakptr.use_count(), 2);
}

TEST(TestWeakPtrFactory, TestWeakPtrFactoryCaseCopyConstructor) {
  base::WeakPtr<Test2> weakptr;
  EXPECT_EQ(weakptr.use_count(), 0);

  std::shared_ptr<Test2> stdptr = std::make_shared<Test2>();
  {
    weakptr = stdptr->GetWeakPtr();

    base::WeakPtr<Test2> weakptr2 = weakptr;
    EXPECT_EQ(weakptr2.use_count(), 3);
    EXPECT_EQ(weakptr.use_count(), 3);
  }
  EXPECT_EQ(weakptr.use_count(), 2);
}

TEST(TestWeakPtrFactory, TestWeakPtrFactoryCaseAssignmentOperator) {
  base::WeakPtr<Test2> weakptr;
  EXPECT_EQ(weakptr.use_count(), 0);

  std::shared_ptr<Test2> stdptr = std::make_shared<Test2>();
  {
    weakptr = stdptr->GetWeakPtr();

    base::WeakPtr<Test2> weakptr2 = stdptr->GetWeakPtr();
    weakptr2 = weakptr;
    EXPECT_EQ(weakptr2.use_count(), 3);
    EXPECT_EQ(weakptr.use_count(), 3);
  }
  EXPECT_EQ(weakptr.use_count(), 2);
}

TEST(TestWeakPtrFactory, TestWeakPtrFactoryCaseReset) {
  base::WeakPtr<Test2> weakptr;
  EXPECT_EQ(weakptr.use_count(), 0);

  std::shared_ptr<Test2> stdptr = std::make_shared<Test2>();
  {
    weakptr = stdptr->GetWeakPtr();

    base::WeakPtr<Test2> weakptr2;
    weakptr2 = weakptr;

    EXPECT_EQ(weakptr.use_count(), 3);
    weakptr2.reset();
    EXPECT_EQ(weakptr.use_count(), 2);
    EXPECT_EQ(weakptr2.use_count(), 0);
  }
  EXPECT_EQ(weakptr.use_count(), 2);
}

TEST(TestWeakPtrFactory, TestWeakPtrFactoryCaseLock) {
  std::weak_ptr<Test2> stdweakptr;
  base::WeakPtr<Test2> weakptr;
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());

  {
    std::shared_ptr<Test2> stdptr = std::make_shared<Test2>();

    stdweakptr = stdptr;
    weakptr = stdptr->GetWeakPtr();

    std::shared_ptr<Test2> stdptr2 = stdweakptr.lock();
    EXPECT_TRUE(stdptr2.get());
    EXPECT_TRUE(weakptr.get());
    EXPECT_TRUE(weakptr.use_count() == 2);

    std::shared_ptr<Test2> stdptr3;
    {
      stdptr3 = stdweakptr.lock();
      EXPECT_TRUE(stdptr3.get());
      EXPECT_TRUE(weakptr.get());
      EXPECT_EQ(weakptr.use_count(), 2);
      EXPECT_TRUE(weakptr.use_count() == 2);
    }
  }
  EXPECT_TRUE(stdweakptr.lock().get() == nullptr);
  EXPECT_TRUE(weakptr.get() == nullptr);

  EXPECT_EQ(weakptr.use_count(), 1);
}

TEST(TestWeakPtrFactory, TestWeakPtrFactoryCaseMoveConstructor) {
  std::weak_ptr<Test2> stdweakptr = std::make_shared<Test2>();
  auto stdsharedptr = stdweakptr.lock();
  base::WeakPtr<Test2> weakptr = stdsharedptr ? stdsharedptr->GetWeakPtr() : base::WeakPtr<Test2>();
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 0);
  std::weak_ptr<Test2> stdweakptr2 = std::move(stdweakptr);
  base::WeakPtr<Test2> weakptr2 = std::move(weakptr);
  EXPECT_EQ(stdweakptr2.use_count(), weakptr2.use_count());
  EXPECT_EQ(weakptr2.use_count(), 0);
  EXPECT_EQ(weakptr.use_count(), 0);

  EXPECT_EQ(stdweakptr2.lock().get(), nullptr);
  EXPECT_EQ(weakptr2.get(), nullptr);
}

TEST(TestWeakPtrFactory, TestWeakPtrFactoryCaseMoveAssignmentOperator) {
  std::weak_ptr<Test2> stdweakptr = std::make_shared<Test2>();
  auto stdsharedptr = stdweakptr.lock();
  base::WeakPtr<Test2> weakptr = stdsharedptr ? stdsharedptr->GetWeakPtr() : base::WeakPtr<Test2>();
  EXPECT_EQ(stdweakptr.use_count(), weakptr.use_count());
  EXPECT_EQ(weakptr.use_count(), 0);

  std::weak_ptr<Test2> stdweakptr2;
  base::WeakPtr<Test2> weakptr2;
  stdweakptr2 = std::move(stdweakptr);
  weakptr2 = std::move(weakptr);
  EXPECT_EQ(stdweakptr2.use_count(), weakptr2.use_count());
  EXPECT_EQ(weakptr2.use_count(), 0);
  EXPECT_EQ(weakptr.use_count(), 0);

  EXPECT_EQ(stdweakptr2.lock().get(), nullptr);
  EXPECT_EQ(weakptr2.get(), nullptr);
}