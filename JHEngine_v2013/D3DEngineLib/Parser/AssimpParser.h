#pragma once

#ifndef _ASSIMP_PARSER_H_
#define _ASSIMP_PARSER_H_

// CRT
#include <string>
#include <vector>
#include <unordered_map>

// Others
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/ai_assert.h>
#include <assimp/cfileio.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/IOSystem.hpp>
#include <assimp/IOStream.hpp>
#include <assimp/LogStream.hpp>
#include <assimp/DefaultLogger.hpp>


#include <fbxsdk.h>

// Resource
#include "..\GameObject\GameObject.h"
#include "..\GameObject\Component\AnimationComponent\Animation\Animator.h"
#include "..\Resource\Mesh.h"

struct ST_VertexWeight
{
	UINT	boneIndex;
	FLOAT	weight;

	ST_VertexWeight(UINT _index, FLOAT _weight)
		: boneIndex(_index), weight(_weight) {}
};

class CAssimpParser
{
public:
	CGameObject*		LoadFile(const std::wstring& fileFullPath);


private:
	void				PairMeshNumAndMeshName(aiNode* node);

	CAnimator*			ExtractAnimation(const aiScene* scene)
		;
	void				ExtractBoneWeightsFromMesh(aiMesh* mesh);
	CMesh*				ExtractMesh(const aiMesh* mesh, std::wstring& meshName);
	CMesh*				ExtractSkinnedMesh(const aiMesh* mesh, std::wstring& meshName);

	CGameObject*		CreateBoneGameObject(CBone* bone);

public:
	CAssimpParser();
	~CAssimpParser();

private:
	CAnimator*			m_animator;
	std::unordered_map<UINT, std::vector<ST_VertexWeight>> m_vertToBoneWeight;

	std::unordered_map<UINT, std::wstring> m_mapMeshNumName;

};

#endif // !_ASSIMP_PARSER_H_