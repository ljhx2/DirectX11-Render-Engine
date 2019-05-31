#pragma once

#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <vector>

#include "..\..\..\Core\Singleton.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "SpotLightComponent.h"

#define g_pLightMgr CLightManager::GetInstance()

class CLightManager : public CSingleton<CLightManager>
{
public:
	int								GetDirectionalLightSize()	{ return m_vecDir.size(); }
	int								GetPointLightSize()			{ return m_vecPoint.size(); }
	int								GetSpotLightSize()			{ return m_vecSpot.size(); }

	std::vector<CDirectionalLightComponent*>& GetVecDirectionalLight()	{ return m_vecDir; }
	CPointLightComponent*			GetPointLight(int index)		{ return m_vecPoint[index]; }
	CSpotLightComponent*			GetSpotLight(int index)			{ return m_vecSpot[index]; }

public:
	void		AddDirectionalLight(CDirectionalLightComponent* dir)	{ m_vecDir.push_back(dir); }
	void		AddPointLight(CPointLightComponent* point)	{ m_vecPoint.push_back(point); }
	void		AddSpotLight(CSpotLightComponent* spot)	{ m_vecSpot.push_back(spot); }
	
	void		EraseDirectionalLight(CDirectionalLightComponent* dir);
	void		ErasePointLight(CPointLightComponent* point);
	void		EraseSpotLight(CSpotLightComponent* spot);
public:
	CLightManager();
	~CLightManager();

private:
	std::vector<CDirectionalLightComponent*>	m_vecDir;
	std::vector<CPointLightComponent*>			m_vecPoint;
	std::vector<CSpotLightComponent*>			m_vecSpot;
};

#endif // !_LIGHT_MANAGER_H_
