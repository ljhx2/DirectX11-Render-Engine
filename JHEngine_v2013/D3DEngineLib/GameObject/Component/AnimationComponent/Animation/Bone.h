#pragma once

#ifndef _CBONE_H_
#define _CBONE_H_

#include <string>
#include <vector>


struct ST_LOCAL_SQT
{
	XMFLOAT3 localScale;
	XMFLOAT3 localPosition;
	XMFLOAT4 localQuternion;
};


class CBone
{
public:
	CBone();
	~CBone();

public:
	std::wstring		m_name;
	XMFLOAT4X4			m_offset;
	XMFLOAT4X4			m_localTransform;
	XMFLOAT4X4			m_globalTransform;
	XMFLOAT4X4			m_originalLocalTransform;

	ST_LOCAL_SQT		m_localSQT;
	
	CBone*				m_parent;
	std::vector<CBone*>	m_children;
};

#endif // !_CBONE_H_