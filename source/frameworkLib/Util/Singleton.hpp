#pragma once

namespace framework
{


template <typename T>
class Singleton
{
private:
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

protected:
	static T* instance_;

	Singleton()
	{
		instance_ = new T;
		/*instance_ = static_cast<T*>(this);*/ 	// TODO: doesn't work?
	}
	virtual ~Singleton() { if(instance_) delete instance_; }

public:
	static T* getInstance();
	static void destroy();

};


template<typename T>
T* Singleton<T>::instance_ = nullptr;

template<typename T>
T* Singleton<T>::getInstance()
{
	if (instance_ == nullptr)
	{
		Singleton<T>::instance_ = new T();
	}
	return instance_;
}

template<typename T>
void Singleton<T>::destroy()
{
	delete Singleton<T>::instance_;
	Singleton<T>::instance_ = nullptr;
}

}
