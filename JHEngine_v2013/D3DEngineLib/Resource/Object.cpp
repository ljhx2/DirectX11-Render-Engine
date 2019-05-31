#include "Object.h"


cObject::cObject()
	: m_nRefCnt(0)
{
}


cObject::~cObject()
{
}

void cObject::AddRef()
{
	++m_nRefCnt;
}

void cObject::Release()
{
	--m_nRefCnt;
	if (m_nRefCnt <= 0)
	{
		delete this;
	}
}