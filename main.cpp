#include <iostream>
#include <mutex>
#include "Delegate.h"

struct SS {
public:
	int foo(int i) {
		std::cout << "Hello foo #" << i << std::endl;		
		return i;
	}

	static int staticFoo(int i) {		
		std::cout << "Hello staticFoo #" << i << std::endl;
		return i;
	}
};

auto lambdaFoo = [](int i) -> int {	
	std::cout << "Hello lambdaFoo #" << i << std::endl;
	return i;
};

int globalFoo(int i) {
	std::cout << "Hello globalFoo #" << i << std::endl;
	return i;
}

int main() {
	SS ss;
	Delegates::Delegate<int(int)> del;
	Delegates::Delegate<int(int)> temp;
	
	// Add a lambda
	del = [](int i) -> int {
		std::cout << "Hello lambda #" << i << std::endl;
		return i;
	};
	del(1);
	del = lambdaFoo;
	del(2);

	// Add a global function
	temp = del.create<globalFoo>();	
	temp(3);
	del(4);
	Delegates::Delegate<int(int)> d(Delegates::Delegate<int(int)>::create<globalFoo>());
	d(5);

	// Add a static class method
	d = &SS::staticFoo;
	d(6);
	
	// Add a non-static class method
	temp = del.create<SS, &SS::foo>(std::make_shared<SS>(ss));
	temp(7);


	system("pause");
	return 0;
}
