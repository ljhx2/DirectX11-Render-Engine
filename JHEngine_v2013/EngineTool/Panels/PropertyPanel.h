#pragma once

#ifndef _PROPERTY_PANEL_H_
#define _PROPERTY_PANEL_H_

#include "ComponentPanels\TransformPanel.h"
#include "ComponentPanels\RendererPanel.h"
#include "ComponentPanels\LightPanel.h"
#include "ComponentPanels\SkinnedRendererPanel.h"
#include "ComponentPanels\AnimatorPanel.h"

#include <GameObject\GameObject.h>

class cMainFrame;



class CPropertyPanel : public wxPanel
{
public:
	//이벤트
	void OnIdle(wxIdleEvent& event);

public:
	void				ShowGameObjectProperty(CGameObject* go);
	void				AllComponentPanelHide();
private:
	//ShowGameObjectProperty 함수에서 사용할 함수들
	void				CheckTransformComponent(CGameObject* go);
	void				CheckRendererComponent(CGameObject* go);
	void				CheckDirLightComponent(CGameObject* go);
	void				CheckSkinnedRendererComponent(CGameObject* go);
	void				CheckAnimatorComponent(CGameObject* go);

public:
	CPropertyPanel(cMainFrame* parent);
	~CPropertyPanel();

private:
	wxBoxSizer*					m_bSizer;
	

	CTransformPanel*			m_transformPanel;
	CRendererPanel*				m_rendererPanel;
	CLightPanel*				m_lightPanel;
	CSkinnedRendererPanel*		m_skinnedPanel;
	CAnimatorPanel*				m_animPanel;

	cMainFrame*					m_mainFrame;


	DECLARE_EVENT_TABLE()
};

#endif // !_PROPERTY_PANEL_H_

