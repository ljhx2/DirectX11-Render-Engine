#pragma once

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <assimp/scene.h>
#include "AnimEvaluator.h"
#include "Bone.h"

#include "AnimClip.h"

class CAnimator
{
	friend class CAssimpParser; //m_bonesByName 사용하기 위해서

public:
	void		Init(const aiScene* pScene);
	bool		HasSkeleton() const { return !m_bones.empty(); }

	int			GetAnimIndex() const { return m_currentAnimIndex; }
	bool		SetAnimIndex(int pAnimIndex);
	bool		SetAnimation(const std::wstring& name);
	CAnimEvaluator* GetAnimation(std::wstring& name);

	std::vector<XMFLOAT4X4>& GetTransforms(float dt) { return m_animations[m_currentAnimIndex].GetTransforms(dt); }
	std::wstring			GetAnimationName() const { return m_animations[m_currentAnimIndex].m_name; }

	int			GetBoneIndex(const std::wstring& bname);
	XMFLOAT4X4	GetBoneTransform(float dt, const std::wstring& name);
	XMFLOAT4X4	GetBoneTransform(float dt, unsigned int bindex);

	ST_LOCAL_SQT GetBoneSQT(float dt, const std::wstring& name);


private:
	void		UpdateTransforms(CBone* pNode);
	void		CalculateBoneToWorldTransform(CBone* pInternalNode);

	void		Calculate(float pTime);
	//void		CalcBoneMatrices();

	void		ExtractAnimations(const aiScene* pScene);
	int			createBoneIndex;
	CBone*		CreateBoneTree(aiNode* pNode, CBone* pParent);

public:
	CAnimator();
	~CAnimator();

public:
	std::vector<CAnimEvaluator>						m_animations;
	int												m_currentAnimIndex;

public:
	//clip
	std::unordered_map<std::wstring, CAnimClip*>		m_animClips;

private:
	CBone*											m_skeleton;	//루트 노드
	std::unordered_map<std::wstring, CBone*>		m_bonesByName;
	std::unordered_map<std::wstring, unsigned int>	m_bonesToIndex;
	std::unordered_map<std::wstring, unsigned int>	m_animationNameToId;
	std::vector<CBone*>								m_bones;
	std::vector<XMFLOAT4X4>							m_transforms;
};

#endif // !_ANIMATOR_H_