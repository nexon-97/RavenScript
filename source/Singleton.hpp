#pragma once
#include <cassert>

// Templatized singleton pattern implementation

///////////////////////////////////////////////////////////////////////////////

template <class T>
class Singleton
{
public:
	// Simple constructor is used instead of some sort of CreateInstance() method
	Singleton()
	{
		assert(!s_instance);
		s_instance = static_cast<T*>(this);
	}

	static void FreeInstance()
	{
		assert(!!s_instance);
		if (!!s_instance)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}

	static T* GetInstance()
	{
		assert(!!s_instance);
		return s_instance;
	}

	static bool HasInstance()
	{
		return !!s_instance;
	}

protected:
	~Singleton() {}
	Singleton(Singleton& ref) = delete;

	static T* s_instance;
};

template <class T>
T* Singleton<T>::s_instance = nullptr;

///////////////////////////////////////////////////////////////////////////////
