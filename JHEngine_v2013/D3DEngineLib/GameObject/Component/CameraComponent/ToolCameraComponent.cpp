#include "..\..\..\Common.h"
#include "ToolCameraComponent.h"

#include "..\..\..\Core\Input.h"


ImplRTTI(CToolCameraComponent, CCameraComponent);

CToolCameraComponent::CToolCameraComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: CCameraComponent(id, owner), m_isControl(false), m_delta(20.0f)
{
}


CToolCameraComponent::~CToolCameraComponent()
{
}

bool CToolCameraComponent::Update(float deltaTime)
{
	if (!m_isControl) return true;

	

	if (Input::GetKey('E') || Input::GetKey('e'))
	{
		this->Rise(m_delta * deltaTime);
	}
	if (Input::GetKey('Q') || Input::GetKey('q'))
	{
		this->Rise(m_delta * -1.0f * deltaTime);
	}
	if (Input::GetKey('W') || Input::GetKey('w'))
	{
		this->Walk(m_delta * deltaTime);
	}
	if (Input::GetKey('S') || Input::GetKey('s'))
	{
		this->Walk(m_delta * -1.0f * deltaTime);
	}
	if (Input::GetKey('D') || Input::GetKey('d'))
	{
		this->Strafe(m_delta * deltaTime);
	}
	if (Input::GetKey('A') || Input::GetKey('a'))
	{
		this->Strafe(m_delta * -1.0f * deltaTime);
	}

	return true;
}