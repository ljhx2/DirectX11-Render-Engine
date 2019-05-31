#include "stdafx.h"
#include "..\stdafx.h"
#include "MainGame.h"

#include <GameObject\Component\CameraComponent\CameraComponent.h>
#include <GameObject\Component\RendererComponent\RenderComponent.h>
#include <Resource\gFXManager.h>
#include <Resource\ResourceMgr.h>
#include <Core\MathHelper.h>

#include <GameObject\Component\LightComponent\LightManager.h>
#include <GameObject\Component\CameraComponent\CameraManager.h>


#include <Core\ShadowManager.h>

CMainGame::CMainGame(wxPanel* parnet)
	: m_pParent(parnet)
{
}


CMainGame::~CMainGame()
{
}

bool CMainGame::Setup()
{
	if (g_pResouceMgr->AddEffect(L"FX/Basic.fx") == false) return false;
	

	CScene* newScene = new CScene;
	newScene->SetSceneID(L"newScene");

	wxSize size = m_pParent->GetSize();
	float aspect = size.GetWidth() / size.GetHeight();
	newScene->GetMainCamera()->SetLens(0.25f * CMathHelper::Pi, aspect, 1.0f, 1000.0f);
	
	/////
	//CGameObject* dirLight = new CGameObject(L"dirLight");
	//dirLight->AddComponent<CDirectionalLightComponent>();
	//dirLight->GetTransform()->Rotate_World(-10.0f, 0.0f, 0.0f);
	//
	//newScene->AddSceneNode(dirLight);
	////

	g_pSceneMgr->AddScene(newScene);


	g_pResouceMgr->AddMesh(L"Box");
	g_pResouceMgr->AddMesh(L"Sphere");
	g_pResouceMgr->AddMesh(L"Cylinder");
	g_pResouceMgr->AddMesh(L"Plane");
	//기본메쉬들은 지워지지 않도록 하기위해 레퍼런스카운트를 1올린다.
	g_pResouceMgr->GetMesh(L"Box")->AddRef();
	g_pResouceMgr->GetMesh(L"Sphere")->AddRef();
	g_pResouceMgr->GetMesh(L"Cylinder")->AddRef();
	g_pResouceMgr->GetMesh(L"Plane")->AddRef();
	

	g_pCameraMgr->ChangeCamera(newScene->GetMainCamera());

	return g_pSceneMgr->ChangeScene(L"newScene");
}

void CMainGame::Update(float deltaTime)
{
	g_pGameObjectMgr->ProcessWaitingGameObjects();
	g_pMessageMgr->DispatchDelayedMessage();
	g_pSceneMgr->Update(deltaTime);


}

void CMainGame::ShadowRender()
{
	g_pSceneMgr->ShadowBuild();
}

void CMainGame::Render()
{
	g_pResouceMgr->SetEffectCbPerFrame();
	g_pSceneMgr->Render();

	g_pShadowMgr->RenderScreenQuad();
}



void CMainGame::Destroy()
{
	g_pSceneMgr->GetCurrScene()->AllNodeDelete();
	g_pSceneMgr->DeleteScene(L"newScene");
	g_pGameObjectMgr->DestroyAllGameObjects();

	//싱글톤삭제
	g_pGameObjectMgr->Destroy();
	g_pMessageMgr->Destroy();
	g_pSceneMgr->Destroy();
}