#pragma once

#ifndef _MATERIAL_H_
#define _MATERIAL_H_



#include <Windows.h>
#include <xnamath.h>
#include <string>

#include "Object.h"
#include "Texture.h"

class CMaterial : public cObject
{
public:
	static void			SaveMaterial(std::wstring filePath, CMaterial* material);
	static bool			LoadMaterial(std::wstring filePath, CMaterial* material);

public:
	const std::wstring&				GetID()	const	{ return m_id; }
	void							SetID(std::wstring& id) { m_id = id; }

	XMFLOAT4		GetAmbient()	{ return m_Ambient; }
	XMFLOAT4		GetDiffuse()	{ return m_Diffuse; }
	XMFLOAT4		GetSpecular()	{ return m_Specular; }
	XMFLOAT4		GetReflect()	{ return m_Reflect; }
	XMVECTOR		GetAmbientXM()	{ return XMLoadFloat4(&m_Ambient); }
	XMVECTOR		GetDiffuseXM()	{ return XMLoadFloat4(&m_Diffuse); }
	XMVECTOR		GetSpecularXM()	{ return XMLoadFloat4(&m_Specular); }
	XMVECTOR		GetReflectXM()	{ return XMLoadFloat4(&m_Reflect); }

	void			SetAmbient(XMFLOAT4 ambient)	{ m_Ambient = ambient; }
	void			SetDiffuse(XMFLOAT4 diffuse)	{ m_Diffuse = diffuse; }
	void			SetSpecular(XMFLOAT4 specular)	{ m_Specular = specular; }
	void			SetReflect(XMFLOAT4 reflect)	{ m_Reflect = reflect; }
	void			SetAmbient(FXMVECTOR ambient)	{ XMStoreFloat4(&m_Ambient, ambient); }
	void			SetDiffuse(FXMVECTOR diffuse)	{ XMStoreFloat4(&m_Diffuse, diffuse); }
	void			SetSpecular(FXMVECTOR specular)	{ XMStoreFloat4(&m_Specular, specular); }
	void			SetReflect(FXMVECTOR reflect)	{ XMStoreFloat4(&m_Reflect, reflect); }

	CTexture*		GetDiffuseMap()	{ return m_DiffuseMap; }
	void			SetDiffuseMap(CTexture* diffuseMap);
	CTexture*		GetSpecularMap()	{ return m_SpecularMap; }
	void			SetSpecularMap(CTexture* specular);
	CTexture*		GetNormalMap()		{ return m_NormalMap; }
	void			SetNormalMap(CTexture* normal);

public:
	CMaterial& Clone(CMaterial& material)
	{
		this->m_id = material.m_id;
		this->m_Ambient = material.m_Ambient;
		this->m_Diffuse = material.m_Diffuse;
		this->m_Specular = material.m_Specular;
		this->m_Reflect = material.m_Reflect;
		this->SetDiffuseMap(material.m_DiffuseMap);
		this->SetSpecularMap(material.m_SpecularMap);
		this->SetNormalMap(material.m_NormalMap);


		return *this;
	}

public:
	CMaterial();
	virtual ~CMaterial();

private:
	std::wstring					m_id;	//파일경로, 이름(상대경로 해야할듯)
	
	XMFLOAT4						m_Ambient;
	XMFLOAT4						m_Diffuse;
	XMFLOAT4						m_Specular; // w = SpecPower
	XMFLOAT4						m_Reflect;

	CTexture*						m_DiffuseMap;
	CTexture*						m_SpecularMap;
	CTexture*						m_NormalMap;

};


#endif // !_MATERIAL_H_