#include "LightManager.h"


CLightManager::CLightManager()
{
	
}


CLightManager::~CLightManager()
{
}

void CLightManager::EraseDirectionalLight(CDirectionalLightComponent* dir)
{
	std::vector<CDirectionalLightComponent*>::iterator iter;
	for (iter = m_vecDir.begin(); iter != m_vecDir.end();)
	{
		if ((*iter) == dir)
		{
			iter = m_vecDir.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CLightManager::ErasePointLight(CPointLightComponent* point)
{
	std::vector<CPointLightComponent*>::iterator iter;
	for (iter = m_vecPoint.begin(); iter != m_vecPoint.end();)
	{
		if ((*iter) == point)
		{
			iter = m_vecPoint.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CLightManager::EraseSpotLight(CSpotLightComponent* spot)
{
	std::vector<CSpotLightComponent*>::iterator iter;
	for (iter = m_vecSpot.begin(); iter != m_vecSpot.end();)
	{
		if ((*iter) == spot)
		{
			iter = m_vecSpot.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}