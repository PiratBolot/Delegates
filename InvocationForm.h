#ifndef STORAGE_DELEGATE_H
#define STORAGE_DELEGATE_H

#include<memory>

namespace Delegates {
																				
	template<typename T>
	class InvocationForm;

	template<typename RetType, typename ...Args>
	class InvocationForm<RetType(Args...)> {

	public:

		// Function signature
		using invocationType = RetType(*)(std::shared_ptr<void>, Args...);		
			
		InvocationForm() : object(nullptr), invocationFun(nullptr) {};

		InvocationForm(std::shared_ptr<void> object, invocationType fun) :
			object(object), invocationFun(fun) {};

		void clone(InvocationForm& dest) const {
			dest = *this;
		}

		bool operator==(const InvocationForm& elem) const {
			return this->object == elem.object && 
				this->invocationFun == elem.invocationFun;
		}

		bool operator!=(const InvocationForm& elem) const {
			return !this->operator==(this, elem);
		}

		InvocationForm& operator=(const InvocationForm& elem) {
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

#endif // !STORAGE_DELEGATE_H
