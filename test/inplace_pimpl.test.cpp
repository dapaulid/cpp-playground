#include <gtest/gtest.h>

#include "inplace_pimpl.test.h"

struct MyClass::Impl {
  int foo = 122;
};

int MyClass::add_foo(int x) {
	m_pimpl->foo += x;
	return m_pimpl->foo;
}

TEST(inplace_pimpl, Good) {
  MyClass foo;

  EXPECT_EQ(123, foo.add_foo(1));
}