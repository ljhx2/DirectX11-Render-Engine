#pragma once

#ifndef _POINT_LIGHT_COMPONENT_
#define _POINT_LIGHT_COMPONENT_

#include "LightComponent.h"

class CPointLightComponent : public CLightComponent
{
	DeclRTTI;
public:
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) override;

	virtual bool		HandleMessage(const CMessage& msg) override;

public:
	XMFLOAT3			GetPosition();
	XMVECTOR			GetPositionXM();

	float				GetRange()				{ return m_Range; }
	void				SetRange(float range)	{ m_Range = range; }

	XMFLOAT3			GetAtt()				{ return m_Att; }
	void				SetAtt(XMFLOAT3 att)	{ m_Att = att; }
	

public:
	CPointLightComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CPointLightComponent();

private:
	float				m_Range;
	XMFLOAT3			m_Att;
};

#endif // !_POINT_LIGHT_COMPONENT_