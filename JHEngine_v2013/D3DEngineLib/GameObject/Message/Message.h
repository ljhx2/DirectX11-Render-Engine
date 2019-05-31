#pragma once

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "MessageArg.h"

enum eMessageType
{
	MSG_TYPE_NONE = 0,

};

//const UINT MAX_MSG_ARG_COUNT = 2;

class CMessage
{
public:
	inline DWORD		GetDispatchTime() const			{ return m_dispatchTime; }
	inline UINT			GetSenderUID() const			{ return m_senderUID; }
	inline UINT			GetReceiverUID() const			{ return m_receiverUID; }
	inline eMessageType GetMessageType() const			{ return m_type; }
	inline CMessageArg	GetMessageArg() const			{ return m_arg; }
	//inline CMessageArg  GetMessageArg(UINT index) const 
	//{ 
	//	if (index >= MAX_MSG_ARG_COUNT)
	//	{
	//		assert(false && "MSG_ARG_INDEX is OverFlow");
	//	}
	//	return m_args[index]; 
	//}

	inline void			SetDispatchTime(DWORD currTime)		{ m_dispatchTime = currTime; }
	inline void			SetSenderUID(UINT senderUID)		{ m_senderUID = senderUID; }
	inline void			SetReceiverUID(UINT receiverUID)	{ m_receiverUID = receiverUID; }
	inline void			SetMessageType(eMessageType type)	{ m_type = type; }
	//inline void			SetMeesageArg(UINT index, CMessageArg& arg)
	//{
	//	if (index >= MAX_MSG_ARG_COUNT)
	//	{
	//		assert(false && "MSG_ARG_INDEX is OverFlow");
	//	}
	//
	//	m_args[index] = arg;
	//}
	inline void			SetMeesageArg(CMessageArg& arg)		{ m_arg = arg; }

public:
	CMessage();
	~CMessage();

	bool operator >(const CMessage& rhs) const
	{
		return m_dispatchTime > rhs.m_dispatchTime;
	}

private:
	DWORD				m_dispatchTime;

	UINT				m_senderUID;
	UINT				m_receiverUID;

	eMessageType		m_type;
	//CMessageArg			m_args[MAX_MSG_ARG_COUNT];
	CMessageArg			m_arg;

};

#endif // !_MESSAGE_H_