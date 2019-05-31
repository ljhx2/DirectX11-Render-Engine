#pragma once

#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

#include "..\..\..\Core\Singleton.h"

#include "CameraComponent.h"


#define g_pCameraMgr CCameraManager::GetInstance()

class CCameraManager : public CSingleton<CCameraManager>
{
public:
	CCameraComponent*			GetCurrentCamera() { return m_currentCamera; }
	void						ChangeCamera(CCameraComponent* camera) { m_currentCamera = camera; }

public:
	CCameraManager();
	~CCameraManager();

private:
	CCameraComponent*	m_currentCamera;

};

#endif // !_CAMERA_MANAGER_H_
