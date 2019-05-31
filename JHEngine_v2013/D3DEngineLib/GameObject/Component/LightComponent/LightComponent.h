#pragma once

#ifndef _LIGHT_COMPONENT_H_
#define _LIGHT_COMPONENT_H_

#include "..\Component.h"
#include "..\..\..\Core\LightHelper.h"

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
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) = 0;

	virtual bool		HandleMessage(const CMessage& msg) { return false; }

public:
	eLightType			GetLightType()	{ return m_light_type; }
	void				SetLightType(eLightType type)	{ m_light_type = type; }
	
	XMFLOAT4			GetAmbient()	{ return m_Ambient; }
	XMFLOAT4			GetDiffuse()	{ return m_Diffuse; }
	XMFLOAT4			GetSpecular()	{ return m_Specular; }
	XMVECTOR			GetAmbientXM()	{ return XMLoadFloat4(&m_Ambient); }
	XMVECTOR			GetDiffuseXM()	{ return XMLoadFloat4(&m_Diffuse); }
	XMVECTOR			GetSpecularXM()	{ return XMLoadFloat4(&m_Specular); }

	void				SetAmbient(XMFLOAT4& ambient) { m_Ambient = ambient; }
	void				SetDiffuse(XMFLOAT4& diffuse) { m_Diffuse = diffuse; }
	void				SetSpecular(XMFLOAT4& specular) { m_Specular = specular; }
	void				SetAmbientXM(FXMVECTOR ambient) { XMStoreFloat4(&m_Ambient, ambient); }
	void				SetDiffuseXm(FXMVECTOR diffuse) { XMStoreFloat4(&m_Diffuse, diffuse); }
	void				SetSpecularXM(FXMVECTOR specular) { XMStoreFloat4(&m_Specular, specular); }

public:
	CLightComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CLightComponent();

protected:
	eLightType			m_light_type;

	XMFLOAT4			m_Ambient;
	XMFLOAT4			m_Diffuse;
	XMFLOAT4			m_Specular;


};

#endif // !_LIGHT_COMPONENT_H_