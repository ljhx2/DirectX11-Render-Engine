#include "..\Common.h"
#include "SceneMgr.h"


CSceneMgr::CSceneMgr()
	: m_pCurrScene(NULL)
{
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Update(float deltaTime)
{
	assert(m_pCurrScene);

	m_pCurrScene->Update(deltaTime);
}

void CSceneMgr::ShadowBuild()
{
	assert(m_pCurrScene);

	m_pCurrScene->ShadowBuild();
}

void CSceneMgr::Render()
{
	assert(m_pCurrScene);

	m_pCurrScene->Render();
}

bool CSceneMgr::ChangeScene(const SCENE_ID_T& id)
{
	SCENE_MAP_T::iterator iter = m_mapScenes.find(id);

	if (iter != m_mapScenes.end())
	{
		if (m_pCurrScene)
		{
			m_pCurrScene->OnLeave();
		}

		m_pCurrScene = iter->second;
		if (m_pCurrScene->OnEnter())
		{
			return true;
		}
	}

	return false;
}

CScene* CSceneMgr::GetCurrScene()
{
	assert(m_pCurrScene);

	return m_pCurrScene;
}

void CSceneMgr::AddScene(CScene* scene)
{
	assert(scene);

	m_mapScenes.insert(std::make_pair(scene->GetSceneID(), scene));
}

void CSceneMgr::DeleteScene(const SCENE_ID_T& id)
{
	SCENE_MAP_T::iterator iter = m_mapScenes.find(id);

	if (iter != m_mapScenes.end())
	{
		SAFE_DELETE(iter->second);
		m_mapScenes.erase(iter);
	}
}

