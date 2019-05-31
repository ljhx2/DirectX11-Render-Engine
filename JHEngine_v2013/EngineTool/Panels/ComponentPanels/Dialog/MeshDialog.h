#pragma once

#ifndef _MESH_DIALOG_H_
#define _MESH_DIALOG_H_


#include <wx/filepicker.h>

#include <GameObject\Component\RendererComponent\RenderComponent.h>

class CRendererPanel;

class CMeshListData : public wxClientData
{
public:
	CMesh*		GetMeshData() { return meshData; }

public:
	CMeshListData(CMesh* mesh) : wxClientData(), meshData(mesh) {}
	virtual ~CMeshListData() {}

private:
	CMesh* meshData;
};

class CMeshDialog : public wxDialog
{
public:
	//RendererPanel에서 실행
	void		SetRenderComp(CRenderComponent* rendComp) { m_selectedRenderComp = rendComp; }
	void		SetListBox();

public:
	//이벤트
	virtual void m_meshListBoxOnListBoxDClick(wxCommandEvent& event);
	virtual void m_filePickerOnFileChanged(wxFileDirPickerEvent& event);
	virtual void m_okButtonOnButtonClick(wxCommandEvent& event);

public:
	CMeshDialog(CRendererPanel* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Mesh"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(380, 340), long style = wxDEFAULT_DIALOG_STYLE);
	~CMeshDialog();

private:
	wxBoxSizer*				m_bSizer;

	wxListBox*				m_meshListBox;
	wxFilePickerCtrl*		m_filePicker;
	wxButton*				m_okButton;

private:
	CRenderComponent*		m_selectedRenderComp;

private:
	CRendererPanel*			m_pParent;

};

#endif // !_MESH_DIALOG_H_