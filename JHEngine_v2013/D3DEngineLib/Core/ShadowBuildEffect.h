#pragma once

#ifndef _SHADOW_BUILD_EFFECT_H_
#define _SHADOW_BUILD_EFFECT_H_

#include "..\Resource\VertexType.h"

class CShadowBuildEffect
{
public:
	ID3DX11EffectTechnique* GetBiuldShadowMapTech() { return BuildShadowMapTech; }
	ID3DX11EffectTechnique* GetBuildShadowMapAlphaClipTech() { return BuildShadowMapAlphaClipTech; }
	ID3DX11EffectTechnique* GetBuildShadowMapSkinnedTech() { return BuildShadowMapSkinnedTech; }
	ID3DX11EffectTechnique* GetBuildShadowMapAlphaClipSkinnedTech() { return BuildShadowMapAlphaClipSkinnedTech; }

	void SetViewProj(CXMMATRIX M)                       { ViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetBoneTransforms(const XMFLOAT4X4* M, int cnt){ BoneTransforms->SetMatrixArray(reinterpret_cast<const float*>(M), 0, cnt); }
	void SetBoneTransformsIdentity()					{ BoneTransforms->SetMatrixArray(reinterpret_cast<const float*>(&m_IdentityTransforms[0]), 0, MAX_JOINT_COUNT); }
	void SetTexTransform(CXMMATRIX M)                   { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }

	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { DiffuseMap->SetResource(tex); }
	
public:
	CShadowBuildEffect(ID3D11Device* device, const std::wstring& filename);
	~CShadowBuildEffect();

private:
	ID3DX11EffectTechnique* BuildShadowMapTech;
	ID3DX11EffectTechnique* BuildShadowMapAlphaClipTech;
	ID3DX11EffectTechnique* BuildShadowMapSkinnedTech;
	ID3DX11EffectTechnique* BuildShadowMapAlphaClipSkinnedTech;

	ID3DX11EffectMatrixVariable* ViewProj;
	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* BoneTransforms;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;

	ID3DX11Effect* mFX;


	std::vector<XMFLOAT4X4>	m_IdentityTransforms;
};

#endif // !_SHADOW_BUILD_EFFECT_H_
