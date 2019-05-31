#pragma once

#ifndef _CAMERA_COMP_H_
#define	_CAMERA_COMP_H_




#include "..\Component.h"


class CCameraComponent : public IComponent
{
	DeclRTTI;

public:
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) override;

	virtual bool		HandleMessage(const CMessage& msg) override;

public:
	virtual void		SetLens(float fovY, float aspect, float zn, float zf);	//����ü ����

	virtual void		OnResize(UINT clientWidth, UINT clientHeight);

	//ī�޶��� ��ġ�� �ü� �� ���� �������� ī�޶������ �����Ѵ�.
	//void				LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
	//void				LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);

	//�þ� ��İ� ���� ����� �����ش�
	XMMATRIX			GetViewMatrix() const { return XMLoadFloat4x4(&m_matView); }
	XMMATRIX			GetProjMatrix() const { return XMLoadFloat4x4(&m_matProj); }
	XMMATRIX			GetViewProjMatrix() const { return XMLoadFloat4x4(&m_matView) * XMLoadFloat4x4(&m_matProj); }

	//ī�޶� �Ÿ� d��ŭ Ⱦ�̵�, ���̵��Ѵ�.
	void				Strafe(float d);
	void				Walk(float d);
	void				Rise(float d);
	void				SetPosition(float x, float y, float z);
	void				SetRotation(float x, float y, float z);

	//ī�޶� ȸ���Ѵ�.
	void				RotateX(float angle);
	void				RotateY(float angle);

	//�� �����Ӹ���, ī�޶� ��ġ�� ������ ������ ��,
	//�� �޼��带 ȣ���ؼ� �þ� ����� �籸���Ѵ�.
	void				UpdateViewMatrix();


public:
	float				GetNeaZ() const { return m_nearZ; }
	float				GetFarZ() const { return m_farZ; }
	float				GetAspect() const { return m_aspect; }
	float				GetFovY() const { return m_fovY; }
	float				GetFovX() const { float halfWidth = 0.5f * GetNearWindowWidth(); return 2.0f * atan(halfWidth / m_nearZ); }
	
	float				GetNearWindowWidth() const { return m_aspect * m_nearWindowHeight; }
	float				GetNearWindowHeight() const { return m_nearWindowHeight; }
	float				GetFarWindowWidth() const { return m_aspect * m_farWindowHeight; }
	float				GetFarWindowHeight() const { return m_farWindowHeight; }


public:
	CCameraComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CCameraComponent();

protected:
	float			m_nearZ;
	float			m_farZ;
	float			m_aspect;
	float			m_fovY;
	float			m_nearWindowHeight;
	float			m_farWindowHeight;

	XMFLOAT4X4		m_matView;
	XMFLOAT4X4		m_matProj;

};

#endif // !_CAMERA_COMP_H_