#pragma once

#ifndef _RENDER_COMPONENT_H_
#define _RENDER_COMPONENT_H_

#include "..\Component.h"
#include "..\..\..\Resource\Mesh.h"
#include "..\..\..\Resource\Material.h"
#include "..\..\..\Resource\Effect.h"


class CRenderComponent : public IComponent
{
	DeclRTTI;

public:
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) override;

	virtual bool		HandleMessage(const CMessage& msg) override;

	virtual void		BuildShadowMap(CXMMATRIX matWorld);
	
	virtual void		Render(CXMMATRIX matWorld);

public:
	void				SetEffect(CEffect* effect);
	void				SetMesh(CMesh* mesh);

	void				SetExternMaterial(CMaterial* material);
	void				CopyExternMaterialToMaterial();

	void				SetTexTrans(float value) { m_texTransform = value; }

	void				SetCastShadow(bool b) { m_castShadow = b; }
	void				SetReceiveShadow(bool b) { m_receiveShadow = b; }

public:
	CMesh*				GetMesh()			{ return m_mesh; }
	CMaterial*			GetExternMaterial()	{ return m_extern_material; }
	CMaterial&			GetMaterial()		{ return m_material; }
	float				GetTexTrans()		{ return m_texTransform; }

	bool				GetCastShadow() { return m_castShadow; }
	bool				GetReceiveShadow() { return m_receiveShadow; }


public:
	CRenderComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CRenderComponent();

protected:
	CMesh*							m_mesh;

	//���� ���ӿ�����Ʈ�� ���� ���͸��� ������ �������־ ���ӿ�����Ʈ���� �������� �ֱ� ���� ������ ����Ǵ� ���͸����� ���� �������ִ�. 
	CMaterial						m_material; //���� ������ �� �� ����Ǵ� ���͸���
	CMaterial*						m_extern_material;	//���Ϸ� ������ ���׸���(�� ���͸����� ���� ���͸��� ����ȴ�)

	CEffect*						m_effect;

	float							m_texTransform;

	bool							m_castShadow;
	bool							m_receiveShadow;
};


#endif // !_RENDER_COMPONENT_H_
