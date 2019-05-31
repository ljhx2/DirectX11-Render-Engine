#pragma once

#ifndef _EFFECT_H_
#define	_EFFECT_H_

#include <string>
#include <vector>

#include "VertexType.h"
#include "Object.h"
#include "..\Core\LightHelper.h"
#include "Material.h"
#include "..\GameObject\Component\LightComponent\DirectionalLightComponent.h"

class CEffect : public cObject
{
public:
	//cbPerObject
	void			SetWorldViewProj(CXMMATRIX M)			{ m_worldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void			SetWorld(CXMMATRIX M)					{ m_world->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void			SetWorldInvTranspose(CXMMATRIX M)		{ m_worldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void			SetTexTransform(CXMMATRIX M)			{ m_texTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void			SetMaterial(CMaterial& mat);
	void			SetBoneTransforms(const XMFLOAT4X4* M, int cnt)	{ BoneTransforms->SetMatrixArray(reinterpret_cast<const float*>(M), 0, cnt); }
	void			SetBoneTransformsIdentity()	{ BoneTransforms->SetMatrixArray(reinterpret_cast<const float*>(&m_IdentityTransforms[0]), 0, MAX_JOINT_COUNT); }
	void			SetReceiveShadow(bool receiveShadow)	{ m_receiveShadow->SetBool(receiveShadow); }
	void			SetShadowTransform(CXMMATRIX M)         { ShadowTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetShadowMap(ID3D11ShaderResourceView* tex)    { m_shadowMap->SetResource(tex); }


	//cbPerFrame
	void			SetDirLights(std::vector<CDirectionalLightComponent*>& vecDir);
	void			SetEyePosW(const XMFLOAT3& v)			{ m_eyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }

public:
	ID3DX11EffectTechnique*		GetTech()			{ return m_tech; }
	ID3DX11EffectTechnique*		GetSkinnedTech()	{ return m_skineedTech; }

public:
	bool			CreateFX(ID3D11Device* device, const std::wstring& filename);
	void			CreateMember();
public:

	CEffect();
	~CEffect();

private:
	std::wstring								m_id;		//경로, 파일이름

	ID3DX11Effect*								m_fx;

	ID3DX11EffectTechnique*						m_tech;
	ID3DX11EffectTechnique*						m_skineedTech;
	
	ID3DX11EffectMatrixVariable*				m_worldViewProj;
	ID3DX11EffectMatrixVariable*				m_world;
	ID3DX11EffectMatrixVariable*				m_worldInvTranspose;
	ID3DX11EffectMatrixVariable*				m_texTransform;
	ID3DX11EffectVectorVariable*				m_eyePosW;
	ID3DX11EffectVariable*						m_dirLights;
	ID3DX11EffectVariable*						m_mat;
	ID3DX11EffectScalarVariable*				m_dirLightCnt;
	ID3DX11EffectScalarVariable*				m_useTexture;
	ID3DX11EffectScalarVariable*				m_useNormalMap;
	ID3DX11EffectScalarVariable*				m_receiveShadow;
	ID3DX11EffectMatrixVariable*				BoneTransforms;
	ID3DX11EffectMatrixVariable*				ShadowTransform;

	ID3DX11EffectShaderResourceVariable*		m_diffuseMap;
	ID3DX11EffectShaderResourceVariable*		m_normalMap;
	ID3DX11EffectShaderResourceVariable*		m_shadowMap;

	std::vector<XMFLOAT4X4>						m_IdentityTransforms;
};

#endif // !_EFFECT_H_