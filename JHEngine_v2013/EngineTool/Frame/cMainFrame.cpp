#include "stdafx.h"
#include "..\stdafx.h"
#include "cMainFrame.h"

#include <GameObject\GameObjectMgr.h>
#include <GameObject\Component\RendererComponent\RenderComponent.h>
#include <Scene\SceneMgr.h>

#include <Resource\gFXManager.h>
#include <Resource\ResourceMgr.h>

#include <Resource\Material.h>

//for Asset Import
#include <Parser\AssimpParser.h>

cMainFrame::cMainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style), m_selectedGameObject(NULL)
{

// Make Menu bar
	m_menuBar = new wxMenuBar;

// Make Menues
	m_menuFile = new wxMenu;
	m_menuGameObject = new wxMenu;
	m_menu3DObject = new wxMenu;
	m_menuLight = new wxMenu;
	m_menuAsset = new wxMenu;

// Make Menu Items
	// File
	m_newFile = new wxMenuItem(m_menuFile, wxID_NEW, wxT("&New\tCtrl+N"));
	m_openFile = new wxMenuItem(m_menuFile, wxID_OPEN, wxT("&Open\tCtrl+O"));
	m_saveFile = new wxMenuItem(m_menuFile, wxID_SAVE, wxT("&Save\tCtrl+S"));
	m_quit = new wxMenuItem(m_menuFile, wxID_EXIT, wxT("&Quit\tCtrl+X"));
	
	// GameObject
	m_createEmpty = new wxMenuItem(m_menuGameObject, eID_CREATE_EMPTY, wxT("&Create Empty"));
	m_cube = new wxMenuItem(m_menu3DObject, eID_CUBE, wxT("&Cube"));
	m_sphere = new wxMenuItem(m_menu3DObject, eID_SPHERE, wxT("&Sphere"));
	m_cylinder = new wxMenuItem(m_menu3DObject, eID_CYLINDER, wxT("&Cylinder"));
	m_plane = new wxMenuItem(m_menu3DObject, eID_PLANE, wxT("&Plane"));

	// Light
	m_dirLight = new wxMenuItem(m_menuLight, eID_DIR_LIGHT, wxT("&Directional Light"));
	m_pointLight = new wxMenuItem(m_menuLight, eID_POINT_LIGHT, wxT("&Point Light"));
	m_spotLight = new wxMenuItem(m_menuLight, eID_SPOT_LIGHT, wxT("&Spotlight"));

	//Assert
	m_import = new wxMenuItem(m_menuAsset, eID_IMPORT, wxT("&Import Asset"));


// Appending
	// File
	m_menuFile->Append(m_newFile);
	m_menuFile->Append(m_openFile);
	m_menuFile->Append(m_saveFile);
	m_menuFile->Append(m_quit);

	// GameObject
	m_menu3DObject->Append(m_cube);
	m_menu3DObject->Append(m_sphere);
	m_menu3DObject->Append(m_cylinder);
	m_menu3DObject->Append(m_plane);
	// Light
	m_menuLight->Append(m_dirLight);
	m_menuLight->Append(m_pointLight);
	m_menuLight->Append(m_spotLight);
	// GameObject Append
	m_menuGameObject->Append(m_createEmpty);
	m_menuGameObject->AppendSubMenu(m_menu3DObject, wxT("&3D Object"));
	m_menuGameObject->AppendSubMenu(m_menuLight, wxT("&Light"));
	// Asset
	m_menuAsset->Append(m_import);

	m_menuBar->Append(m_menuFile, wxT("&File"));
	m_menuBar->Append(m_menuAsset, wxT("&Assert"));
	m_menuBar->Append(m_menuGameObject, wxT("GameObject"));
	

// set menubar
	SetMenuBar(m_menuBar);

/* Make Event Connection */
	// File
	Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnNew));
	Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnOpen));
	Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnSave));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnQuit));

	// GameObject
	Connect(eID_CREATE_EMPTY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnCreateEmpty));
	Connect(eID_CUBE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnCube));
	Connect(eID_SPHERE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnSphere));
	Connect(eID_CYLINDER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnCylinder));
	Connect(eID_PLANE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnPlane));
	// Light
	Connect(eID_DIR_LIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnDirLight));
	Connect(eID_POINT_LIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnPointLight));
	Connect(eID_SPOT_LIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnSpotLight));
	
	//Asset
	Connect(eID_IMPORT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnImport));

