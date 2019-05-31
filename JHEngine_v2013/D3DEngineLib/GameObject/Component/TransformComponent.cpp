#include "TransformComponent.h"

#include <cassert>


#include "..\GameObject.h"

#include "..\..\Core\MathHelper.h"

ImplRTTI(CTransformComponent, IComponent);


CTransformComponent::CTransformComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: IComponent(id, owner)
{
	m_pParent = NULL;
	m_listChildren.clear();

	Reset();
}


CTransformComponent::~CTransformComponent()
{
	if (m_pParent)
	{
		m_pParent->DetechChild(this);
	}
}

bool CTransformComponent::Setup()
{
	return true;
}

bool CTransformComponent::Update(float deltaTime)
{
	return true;
}

bool CTransformComponent::HandleMessage(const CMessage& msg)
{
	return IComponent::HandleMessage(msg);
}

void CTransformComponent::Reset()
{
	XMVECTOR front = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMStoreFloat3(&m_Front, front);
	XMStoreFloat3(&m_Up, up);
	XMStoreFloat3(&m_Right, right);

	XMVECTOR zero = XMVectorZero();
	XMStoreFloat3(&m_Rotation, zero);
	XMStoreFloat3(&m_Position, zero);


	XMVECTOR scale = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMStoreFloat3(&m_Scale, scale);

	UpdateMatrix();
}

void CTransformComponent::ResetRotation()
{
	XMVECTOR front	= XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMStoreFloat3(&m_Front, front);
	XMStoreFloat3(&m_Up, up);
	XMStoreFloat3(&m_Right, right);

	XMVECTOR zero = XMVectorZero();
	XMStoreFloat3(&m_Rotation, zero);

	UpdateMatrix();
}

void CTransformComponent::ResetPosition()
{
	XMVECTOR zero = XMVectorZero();
	XMStoreFloat3(&m_Position, zero);

	UpdateMatrix();
}

void CTransformComponent::ResetScale()
{
	XMVECTOR scale = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMStoreFloat3(&m_Scale, scale);

	UpdateMatrix();
}

void CTransformComponent::Translation_World(float dx, float dy, float dz)
{
	m_Position.x += dx;
	m_Position.y += dy;
	m_Position.z += dz;

	UpdateMatrix();
}

void CTransformComponent::Translation_Self(float dx, float dy, float dz)
{
	XMVECTOR position = XMLoadFloat3(&m_Position);
	position += XMLoadFloat3(&m_Right) * dx;
	position += XMLoadFloat3(&m_Up) * dy;
	position += XMLoadFloat3(&m_Front) * dz;
	XMStoreFloat3(&m_Position, position);

	UpdateMatrix();
}

void CTransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;

	UpdateMatrix();
}

void CTransformComponent::Scaling(float dx, float dy, float dz)
{
	m_Scale.x += dx;
	m_Scale.y += dy;
	m_Scale.z += dz;

	UpdateMatrix();
}

void CTransformComponent::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;

	UpdateMatrix();
}

void CTransformComponent::Rotate_World(float dx, float dy, float dz)
{
	m_Rotation.x += dx;
	m_Rotation.y += dy;
	m_Rotation.z += dz;

	UpdateRotate();
	UpdateMatrix();
}

void CTransformComponent::Rotate_Self(float dx, float dy, float dz)
{
	XMVECTOR rotation = XMLoadFloat3(&m_Rotation);
	rotation += XMLoadFloat3(&m_Right) * dx;
	rotation += XMLoadFloat3(&m_Up) * dy;
	rotation += XMLoadFloat3(&m_Front) * dz;
	XMStoreFloat3(&m_Rotation, rotation);

	UpdateRotate();
	UpdateMatrix();
}

void CTransformComponent::SetRotation(float x, float y, float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;

	UpdateRotate();
	UpdateMatrix();

}

void CTransformComponent::SetQuternion(float x, float y, float z, float w)
{
	XMFLOAT4 quternion = XMFLOAT4(x, y, z, w);

	//XMFLOAT3 euler = CMathHelper::ConvertQuaternionToEulerAngle(quternion);
	//this->SetRotation(XMConvertToRadians(euler.x), XMConvertToRadians(euler.y), XMConvertToRadians(euler.z));
	
	XMFLOAT3 euler;
	CMathHelper::quat_2_euler_d3d(quternion, euler.x, euler.y, euler.z);
	this->SetRotation(euler.x, euler.y, euler.z);
}

void CTransformComponent::SetMatrix(CXMMATRIX matrix)
{
	XMVECTOR scale, pos, qut;
	XMMatrixDecompose(&scale, &qut, &pos, matrix);

	XMStoreFloat3(&m_Scale, scale);
	XMStoreFloat3(&m_Position, pos);

	XMFLOAT4 qutF;
	XMStoreFloat4(&qutF, qut);
	CMathHelper::quat_2_euler_d3d(qutF, m_Rotation.x, m_Rotation.y, m_Rotation.z);

	UpdateRotate();
	UpdateMatrix();
}

