#include "..\..\..\..\Common.h"
#include "Animator.h"

#include "..\..\..\..\Core\StringHelper.h"

CAnimator::CAnimator()
{
	m_skeleton = NULL;
	m_currentAnimIndex = -1;
	createBoneIndex = 0;
}


CAnimator::~CAnimator()
{
	delete m_skeleton;

	std::unordered_map<std::wstring, CAnimClip*>::iterator iter;
	for (iter = m_animClips.begin(); iter != m_animClips.end(); ++iter)
	{
		delete iter->second;
	}
}

void CAnimator::Init(const aiScene* pScene)
{
	if (!pScene->HasAnimations()) return;

	m_skeleton = CreateBoneTree(pScene->mRootNode, NULL);

	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i)
	{
		const aiMesh* mesh = pScene->mMeshes[i];

		for (unsigned int n = 0; n < mesh->mNumBones; ++n)
		{
			const aiBone* bone = mesh->mBones[n];
			std::wstring boneName;
			CStringHelper::StringToWString(bone->mName.data, boneName);

			std::unordered_map<std::wstring, CBone*>::iterator found;
			found = m_bonesByName.find(boneName);
			if (found != m_bonesByName.end())
			{
				bool skip = false;
				for (unsigned int j = 0; j < m_bones.size(); ++j)
				{
					if (m_bones[j]->m_name == boneName)
					{
						skip = true;
						break;
					}
				}
				if (!skip)
				{
					aiMatrix4x4 temp = bone->mOffsetMatrix;
					TransformMatrix(found->second->m_offset, temp.Transpose());
					m_bones.push_back(found->second);
					m_bonesToIndex[found->first] = m_bones.size() - 1;
				}
			}
		}
	}
	ExtractAnimations(pScene);

	m_transforms.resize(m_bones.size());
	float timestep = 1.0f / 60.0f;	// FPS 60
	for (int i = 0; i < m_animations.size(); ++i)
	{
		SetAnimIndex(i);
		float dt = 0.0f;
		for (float ticks = 0.0f; ticks < m_animations[i].m_duration; ticks += m_animations[i].m_tickPerSecond / 60.0f)
		{
			dt += timestep;
			Calculate(dt);

			m_animations[i].m_transforms.push_back(std::vector<XMFLOAT4X4>());
			std::vector<XMFLOAT4X4>& trans = m_animations[i].m_transforms.back();

			m_animations[i].m_localSQT.push_back(std::vector<ST_LOCAL_SQT>());
			std::vector<ST_LOCAL_SQT>& sqt = m_animations[i].m_localSQT.back();

			for (int a = 0; a < m_transforms.size(); ++a)
			{
				XMFLOAT4X4 rotationmat;
				XMMATRIX temp = XMLoadFloat4x4(&m_bones[a]->m_offset) * XMLoadFloat4x4(&m_bones[a]->m_globalTransform);
				XMStoreFloat4x4(&rotationmat, temp);
				trans.push_back(rotationmat);

				sqt.push_back(m_bones[a]->m_localSQT);
			}
		}
	}
}

bool CAnimator::SetAnimIndex(int pAnimIndex)
{
	if (pAnimIndex >= m_animations.size()) return false;
	int oldindex = m_currentAnimIndex;
	m_currentAnimIndex = pAnimIndex;
	return oldindex != m_currentAnimIndex;
}

bool CAnimator::SetAnimation(const std::wstring& name)
{
	std::unordered_map<std::wstring, unsigned int>::iterator iter;
	iter = m_animationNameToId.find(name);
	int oldindex = m_currentAnimIndex;
	if (iter != m_animationNameToId.end()) m_currentAnimIndex = iter->second;
	return oldindex != m_currentAnimIndex;
}

CAnimEvaluator* CAnimator::GetAnimation(std::wstring& name)
{
	std::unordered_map<std::wstring, unsigned int>::iterator iter;
	iter = m_animationNameToId.find(name);
	if (iter == m_animationNameToId.end()) return NULL;
	return &m_animations[iter->second];
}


int CAnimator::GetBoneIndex(const std::wstring& bname)
{
	std::unordered_map<std::wstring, unsigned int>::iterator found = m_bonesToIndex.find(bname);
	if (found != m_bonesToIndex.end())
		return found->second; 
	else return -1;
}