// AUI PART
	m_panelManager.SetManagedWindow(this);

	m_viewPanel = new CViewPanel(this);
	m_treePanel = new CTreePanel(this);
	m_logPanel = new CLogPanel(this);
	m_propertyPanel = new CPropertyPanel(this);

	// Add Pane
	m_panelManager.AddPane(m_viewPanel, wxCENTER, wxT("Render Window"));
	m_panelManager.AddPane(m_treePanel, wxLEFT, wxT("Hierarchy"));
	m_panelManager.AddPane(m_logPanel, wxBOTTOM, wxT("Log"));
	m_panelManager.AddPane(m_propertyPanel, wxRIGHT, wxT("Property"));

	m_panelManager.SetDockSizeConstraint(0.5, 0.5);


	// commit changes
	m_panelManager.Update();

	Centre();

}


cMainFrame::~cMainFrame()
{

	/* Event Disnnection */
	// File
	Disconnect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnNew));
	Disconnect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnOpen));
	Disconnect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnSave));
	Disconnect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnQuit));

	// GameObject
	Disconnect(eID_CREATE_EMPTY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnCreateEmpty));
	Disconnect(eID_CUBE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnCube));
	Disconnect(eID_SPHERE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnSphere));
	Disconnect(eID_CYLINDER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnCylinder));
	Disconnect(eID_PLANE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnPlane));
	// Light
	Disconnect(eID_DIR_LIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnDirLight));
	Disconnect(eID_POINT_LIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnPointLight));
	Disconnect(eID_SPOT_LIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnSpotLight));

	//Asset
	Disconnect(eID_IMPORT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnImport));
	
	m_panelManager.UnInit();
}

// Event Functions
// File
void cMainFrame::OnNew(wxCommandEvent& event)
{

}

void cMainFrame::OnOpen(wxCommandEvent& event)
{

}

void cMainFrame::OnSave(wxCommandEvent& event)
{

}

void cMainFrame::OnQuit(wxCommandEvent& event)
{
	Close(true);
}

// GameObject
void cMainFrame::OnCreateEmpty(wxCommandEvent& event)
{
	CScene* currnetScene = g_pSceneMgr->GetCurrScene();
	if (currnetScene == NULL) return;

	static int number = 0;
	number++;

	WCHAR gameObjectName[1024];
	wsprintf(gameObjectName, L"GameObject%d", number);

	CGameObject* gameObject = new CGameObject(gameObjectName);
	currnetScene->AddSceneNode(gameObject);

	m_treePanel->AppendRoot(gameObject);

	wxLogMessage(wxT("Create [GameObject%d]"), number);

}

void cMainFrame::OnCube(wxCommandEvent& event)
{
	CScene* currnetScene = g_pSceneMgr->GetCurrScene();
	if (currnetScene == NULL) return;

	static int number = 0;
	number++;

	WCHAR gameObjectName[1024];
	wsprintf(gameObjectName, L"Cube%d", number);

	CGameObject* gameObject = new CGameObject(gameObjectName);
	CRenderComponent* renderComp = gameObject->AddComponent<CRenderComponent>();
	
	

	renderComp->SetMesh(g_pResouceMgr->GetMesh(L"Box"));
	renderComp->SetEffect(g_pResouceMgr->GetEffect(L"FX/Basic.fx"));

	currnetScene->AddSceneNode(gameObject);


	m_treePanel->AppendRoot(gameObject);

	wxLogMessage(wxT("Create [Cube%d]"), number);

	
}

