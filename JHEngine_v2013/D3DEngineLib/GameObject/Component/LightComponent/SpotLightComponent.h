#pragma once

#ifndef _SPOT_LIGHT_COMPONENT_H_
#define	_SPOT_LIGHT_COMPONENT_H_

#include "LightComponent.h"

class CSpotLightComponent : public CLightComponent
{
	DeclRTTI;
public:
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) override;

	virtual bool		HandleMessage(const CMessage& msg) override;

public:
	XMFLOAT3			GetPosition();
	XMVECTOR			GetPositionXM();

	XMFLOAT3			GetDirection();
	XMVECTOR			GetDirectionXM();

	float				GetRange()				{ return m_Range; }
	float				GetSpot()				{ return m_Spot; }
	XMFLOAT3			GetAtt()				{ return m_Att; }

	void				SetRange(float range)	{ m_Range = range; }
	void				SetSpot(float spot)		{ m_Spot = spot; }
	void				SetAtt(XMFLOAT3 att)	{ m_Att = att; }

public:
	CSpotLightComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CSpotLightComponent();

private:
	float				m_Range;
	float				m_Spot;
	XMFLOAT3			m_Att;

};

#endif // !_SPOT_LIGHT_COMPONENT_H_
