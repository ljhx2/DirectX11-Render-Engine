#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include <list>

#include "..\GameObject\GameObject.h"
#include "Grid.h"
#include "..\GameObject\Component\CameraComponent\ToolCameraComponent.h"

typedef std::wstring				SCENE_ID_T;



class CScene
{
public:
	virtual void						Load(const std::wstring& fileName) {}
	virtual void						Unload() {}

	virtual bool						OnEnter() { return Setup(); }
	virtual void						OnLeave() { AllNodeDelete(); }

public:
	bool								Setup();
	void								Update(float deltaTime);
	void								ShadowBuild();
	void								Render();

public:
	inline const SCENE_ID_T&			GetSceneID() const { return m_id; }
	inline void							SetSceneID(const SCENE_ID_T& id) { m_id = id; }

	inline CGameObject*					GetSceneRoot()	{ return m_sceneRoot; }

	inline CCameraComponent*			GetMainCamera() { return m_mainCameraComp; }

	inline CGameObject*					GetGlobalLight() { return m_globalLight; }
	inline void							SetGlobalLight(CGameObject* light) { m_globalLight = light; }

	void								AddSceneNode(CGameObject* obj);
	void								DeleteSceneNode(CGameObject* obj);
	void								AllNodeDelete();

public:
	CScene();
	virtual ~CScene();

protected:
	SCENE_ID_T							m_id;

	CGameObject*						m_sceneRoot;		


	CGameObject*						m_mainCamera;
	CCameraComponent*					m_mainCameraComp;
	CGameObject*						m_globalLight;
	CGrid*								m_grid;
};

#endif // !_SCENE_H_