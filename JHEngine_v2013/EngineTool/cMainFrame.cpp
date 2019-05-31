#include "stdafx.h"
#include "cMainFrame.h"


cMainFrame::cMainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{

	// Make Menu bar
	m_menuBar = new wxMenuBar;

	// Make Menues
	m_menuFile = new wxMenu;

	// Make Menu Items
	// File
	newFile = new wxMenuItem(m_menuFile, wxID_NEW, wxT("&New\tCtrl+N"));
	openFile = new wxMenuItem(m_menuFile, wxID_OPEN, wxT("&Open\tCtrl+O"));
	saveFile = new wxMenuItem(m_menuFile, wxID_SAVE, wxT("&Save\tCtrl+S"));
	quit = new wxMenuItem(m_menuFile, wxID_EXIT, wxT("&Quit\tCtrl+X"));


	// Appending
	m_menuFile->Append(newFile);
	m_menuFile->Append(openFile);
	m_menuFile->Append(saveFile);
	m_menuFile->Append(quit);

	m_menuBar->Append(m_menuFile, wxT("&File"));

	// set menubar
	SetMenuBar(m_menuBar);

	/* Make Event Connection */
	// File
	Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnNew));
	Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnOpen));
	Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnSave));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMainFrame::OnQuit));


	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_splitter1 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_NO_XP_THEME);
	m_splitter1->Connect(wxEVT_IDLE, wxIdleEventHandler(cMainFrame::m_splitter1OnIdle), NULL, this);

	m_panel1 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_notebook1 = new wxNotebook(m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	m_panel3 = new wxPanel(m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	m_treeCtrl3 = new wxTreeCtrl(m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
	bSizer7->Add(m_treeCtrl3, 1, wxALL | wxEXPAND, 5);


	m_panel3->SetSizer(bSizer7);
	m_panel3->Layout();
	bSizer7->Fit(m_panel3);
	m_notebook1->AddPage(m_panel3, wxT("a page"), true);
	m_panel4 = new wxPanel(m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_notebook1->AddPage(m_panel4, wxT("a page"), false);

	bSizer2->Add(m_notebook1, 1, wxEXPAND | wxALL, 5);


	m_panel1->SetSizer(bSizer2);
	m_panel1->Layout();
	bSizer2->Fit(m_panel1);
	m_panel2 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_splitter2 = new wxSplitterWindow(m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_NO_XP_THEME);
	m_splitter2->Connect(wxEVT_IDLE, wxIdleEventHandler(cMainFrame::m_splitter2OnIdle), NULL, this);

	m_panel6 = new wxPanel(m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);


	m_panel6->SetSizer(bSizer5);
	m_panel6->Layout();
	bSizer5->Fit(m_panel6);
	m_panel7 = new wxPanel(m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);


	m_panel7->SetSizer(bSizer6);
	m_panel7->Layout();
	bSizer6->Fit(m_panel7);
	m_splitter2->SplitVertically(m_panel6, m_panel7, 412);
	bSizer4->Add(m_splitter2, 1, wxEXPAND, 5);


	m_panel2->SetSizer(bSizer4);
	m_panel2->Layout();
	bSizer4->Fit(m_panel2);
	m_splitter1->SplitVertically(m_panel1, m_panel2, 252);
	bSizer1->Add(m_splitter1, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();
	m_menubar1 = new wxMenuBar(0);
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem(m_menu1, wxID_ANY, wxString(wxT("MyMenuItem")), wxEmptyString, wxITEM_NORMAL);
	m_menu1->Append(m_menuItem1);

	m_menubar1->Append(m_menu1, wxT("MyMenu"));

	this->SetMenuBar(m_menubar1);

	m_statusBar1 = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);

	box = 0;
	if (CreateD3D((HWND)m_panel6->GetHWND(), m_panel6->GetSize().GetWidth(), m_panel6->GetSize().GetHeight()))
	{
		box = new BoxTest;
	}
	
	
}


cMainFrame::~cMainFrame()
{
	DestroyD3D();
	SAFE_DELETE(box);
}

bool cMainFrame::CreateD3D(HWND hWnd, int ClientWidth, int ClientHeight)
{

	if (g_pDeviceMgr->InitDirect3D(hWnd, ClientWidth, ClientHeight))
	{
		g_pDeviceMgr->OnResize(ClientWidth, ClientWidth);
		return true;
	}
		

	return false;
}

void cMainFrame::DestroyD3D()
{
	if (!g_pDeviceMgr) return;

	g_pDeviceMgr->DestroyDirect3D();

}

void cMainFrame::OnRender(wxEraseEvent& event)
{
	box->Update(0.0f);

	g_pDeviceMgr->BeginFrame();

	box->Render();

	g_pDeviceMgr->EndFrame();
	g_pDeviceMgr->Present();
}

// 이벤트테이블관련
BEGIN_EVENT_TABLE(cMainFrame, wxFrame)
// 렌더링시 사용될함수를 등록해준다.
EVT_ERASE_BACKGROUND(cMainFrame::OnRender)
END_EVENT_TABLE()