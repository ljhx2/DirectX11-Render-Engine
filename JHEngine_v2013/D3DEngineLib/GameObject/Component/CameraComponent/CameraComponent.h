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
	virtual void		SetLens(float fovY, float aspect, float zn, float zf);	//절두체 설정

	virtual void		OnResize(UINT clientWidth, UINT clientHeight);

	//카메라의 위치와 시선 및 위쪽 방향으로 카메라공간을 설정한다.
	//void				LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
	//void				LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);

	//시야 행렬과 투영 행렬을 돌려준다
	XMMATRIX			GetViewMatrix() const { return XMLoadFloat4x4(&m_matView); }
	XMMATRIX			GetProjMatrix() const { return XMLoadFloat4x4(&m_matProj); }
	XMMATRIX			GetViewProjMatrix() const { return XMLoadFloat4x4(&m_matView) * XMLoadFloat4x4(&m_matProj); }

	//카메라를 거리 d만큼 횡이동, 축이동한다.
	void				Strafe(float d);
	void				Walk(float d);
	void				Rise(float d);
	void				SetPosition(float x, float y, float z);
	void				SetRotation(float x, float y, float z);

	//카메라를 회전한다.
	void				RotateX(float angle);
	void				RotateY(float angle);

	//매 프레임마다, 카메라 위치나 방향을 수정한 후,
	//이 메서드를 호출해서 시야 행렬을 재구축한다.
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