void CTransformComponent::UpdateMatrix()
{
	XMFLOAT4 xAxis;
	XMFLOAT4 yAxis;
	XMFLOAT4 zAxis;
	XMStoreFloat4(&xAxis,  XMLoadFloat3(&m_Right) * m_Scale.x);
	XMStoreFloat4(&yAxis,  XMLoadFloat3(&m_Up) * m_Scale.y);
	XMStoreFloat4(&zAxis,  XMLoadFloat3(&m_Front) * m_Scale.z);

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&m_matLocal, I);

	memcpy(&m_matLocal._11, &xAxis, sizeof(XMFLOAT4));
	memcpy(&m_matLocal._21, &yAxis, sizeof(XMFLOAT4));
	memcpy(&m_matLocal._31, &zAxis, sizeof(XMFLOAT4));
	memcpy(&m_matLocal._41, &m_Position, sizeof(XMFLOAT3));
	
	CGameObject* parent = m_pOwner->GetParent();
	if (parent == NULL)
	{
		m_matWorld = m_matLocal;
	}
	else
	{
		XMMATRIX matParent = parent->GetTransform()->GetWorldMatrix();
		XMMATRIX matWorld = XMMatrixMultiply(XMLoadFloat4x4(&m_matLocal), matParent);

		XMStoreFloat4x4(&m_matWorld, matWorld);
	}


	std::list<CTransformComponent*>::iterator iter;
	for (iter = m_listChildren.begin(); iter != m_listChildren.end(); ++iter)
	{
		(*iter)->UpdateMatrix();
	}

}

void CTransformComponent::UpdateRotate()
{
	XMVECTOR rotation = XMLoadFloat3(&m_Rotation);
	XMMATRIX matRotate = XMMatrixRotationRollPitchYawFromVector(rotation);
	memcpy(&m_Right, matRotate.m[0], sizeof(XMFLOAT3));
	memcpy(&m_Up, matRotate.m[1], sizeof(XMFLOAT3));
	memcpy(&m_Front, matRotate.m[2], sizeof(XMFLOAT3));
}

XMVECTOR CTransformComponent::GetWorldFront()
{
	XMMATRIX world = XMLoadFloat4x4(&m_matWorld);
	XMVECTOR front = world.r[2];
	
	return XMVector3Normalize(front);
}

XMVECTOR CTransformComponent::GetWorldUp()
{
	XMMATRIX world = XMLoadFloat4x4(&m_matWorld);
	XMVECTOR up = world.r[1];

	return XMVector3Normalize(up);
}

XMVECTOR CTransformComponent::GetWorldRight()
{
	XMMATRIX world = XMLoadFloat4x4(&m_matWorld);
	XMVECTOR right = world.r[0];

	return XMVector3Normalize(right);
}

XMVECTOR CTransformComponent::GetWorldPosition()
{
	XMMATRIX world = XMLoadFloat4x4(&m_matWorld);

	return world.r[3];
}

XMMATRIX CTransformComponent::GetViewMatrix()
{
	//ºäÇà·Ä
	// XAxis.x			YAxis.x				ZAxis.x			0.0f
	// XAxis.y			YAxis.y				ZAxis.y			0.0f
	// XAxis.z			YAxis.z				ZAxis.z			0.0f
	// -(XAxis Dot pos) -(YAxis Dot pos)  -(ZAxis Dot pos)  1.0f

	XMVECTOR front = GetWorldFront();
	XMVECTOR up = GetWorldUp();
	XMVECTOR right = GetWorldRight();
	XMVECTOR pos = GetWorldPosition();
	float dotX = XMVectorGetX(-XMVector3Dot(right, pos));
	float dotY = XMVectorGetX(-XMVector3Dot(up, pos));
	float dotZ = XMVectorGetX(-XMVector3Dot(front, pos));

	XMFLOAT3 front_f, up_f, right_f;
	XMStoreFloat3(&front_f, front);
	XMStoreFloat3(&up_f, up);
	XMStoreFloat3(&right_f, right);

	XMMATRIX view;
	view.m[0][0] = right_f.x;			view.m[0][1] = up_f.x;			view.m[0][2] = front_f.x;			view.m[0][3] = 0.0f;
	view.m[1][0] = right_f.y;			view.m[1][1] = up_f.y;			view.m[1][2] = front_f.y;			view.m[1][3] = 0.0f;
	view.m[2][0] = right_f.z;			view.m[2][1] = up_f.z;			view.m[2][2] = front_f.z;			view.m[2][3] = 0.0f;
	view.m[3][0] = dotX;				view.m[3][1] = dotY;			view.m[3][2] = dotZ;				view.m[3][3] = 1.0f;

	return view;
}

void CTransformComponent::AddChild(CTransformComponent* pChild)
{
	assert(pChild);

	//std::list<CTransformComponent*>::iterator iter;
	//for (iter = m_listChildren.begin(); iter != m_listChildren.end(); ++iter)
	//{
	//	if ((*iter) == pChild)
	//	{
	//		return;
	//	}
	//}

	m_listChildren.push_back(pChild);
	pChild->SetParent(this);
}

void CTransformComponent::DetechChild(CTransformComponent* pChild)
{
	assert(pChild);
	this;
	m_listChildren.remove(pChild);
	pChild->SetParent(NULL);
	
}