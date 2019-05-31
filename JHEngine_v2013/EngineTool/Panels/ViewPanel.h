#pragma once

#ifndef _VIEW_PANEL_H_
#define _VIEW_PANEL_H_

#include <Core\D3DRenderer.h>
#include "..\Game\MainGame.h"

class cMainFrame;

class CViewPanel : public wxPanel
{
public:
	bool CreateD3D(HWND hWnd, int ClientWidth, int ClientHeight);
	void DestroyD3D();

public:
	//¿Ã∫•∆Æ
	void OnIdle(wxIdleEvent& event);
	void OnRender(wxEraseEvent& event);
	void OnSize(wxSizeEvent& event);

	void OnMouseMove(wxMouseEvent& event);
	void OnLMouseDown(wxMouseEvent& event);
	void OnLMouseUp(wxMouseEvent& event);
	void OnRMouseDown(wxMouseEvent& event);
	void OnRMouseUp(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);

	void OnKillFocus(wxFocusEvent& event);
	void OnSetFocus(wxFocusEvent& event);

public:
	CViewPanel(cMainFrame* parent);
	virtual ~CViewPanel();

	POINT				GetLastMousePoint()				{ return m_lastMousePoint; }
	void				SetLastMousePoint(POINT point)	{ m_lastMousePoint = point; }

private:
	D3DRenderer*			m_renderer;
	CMainGame*				m_mainGame;

	POINT					m_lastMousePoint;
	bool					m_isDrag;

	cMainFrame*				m_mainFrame;

	DECLARE_EVENT_TABLE()
};

#endif // !_VIEW_PANEL_H_
