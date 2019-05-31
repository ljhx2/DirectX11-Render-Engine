#include "ResourceMgr.h"

#include "GeometryGenerator.h"
#include "..\Core\gDeviceManager.h"

#include "..\GameObject\Component\LightComponent\LightManager.h"
#include "..\GameObject\Component\CameraComponent\CameraManager.h"
#include "..\GameObject\GameObject.h"

CResourceMgr::CResourceMgr()
{
}


CResourceMgr::~CResourceMgr()
{
}

CMesh* CResourceMgr::GetMesh(const RESOURCE_ID_T& id)
{
	
	if (m_mapMeshes.find(id) == m_mapMeshes.end())
	{
		if (AddMesh(id) == false)
		{
			return NULL;
		}

	}

	return m_mapMeshes[id];
}

void CResourceMgr::EraseMesh(RESOURCE_ID_T& id)
{
	std::unordered_map<RESOURCE_ID_T, CMesh*>::iterator iter;
	iter = m_mapMeshes.find(id);
	if (iter != m_mapMeshes.end())
	{
		m_mapMeshes.erase(iter);
	}
}

bool CResourceMgr::AddMesh(const RESOURCE_ID_T& id)
{
	std::unordered_map<RESOURCE_ID_T, CMesh*>::iterator iter;
	iter = m_mapMeshes.find(id);
	if (iter != m_mapMeshes.end())
	{
		//중복검사
		return false;
	}
	if (id == L"Box")
	{
		CMesh* box = CGeometryGenerator::CreateBox();
		m_mapMeshes.insert(std::make_pair(L"Box", box));
		return true;

	}
	else if (id == L"Sphere")
	{
		CMesh* sphere = CGeometryGenerator::CreateSphere();
		m_mapMeshes.insert(std::make_pair(L"Sphere", sphere));
		return true;
	}
	else if (id == L"Cylinder")
	{
		CMesh* cylinder = CGeometryGenerator::CreateCylinder();
		m_mapMeshes.insert(std::make_pair(L"Cylinder", cylinder));
		return true;
	}
	else if (id == L"Plane")
	{
		CMesh* plane = CGeometryGenerator::CreatePlane();
		m_mapMeshes.insert(std::make_pair(L"Plane", plane));
		return true;
	}

	
	//TODO : 다른 기본도형들 추가 
	return false;
}

bool CResourceMgr::AddMesh(const RESOURCE_ID_T& id, CMesh* mesh)
{
	if (mesh == NULL) return false;

	std::unordered_map<RESOURCE_ID_T, CMesh*>::iterator iter;
	iter = m_mapMeshes.find(id);
	if (iter != m_mapMeshes.end())
	{
		//중복검사
		return false;
	}

	m_mapMeshes[id] = mesh;
	return true;
}

CTexture* CResourceMgr::GetTexture(const RESOURCE_ID_T& id)
{
	if (m_mapTextures.find(id) == m_mapTextures.end())
	{
		if (AddTexture(id) == false)
		{
			return NULL;
		}
	}

	return m_mapTextures[id];

}

void CResourceMgr::EraseTexture(RESOURCE_ID_T& id)
{
	std::unordered_map<RESOURCE_ID_T, CTexture*>::iterator iter;
	iter = m_mapTextures.find(id);
	if (iter != m_mapTextures.end())
	{
		m_mapTextures.erase(iter);
	}
}

bool CResourceMgr::AddTexture(const RESOURCE_ID_T& id)
{
	CTexture* tex = new CTexture(id);

	ID3D11ShaderResourceView* srv;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(g_pDeviceMgr->GetDevice(),
		id.c_str(), 0, 0, &srv, 0);

	if (FAILED(hr))
	{
		delete tex;
		//assert(false && "Create Texture Failed");
		return false;
	}
	
	tex->SetTexture(srv);

	m_mapTextures.insert(std::make_pair(id, tex));
	return true;
}

CMaterial* CResourceMgr::GetMaterial(const RESOURCE_ID_T& id)
{
	if (m_mapMaterials.find(id) == m_mapMaterials.end())
	{
		return NULL;
	}

	return m_mapMaterials[id];
}

void CResourceMgr::EraseMaterial(RESOURCE_ID_T& id)
{
	std::unordered_map<RESOURCE_ID_T, CMaterial*>::iterator iter;
	iter = m_mapMaterials.find(id);
	if (iter != m_mapMaterials.end())
	{
		m_mapMaterials.erase(iter);
	}
}

bool CResourceMgr::AddMaterial(const RESOURCE_ID_T& id)
{
	CMaterial* material = new CMaterial;

	bool isSuccess = CMaterial::LoadMaterial(id, material);
	if (isSuccess == false)
	{
		delete material;
		return false;
	}

	m_mapMaterials.insert(std::make_pair(id, material));

	return true;
}

bool CResourceMgr::AddMaterial(const RESOURCE_ID_T& id, CMaterial* material)
{
	if (m_mapMaterials.find(id) == m_mapMaterials.end())
	{
		m_mapMaterials[id] = material;
		return true;
	}

	return false;
}


CEffect* CResourceMgr::GetEffect(const RESOURCE_ID_T& id)
{
	if (m_mapEffects.find(id) == m_mapEffects.end())
	{
		return NULL;
	}

	return m_mapEffects[id];
}

void CResourceMgr::EraseEffect(RESOURCE_ID_T& id)
{
	std::unordered_map<RESOURCE_ID_T, CEffect*>::iterator iter;
	iter = m_mapEffects.find(id);
	if (iter != m_mapEffects.end())
	{
		m_mapEffects.erase(iter);
	}
}

bool CResourceMgr::AddEffect(const RESOURCE_ID_T& id)
{
	std::unordered_map<RESOURCE_ID_T, CEffect*>::iterator iter;
	iter = m_mapEffects.find(id);
	if (iter != m_mapEffects.end())
	{
		// 이미 있다.
		return false;
	}

	CEffect* fx = new CEffect;
	
	if (fx->CreateFX(g_pDeviceMgr->GetDevice(), id) == false)
	{
		delete fx;
		return false;
	}

	fx->CreateMember();

	m_mapEffects.insert(std::make_pair(id, fx));

	return true;
}

void CResourceMgr::SetEffectCbPerFrame()
{
	CEffect* fx = GetEffect(L"FX/Basic.fx");
	if (fx == NULL) return;

	//Light
	fx->SetDirLights(g_pLightMgr->GetVecDirectionalLight());

	//EyePosW
	XMVECTOR eyePosW = g_pCameraMgr->GetCurrentCamera()->GetOwner()->GetTransform()->GetWorldPosition();
	XMFLOAT3 eyePos;
	XMStoreFloat3(&eyePos, eyePosW);
	fx->SetEyePosW(eyePos);
}
