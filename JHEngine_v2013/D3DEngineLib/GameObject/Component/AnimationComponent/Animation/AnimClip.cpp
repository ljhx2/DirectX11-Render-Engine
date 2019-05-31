#include "..\..\..\..\Common.h"
#include "AnimClip.h"


CAnimClip::CAnimClip(std::wstring& name, CAnimEvaluator* track,
	float startTime, float endTime, bool isLoop)
	: m_name(name), m_track(track)
	, m_startTime(startTime), m_endTime(endTime), m_isLoop(isLoop)
{
}


CAnimClip::~CAnimClip()
{
}
