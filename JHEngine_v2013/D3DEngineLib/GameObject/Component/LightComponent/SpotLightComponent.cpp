#include "SpotLightComponent.h"

#include "..\..\GameObject.h"

#include "LightManager.h"

ImplRTTI(CSpotLightComponent, CLightComponent);

CSpotLightComponent::CSpotLightComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: CLightComponent(id, owner)
{
	g_pLightMgr->AddSpotLight(this);
}


CSpotLightComponent::~CSpotLightComponent()
{
	g_pLightMgr->EraseSpotLight(this);
}

bool CSpotLightComponent::Setup()
{
	CLightComponent::Setup();

	return true;
}

bool CSpotLightComponent::Update(float deltaTime)
{
	return true;
}

bool CSpotLightComponent::HandleMessage(const CMessage& msg)
{
	return IComponent::HandleMessage(msg);
}

XMFLOAT3 CSpotLightComponent::GetPosition()
{
	XMFLOAT3 pos;
	XMStoreFloat3(&pos, m_pOwner->GetTransform()->GetWorldPosition());

	return pos;
}

XMVECTOR CSpotLightComponent::GetPositionXM()
{
	return m_pOwner->GetTransform()->GetWorldPosition();
}

XMFLOAT3 CSpotLightComponent::GetDirection()
{
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, m_pOwner->GetTransform()->GetWorldFront());

	return dir;
}

XMVECTOR CSpotLightComponent::GetDirectionXM()
{
	return m_pOwner->GetTransform()->GetWorldFront();
}