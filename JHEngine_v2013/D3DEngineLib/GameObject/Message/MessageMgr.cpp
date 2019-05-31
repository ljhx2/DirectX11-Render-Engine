#include "..\..\Common.h"
#include "MessageMgr.h"

#include "..\..\Core\GameTimer.h"
#include "..\GameObjectMgr.h"

CMessageMgr::CMessageMgr()
{
}


CMessageMgr::~CMessageMgr()
{
}

void CMessageMgr::DispatchDelayedMessage()
{
	DWORD currTIme = g_pGameTimer->CurrentTime();

	while (!m_msgQue.empty())
	{
		CMessage& msg = m_msgQue.top();

		if (msg.GetDispatchTime() > currTIme)
		{
			break;
		}

		if (msg.GetMessageType() == MSG_TYPE_NONE)
		{
			m_msgQue.pop();
			continue;
		}

		SendMessageNoDelay(msg);

		m_msgQue.pop();
	}
}

void CMessageMgr::SendMSG(DWORD delayTime, UINT senderUID, UINT receiverUID, eMessageType msgType, CMessageArg& arg)
{
	DWORD dispatchTime = g_pGameTimer->CurrentTime() + delayTime;
	
	CMessage msg;
	msg.SetDispatchTime(dispatchTime);
	msg.SetSenderUID(senderUID);
	msg.SetReceiverUID(receiverUID);
	msg.SetMessageType(msgType);
	msg.SetMeesageArg(arg);

	if (delayTime == MSG_NO_DELAY)
	{
		SendMessageNoDelay(msg);
	}
	else
	{
		m_msgQue.push(msg);
	}
}
	 
void CMessageMgr::SendMessageNoDelay(const CMessage& msg)
{
	if (msg.GetReceiverUID() != GAMEOBJ_UID_ALL)
	{
		CGameObject* receiver = g_pGameObjectMgr->GetGameObjectByUID(msg.GetReceiverUID());

		if (receiver)
		{
			receiver->HandleMessage(msg);
		}
	}
	else
	{
		g_pGameObjectMgr->SendMessageToAll(msg);
	}

}