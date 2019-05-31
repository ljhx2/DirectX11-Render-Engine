#include "DirectionalLightComponent.h"

#include "..\..\GameObject.h"
#include "LightManager.h"

ImplRTTI(CDirectionalLightComponent, CLightComponent);

CDirectionalLightComponent::CDirectionalLightComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: CLightComponent(id, owner)
{
	g_pLightMgr->AddDirectionalLight(this);
}


CDirectionalLightComponent::~CDirectionalLightComponent()
{
	g_pLightMgr->EraseDirectionalLight(this);
}

bool CDirectionalLightComponent::Setup()
{
	CLightComponent::Setup();

	return true;
}

bool CDirectionalLightComponent::Update(float deltaTime)
{
	return true;
}

bool CDirectionalLightComponent::HandleMessage(const CMessage& msg)
{
	return IComponent::HandleMessage(msg);
}

XMFLOAT3 CDirectionalLightComponent::GetDirection()
{
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, m_pOwner->GetTransform()->GetWorldFront());

	return dir;
}

XMVECTOR CDirectionalLightComponent::GetDirectionXM()
{
	return m_pOwner->GetTransform()->GetWorldFront();
}

