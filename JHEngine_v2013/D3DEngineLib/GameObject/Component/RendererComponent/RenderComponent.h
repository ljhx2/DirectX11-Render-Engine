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

	//여러 게임오브젝트가 같은 머터리얼 파일을 가지고있어도 게임오브젝트마다 개별성을 주기 위해 실제로 적용되는 머터리얼을 따로 가지고있다. 
	CMaterial						m_material; //실제 랜더링 할 때 적용되는 머터리얼
	CMaterial*						m_extern_material;	//파일로 가져온 머테리얼(이 머터리얼이 실제 머터리얼에 복사된다)

	CEffect*						m_effect;

	float							m_texTransform;

	bool							m_castShadow;
	bool							m_receiveShadow;
};


#endif // !_RENDER_COMPONENT_H_
