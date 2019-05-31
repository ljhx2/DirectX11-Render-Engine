#include "LightComponent.h"


ImplRTTI(CLightComponent, IComponent);

CLightComponent::CLightComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: IComponent(id, owner)
{
	m_Ambient = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
}


CLightComponent::~CLightComponent()
{
}

bool CLightComponent::Setup()
{
	return true;
}