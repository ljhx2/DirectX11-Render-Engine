#pragma once

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <cassert>

template<class T>
class CSingleton
{
public:
	static T* GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new T;
		}

		return m_instance;
	}

	static void Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}


protected:
	CSingleton() { assert(!m_instance); }
	virtual ~CSingleton() {}

private:
	CSingleton(const T &rhs) { assert(false); }
	CSingleton& operator =(const CSingleton &rhs) { assert(false;) return *this; }

private:
	static T* m_instance;
};

template<class T>
T *CSingleton<T>::m_instance = 0;

#endif //_SINGLETON_H_