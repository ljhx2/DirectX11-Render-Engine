#include "stdafx.h"
#include "..\stdafx.h"
#include "ViewPanel.h"

#include <Core\GameTimer.h>

#include <GameObject\GameObjectMgr.h>
#include <Core\ShadowManager.h>


#include "..\Frame\cMainFrame.h"

BEGIN_EVENT_TABLE(CViewPanel, wxPanel)
	
	EVT_IDLE(CViewPanel::OnIdle)
	EVT_ERASE_BACKGROUND(CViewPanel::OnRender)
	EVT_SIZE(CViewPanel::OnSize)

	EVT_MOTION(CViewPanel::OnMouseMove)
	EVT_LEFT_DOWN(CViewPanel::OnLMouseDown)
	EVT_LEFT_UP(CViewPanel::OnLMouseUp)
	EVT_RIGHT_DOWN(CViewPanel::OnRMouseDown)
	EVT_RIGHT_UP(CViewPanel::OnRMouseUp)
	EVT_MOUSEWHEEL(CViewPanel::OnMouseWheel)

	EVT_KILL_FOCUS(CViewPanel::OnKillFocus)
	EVT_SET_FOCUS(CViewPanel::OnSetFocus)
	

END_EVENT_TABLE()


CViewPanel::CViewPanel(cMainFrame* parent)
: wxPanel(parent), m_mainFrame(parent)
	, m_renderer(NULL), m_mainGame(NULL), m_isDrag(false)
{
	m_lastMousePoint.x = 0;
	m_lastMousePoint.y = 0;

	m_renderer = new D3DRenderer;
	wxSize panelSize = this->GetSize();
	CreateD3D(this->GetHWND(), panelSize.GetWidth(), panelSize.GetHeight());

	m_mainGame = new CMainGame(this);

	m_mainGame->Setup();

	g_pGameTimer->Reset();

	g_pShadowMgr->Init();
}


CViewPanel::~CViewPanel()
{
	m_mainGame->Destroy();
	SAFE_DELETE(m_mainGame);

	DestroyD3D();
	SAFE_DELETE(m_renderer);
}

bool CViewPanel::CreateD3D(HWND hWnd, int ClientWidth, int ClientHeight)
{
	return m_renderer->CreateDevice(hWnd, ClientWidth, ClientHeight);
}

void CViewPanel::DestroyD3D()
{
	m_renderer->DestroyDevice();
}

void CViewPanel::OnIdle(wxIdleEvent& event)
{
	Refresh();
}

void CViewPanel::OnRender(wxEraseEvent& event)
{
	//time
	g_pGameTimer->Tick();

	//update
	m_mainGame->Update(g_pGameTimer->DeltaTime());

	// ±×¸²ÀÚ Render
	g_pShadowMgr->BeginShadowMap();
	m_mainGame->ShadowRender();
	g_pShadowMgr->EndShadowMap();

	// render
	m_renderer->BeginFrame();
	m_mainGame->Render();
	m_renderer->EndFrame();


	m_renderer->Present();
	

}

void CViewPanel::OnSize(wxSizeEvent& event)
{
	wxSize size = this->GetClientSize();
	m_renderer->OnReSize(size.GetWidth(), size.GetHeight());

	g_pSceneMgr->GetCurrScene()->GetMainCamera()->OnResize(size.GetWidth(), size.GetHeight());
}

void CViewPanel::OnMouseMove(wxMouseEvent& event)
{
	if (m_isDrag)
	{
		wxPoint curPoint = event.GetPosition();

		POINT distance;
		distance.x = curPoint.x - m_lastMousePoint.x;
		distance.y = curPoint.y - m_lastMousePoint.y;

		m_lastMousePoint.x = curPoint.x;
		m_lastMousePoint.y = curPoint.y;


		CCameraComponent* camera = g_pSceneMgr->GetCurrScene()->GetMainCamera();
		
		camera->RotateY(distance.x * 0.002f);
		camera->RotateX(distance.y * 0.002f);
	}
}

void CViewPanel::OnLMouseDown(wxMouseEvent& event)
{
}

void CViewPanel::OnLMouseUp(wxMouseEvent& event)
{
	
}

void CViewPanel::OnRMouseDown(wxMouseEvent& event)
{
	wxPoint point = event.GetPosition();
	m_lastMousePoint.x = point.x;
	m_lastMousePoint.y = point.y;
	
	m_isDrag = true;

	CToolCameraComponent* camera =
		static_cast<CToolCameraComponent*>(g_pSceneMgr->GetCurrScene()->GetMainCamera());

	camera->SetIsControl(true);
}

void CViewPanel::OnRMouseUp(wxMouseEvent& event)
{
	m_isDrag = false;

	CToolCameraComponent* camera =
		static_cast<CToolCameraComponent*>(g_pSceneMgr->GetCurrScene()->GetMainCamera());

	camera->SetIsControl(false);
}

void CViewPanel::OnMouseWheel(wxMouseEvent& event)
{

}

void CViewPanel::OnKillFocus(wxFocusEvent& event)
{
	
}

void CViewPanel::OnSetFocus(wxFocusEvent& event)
{
	
}