#pragma once

#ifndef _SCENE_MGR_H_
#define _SCENE_MGR_H_

#include <unordered_map>

#include "..\Core\Singleton.h"
#include "Scene.h"

#define g_pSceneMgr CSceneMgr::GetInstance()


typedef std::unordered_map<SCENE_ID_T, CScene*>		SCENE_MAP_T;

class CSceneMgr : public CSingleton<CSceneMgr>
{
public:
	void								Update(float deltaTime);
	void								ShadowBuild();
	void								Render();

public:
	bool								ChangeScene(const SCENE_ID_T& id);
	CScene*								GetCurrScene();

	void								AddScene(CScene* scene);
	void								DeleteScene(const SCENE_ID_T& id);

public:
	CSceneMgr();
	~CSceneMgr();

private:
	SCENE_MAP_T							m_mapScenes;
	CScene*								m_pCurrScene;
};

#endif // !_SCENE_MGR_H_