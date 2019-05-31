#include "stdafx.h"
#include "..\stdafx.h"
#include "PropertyPanel.h"

#include "..\Frame\cMainFrame.h"

BEGIN_EVENT_TABLE(CPropertyPanel, wxPanel)

	EVT_IDLE(CPropertyPanel::OnIdle)
	
END_EVENT_TABLE()

CPropertyPanel::CPropertyPanel(cMainFrame* parent)
: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 500))
	, m_mainFrame(parent)
{
	m_bSizer = new wxBoxSizer(wxVERTICAL);

	m_transformPanel = new CTransformPanel(this);
	m_rendererPanel = new CRendererPanel(this);
	m_lightPanel = new CLightPanel(this);
	m_skinnedPanel = new CSkinnedRendererPanel(this);
	m_animPanel = new CAnimatorPanel(this);
	
	m_bSizer->Add(m_transformPanel, 0, wxALL | wxEXPAND, 5);
	m_bSizer->Add(m_rendererPanel, 0, wxALL | wxEXPAND, 5);
	m_bSizer->Add(m_lightPanel, 0, wxALL | wxEXPAND, 5);
	m_bSizer->Add(m_skinnedPanel, 0, wxALL | wxEXPAND, 5);
	m_bSizer->Add(m_animPanel, 0, wxALL | wxEXPAND, 5);
	
	m_bSizer->Hide(m_transformPanel);
	m_bSizer->Hide(m_rendererPanel);
	m_bSizer->Hide(m_lightPanel);
	m_bSizer->Hide(m_skinnedPanel);
	m_bSizer->Hide(m_animPanel);

	this->SetSizer(m_bSizer);
	this->Layout();
	this->Fit();
	this->SetAutoLayout(true);

}


CPropertyPanel::~CPropertyPanel()
{
}

void CPropertyPanel::ShowGameObjectProperty(CGameObject* go)
{
	AllComponentPanelHide();
	CheckTransformComponent(go);
	CheckRendererComponent(go);
	CheckDirLightComponent(go);
	CheckSkinnedRendererComponent(go);
	CheckAnimatorComponent(go);

	m_bSizer->Layout();
}

void CPropertyPanel::AllComponentPanelHide()
{
	m_bSizer->Hide(m_transformPanel);
	m_bSizer->Hide(m_rendererPanel);
	m_bSizer->Hide(m_lightPanel);
	m_bSizer->Hide(m_skinnedPanel);
	m_bSizer->Hide(m_animPanel);
}

void CPropertyPanel::CheckTransformComponent(CGameObject* go)
{
	CTransformComponent* transComp = go->GetComponent<CTransformComponent>();
	if (transComp)
	{
		m_bSizer->Show(m_transformPanel);
		m_transformPanel->SetTransform(transComp);
	}
}

void CPropertyPanel::CheckRendererComponent(CGameObject* go)
{
	CRenderComponent* rendComp = go->GetComponent<CRenderComponent>();
	if (rendComp)
	{
		m_bSizer->Show(m_rendererPanel);
		m_rendererPanel->SetRenderer(rendComp);
	}
}

void CPropertyPanel::CheckDirLightComponent(CGameObject* go)
{
	CDirectionalLightComponent* dirLightComp = go->GetComponent<CDirectionalLightComponent>();
	if (dirLightComp)
	{
		m_bSizer->Show(m_lightPanel);
		m_lightPanel->SetLightComponent(dirLightComp);
	}
}

void CPropertyPanel::CheckSkinnedRendererComponent(CGameObject* go)
{
	
	CSkinnedMeshRenderer* rendComp = go->GetComponent<CSkinnedMeshRenderer>();
	if (rendComp)
	{
		m_bSizer->Show(m_skinnedPanel);
		m_skinnedPanel->SetRenderer(rendComp);
	}
}

void CPropertyPanel::CheckAnimatorComponent(CGameObject* go)
{
	CAnimComponent* animComp = go->GetComponent<CAnimComponent>();
	if (animComp)
	{
		m_bSizer->Show(m_animPanel);
		m_animPanel->SetAnimatorComp(animComp);
	}
}

//ÀÌº¥Æ®
void CPropertyPanel::OnIdle(wxIdleEvent& event)
{
	if (m_transformPanel->IsShown())
		m_transformPanel->Update();

	if (m_animPanel->IsShown())
		m_animPanel->Update();

}
