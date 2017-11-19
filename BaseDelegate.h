#ifndef STORAGE_DELEGATE_H
#define STORAGE_DELEGATE_H

#include<memory>

namespace Delegates {
																				
	template<typename T>
	class Storage;

	template<typename RetType, typename ...Args>
	class Storage<RetType(Args...)> {

	public:

		// Function signature
		using invocationType = RetType(*)(std::shared_ptr<void>, Args...);		
			
		Storage() : object(nullptr), invocationFun(nullptr) {};

		Storage(std::shared_ptr<void> object, invocationType fun) :
			object(object), invocationFun(fun) {};

		void clone(Storage& dest) const {
			dest = *this;
		}

		bool operator==(const Storage& elem) const {
			return this->object == elem.object && 
				this->invocationFun == elem.invocationFun;
		}

		bool operator!=(const Storage& elem) const {
			return !this->operator==(this, elem);
		}

		Storage& operator=(const Storage& elem) {
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
