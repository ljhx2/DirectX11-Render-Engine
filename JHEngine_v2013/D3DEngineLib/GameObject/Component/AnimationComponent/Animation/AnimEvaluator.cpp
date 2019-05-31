#include "..\..\..\..\Common.h"
#include "AnimEvaluator.h"

#include "..\..\..\..\Core\StringHelper.h"

CAnimEvaluator::CAnimEvaluator(const aiAnimation* pAnim)
{
	m_lastTime = 0.0f;
	m_tickPerSecond = static_cast<float>(pAnim->mTicksPerSecond != 0.0f ? pAnim->mTicksPerSecond : 920.0f);
	m_duration = static_cast<float>(pAnim->mDuration);
	
	CStringHelper::StringToWString(pAnim->mName.data, m_name);

	m_channels.resize(pAnim->mNumChannels);
	for (unsigned int a = 0; a < pAnim->mNumChannels; ++a)
	{
		CStringHelper::StringToWString(pAnim->mChannels[a]->mNodeName.data, m_channels[a].m_name);
		for (unsigned int i = 0; i < pAnim->mChannels[a]->mNumPositionKeys; ++i) m_channels[a].m_positionKeys.push_back(pAnim->mChannels[a]->mPositionKeys[i]);
		for (unsigned int i = 0; i< pAnim->mChannels[a]->mNumRotationKeys; i++) m_channels[a].m_rotationKeys.push_back(pAnim->mChannels[a]->mRotationKeys[i]);
		for (unsigned int i = 0; i< pAnim->mChannels[a]->mNumScalingKeys; i++) m_channels[a].m_scalingKeys.push_back(pAnim->mChannels[a]->mScalingKeys[i]);
	}

	m_lastPositions.resize(pAnim->mNumChannels, std::make_tuple(0, 0, 0));
}


CAnimEvaluator::~CAnimEvaluator()
{
}

void CAnimEvaluator::Evaluate(float pTime, std::unordered_map<std::wstring, CBone*>& bones)
{
	pTime *= m_tickPerSecond;

	float time = 0.0f;
	if (m_duration > 0.0f)
		time = fmod(pTime, m_duration);

	for (unsigned int a = 0; a < m_channels.size(); ++a)
	{
		const CAnimChannel* channel = &m_channels[a];
		std::unordered_map<std::wstring, CBone*>::iterator bonenode = bones.find(channel->m_name);

		if (bonenode == bones.end())
			continue;

		// ***** position ******
		aiVector3D presentPosition(0, 0, 0);
		if (channel->m_positionKeys.size() > 0)
		{
			unsigned int frame = (time >= m_lastTime) ? std::get<0>(m_lastPositions[a]) : 0;
			while (frame < channel->m_positionKeys.size() - 1)
			{
				if (time < channel->m_positionKeys[frame + 1].mTime)
				{
					break;
				}
				frame++;
			}

			unsigned int nextFrame = (frame + 1) % channel->m_positionKeys.size();

			const aiVectorKey& key = channel->m_positionKeys[frame];
			const aiVectorKey& nextKey = channel->m_positionKeys[nextFrame];
			double diffTime = nextKey.mTime - key.mTime;
			if (diffTime < 0.0)
				diffTime += m_duration;
			if (diffTime > 0)
			{
				float factor = float((time - key.mTime) / diffTime);
				presentPosition = key.mValue + (nextKey.mValue - key.mValue) * factor;
			}
			else
			{
				presentPosition = key.mValue;
			}
			std::get<0>(m_lastPositions[a]) = frame;
		}

		//****** rotation ********
		aiQuaternion presentRotation(1, 0, 0, 0);
		if (channel->m_rotationKeys.size() > 0)
		{
			unsigned int frame = (time >= m_lastTime) ? std::get<1>(m_lastPositions[a]) : 0;
			while (frame < channel->m_rotationKeys.size() - 1)
			{
				if (time < channel->m_rotationKeys[frame + 1].mTime)
				{
					break;
				}
				frame++;
			}

			unsigned int nextFrame = (frame + 1) % channel->m_rotationKeys.size();

			const aiQuatKey& key = channel->m_rotationKeys[frame];
			const aiQuatKey& nextKey = channel->m_rotationKeys[nextFrame];
			double diffTime = nextKey.mTime - key.mTime;
			if (diffTime < 0.0) diffTime += m_duration;
			if (diffTime > 0)
			{
				float factor = float((time - key.mTime) / diffTime);
				aiQuaternion::Interpolate(presentRotation, key.mValue, nextKey.mValue, factor);
			}
			else
			{
				presentRotation = key.mValue;
			}
			std::get<1>(m_lastPositions[a]) = frame;
		}

		// ****** scaling ********
		aiVector3D presentScaling(1, 1, 1);
		if (channel->m_scalingKeys.size() > 0)
		{
			unsigned int frame = (time >= m_lastTime) ? std::get<2>(m_lastPositions[a]) : 0;
			while (frame < channel->m_scalingKeys.size() - 1)
			{
				if (time < channel->m_scalingKeys[frame + 1].mTime)
				{
					break;
				}
				frame++;
			}

			presentScaling = channel->m_scalingKeys[frame].mValue;
			std::get<2>(m_lastPositions[a]) = frame;
		}

		aiMatrix4x4 mat = aiMatrix4x4(presentRotation.GetMatrix());

		mat.a1 *= presentScaling.x; mat.b1 *= presentScaling.x; mat.c1 *= presentScaling.x;
		mat.a2 *= presentScaling.y; mat.b2 *= presentScaling.y; mat.c2 *= presentScaling.y;
		mat.a3 *= presentScaling.z; mat.b3 *= presentScaling.z; mat.c3 *= presentScaling.z;
		mat.a4 = presentPosition.x; mat.b4 = presentPosition.y; mat.c4 = presentPosition.z;
		mat.Transpose();

		TransformMatrix(bonenode->second->m_localTransform, mat);

		bonenode->second->m_localSQT.localScale = XMFLOAT3(presentScaling.x, presentScaling.y, presentScaling.y);
		bonenode->second->m_localSQT.localQuternion = XMFLOAT4(presentRotation.x, presentRotation.y, presentRotation.z, presentRotation.w);
		bonenode->second->m_localSQT.localPosition = XMFLOAT3(presentPosition.x, presentPosition.y, presentPosition.z);
	}
	m_lastTime = time;
}

std::vector<XMFLOAT4X4>& CAnimEvaluator::GetTransforms(float dt)
{
	return m_transforms[GetFrameIndexAt(dt)];
}

std::vector<ST_LOCAL_SQT>&	CAnimEvaluator::GetLocalSQT(float dt)
{
	return m_localSQT[GetFrameIndexAt(dt)];
}

unsigned int CAnimEvaluator::GetFrameIndexAt(float ptime)
{
	ptime *= m_tickPerSecond;

	float time = 0.0f;
	if (m_duration > 0.0f)
		time = fmod(ptime, m_duration);

	float percent = time / m_duration;
	
	return static_cast<unsigned int>((static_cast<float>(m_transforms.size()) * percent));
}