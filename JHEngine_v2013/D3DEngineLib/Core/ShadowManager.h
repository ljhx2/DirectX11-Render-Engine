#pragma once

#ifndef _SHADOW_MANAGER_H_
#define _SHADOW_MANAGER_H_

#include "Singleton.h"

#include "ShadowMap.h"
#include "ShadowBuildEffect.h"

//Debug
#include "..\Resource\Mesh.h"
#include "..\Resource\DebugTexEffect.h"

#define g_pShadowMgr CShadowManager::GetInstance()


class CShadowManager : public CSingleton<CShadowManager>
{
public:
	CShadowMap*			GetShadowMap()	{ return m_shadowMap; }
	CShadowBuildEffect* GetShadowEffect()	{ return m_shadowEffect; }

	XMFLOAT4X4&			GetLightView() { return m_lightView; }
	XMFLOAT4X4&			GetLightProj() { return m_lightProj; }
	XMFLOAT4X4&			GetLightViewProj() { return m_lightViewProj; }
	XMFLOAT4X4&			GetShadowTransform() { return m_shadowTransform; }

public:
	void				Init();
	void				BeginShadowMap();
	void				EndShadowMap();

	//Debug
	void				RenderScreenQuad();
	void				SetShowShadowTexture(bool b) { m_showShadowTexture = b; }

private:
	void				CalcLightMatrix();

	//Debug
	void				CerateVertex();

public:
	CShadowManager();
	~CShadowManager();

private:
	CShadowMap*					m_shadowMap;
	CShadowBuildEffect*			m_shadowEffect;

	XMFLOAT4X4					m_lightView;
	XMFLOAT4X4					m_lightProj;
	XMFLOAT4X4					m_lightViewProj;

	XMFLOAT4X4					m_shadowTransform;

	//Debug
	CMesh*						m_screenQuad;
	CDebugTexEffect*			m_debugEffect;
	
	bool						m_showShadowTexture;

};

#endif // !_SHADOW_MANAGER_H_