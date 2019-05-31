#include "Message.h"


CMessage::CMessage()
	: m_dispatchTime(0UL), m_senderUID(0U), m_receiverUID(0U), m_type(MSG_TYPE_NONE)
{
}


CMessage::~CMessage()
{
}

