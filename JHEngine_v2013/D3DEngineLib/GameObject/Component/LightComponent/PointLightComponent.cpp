#include "PointLightComponent.h"

#include "..\..\GameObject.h"

#include "LightManager.h"

ImplRTTI(CPointLightComponent, CLightComponent);

CPointLightComponent::CPointLightComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: CLightComponent(id, owner), m_Range(20.0f), m_Att(0, 1, 0)
{
	g_pLightMgr->AddPointLight(this);
}


CPointLightComponent::~CPointLightComponent()
{
	g_pLightMgr->ErasePointLight(this);
}

bool CPointLightComponent::Setup()
{
	CLightComponent::Setup();

	return true;
}

bool CPointLightComponent::Update(float deltaTime)
{
	return true;
}

bool CPointLightComponent::HandleMessage(const CMessage& msg)
{
	return IComponent::HandleMessage(msg);
}

XMFLOAT3 CPointLightComponent::GetPosition()
{
	XMFLOAT3 pos;
	XMStoreFloat3(&pos, m_pOwner->GetTransform()->GetWorldPosition());
	
	return pos;
}

XMVECTOR CPointLightComponent::GetPositionXM()
{
	return m_pOwner->GetTransform()->GetWorldPosition();
}