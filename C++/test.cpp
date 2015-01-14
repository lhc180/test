#include <iostream>
#include <limits.h>

class  Base{
	virtual void f();
};

class Derived : public Base{
	void f() override;
};

int __attribute__((stdcall)) test()
{
	printf("hello\n");
	printf("PATH_MAX: %d\n", PATH_MAX);
}

int main()
{
	test();
	return 0;
}
