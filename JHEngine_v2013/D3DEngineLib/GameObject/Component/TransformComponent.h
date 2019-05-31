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
	//�ʱ�ȭ
	void				Reset();			//��ü ���� �� �ʱ�ȭ
	void				ResetRotation();	//��ġ�� �ʱ�ȭ
	void				ResetPosition();	//ȸ�� �� �ʱ�ȭ
	void				ResetScale();		//������ �ʱ�ȭ

	//�̵�
	void				Translation_World(float dx, float dy, float dz);	//������ �������� �̵�
	void				Translation_Self(float dx, float dy, float dz);		//������ �������� �̵�
	void				SetPosition(float x, float y, float z);				//���� ��ġ�� ����
	//������
	void				Scaling(float dx, float dy, float dz);				//������ �� ��ȭ
	void				SetScale(float x, float y, float z);				//������ �� ����
	//ȸ��
	void				Rotate_World(float dx, float dy, float dz);			//������ �������� ȸ��
	void				Rotate_Self(float dx, float dy, float dz);			//������ �������� ȸ��
	void				SetRotation(float x, float y, float z);				//���� ȸ����
	void				SetQuternion(float x, float y, float z, float w);

	void				SetMatrix(CXMMATRIX matrix);
	
	void				UpdateMatrix();										//���� ��ȭ�� ������ ȣ��
	void				UpdateRotate();										//ȸ���� ��ȭ�� ������ ȣ��
	
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

	XMMATRIX			GetViewMatrix();									//������� ���Ѵ�

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

	//���⺤��
	XMFLOAT3							m_Right;
	XMFLOAT3							m_Up;
	XMFLOAT3							m_Front;

	XMFLOAT4X4							m_matWorld;
	XMFLOAT4X4							m_matLocal;		//�θ� ������ ���� ��İ� ��������.

	CTransformComponent*				m_pParent;		//�θ� ���ٸ� null
	std::list<CTransformComponent*>		m_listChildren;
};

#endif // !_TRANSFORM_COMPONENT_H_