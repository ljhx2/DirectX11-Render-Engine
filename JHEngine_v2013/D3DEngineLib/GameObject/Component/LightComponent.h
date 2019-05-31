#pragma once

#ifndef _LIGHT_COMPONENT_H_
#define _LIGHT_COMPONENT_H_

#include "Component.h"
#include "..\..\Core\LightHelper.h"

enum eLightType
{
	LIGHT_TYPE_DIRECTIONAL,
	LIGHT_TYPE_POINT,
	LIGHT_TYPE_SPOT,
};

class CLightComponent : public IComponent
{
	DeclRTTI;
public:
	virtual bool		Setup() = 0;
	virtual bool		Update(float deltaTime) = 0;

	virtual bool		HandleMessage(const CMessage& msg) { return false; }

public:
	eLightType			GetLightType()	{ return m_light_type; }
	void				SetLightType(eLightType type)	{ m_light_type = type; }
	

public:
	CLightComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CLightComponent();

protected:
	eLightType			m_light_type;


};

#endif // !_LIGHT_COMPONENT_H_