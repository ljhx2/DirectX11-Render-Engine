#pragma once

#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_

#include <list>

#include "Component.h"



class CTransformComponent : public IComponent
{
	DeclRTTI;
public:
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) override;

	virtual bool		HandleMessage(const CMessage& msg) override;

public:
	//초기화
	void				Reset();			//전체 방위 값 초기화
	void				ResetRotation();	//위치값 초기화
	void				ResetPosition();	//회전 값 초기화
	void				ResetScale();		//스케일 초기화

	//이동
	void				Translation_World(float dx, float dy, float dz);	//월드축 기준으로 이동
	void				Translation_Self(float dx, float dy, float dz);		//로컬축 기준으로 이동
	void				SetPosition(float x, float y, float z);				//월드 위치값 세팅
	//스케일
	void				Scaling(float dx, float dy, float dz);				//스케일 값 변화
	void				SetScale(float x, float y, float z);				//스케일 값 세팅
	//회전
	void				Rotate_World(float dx, float dy, float dz);			//월드축 기준으로 회전
	void				Rotate_Self(float dx, float dy, float dz);			//로컬축 기준으로 회전
	void				SetRotation(float x, float y, float z);				//월드 회전값
	void				SetQuternion(float x, float y, float z, float w);

	void				SetMatrix(CXMMATRIX matrix);
	
	void				UpdateMatrix();										//방위 변화가 있으면 호출
	void				UpdateRotate();										//회전값 변화가 있으면 호출
	
	inline XMMATRIX		GetWorldMatrix()		{ return XMLoadFloat4x4(&m_matWorld); }
	inline XMMATRIX		GetLocalMatrix()		{ return XMLoadFloat4x4(&m_matLocal); }
	inline XMVECTOR		GetLocalFront()			{ return XMLoadFloat3(&m_Front); }
	inline XMVECTOR		GetLocalUp()			{ return XMLoadFloat3(&m_Up); }
	inline XMVECTOR		GetLocalRight()			{ return XMLoadFloat3(&m_Right); }
	inline XMVECTOR		GetLocalRotation()		{ return XMLoadFloat3(&m_Rotation); }
	inline XMVECTOR		GetLocalPosition()		{ return XMLoadFloat3(&m_Position); }
	inline XMVECTOR		GetLocalScale()			{ return XMLoadFloat3(&m_Scale); }
	
	XMVECTOR			GetWorldFront();
	XMVECTOR			GetWorldUp();
	XMVECTOR			GetWorldRight();
	XMVECTOR			GetWorldPosition();

	XMMATRIX			GetViewMatrix();									//뷰행렬을 구한다

	CTransformComponent* GetParent()			{ return m_pParent; }
	void				SetParent(CTransformComponent* parent) { m_pParent = parent; }

	void				AddChild(CTransformComponent* pChild);
	void				DetechChild(CTransformComponent* pChild);

public:
	CTransformComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CTransformComponent();

private:
	XMFLOAT3							m_Position;
	XMFLOAT3							m_Scale;
	XMFLOAT3							m_Rotation;

	//방향벡터
	XMFLOAT3							m_Right;
	XMFLOAT3							m_Up;
	XMFLOAT3							m_Front;

	XMFLOAT4X4							m_matWorld;
	XMFLOAT4X4							m_matLocal;		//부모가 없으면 월드 행렬과 같아진다.

	CTransformComponent*				m_pParent;		//부모가 없다면 null
	std::list<CTransformComponent*>		m_listChildren;
};

#endif // !_TRANSFORM_COMPONENT_H_