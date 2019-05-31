#pragma once

#ifndef _RESOURCE_MGR_H_
#define _REsOURCE_MGR_H_

#include <unordered_map>
#include <string>

#include "..\Core\Singleton.h"

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Effect.h"


#define g_pResouceMgr CResourceMgr::GetInstance()



typedef std::wstring									RESOURCE_ID_T;
typedef std::unordered_map<RESOURCE_ID_T, CMesh*>		MESHMAP_T;

class CResourceMgr : public CSingleton<CResourceMgr>
{
public:
	CMesh*				GetMesh(const RESOURCE_ID_T& id);
	void				EraseMesh(RESOURCE_ID_T& id);
	bool				AddMesh(const RESOURCE_ID_T& id);
	bool				AddMesh(const RESOURCE_ID_T& id, CMesh* mesh);
	MESHMAP_T&			GetMeshMap()	{ return m_mapMeshes; }

public:
	CTexture*			GetTexture(const RESOURCE_ID_T& id);
	void				EraseTexture(RESOURCE_ID_T& id);
	bool				AddTexture(const RESOURCE_ID_T& id);

public:
	CMaterial*			GetMaterial(const RESOURCE_ID_T& id);
	void				EraseMaterial(RESOURCE_ID_T& id);
	bool				AddMaterial(const RESOURCE_ID_T& id);
	bool				AddMaterial(const RESOURCE_ID_T& id, CMaterial* material);
	//bool				IdChange();

public:
	CEffect*			GetEffect(const RESOURCE_ID_T& id);
	void				EraseEffect(RESOURCE_ID_T& id);
	bool				AddEffect(const RESOURCE_ID_T& id);

	void				SetEffectCbPerFrame();

public:

public:
	CResourceMgr();
	~CResourceMgr();

private:
	//���Ϸ� ���� �о���̴� �ڿ�.
	//id�� ���ϰ�ο� �̸��̴�.
	std::unordered_map<RESOURCE_ID_T, CMesh*>		m_mapMeshes;
	std::unordered_map<RESOURCE_ID_T, CTexture*>	m_mapTextures;
	
private:
	//���Ϸ� ���� �о� ���ϼ� �� �ְ�, ������ ���� ����� �� �ִ� �ڿ�.
	//id�� ���ϰ�ο� �̸��̴�.	(�����̸��� ����� �� �ִ�. ����Ǹ� �ʿ��� �����ٰ� �ٽ� ����ؾ���)
	std::unordered_map<RESOURCE_ID_T, CMaterial*>	m_mapMaterials;

private:
	std::unordered_map<RESOURCE_ID_T, CEffect*>		m_mapEffects;

};

#endif // !_RESOURCE_MGR_H_