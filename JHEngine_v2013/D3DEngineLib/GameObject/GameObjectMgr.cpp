#include "..\Common.h"
#include "GameObjectMgr.h"


CGameObjectMgr::CGameObjectMgr()
{
}


CGameObjectMgr::~CGameObjectMgr()
{
	DestroyAllGameObjects();
}

void CGameObjectMgr::ProcessWaitingGameObjects()
{
	if (m_WaitingGameObjects.empty())
	{
		return;
	}

	GAMEOBJ_MAP_T::iterator iter;
	for (iter = m_WaitingGameObjects.begin(); iter != m_WaitingGameObjects.end(); ++iter)
	{
		m_GameObjects.insert(*iter);
	}

	m_WaitingGameObjects.clear();
}

void CGameObjectMgr::DestroyAllGameObjects()
{
	for (auto iter : m_WaitingGameObjects)
	{
		SAFE_DELETE(iter.second);
	}
	m_WaitingGameObjects.clear();
	for (auto iter : m_GameObjects)
	{
		SAFE_DELETE(iter.second);
	}
	m_GameObjects.clear();
}

bool CGameObjectMgr::isUniqueUID(GAMEOBJ_UID_T UID)
{
	if (m_GameObjects.find(UID) != m_GameObjects.end())
	{
		return false;
	}

	if (m_WaitingGameObjects.find(UID) != m_WaitingGameObjects.end())
	{
		return false;
	}

	return true;
}
					
GAMEOBJ_UID_T CGameObjectMgr::GenUID()
{
	static GAMEOBJ_UID_T UID = 0U;

	GAMEOBJ_UID_T prevUID = UID;

	do
	{
		++UID;

		if (UID == 0U)
		{
			UID = 1U;
		}

		if (UID == prevUID)
		{
			assert(false && "UID has been full");
		}

	} while (!(isUniqueUID(UID)));

	assert(UID && "UID is 0");

	return UID;
}

CGameObject* CGameObjectMgr::GetGameObjectByUID(const GAMEOBJ_UID_T& id) 
{
	GAMEOBJ_MAP_T::iterator iter = m_GameObjects.find(id);

	if (iter == m_GameObjects.end())
	{
		return NULL;
	}

	return iter->second;
}

CGameObject* CGameObjectMgr::GetGameObjectByID(const GAMEOBJ_ID_T& id)
{
	GAMEOBJ_MAP_T::iterator iter;
	for (iter = m_GameObjects.begin(); iter != m_GameObjects.end(); ++iter)
	{
		if (iter->second->GetID() == id)
		{
			return iter->second;
		}
	}

	return NULL;
}
			
void CGameObjectMgr::AddObject(CGameObject* obj)
{
	m_GameObjects.insert(std::make_pair(obj->GetUID(), obj));
}

void CGameObjectMgr::AddWaitingObject(CGameObject* obj)
{
	m_WaitingGameObjects.insert(std::make_pair(obj->GetUID(), obj));
}

void CGameObjectMgr::EraseObjct(CGameObject* obj)
{
	GAMEOBJ_MAP_T::iterator iter = m_GameObjects.find(obj->GetUID());

	if (iter != m_GameObjects.end())
	{
		m_GameObjects.erase(iter);
	}
}

void CGameObjectMgr::SendMessageToAll(const CMessage& msg)
{
	GAMEOBJ_MAP_T::iterator iter;
	for (iter = m_GameObjects.begin(); iter != m_GameObjects.end(); ++iter)
	{
		if (iter->second->HandleMessage(msg))
		{
			break;
		}
	}
}