#include "..\Common.h"
#include "Texture.h"


#include "ResourceMgr.h"

CTexture::CTexture(const std::wstring& id)
	: cObject(), m_texture(NULL), m_id(id), m_textureSamplerState(NULL)
{
}


CTexture::~CTexture()
{
	SAFE_RELEASE(m_texture);
	SAFE_RELEASE(m_textureSamplerState);
	g_pResouceMgr->EraseTexture(m_id);
}

void CTexture::SetSamplerState(ID3D11SamplerState* textureSamplerState)
{
	SAFE_RELEASE(m_textureSamplerState);
	m_textureSamplerState = textureSamplerState;
}