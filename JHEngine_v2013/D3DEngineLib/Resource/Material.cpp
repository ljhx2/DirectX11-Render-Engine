#include "..\Common.h"
#include "Material.h"

#include "ResourceMgr.h"


#include "..\Core\StringHelper.h"

#include <json\json.h>
#pragma comment(lib, "lib_json.lib")

CMaterial::CMaterial()
	: cObject(), m_DiffuseMap(NULL), m_SpecularMap(NULL), m_NormalMap(NULL)
{
	m_id.clear();
	//기본값
	XMStoreFloat4(&m_Ambient, XMVectorSet(0.5f, 0.5f, 0.5f, 1.0f));
	XMStoreFloat4(&m_Diffuse, XMVectorSet(0.8f, 0.8f, 0.8f, 1.0f));
	XMStoreFloat4(&m_Specular, XMVectorSet(0.2f, 0.2f, 0.2f, 16.0f));
	XMStoreFloat4(&m_Reflect, XMVectorZero());
}


CMaterial::~CMaterial()
{
	if (m_DiffuseMap) m_DiffuseMap->Release();
	if (m_SpecularMap) m_SpecularMap->Release();
	if (m_NormalMap) m_NormalMap->Release();
	g_pResouceMgr->EraseMaterial(m_id);
}

void CMaterial::SaveMaterial(std::wstring filePath, CMaterial* material)
{
	if (material == NULL) return;

	XMFLOAT4 ambient = material->GetAmbient();
	XMFLOAT4 diffuse = material->GetDiffuse();
	XMFLOAT4 specular = material->GetSpecular();
	XMFLOAT4 reflect = material->GetReflect();
	CTexture* diffuseMap = material->GetDiffuseMap();
	CTexture* specularMap = material->GetSpecularMap();
	CTexture* normalMap = material->GetNormalMap();

	std::string id;
	CStringHelper::WStringToString(filePath, id);

	Json::Value Jroot;

	Jroot["id"] = id;

	Json::Value Jambient;
	Jambient["R"] = ambient.x;
	Jambient["G"] = ambient.y;
	Jambient["B"] = ambient.z;
	Jambient["A"] = ambient.w;
	Jroot["Ambient"] = Jambient;

	Json::Value Jdiffuse;
	Jdiffuse["R"] = diffuse.x;
	Jdiffuse["G"] = diffuse.y;
	Jdiffuse["B"] = diffuse.z;
	Jdiffuse["A"] = diffuse.w;
	Jroot["Diffuse"] = Jdiffuse;

	Json::Value Jspecular;
	Jspecular["R"] = specular.x;
	Jspecular["G"] = specular.y;
	Jspecular["B"] = specular.z;
	Jspecular["A"] = specular.w;
	Jroot["Specular"] = Jspecular;

	Json::Value Jreflect;
	Jreflect["R"] = reflect.x;
	Jreflect["G"] = reflect.y;
	Jreflect["B"] = reflect.z;
	Jreflect["A"] = reflect.w;
	Jroot["Reflect"] = Jreflect;

	if (diffuseMap)
	{
		std::string strDiffuseMap;
		CStringHelper::WStringToString(diffuseMap->GetID(), strDiffuseMap);
		
		Jroot["DiffuseMap"] = strDiffuseMap;
	}
	if (specularMap)
	{
		std::string strSpecularMap;
		CStringHelper::WStringToString(specularMap->GetID(), strSpecularMap);

		Jroot["SpecularMap"] = strSpecularMap;
	}
	if (normalMap)
	{
		std::string strNormalMap;
		CStringHelper::WStringToString(normalMap->GetID(), strNormalMap);

		Jroot["NormalMap"] = strNormalMap;
	}
	
	Json::StyledWriter writer;
	std::string outputConfig = writer.write(Jroot);

	std::ofstream file(filePath.c_str(), std::ios_base::out | std::ios_base::trunc);
	file.write(outputConfig.c_str(), outputConfig.length());

	//순서
	//ID, ambient, diffuse, specular, reflect, diffuseMap, specularMap
	/*
	file << id.c_str() << std::endl;
	file << ambient.x << " " << ambient.y << " " << ambient.z << " " << ambient.w << std::endl;
	file << diffuse.x << " " << diffuse.y << " " << diffuse.z << " " << diffuse.w << std::endl;
	file << specular.x << " " << specular.y << " " << specular.z << " " << specular.w << std::endl;
	file << reflect.x << " " << reflect.y << " " << reflect.z << " " << reflect.w << std::endl;
	if (diffuseMap == NULL)
	{
		file << "NULL" << std::endl;
	}
	else
	{
		std::string strDiffuseMap;
		CStringHelper::WStringToString(diffuseMap->GetID(), strDiffuseMap);
		file << strDiffuseMap.c_str() << std::endl;
	}
	if (specularMap == NULL)
	{
		file << "NULL" << std::endl;
	}
	else
	{
		std::string strSpecularMap;
		CStringHelper::WStringToString(specularMap->GetID(), strSpecularMap);
		file << strSpecularMap.c_str() << std::endl;
	}
	*/
	file.close();
	

	
}

