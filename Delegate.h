#ifndef DELEGATE_H
#define DELEGATE_H

#include <utility>
#include <type_traits>
#include "InvocationForm.h"

namespace Delegates {

	template<typename T> class Delegate;

	template<typename RetType, typename ...Args>
	class Delegate<RetType(Args...)> final {

	public:

		Delegate() = default;

		// Copying constructor
		Delegate(const Delegate& del) {
			this->invocation = del.invocation;
		}

		template<typename LambdaFun>
		Delegate(std::shared_ptr<LambdaFun>& lambda) {
			assign(lambda, functorCaller<LambdaFun>);
		}

		bool operator==(const Delegate& elem) const {
			return invocation == elem.invocation;
		}

		bool operator!=(const Delegate& elem) const {
			return invocation != elem.invocation;
		}

		explicit operator bool() const {
			return !isNull();
		}

		bool operator!() const {
			return isNull();
		}

		Delegate& operator=(const Delegate& elem) {
			invocation = elem.invocation;
			return *this;
		}

		template<typename LambdaFun>
		Delegate& operator=(std::shared_ptr<LambdaFun> lambda) {
			assign(lambda, functorCaller<LambdaFun>);
			return *this;
		}

		template<typename LambdaFun>
		Delegate& operator=(const LambdaFun& lambda) {
			assign(std::make_shared<LambdaFun>(lambda), functorCaller<LambdaFun>);
			return *this;
		}

		bool isNull() const {
			return invocation.getInvocationFun() == nullptr;
		}

		template <class T, RetType(T::*TMethod)(Args...)>
		static Delegate create(std::shared_ptr<T> elem) {
			return Delegate(elem, memberCaller<T, TMethod>);
		}	

		template <RetType(*TMethod)(Args...)>
		static Delegate create() {
			return Delegate(nullptr, functionCaller<TMethod>);
		} 

		template <typename LambdaFun>
		static Delegate create(std::shared_ptr<LambdaFun> lambda) {
			return Delegate(lambda, &functorCaller<LambdaFun>);
		}

		static Delegate create(Delegate<RetType(Args...)> del) {
			return Delegate(del);
		}

		RetType operator()(Args... arg) const {
			return (*invocation.getInvocationFun())(invocation.getObject(), arg...);
		}		

	private:

		Delegates::InvocationForm<RetType(Args...)> invocation;

		Delegate(std::shared_ptr<void> object, 
			typename InvocationForm<RetType(Args...)>::invocationType fun) : 
			invocation(object, fun) {};

		void assign(std::shared_ptr<void> object, 
			typename InvocationForm<RetType(Args...)>::invocationType fun) {

			InvocationForm<RetType(Args...)> temp(object, fun);
			invocation = temp;
		}

		template<class T, RetType(T::*TMethod)(Args...)>
		static RetType memberCaller(std::shared_ptr<void> obj, Args... args) {
			return (static_cast<T*>(obj.get())->*TMethod)(args...);
		}

		template<typename LambdaFun>
		static RetType functorCaller(std::shared_ptr<void> lambda, Args... args) {
			return (*static_cast<LambdaFun*>(lambda.get()))(args...);
		}

		template<RetType(*function)(Args...)>
		static RetType functionCaller(std::shared_ptr<void>, Args... args) {
			return function(args...);
		}
	};
}

#endif // !DELEGATE_H
