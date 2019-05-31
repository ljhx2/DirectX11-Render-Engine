#include "..\Common.h"
#include "AssimpParser.h"

#include "..\Core\StringHelper.h"
#include "..\Resource\VertexType.h"
#include "..\Resource\Effect.h"

#include "..\Resource\ResourceMgr.h"

#include "..\GameObject\Component\RendererComponent\RenderComponent.h"
#include "..\GameObject\Component\RendererComponent\SkinnedMeshRenderer.h"
#include "..\GameObject\Component\AnimationComponent\AnimComponent.h"

CAssimpParser::CAssimpParser()
{
}


CAssimpParser::~CAssimpParser()
{
	
}

CGameObject* CAssimpParser::LoadFile(const std::wstring& fileFullPath)
{

	std::string str_fileName;
	CStringHelper::WStringToString(fileFullPath, str_fileName);

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(str_fileName.c_str(), aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
	if (scene == NULL) return NULL;

	std::wstring fileName = CStringHelper::PickFileNameFromFullPath(fileFullPath);
	CGameObject* rootObj = new CGameObject(fileName);

	//animator
	if (scene->HasAnimations())
	{
		CAnimator* animator = ExtractAnimation(scene);
		m_animator = animator;
		CAnimComponent* animComp = rootObj->AddComponent<CAnimComponent>();
		animComp->SetAnimator(animator);

		//Bone GameObject
		CBone* rootBone = NULL;
		rootBone = m_animator->m_bonesByName[L"XS_Dummy_Root"];
		if (rootBone)
		{
			CGameObject* boneGameObject = CreateBoneGameObject(rootBone);
			boneGameObject->GetTransform()->Rotate_World(XMConvertToRadians(-90), 0, 0);
			rootObj->AddChild(boneGameObject);
			animComp->SetRootBone(boneGameObject);
		}
		
	}

	PairMeshNumAndMeshName(scene->mRootNode);

	for (int i = 0; i < scene->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[i];

		CMesh* myMesh;
		if (mesh->HasBones())
		{
			ExtractBoneWeightsFromMesh(mesh);
			myMesh = ExtractSkinnedMesh(mesh, m_mapMeshNumName[i]);
			m_vertToBoneWeight.clear();
		}
		else
		{
			myMesh = ExtractMesh(mesh, m_mapMeshNumName[i]);
		}
		
		if (myMesh == NULL) return NULL;

		CGameObject* renderObj = new CGameObject(m_mapMeshNumName[i]);
		if (myMesh->GetMeshType() == MESH_TYPE_SKINNED)
		{
			CSkinnedMeshRenderer* renderComp = renderObj->AddComponent<CSkinnedMeshRenderer>();
			renderComp->SetMesh(myMesh);
			renderComp->SetEffect(g_pResouceMgr->GetEffect(L"FX/Basic.fx"));
		}
		else
		{
			CRenderComponent* renderComp = renderObj->AddComponent<CRenderComponent>();
			renderComp->SetMesh(myMesh);
			renderComp->SetEffect(g_pResouceMgr->GetEffect(L"FX/Basic.fx"));
		}

		rootObj->AddChild(renderObj);
	}

	

	//aiReleaseImport(scene);

	return rootObj;
}

void CAssimpParser::PairMeshNumAndMeshName(aiNode* node)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		std::wstring name;
		CStringHelper::StringToWString(node->mName.data, name);
		m_mapMeshNumName[node->mMeshes[i]] = name;
	}

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		PairMeshNumAndMeshName(node->mChildren[i]);
	}
}

CAnimator* CAssimpParser::ExtractAnimation(const aiScene* scene)
{
	CAnimator* animator = new CAnimator();
	animator->Init(scene);

	return animator;
}

void CAssimpParser::ExtractBoneWeightsFromMesh(aiMesh* mesh)
{
	for (int i = 0; i < mesh->mNumBones; ++i)
	{
		const aiBone* bone = mesh->mBones[i];
		std::wstring boneName;
		CStringHelper::StringToWString(bone->mName.data, boneName);

		int boneIndex = m_animator->GetBoneIndex(boneName);

		for (int j = 0; j < bone->mNumWeights; ++j)
		{
			aiVertexWeight weight = bone->mWeights[j];
			if (m_vertToBoneWeight.find(weight.mVertexId) != m_vertToBoneWeight.end())
			{
				m_vertToBoneWeight[weight.mVertexId].push_back(ST_VertexWeight(boneIndex, weight.mWeight));
			}
			else
			{
				std::vector<ST_VertexWeight> vecST;
				vecST.push_back(ST_VertexWeight(boneIndex, weight.mWeight));
				m_vertToBoneWeight.insert(std::make_pair(weight.mVertexId, vecST));
			}
		}
	}
}

