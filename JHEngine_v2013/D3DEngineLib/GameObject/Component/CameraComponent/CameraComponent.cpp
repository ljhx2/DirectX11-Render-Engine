#include "..\..\..\Common.h"
#include "CameraComponent.h"
#include "..\..\GameObject.h"

ImplRTTI(CCameraComponent, IComponent);

CCameraComponent::CCameraComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: IComponent(id, owner)
	, m_nearZ(0.0f), m_farZ(0.0f), m_aspect(0.0f), m_fovY(0.0f)
	, m_nearWindowHeight(0.0f), m_farWindowHeight(0.0f)
{
	UpdateViewMatrix();

	XMMATRIX i = XMMatrixIdentity();
	XMStoreFloat4x4(&m_matProj, i);
}


CCameraComponent::~CCameraComponent()
{
}

bool CCameraComponent::Setup()
{
	return true;
}

bool CCameraComponent::Update(float deltaTime)
{
	return true;
}
 
bool CCameraComponent::HandleMessage(const CMessage& msg) 
{ 
	return false; 
}

void CCameraComponent::SetLens(float fovY, float aspect, float zn, float zf)
{
	m_fovY = fovY;
	m_aspect = aspect;
	m_nearZ = zn;
	m_farZ = zf;

	m_nearWindowHeight = 2.0f * m_nearZ * tanf(0.5f * m_fovY);
	m_farWindowHeight = 2.0f * m_farZ * tanf(0.5f * m_fovY);

	XMMATRIX p = XMMatrixPerspectiveFovLH(m_fovY, m_aspect, m_nearZ, m_farZ);
	XMStoreFloat4x4(&m_matProj, p);
}

void CCameraComponent::OnResize(UINT clientWidth, UINT clientHeight)
{
	m_aspect = (float)clientWidth / (float)clientHeight;

	XMMATRIX p = XMMatrixPerspectiveFovLH(m_fovY, m_aspect, m_nearZ, m_farZ);
	XMStoreFloat4x4(&m_matProj, p);
}

void CCameraComponent::Strafe(float d)
{
	m_pOwner->GetTransform()->Translation_Self(d, 0.0f, 0.0f);

	UpdateViewMatrix();
}

void CCameraComponent::Walk(float d)
{
	m_pOwner->GetTransform()->Translation_Self(0.0f, 0.0f, d);

	UpdateViewMatrix();
}

void CCameraComponent::Rise(float d)
{
	m_pOwner->GetTransform()->Translation_World(0.0f, d, 0.0f);

	UpdateViewMatrix();
}

void CCameraComponent::SetPosition(float x, float y, float z)
{
	m_pOwner->GetTransform()->SetPosition(x, y, z);
	UpdateViewMatrix();
}

void CCameraComponent::SetRotation(float x, float y, float z)
{
	m_pOwner->GetTransform()->SetRotation(x, y, z);
	UpdateViewMatrix();
}

void CCameraComponent::RotateX(float angle)
{
	m_pOwner->GetTransform()->Rotate_World(angle, 0.0f, 0.0f);

	UpdateViewMatrix();
}

void CCameraComponent::RotateY(float angle)
{
	m_pOwner->GetTransform()->Rotate_World(0.0f, angle, 0.0f);

	UpdateViewMatrix();
}

void CCameraComponent::UpdateViewMatrix()
{
	XMMATRIX view = m_pOwner->GetTransform()->GetViewMatrix();
	XMStoreFloat4x4(&m_matView, view);

}