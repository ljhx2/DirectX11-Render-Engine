#pragma once

#ifndef _ANIM_COMPONENT_H_
#define _ANIM_COMPONENT_H_

#include <vector>

#include "..\Component.h"
#include "Animation\Animator.h"

enum eANIM_PLAY_STATE
{
	eANIM_PLAY,
	eANIM_PAUSE,
	eANIM_STOP,
};

class CAnimComponent : public IComponent
{
	DeclRTTI;
public:
	virtual bool		Setup() override;
	virtual bool		Update(float deltaTime) override;

	virtual bool		HandleMessage(const CMessage& msg) override;

public:
	CAnimator*			GetAnimator()	{ return m_animator; }
	void				SetAnimator(CAnimator* anim); 

	float				GetStartTime() { return m_startTime; }
	float				GetAccumTime() { return m_accumlateTime; }
	float				GetEndTime()	{ return m_endTime; }

	bool				GetUseClip() { return m_useClip; }
	void				SetUseClip(bool b);

	void				SetRootBone(CGameObject* rootBone) { m_rootBone = rootBone; }

public:
	void				PlayAnim();
	void				PauseAnim();
	void				StopAnim();

	void				ChangeAnimation(const std::wstring& name);
	void				ChangeAnimation(int index);

	void				AddClip(std::wstring& name, CAnimEvaluator* track, float start, float end, bool loop);
	void				SelectClip(std::wstring& name);
	CAnimClip*			GetAnimClip(std::wstring& name);
	void				DeleteClip(std::wstring& name);

	std::vector<XMFLOAT4X4>& GetFinalTransforms();

private:
	void				MoveBoneObject(float dt, CGameObject* bone);

public:
	CAnimComponent(const COMPONENT_ID_T id, CGameObject* owner);
	virtual ~CAnimComponent();

private:
	CAnimator*						m_animator;

	float							m_startTime;
	float							m_endTime;
	float							m_accumlateTime;

	eANIM_PLAY_STATE				m_animState;

	bool							m_useClip;

	CAnimClip*						m_currentClip;
	float							m_clipCurrentTime;

	CGameObject*					m_rootBone;
};

#endif // !_ANIM_COMPONENT_H_