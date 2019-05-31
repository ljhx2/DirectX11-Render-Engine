#pragma once

#ifndef _SKINNED_MESH_RENDERER_H_
#define _SKINNED_MESH_RENDERER_H_

#include "RenderComponent.h"

#include "..\AnimationComponent\AnimComponent.h"

class CSkinnedMeshRenderer : public CRenderComponent
{
	DeclRTTI;

public:
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) override;

	virtual bool		HandleMessage(const CMessage& msg) override;

	virtual void		BuildShadowMap(CXMMATRIX matWorld);
	virtual void		Render(CXMMATRIX matWorld);
public:
	CSkinnedMeshRenderer(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CSkinnedMeshRenderer();

private:

};

#endif // !_SKINNED_MESH_RENDERER_H_
