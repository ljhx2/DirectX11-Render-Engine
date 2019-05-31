#pragma once

#ifndef _MESSAGE_ARG_H_
#define _MESSAGE_ARG_H_

#include <Windows.h>
#include <xnamath.h>

class CMessageArg
{
public:
	enum eType
	{
		TYPE_NONE = 0,

		TYPE_INT,
		TYPE_UINT,
		TYPE_FLOAT,
		TYPE_BOOL,
		TYPE_STRINGA,
		TYPE_STRINGW,
		TYPE_VECTOR3,
	};

public:
	inline eType			GetType() const					{ return m_type; }

	inline INT				AsInt() const					{ return m_asInt; }
	inline UINT				AsUint() const					{ return m_asUint; }
	inline FLOAT			AsFloat() const					{ return m_asFloat; }
	inline BOOL				AsBool() const					{ return m_asBool; }
	inline CHAR*			AsStringA() const				{ return static_cast<CHAR*>(m_asString); }
	inline WCHAR*			AsStringW() const				{ return static_cast<WCHAR*>(m_asString); }
	inline XMFLOAT3			AsVector3() const				{ XMFLOAT3 vec3(m_asVector3); return vec3; }

	inline void				SetAsInt(INT val)				{ m_asInt = val; m_type = TYPE_INT; }
	inline void				SetAsUint(UINT val)				{ m_asUint = val; m_type = TYPE_UINT; }
	inline void				SetAsFloat(FLOAT val)			{ m_asFloat = val; m_type = TYPE_FLOAT; }
	inline void				SetAsBool(BOOL val)				{ m_asBool = val; m_type = TYPE_BOOL; }
	inline void				SetAsStringA(CHAR* val)			{ m_asString = reinterpret_cast<void*>(val); m_type = TYPE_STRINGA; }
	inline void				SetAsStringW(WCHAR* val)		{ m_asString = reinterpret_cast<void*>(val); m_type = TYPE_STRINGW; }
	inline void				SetAsVecotr3(const XMFLOAT3& val)
	{
		m_asVector3[0] = val.x;
		m_asVector3[1] = val.y;
		m_asVector3[2] = val.z;
		m_type = TYPE_VECTOR3;
	}


public:
	CMessageArg();
	~CMessageArg();

private:
	union
	{
		INT			m_asInt;
		UINT		m_asUint;
		FLOAT		m_asFloat;
		BOOL		m_asBool;
		void*		m_asString;
		FLOAT		m_asVector3[3];
	};

	eType		m_type;
};

#endif	//_MESSAGE_ARG_H_