void cMainFrame::OnSphere(wxCommandEvent& event)
{
	CScene* currnetScene = g_pSceneMgr->GetCurrScene();
	if (currnetScene == NULL) return;

	static int number = 0;
	number++;

	WCHAR gameObjectName[1024];
	wsprintf(gameObjectName, L"Sphere%d", number);

	CGameObject* gameObject = new CGameObject(gameObjectName);
	CRenderComponent* renderComp = gameObject->AddComponent<CRenderComponent>();



	renderComp->SetMesh(g_pResouceMgr->GetMesh(L"Sphere"));
	renderComp->SetEffect(g_pResouceMgr->GetEffect(L"FX/Basic.fx"));

	currnetScene->AddSceneNode(gameObject);


	m_treePanel->AppendRoot(gameObject);

	wxLogMessage(wxT("Create [Sphere%d]"), number);
}

void cMainFrame::OnCylinder(wxCommandEvent& event)
{
	CScene* currnetScene = g_pSceneMgr->GetCurrScene();
	if (currnetScene == NULL) return;

	static int number = 0;
	number++;

	WCHAR gameObjectName[1024];
	wsprintf(gameObjectName, L"Cylinder%d", number);

	CGameObject* gameObject = new CGameObject(gameObjectName);
	CRenderComponent* renderComp = gameObject->AddComponent<CRenderComponent>();



	renderComp->SetMesh(g_pResouceMgr->GetMesh(L"Cylinder"));
	renderComp->SetEffect(g_pResouceMgr->GetEffect(L"FX/Basic.fx"));

	currnetScene->AddSceneNode(gameObject);


	m_treePanel->AppendRoot(gameObject);

	wxLogMessage(wxT("Create [Cylinder%d]"), number);
}

void cMainFrame::OnPlane(wxCommandEvent& event)
{
	CScene* currnetScene = g_pSceneMgr->GetCurrScene();
	if (currnetScene == NULL) return;

	static int number = 0;
	number++;

	WCHAR gameObjectName[1024];
	wsprintf(gameObjectName, L"Plane%d", number);

	CGameObject* gameObject = new CGameObject(gameObjectName);
	CRenderComponent* renderComp = gameObject->AddComponent<CRenderComponent>();



	renderComp->SetMesh(g_pResouceMgr->GetMesh(L"Plane"));
	renderComp->SetEffect(g_pResouceMgr->GetEffect(L"FX/Basic.fx"));

	currnetScene->AddSceneNode(gameObject);


	m_treePanel->AppendRoot(gameObject);

	wxLogMessage(wxT("Create [Plane%d]"), number);
}
// Light
void cMainFrame::OnDirLight(wxCommandEvent& event)
{
	CScene* currnetScene = g_pSceneMgr->GetCurrScene();
	if (currnetScene == NULL) return;

	static int number = 0;
	number++;

	WCHAR gameObjectName[1024];
	wsprintf(gameObjectName, L"Directional Light%d", number);

	CGameObject* gameObject = new CGameObject(gameObjectName);
	CDirectionalLightComponent* dirLightComp = gameObject->AddComponent<CDirectionalLightComponent>();

	currnetScene->AddSceneNode(gameObject);

	m_treePanel->AppendRoot(gameObject);

	wxLogMessage(wxT("Create [Directional Light%d]"), number);
}

void cMainFrame::OnPointLight(wxCommandEvent& event)
{

}

void cMainFrame::OnSpotLight(wxCommandEvent& event)
{

}


//Assert
void cMainFrame::OnImport(wxCommandEvent& event)
{
	WCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);


	wxFileDialog openFileDialog(this, wxT("Open Asset"), wxString(currentDir), "",
		"", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     

	CScene* currnetScene = g_pSceneMgr->GetCurrScene();
	if (currnetScene == NULL) return;

	wxString filepath = openFileDialog.GetPath();
	
	CAssimpParser* parser = new CAssimpParser;
	CGameObject* gameObject = parser->LoadFile(filepath.c_str().AsWChar());
	if (gameObject == NULL)
	{
		SAFE_DELETE(parser);
		return;
	}

	currnetScene->AddSceneNode(gameObject);

	m_treePanel->AppendRoot(gameObject);

	wxLogMessage(wxT("Create [%s]"), filepath);

	SAFE_DELETE(parser);
	
}