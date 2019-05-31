#include "..\Common.h"
#include "Scene.h"

#include "..\Core\MathHelper.h"


CScene::CScene()
	: m_mainCameraComp(NULL), m_globalLight(NULL), m_grid(NULL)
{
	m_grid = new CGrid(this);
	m_sceneRoot = new CGameObject(L"SCENE_ROOT");
	m_mainCamera = new CGameObject(L"TOOL_CAMERA");
	m_mainCameraComp = m_mainCamera->AddComponent<CToolCameraComponent>();
	
}


CScene::~CScene()
{
	SAFE_DELETE(m_grid);
	SAFE_DELETE(m_sceneRoot);
	SAFE_DELETE(m_mainCamera);
}

bool CScene::Setup()
{
	m_grid->Setup(3, 20);

	m_mainCameraComp->Walk(-30.0f);
	m_mainCameraComp->Rise(10.0f);

	return m_sceneRoot->Setup();
}

void CScene::Update(float deltaTime)
{
	m_mainCamera->Update(deltaTime);
	m_sceneRoot->Update(deltaTime);
}

void CScene::ShadowBuild()
{
	m_sceneRoot->ShadowBuild();
}

void CScene::Render()
{
	m_grid->Render();

	m_sceneRoot->Render();
}

void CScene::AddSceneNode(CGameObject* obj)
{
	m_sceneRoot->AddChild(obj);
	obj->SetParent(m_sceneRoot);
	obj->SetOwnerScene(this);
}

void CScene::DeleteSceneNode(CGameObject* obj)
{
	m_sceneRoot->SubChild(obj);
}

void CScene::AllNodeDelete()
{
	
}