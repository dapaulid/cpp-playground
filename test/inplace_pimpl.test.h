#include "inplace_pimpl.h"
class MyClass {

	public:
		int add_foo(int x);

	private:
		struct Impl;
		ForwardDeclaredStorage<Impl, 16> m_pimpl;
};