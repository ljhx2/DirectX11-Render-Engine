#pragma once

#ifndef _MESSAGE_MGR_H_
#define _MESSAGE_MGR_H_

#include <queue>
#include <deque>
#include <functional>

#include "..\..\Core\Singleton.h"
#include "Message.h"

#define g_pMessageMgr CMessageMgr::GetInstance()

const DWORD MSG_NO_DELAY = 0UL;

class CMessageMgr : public CSingleton<CMessageMgr>
{

public:
	void				DispatchDelayedMessage();
	void				SendMSG(DWORD delayTime, UINT senderUID, UINT receiverUID, eMessageType msgType, CMessageArg& arg);

private:
	void				SendMessageNoDelay(const CMessage& msg);

public:
	CMessageMgr();
	virtual ~CMessageMgr();

private:
	std::priority_queue<CMessage, std::deque<CMessage>, std::greater<CMessage>> m_msgQue;

};

#endif // !_MESSAGE_MGR_H_