CMesh* CAssimpParser::ExtractSkinnedMesh(const aiMesh* mesh, std::wstring& meshName)
{
	std::vector<Vertex_PTNTanWB>	vertices;
	std::vector<DWORD>				indices;

	vertices.resize(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		if (mesh->HasPositions())
		{
			vertices[i].Pos.x = mesh->mVertices[i].x;
			vertices[i].Pos.y = mesh->mVertices[i].y;
			vertices[i].Pos.z = mesh->mVertices[i].z;
		}

		if (mesh->HasNormals())
		{
			vertices[i].Normal.x = mesh->mNormals[i].x;
			vertices[i].Normal.y = mesh->mNormals[i].y;
			vertices[i].Normal.z = mesh->mNormals[i].z;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			vertices[i].Tangent.x = mesh->mTangents[i].x;
			vertices[i].Tangent.y = mesh->mTangents[i].y;
			vertices[i].Tangent.z = mesh->mTangents[i].z;
		}

		if (mesh->HasTextureCoords(0))
		{
			vertices[i].Tex.x = mesh->mTextureCoords[0][i].x;
			vertices[i].Tex.y = -(mesh->mTextureCoords[0][i].y);
		}

		if (mesh->HasBones())
		{
			assert(m_vertToBoneWeight[i].size() <= 4 && "m_vertToBoneWeight.size > 4");

			for (int j = 0; j < m_vertToBoneWeight[i].size(); ++j)
			{
				vertices[i].JointIndices[j] = m_vertToBoneWeight[i].at(j).boneIndex;
				if (j < 3)
					vertices[i].Weights[j] = m_vertToBoneWeight[i].at(j).weight;
			}
		}

	}  // !for vertices

	unsigned int nidx;
	switch (mesh->mPrimitiveTypes)
	{
	case aiPrimitiveType_POINT:
		nidx = 1; break;
	case aiPrimitiveType_LINE:
		nidx = 2; break;
	case aiPrimitiveType_TRIANGLE:
		nidx = 3; break;
	default:
		//assert(false && "mesh->mPrimitiveTypes is invalied");
		nidx = 3; break;
		break;
	}

	for (UINT i = 0; i < mesh->mNumFaces; ++i)
	{
		for (UINT j = 0; j < nidx; ++j)
		{
			indices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	// ! Indices

	CMesh* myMesh = new CMesh(meshName);

	myMesh->SetVertexStride(sizeof(Vertex_PTNTanWB));
	
	myMesh->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	switch (mesh->mPrimitiveTypes)
	{
	case aiPrimitiveType_POINT:
		myMesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case aiPrimitiveType_LINE:
		myMesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case aiPrimitiveType_TRIANGLE:
		myMesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	default:
		//assert(false && "mesh->mPrimitiveTypes is invalied");
		myMesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	}

	myMesh->SetFaceCount(mesh->mNumFaces);


	myMesh->SetMeshType(MESH_TYPE_SKINNED);
	

	myMesh->SetVertexCount(vertices.size());
	myMesh->SetIndexCount(indices.size());
	myMesh->SetVertexOffset(0);

	
	if (myMesh->CreateVertexBuffer(&vertices[0], sizeof(Vertex_PTNTanWB) * myMesh->GetVertexCount()) == false
		|| myMesh->CreateIndexBuffer(&indices[0], sizeof(DWORD) * myMesh->GetIndexCount()) == false)
	{
		SAFE_DELETE(myMesh);
		assert(false && "CreateMesh Failed");
		return NULL;
	}

	CEffect* effect = g_pResouceMgr->GetEffect(L"FX/Basic.fx");
	ID3DX11EffectTechnique* tech;
	tech = effect->GetSkinnedTech();


	if (myMesh->CreateLayout(vertexPTNTanWBLayout, 6, tech, 0) == false)
	{
		SAFE_DELETE(myMesh);
		assert(false && "CreateLayout Failed");
		return NULL;
	}

	return myMesh;


}

CMesh* CAssimpParser::ExtractMesh(const aiMesh* mesh, std::wstring& meshName)
{
	std::vector<Vertex_PTNTan>	vertices;
	std::vector<DWORD>				indices;

	vertices.resize(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		if (mesh->HasPositions())
		{
			vertices[i].Pos.x = mesh->mVertices[i].x;
			vertices[i].Pos.y = mesh->mVertices[i].y;
			vertices[i].Pos.z = mesh->mVertices[i].z;
		}

		if (mesh->HasNormals())
		{
			vertices[i].Normal.x = mesh->mNormals[i].x;
			vertices[i].Normal.y = mesh->mNormals[i].y;
			vertices[i].Normal.z = mesh->mNormals[i].z;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			vertices[i].Tangent.x = mesh->mTangents[i].x;
			vertices[i].Tangent.y = mesh->mTangents[i].y;
			vertices[i].Tangent.z = mesh->mTangents[i].z;
		}

		if (mesh->HasTextureCoords(0))
		{
			vertices[i].Tex.x = mesh->mTextureCoords[0][i].x;
			vertices[i].Tex.y = -(mesh->mTextureCoords[0][i].y);
		}

	}  // !for vertices

	unsigned int nidx;
	switch (mesh->mPrimitiveTypes)
	{
	case aiPrimitiveType_POINT:
		nidx = 1; break;
	case aiPrimitiveType_LINE:
		nidx = 2; break;
	case aiPrimitiveType_TRIANGLE:
		nidx = 3; break;
	default:
		//assert(false && "mesh->mPrimitiveTypes is invalied");
		nidx = 3; break;
		break;
	}

	for (UINT i = 0; i < mesh->mNumFaces; ++i)
	{
		for (UINT j = 0; j < nidx; ++j)
		{
			indices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	// ! Indices

	CMesh* myMesh = new CMesh(meshName);
	
	myMesh->SetVertexStride(sizeof(Vertex_PTNTan));
	myMesh->SetIndexFormat(DXGI_FORMAT_R32_UINT);

	switch (mesh->mPrimitiveTypes)
	{
	case aiPrimitiveType_POINT:
		myMesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case aiPrimitiveType_LINE:
		myMesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case aiPrimitiveType_TRIANGLE:
		myMesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	default:
		//assert(false && "mesh->mPrimitiveTypes is invalied");
		myMesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	}

	myMesh->SetFaceCount(mesh->mNumFaces);

	
	myMesh->SetMeshType(MESH_TYPE_STATIC);

	myMesh->SetVertexCount(vertices.size());
	myMesh->SetIndexCount(indices.size());
	myMesh->SetVertexOffset(0);


	if (myMesh->CreateVertexBuffer(&vertices[0], sizeof(Vertex_PTNTan) * myMesh->GetVertexCount()) == false
		|| myMesh->CreateIndexBuffer(&indices[0], sizeof(DWORD) * myMesh->GetIndexCount()) == false)
	{
		SAFE_DELETE(myMesh);
		assert(false && "CreateMesh Failed");
		return NULL;
	}

	CEffect* effect = g_pResouceMgr->GetEffect(L"FX/Basic.fx");
	ID3DX11EffectTechnique* tech;
	tech = effect->GetTech();
	

	if (myMesh->CreateLayout(vertexPTNTanLayout, 4, tech, 0) == false)
	{
		SAFE_DELETE(myMesh);
		assert(false && "CreateLayout Failed");
		return NULL;
	}

	return myMesh;
	

	
}

CGameObject* CAssimpParser::CreateBoneGameObject(CBone* bone)
{
	CGameObject* gameObject = new CGameObject(bone->m_name);

	XMMATRIX matrix = XMLoadFloat4x4(&bone->m_localTransform);
	gameObject->GetTransform()->SetMatrix(matrix);

	//test
	//CRenderComponent* rendComp = gameObject->AddComponent<CRenderComponent>();
	//rendComp->SetMesh(g_pResouceMgr->GetMesh(L"Cylinder"));
	//rendComp->SetEffect(g_pResouceMgr->GetEffect(L"FX/Basic.fx"));

	for (int i = 0; i < bone->m_children.size(); ++i)
	{
		CGameObject* child = CreateBoneGameObject(bone->m_children[i]);
		gameObject->AddChild(child);
	}

	return gameObject;
}