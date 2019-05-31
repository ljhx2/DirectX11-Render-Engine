#include "stdafx.h"
#include "..\..\stdafx.h"
#include "MeshDialog.h"

#include <Resource\ResourceMgr.h>
#include <Core\StringHelper.h>

#include "..\RendererPanel.h"

CMeshDialog::CMeshDialog(CRendererPanel* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_pParent(parent)
{
	m_bSizer = new wxBoxSizer(wxVERTICAL);

	m_meshListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	m_bSizer->Add(m_meshListBox, 1, wxALL | wxEXPAND, 5);

	m_filePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_OPEN);
	m_bSizer->Add(m_filePicker, 0, wxALIGN_RIGHT | wxALL, 5);
	WCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);
	m_filePicker->SetInitialDirectory(wxString(currentDir));

	m_okButton = new wxButton(this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0);
	m_bSizer->Add(m_okButton, 0, wxALIGN_RIGHT | wxALL, 5);


	this->SetSizer(m_bSizer);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_meshListBox->Connect(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(CMeshDialog::m_meshListBoxOnListBoxDClick), NULL, this);
	m_filePicker->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMeshDialog::m_filePickerOnFileChanged), NULL, this);
	m_okButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMeshDialog::m_okButtonOnButtonClick), NULL, this);
}


CMeshDialog::~CMeshDialog()
{
	// Disconnect Events
	m_meshListBox->Disconnect(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(CMeshDialog::m_meshListBoxOnListBoxDClick), NULL, this);
	m_filePicker->Disconnect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMeshDialog::m_filePickerOnFileChanged), NULL, this);
	m_okButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMeshDialog::m_okButtonOnButtonClick), NULL, this);
}

void CMeshDialog::SetListBox()
{
	m_meshListBox->Clear();

	MESHMAP_T::iterator iter;
	MESHMAP_T& mapMesh = g_pResouceMgr->GetMeshMap();
	for (iter = mapMesh.begin(); iter != mapMesh.end(); ++iter)
	{
		wxString filename = CStringHelper::PickFileNameFromFullPath(iter->second->GetID());
		CMeshListData* data = new CMeshListData(iter->second);
		m_meshListBox->Append(filename, data);
	}
}

void CMeshDialog::m_meshListBoxOnListBoxDClick(wxCommandEvent& event)
{
	CMeshListData* data = (CMeshListData*)(event.GetClientObject());
	CMesh* selectMesh = data->GetMeshData();
	m_selectedRenderComp->SetMesh(selectMesh);
	
	m_pParent->SetMeshText(event.GetString());

	this->Close();
}

void CMeshDialog::m_filePickerOnFileChanged(wxFileDirPickerEvent& event)
{

}

void CMeshDialog::m_okButtonOnButtonClick(wxCommandEvent& event)
{
	int index = m_meshListBox->GetSelection();
	if (index == -1)	//선택하지 않으면
	{
		this->Close();
		return;
	}
	
	CMeshListData* data = (CMeshListData*)(m_meshListBox->GetClientObject(index));
	CMesh* selectMesh = data->GetMeshData();
	m_selectedRenderComp->SetMesh(selectMesh);

	m_pParent->SetMeshText(m_meshListBox->GetString(index));

	this->Close();
}
