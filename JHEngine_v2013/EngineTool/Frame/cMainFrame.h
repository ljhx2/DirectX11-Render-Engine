#pragma once

#ifndef _MAIN_FRAME_H_
#define _MAIN_FRAME_H_

#include <wx/aui/aui.h>


#define WINSIZEX 1024
#define WINSIZEY 768

#include "..\Panels\ViewPanel.h"
#include "..\Panels\TreePanel.h"
#include "..\Panels\LogPanel.h"
#include "..\Panels\PropertyPanel.h"


enum eMENU_ID
{
	eID_CREATE_EMPTY = wxID_HIGHEST + 1,

	eID_CUBE,
	eID_SPHERE,
	eID_CYLINDER,
	eID_PLANE,

	eID_DIR_LIGHT,
	eID_POINT_LIGHT,
	eID_SPOT_LIGHT,

	eID_IMPORT,
};

class cMainFrame : public wxFrame
{
public:
	CGameObject*			GetSelectedGameObject() { return m_selectedGameObject; }
	void					SetSelectedGameObject(CGameObject* selected) { m_selectedGameObject = selected; }

	CViewPanel*				GetViewPanel() { return m_viewPanel; }
	CTreePanel*				GetTreePanel() { return m_treePanel; }
	CLogPanel*				GetLogPanel() { return m_logPanel; }
	CPropertyPanel*			GetPropertyPanel() { return m_propertyPanel;
	}
public:
	// File
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);

	// GameObject
	void OnCreateEmpty(wxCommandEvent& event);
	void OnCube(wxCommandEvent& event);
	void OnSphere(wxCommandEvent& event);
	void OnCylinder(wxCommandEvent& event);
	void OnPlane(wxCommandEvent& event);
	// Light
	void OnDirLight(wxCommandEvent& event);
	void OnPointLight(wxCommandEvent& event);
	void OnSpotLight(wxCommandEvent& event);

	//Assert
	void OnImport(wxCommandEvent& event);



public:
	bool CreateD3D(HWND hWnd, int ClientWidth, int ClientHeight);
	void DestroyD3D();

public:
	cMainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(WINSIZEX, WINSIZEY), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~cMainFrame();

protected:
	wxAuiManager			m_panelManager;

	//Menu
	wxMenuBar*				m_menuBar;
	wxMenu*					m_menuFile;
	wxMenu*					m_menuGameObject;
		wxMenu*					m_menu3DObject;
		wxMenu*					m_menuLight;
	wxMenu*					m_menuAsset;

	/* Menu Item */
	// File
	wxMenuItem*				m_newFile;
	wxMenuItem*				m_openFile;
	wxMenuItem*				m_saveFile;
	wxMenuItem*				m_quit;

	// GameObject
	wxMenuItem*				m_createEmpty;
	wxMenuItem*				m_cube;
	wxMenuItem*				m_sphere;
	wxMenuItem*				m_cylinder;
	wxMenuItem*				m_plane;

	// Light
	wxMenuItem*				m_dirLight;
	wxMenuItem*				m_pointLight;
	wxMenuItem*				m_spotLight;

	// Assert
	wxMenuItem*				m_import;



// Panel
	CViewPanel*				m_viewPanel;
	CTreePanel*				m_treePanel;
	CLogPanel*				m_logPanel;
	CPropertyPanel*			m_propertyPanel;

protected:

	CGameObject*			m_selectedGameObject;

};

#endif // !_MAIN_FRAME_H_