XMFLOAT4X4 CAnimator::GetBoneTransform(float dt, const std::wstring& name)
{
	int bindex = GetBoneIndex(name); 

	if (bindex == -1)
	{
		XMFLOAT4X4 i;
		XMStoreFloat4x4(&i, XMMatrixIdentity());
		return i;
	}

	return m_animations[m_currentAnimIndex].GetTransforms(dt)[bindex];
}

XMFLOAT4X4 CAnimator::GetBoneTransform(float dt, unsigned int bindex)
{
	return m_animations[m_currentAnimIndex].GetTransforms(dt)[bindex];
}

ST_LOCAL_SQT CAnimator::GetBoneSQT(float dt, const std::wstring& name)
{
	int bindex = GetBoneIndex(name);

	if (bindex == -1)
	{
		ST_LOCAL_SQT i;
		i.localPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
		i.localScale = XMFLOAT3(1.0f, 1.0f, 1.0f);
		XMStoreFloat4(&i.localQuternion, XMQuaternionIdentity());
		return i;
	}

	return m_animations[m_currentAnimIndex].GetLocalSQT(dt)[bindex];
}

//private
void CAnimator::UpdateTransforms(CBone* pNode)
{
	CalculateBoneToWorldTransform(pNode);
	for (std::vector<CBone*>::iterator it = pNode->m_children.begin(); it != pNode->m_children.end(); ++it)
	{
		UpdateTransforms(*it);
	}
}

void CAnimator::CalculateBoneToWorldTransform(CBone* child)
{
	child->m_globalTransform = child->m_localTransform;
	CBone* parent = child->m_parent;
	while (parent)
	{
		//child->m_globalTransform *= parent->m_localTransform;
		XMMATRIX temp = XMLoadFloat4x4(&child->m_globalTransform) * XMLoadFloat4x4(&parent->m_localTransform);
		XMStoreFloat4x4(&child->m_globalTransform, temp);
		parent = parent->m_parent;
	}
}

void CAnimator::Calculate(float pTime)
{
	if ((m_currentAnimIndex < 0) || m_currentAnimIndex >= m_animations.size()) 
		return;

	m_animations[m_currentAnimIndex].Evaluate(pTime, m_bonesByName);
	UpdateTransforms(m_skeleton);
}

//void CAnimator::CalcBoneMatrices()
//{
//	for (int a = 0; a < m_transforms.size(); ++a)
//	{
//		XMMATRIX temp = XMLoadFloat4x4(&m_bones[a]->m_offset) * XMLoadFloat4x4(&m_bones[a]->m_globalTransform);
//		XMStoreFloat4x4(&m_transforms[a], temp);
//	}
//}

void CAnimator::ExtractAnimations(const aiScene* pScene)
{
	for (int i = 0; i < pScene->mNumAnimations; ++i)
	{
		m_animations.push_back(CAnimEvaluator(pScene->mAnimations[i]));
	}

	for (int i = 0; i < m_animations.size(); ++i)
	{
		m_animationNameToId.insert(std::make_pair(m_animations[i].m_name, i));
	}
	m_currentAnimIndex = 0;

}

CBone* CAnimator::CreateBoneTree(aiNode* pNode, CBone* pParent)
{
	CBone* internalNode = new CBone;
	CStringHelper::StringToWString(pNode->mName.data, internalNode->m_name);
	internalNode->m_parent = pParent;

	if (internalNode->m_name == L"")
	{
		internalNode->m_name = L"foo" + createBoneIndex++;
	}

	m_bonesByName[internalNode->m_name] = internalNode;
	aiMatrix4x4 temp = pNode->mTransformation;
	TransformMatrix(internalNode->m_localTransform, temp.Transpose());
	internalNode->m_originalLocalTransform = internalNode->m_localTransform;
	CalculateBoneToWorldTransform(internalNode);

	for (unsigned int a = 0; a < pNode->mNumChildren; ++a)
	{
		internalNode->m_children.push_back(CreateBoneTree(pNode->mChildren[a], internalNode));
	}
	return internalNode;
}