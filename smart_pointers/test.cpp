#include "pch.h"
#include "D:/test/C++/shared_ptr.h"
#include "D:/test/C++/weak_ptr.h"

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