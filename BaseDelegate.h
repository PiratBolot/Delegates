#ifndef BASE_DELEGATE_H
#define BASE_DELEGATE_H

#include<memory>
#include <utility>

namespace Delegates {

    template<typename T>
    class BaseDelegate;

    template<typename RetType, typename ...Args>
    class BaseDelegate<RetType(Args...)> {

    public:

        // Function signature
        using invocationType = RetType(*)(std::shared_ptr<void>, Args...);

        BaseDelegate() : object(nullptr), invocationFun(nullptr) {};

        BaseDelegate(std::shared_ptr<void> object, invocationType fun) :
                object(std::move(object)), invocationFun(fun) {};

        void clone(BaseDelegate& dest) const {
            dest = *this;
        }

        bool operator==(const BaseDelegate& elem) const {
            return this->object == elem.object &&
                   this->invocationFun == elem.invocationFun;
        }

        bool operator!=(const BaseDelegate& elem) const {
            return !this->operator==(elem);
        }

        BaseDelegate& operator=(const BaseDelegate& elem) {
            if (this == &elem) {
                return *this;
            }
            object = elem.object;
            invocationFun = elem.invocationFun;
            return *this;
        }

        std::shared_ptr<void> getObject() const {
            return object;
        }

        invocationType getInvocationFun() const {
            return invocationFun;
        }

    private:
        std::shared_ptr<void> object;
        invocationType invocationFun;
    };
}

#endif //BASE_DELEGATE_H
