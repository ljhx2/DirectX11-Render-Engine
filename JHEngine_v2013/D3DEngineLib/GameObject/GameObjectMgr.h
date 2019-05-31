#pragma once

#ifndef _GAMEOBJECT_MGR_H_
#define _GAMEOBJECT_MGR_H_


#include "..\Core\Singleton.h"
#include "GameObject.h"


#define g_pGameObjectMgr CGameObjectMgr::GetInstance()

typedef std::unordered_map<GAMEOBJ_UID_T, CGameObject*>	GAMEOBJ_MAP_T;


class CGameObjectMgr : public CSingleton<CGameObjectMgr>
{
public:
	void				ProcessWaitingGameObjects();
	void				DestroyAllGameObjects();

	bool				isUniqueUID(GAMEOBJ_UID_T UID);

	GAMEOBJ_UID_T		GenUID();

public:
	CGameObject*		GetGameObjectByUID(const GAMEOBJ_UID_T& id);
	CGameObject*		GetGameObjectByID(const GAMEOBJ_ID_T& id);

	void				AddObject(CGameObject* obj);
	void				AddWaitingObject(CGameObject* obj);

	void				EraseObjct(CGameObject* obj);

public:	//MessageMgr에서 사용
	void				SendMessageToAll(const CMessage& msg);

public:
	CGameObjectMgr();
	~CGameObjectMgr();

private:
	GAMEOBJ_MAP_T		m_GameObjects;
	GAMEOBJ_MAP_T		m_WaitingGameObjects;

};

#endif	// _GAMEOBJECT_MGR_H_