bool CMaterial::LoadMaterial(std::wstring filePath, CMaterial* material)
{
	
	std::ifstream fin;
	fin.open(filePath.c_str());

	char id[MAX_PATH];
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 specular;
	XMFLOAT4 reflect;
	char diffuseMap[MAX_PATH];
	char specularMap[MAX_PATH];
	char normalMap[MAX_PATH];

	const int bufferLength = 1024;
	char readBuffer[bufferLength] = { 0, };
	fin.read(readBuffer, bufferLength);
	fin.close();

	std::string config_doc = readBuffer;

	Json::Value root;
	Json::Reader reader;
	if (reader.parse(config_doc, root) == false)
	{
		return false;
	}

	std::string Jid = root.get("id", "").asString();

	Json::Value Jambient = root["Ambient"];
	ambient.x = Jambient.get("R", 0.0f).asFloat();
	ambient.y = Jambient.get("G", 0.0f).asFloat();
	ambient.z = Jambient.get("B", 0.0f).asFloat();
	ambient.w = Jambient.get("A", 1.0f).asFloat();

	Json::Value Jdiffuse = root["Diffuse"];
	diffuse.x = Jdiffuse.get("R", 0.0f).asFloat();
	diffuse.y = Jdiffuse.get("G", 0.0f).asFloat();
	diffuse.z = Jdiffuse.get("B", 0.0f).asFloat();
	diffuse.w = Jdiffuse.get("A", 1.0f).asFloat();

	Json::Value Jspecular = root["Specular"];
	specular.x = Jspecular.get("R", 0.0f).asFloat();
	specular.y = Jspecular.get("G", 0.0f).asFloat();
	specular.z = Jspecular.get("B", 0.0f).asFloat();
	specular.w = Jspecular.get("A", 0.0f).asFloat();

	std::string JdiffuseMap = root["DiffuseMap"].asString();
	std::string JspeuclarMap = root.get("SpecularMap", 0).asString();
	std::string JnormalMap = root["NormalMap"].asString();

	std::wstring wID, wDiffuseMap, wSpecularMap, wNormalMap;
	CStringHelper::StringToWString(Jid, wID);
	CStringHelper::StringToWString(JdiffuseMap, wDiffuseMap);
	CStringHelper::StringToWString(JspeuclarMap, wSpecularMap);
	CStringHelper::StringToWString(JnormalMap, wNormalMap);


	material->SetID(wID);
	material->SetAmbient(ambient);
	material->SetDiffuse(diffuse);
	material->SetSpecular(specular);
	material->SetReflect(reflect);
	if (g_pResouceMgr->AddTexture(wDiffuseMap))
		material->SetDiffuseMap(g_pResouceMgr->GetTexture(wDiffuseMap));
	if (g_pResouceMgr->AddTexture(wSpecularMap))
		material->SetSpecularMap(g_pResouceMgr->GetTexture(wSpecularMap));
	if (g_pResouceMgr->AddTexture(wNormalMap))
		material->SetNormalMap(g_pResouceMgr->GetTexture(wNormalMap));

	return true;

	//순서
	//ID, ambient, diffuse, specular, reflect, diffuseMap, specularMap

	//fin >> id;
	//fin >> ambient.x >> ambient.y >> ambient.z >> ambient.w;
	//fin >> diffuse.x >> diffuse.y >> diffuse.z >> diffuse.w;
	//fin >> specular.x >> specular.y >> specular.z >> specular.w;
	//fin >> reflect.x >> reflect.y >> reflect.z >> reflect.w;
	//fin >> diffuseMap;
	//fin >> specularMap;
	//
	//fin.close();
	//
	//wchar_t w_id[MAX_PATH];
	//wchar_t w_diffuseMap[MAX_PATH];
	//wchar_t w_specularMap[MAX_PATH];
	////형변환
	//CStringHelper::ConverCtoWC(id, w_id);
	//CStringHelper::ConverCtoWC(diffuseMap, w_diffuseMap);
	//CStringHelper::ConverCtoWC(specularMap, w_specularMap);
	//
	//std::wstring ws_id(w_id);
	//std::wstring ws_diffuseMap(w_diffuseMap);
	//std::wstring ws_specularMap(w_specularMap);
	//
	
	//
	//return true;
	
}

void CMaterial::SetDiffuseMap(CTexture* diffuseMap)
{ 
	if (m_DiffuseMap) m_DiffuseMap->Release();
	m_DiffuseMap = diffuseMap; 
	if (m_DiffuseMap) m_DiffuseMap->AddRef();
}

void CMaterial::SetSpecularMap(CTexture* specular)
{ 
	if (m_SpecularMap) m_SpecularMap->Release();
	m_SpecularMap = specular; 
	if (m_SpecularMap) m_SpecularMap->AddRef();
}

void CMaterial::SetNormalMap(CTexture* normal)
{
	if (m_NormalMap) m_NormalMap->Release();
	m_NormalMap = normal;
	if (m_NormalMap) m_NormalMap->AddRef();
}