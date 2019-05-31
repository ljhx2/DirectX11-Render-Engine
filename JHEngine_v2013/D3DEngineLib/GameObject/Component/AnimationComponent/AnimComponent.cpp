#include "..\..\..\Common.h"
#include "AnimComponent.h"


#include "..\..\GameObject.h"

ImplRTTI(CAnimComponent, IComponent);

CAnimComponent::CAnimComponent(const COMPONENT_ID_T id, CGameObject* owner)
	: IComponent(id, owner), m_animator(NULL), m_useClip(false), m_currentClip(NULL)
	, m_rootBone(NULL)
{
	m_startTime = 0.0f;
	m_endTime = 0.0f;
	m_accumlateTime = 0.0f;
	m_clipCurrentTime = 0.0f;

	m_animState = eANIM_PLAY;
}


CAnimComponent::~CAnimComponent()
{
}

bool CAnimComponent::Setup()
{
	return true;
}

bool CAnimComponent::Update(float deltaTime)
{
	if (m_animator == NULL) return true;

	if (!m_useClip)
	{
		switch (m_animState)
		{
		case eANIM_PLAY:
		{
			m_accumlateTime += deltaTime;
			if (m_accumlateTime > m_endTime)
				m_accumlateTime = m_startTime;
		}
		break;
		case eANIM_PAUSE:
			break;
		case eANIM_STOP:
		{
			m_accumlateTime = 0.0f;
		}
		break;
		default:
			break;
		}

		//Bone GameObject 움직이기
		MoveBoneObject(m_accumlateTime, m_rootBone);
	}
	else
	{
		if (!m_currentClip) return true;

		switch (m_animState)
		{
		case eANIM_PLAY:
		{
			m_clipCurrentTime += deltaTime;
			if (m_clipCurrentTime > m_currentClip->GetEndTime())
			{
				if (m_currentClip->GetIsLoop())
					m_clipCurrentTime = m_currentClip->GetStartTime();
				else
					m_clipCurrentTime = m_currentClip->GetEndTime();
			}
		}
			break;
		case eANIM_PAUSE:
			break;
		case eANIM_STOP:
		{
			m_clipCurrentTime = m_currentClip->GetStartTime();
		}
			break;
		default:
			break;
		}

		//Bone GameObject 움직이기
		MoveBoneObject(m_clipCurrentTime, m_rootBone);
	}


	

}

bool CAnimComponent::HandleMessage(const CMessage& msg)
{
	return false;
}

void CAnimComponent::SetAnimator(CAnimator* anim)
{
	 m_animator = anim; 

	 m_endTime = m_animator->m_animations[m_animator->GetAnimIndex()].m_duration /
		 m_animator->m_animations[m_animator->GetAnimIndex()].m_tickPerSecond;
}

void CAnimComponent::SetUseClip(bool b)
{
	m_useClip = b;
	StopAnim();
}

void CAnimComponent::PlayAnim()
{
	if (m_animState == eANIM_PLAY) return;

	m_animState = eANIM_PLAY;
}

void CAnimComponent::PauseAnim()
{
	if (m_animState == eANIM_PAUSE) return;

	m_animState = eANIM_PAUSE;
}

void CAnimComponent::StopAnim()
{
	if (m_animState == eANIM_STOP) return;

	m_animState = eANIM_STOP;
}

void CAnimComponent::ChangeAnimation(const std::wstring& name)
{
	if (m_animator->SetAnimation(name))
	{
		m_accumlateTime = 0.0f;

		m_endTime = m_animator->m_animations[m_animator->GetAnimIndex()].m_duration /
			m_animator->m_animations[m_animator->GetAnimIndex()].m_tickPerSecond;
	}
}

void CAnimComponent::ChangeAnimation(int index)
{
	if (m_animator->SetAnimIndex(index))
	{
		m_accumlateTime = 0.0f;

		m_endTime = m_animator->m_animations[m_animator->GetAnimIndex()].m_duration /
			m_animator->m_animations[m_animator->GetAnimIndex()].m_tickPerSecond;
	}
}

void CAnimComponent::AddClip(std::wstring& name, CAnimEvaluator* track, float start, float end, bool loop)
{
	if (!m_animator) return;

	if (m_animator->m_animClips.find(name) != m_animator->m_animClips.end()) return;

	m_animator->m_animClips[name] = new CAnimClip(name, track, start, end, loop);
}

void CAnimComponent::SelectClip(std::wstring& name)
{
	if (!m_animator) return;

	if (m_animator->m_animClips.find(name) != m_animator->m_animClips.end())
	{
		m_currentClip = m_animator->m_animClips.find(name)->second;
		m_clipCurrentTime = m_currentClip->GetStartTime();
	}
}

CAnimClip* CAnimComponent::GetAnimClip(std::wstring& name)
{
	if (!m_animator) return NULL;

	if (m_animator->m_animClips.find(name) != m_animator->m_animClips.end())
	{
		return m_animator->m_animClips.find(name)->second;
	}
	
	return NULL;
}

void CAnimComponent::DeleteClip(std::wstring& name)
{
	if (!m_animator) return;

	auto iter = m_animator->m_animClips.find(name);
	if (iter != m_animator->m_animClips.end())
	{
		if (iter->second == m_currentClip)
		{
			m_currentClip = NULL;
			StopAnim();
		}

		delete iter->second;
		m_animator->m_animClips.erase(iter);
	}

}

std::vector<XMFLOAT4X4>& CAnimComponent::GetFinalTransforms()
{
	if (!m_useClip)
	{
		return m_animator->GetTransforms(m_accumlateTime);
	}

	// useClip
	if (m_currentClip)
		return m_currentClip->GetTrack()->GetTransforms(m_clipCurrentTime);
	else
		return m_animator->GetTransforms(0.0f);

}

void CAnimComponent::MoveBoneObject(float dt, CGameObject* bone)
{
	if (!bone) return;

	if (m_animator->GetBoneIndex(bone->GetID()) == -1)
	{
		for (int i = 0; i < bone->GetChildCount(); ++i)
		{
			MoveBoneObject(dt, bone->GetChild(i));
		}
		return;
	}

	ST_LOCAL_SQT sqt = m_animator->GetBoneSQT(dt, bone->GetID());
	bone->GetTransform()->SetScale(sqt.localScale.x, sqt.localScale.y, sqt.localScale.y);
	bone->GetTransform()->SetPosition(sqt.localPosition.x, sqt.localPosition.y, sqt.localPosition.z);
	bone->GetTransform()->SetQuternion(sqt.localQuternion.x, sqt.localQuternion.y, sqt.localQuternion.z, sqt.localQuternion.w);

	for (int i = 0; i < bone->GetChildCount(); ++i)
	{
		MoveBoneObject(dt, bone->GetChild(i));
	}
}