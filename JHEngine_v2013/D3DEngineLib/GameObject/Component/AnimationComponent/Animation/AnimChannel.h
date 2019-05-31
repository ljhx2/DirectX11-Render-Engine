#pragma once

#ifndef _ANIM_CHANNEL_H_
#define _ANIM_CHANNEL_H_

#include <string>
#include <vector>
#include <assimp/anim.h>


class CAnimChannel
{
public:
	CAnimChannel();
	~CAnimChannel();

public:
	std::wstring				m_name;
	std::vector<aiVectorKey>	m_positionKeys;
	std::vector<aiQuatKey>		m_rotationKeys;
	std::vector<aiVectorKey>	m_scalingKeys;
	
};

#endif // !_ANIM_CHANNEL_H_