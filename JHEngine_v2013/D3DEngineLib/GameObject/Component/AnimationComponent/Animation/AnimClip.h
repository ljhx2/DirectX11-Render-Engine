#pragma once

#ifndef _ANIM_CLIP_H_
#define _ANIM_CLIP_H_

#include <string>
#include "AnimEvaluator.h"

class CAnimClip
{
public:
	std::wstring&			GetName() { return m_name; }
	CAnimEvaluator*			GetTrack() { return m_track; }
	float					GetStartTime() { return m_startTime; }
	float					GetEndTime() { return m_endTime; }
	bool					GetIsLoop() { return m_isLoop; }

public:
	CAnimClip(std::wstring& name, CAnimEvaluator* track,
		float startTime, float endTime, bool isLoop);
	~CAnimClip();

private:
	std::wstring			m_name;

	CAnimEvaluator*			m_track;

	float					m_startTime;
	float					m_endTime;
	
	bool					m_isLoop;

};

#endif // !_ANIM_CLIP_H_
