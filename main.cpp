#include<iostream>
#include<memory>
#include"Delegate.h"

struct A {
public:
    A() : ptr(nullptr) {};

    int Foo() { return 12; }

    std::shared_ptr<void> ptr;
};

class B : public A {

};

int Foo1() { return 13; }

int main() {
    const A a;
    A b;
    B c;
    auto ptr = [](int) -> void {
        std::cout << "Lambda function" << std::endl;
    };
    Delegates::Delegate<void(int)> t;
    t = ptr;
    t(12);

    Delegates::Delegate<int(void)> v;
    v.create<A, &A::Foo>(std::make_shared<A>(c));
    Delegates::Delegate<int(void)> d(Delegates::Delegate<int(void)>::create<A, &A::Foo>(std::make_shared<A>(c)));

    if (d) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    if (!v) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }
    return 0;
}