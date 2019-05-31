#pragma once

#ifndef _DIRECTIONAL_LIGHT_COMPONENT_H_
#define _DIRECTIONAL_LIGHT_COMPONENT_H_

#include "LightComponent.h"

class CDirectionalLightComponent : public CLightComponent
{
	DeclRTTI;
public:
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) override;

	virtual bool		HandleMessage(const CMessage& msg) override;

public:	
	XMFLOAT3			GetDirection();
	XMVECTOR			GetDirectionXM();


public:
	CDirectionalLightComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CDirectionalLightComponent();

};

#endif // !_DIRECTIONAL_LIGHT_COMPONENT_H_
