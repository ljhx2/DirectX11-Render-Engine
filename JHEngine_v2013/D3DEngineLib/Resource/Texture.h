#pragma once

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include "Object.h"


class CTexture : public cObject
{
public:
	const std::wstring&				GetID()	const	{ return m_id; }

	ID3D11ShaderResourceView*		GetTexture()	{ return m_texture; }
	void							SetTexture(ID3D11ShaderResourceView* tex) { m_texture = tex; }

	ID3D11SamplerState*				GetSamplerState() { return m_textureSamplerState; }
	void							SetSamplerState(ID3D11SamplerState* textureSamplerState);
public:
	CTexture(const std::wstring& id);
	virtual ~CTexture();

private:
	std::wstring					m_id;	//파일경로,이름

	ID3D11ShaderResourceView*		m_texture;
	ID3D11SamplerState*				m_textureSamplerState;
};

#endif // !_TEXTURE_H_