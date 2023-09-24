#ifndef Singleton_HPP
#define Singleton_HPP

#include <stdexcept>

template <typename T>
class Singleton
{
public:
	static T *getInstance() {
		if (Singleton<T>::instance == NULL) Singleton<T>::instance = new T();
		return Singleton<T>::instance;
	};
	static void deleteInstance() {
		if (Singleton<T>::instance != NULL) delete Singleton<T>::instance;
		Singleton<T>::instance = NULL;
	};
	
private:
	Singleton() {};
	Singleton(const Singleton &rhs) { (void)rhs; };
	Singleton &operator=(const Singleton &rhs) { return rhs; };
	~Singleton() {};
	static T *instance;
};

template <typename T>
T *Singleton<T>::instance = NULL;

#endif