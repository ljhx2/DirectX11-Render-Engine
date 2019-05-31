#pragma once

#ifndef _ANIM_EVALUATOR_H_
#define _ANIM_EVALUATOR_H_

#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include "AnimChannel.h"
#include "Bone.h"

class CAnimEvaluator
{
public:
	void						Evaluate(float pTime, std::unordered_map<std::wstring, CBone*>& bones);
	std::vector<XMFLOAT4X4>&	GetTransforms(float dt);
	unsigned int				GetFrameIndexAt(float time);

	std::vector<ST_LOCAL_SQT>&	GetLocalSQT(float dt);

public:
	CAnimEvaluator(const aiAnimation* pAnim);
	~CAnimEvaluator();

public:
	std::wstring					m_name;
	std::vector<CAnimChannel>		m_channels;

	float							m_lastTime;
	float							m_tickPerSecond;
	float							m_duration;

	std::vector < std::tuple<unsigned int, unsigned int, unsigned int> > m_lastPositions;
	std::vector<std::vector<XMFLOAT4X4>>			m_transforms;

	std::vector<std::vector<ST_LOCAL_SQT>>			m_localSQT;
};

static void TransformMatrix(XMFLOAT4X4& out, const aiMatrix4x4& in){// there is some type of alignment issue with my mat4 and the aimatrix4x4 class, so the copy must be manually
	out._11 = in.a1;
	out._12 = in.a2;
	out._13 = in.a3;
	out._14 = in.a4;

	out._21 = in.b1;
	out._22 = in.b2;
	out._23 = in.b3;
	out._24 = in.b4;

	out._31 = in.c1;
	out._32 = in.c2;
	out._33 = in.c3;
	out._34 = in.c4;

	out._41 = in.d1;
	out._42 = in.d2;
	out._43 = in.d3;
	out._44 = in.d4;
}


#endif // !_ANIM_EVALUATOR_H_