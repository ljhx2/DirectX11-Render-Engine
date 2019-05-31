#pragma once

#ifndef _SHADOW_MAP_H_
#define _SHADOW_MAP_H_



class CShadowMap
{
public:
	ID3D11ShaderResourceView*		GetDepthMapSRV();

	void							BindDsvAndSetNullRenderTarget(ID3D11DeviceContext* dc);

public:
	CShadowMap(ID3D11Device* device, UINT width, UINT height);
	~CShadowMap();

private:
	CShadowMap(const CShadowMap& rhs);
	CShadowMap& operator=(const CShadowMap& rhs);

private:
	UINT						m_width;
	UINT						m_height;

	ID3D11ShaderResourceView*	m_depthMapSRV;
	ID3D11DepthStencilView*		m_depthMapDSV;

	D3D11_VIEWPORT				m_viewport;
};

#endif // !_SHADOW_MAP_H_