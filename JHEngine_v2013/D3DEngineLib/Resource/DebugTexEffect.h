#pragma once

#ifndef _DEBUG_TEX_EFFECT_H_
#define _DEBUG_TEX_EFFECT_H_



class CDebugTexEffect
{
public:
	CDebugTexEffect(ID3D11Device* device, const std::wstring& filename);
	~CDebugTexEffect();

public:
	void SetWorldViewProj(CXMMATRIX M)              { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexture(ID3D11ShaderResourceView* tex)  { Texture->SetResource(tex); }

	ID3DX11EffectTechnique* ViewArgbTech;
	ID3DX11EffectTechnique* ViewRedTech;
	ID3DX11EffectTechnique* ViewGreenTech;
	ID3DX11EffectTechnique* ViewBlueTech;
	ID3DX11EffectTechnique* ViewAlphaTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectShaderResourceVariable* Texture;

private:
	ID3DX11Effect* mFX;
};

#endif // !_DEBUG_TEX_EFFECT_H_