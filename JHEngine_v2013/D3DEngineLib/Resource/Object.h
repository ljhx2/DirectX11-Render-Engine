#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_




class cObject
{
public:
	virtual void	AddRef();
	virtual void	Release();
	inline int		GetRefCnt()			{ return m_nRefCnt; }

public:
	cObject();
	virtual ~cObject();

private:
	int m_nRefCnt;
};

#endif // !_OBJECT_H_