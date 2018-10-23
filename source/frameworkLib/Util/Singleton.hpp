#pragma once

namespace KM
{

template <typename T>
class Singleton
{
private:
	Singleton(Singleton const&) {}
	Singleton& operator=(Singleton const&) {}

protected:
	static T* instance;

	Singleton() 
	{
		instance = new T; 
		/*instance = static_cast<T*>(this);*/ 
	}
	virtual ~Singleton() {}

public:
	static T* getInstance();
	static void destroy();

};

template<typename T>
typename T* Singleton<T>::instance = nullptr;

template<typename T>
T* Singleton<T>::getInstance()
{
	if (instance == nullptr)
	{
		Singleton<T>::instance = new T();
	}
	return instance;
}

template<typename T>
void Singleton<T>::destroy()
{
	delete Singleton<T>::instance;
	Singleton<T>::instance = nullptr;
}

}