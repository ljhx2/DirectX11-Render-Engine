#pragma once

#ifndef _MATERIAL_DIALOG_H_
#define _MATERIAL_DIALOG_H_


#include <wx/filepicker.h>
#include <wx/clrpicker.h>
#include <wx/colour.h>

#include <GameObject\Component\RendererComponent\RenderComponent.h>

class CRendererPanel;


class CMaterialDialog : public wxDialog
{
public:
	//RendererPanel에서 실행
	void			SetRenderComp(CRenderComponent* rendComp) { m_selectedRenderComp = rendComp; }
	void			SetColor();
	void			SetDirPicker();

public:
	//이벤트
	virtual void MaterialDialogOnClose(wxCloseEvent& event);
	virtual void m_colourPickerAmbientOnColourChanged(wxColourPickerEvent& event);
	virtual void m_textCtrlAmbientAOnTextEnter(wxCommandEvent& event);
	virtual void m_colourPickerDiffuseOnColourChanged(wxColourPickerEvent& event);
	virtual void m_textCtrlDiffuseAOnTextEnter(wxCommandEvent& event);
	virtual void m_colourPickerSpecularOnColourChanged(wxColourPickerEvent& event);
	virtual void m_textCtrlSpecularAOnTextEnter(wxCommandEvent& event);
	virtual void m_filePickerDiffuseMapOnFileChanged(wxFileDirPickerEvent& event);
	virtual void m_filePickerNormalMapOnFileChanged(wxFileDirPickerEvent& event);
	virtual void m_buttonOKOnButtonClick(wxCommandEvent& event);
	virtual void m_buttonCancelOnButtonClick(wxCommandEvent& event);
	virtual void m_filePickerSaveOnFileChanged(wxFileDirPickerEvent& event);
	virtual void m_filePickerLoadOnFileChanged(wxFileDirPickerEvent& event);

public:
	CMaterialDialog(CRendererPanel* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Material Edit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
	~CMaterialDialog();

private:
	wxBoxSizer*				m_bSizer;
	wxFlexGridSizer*		m_fgSizerColor;
	wxFlexGridSizer*		m_fgSizerButton;
	wxFlexGridSizer*		m_fgSizerMap;

	wxStaticText*			m_staticTextAmbient;
	wxStaticText*			m_staticTextAmbientA;
	wxStaticText*			m_staticTextDiffuse;
	wxStaticText*			m_staticTextDiffuseA;
	wxStaticText*			m_staticTextSpecular;
	wxStaticText*			m_staticTextSpecularA;
	wxStaticText*			m_staticTextDiffuseMap;
	wxStaticText*			m_staticTextNormalMap;

	wxStaticText*			m_staticTextSave;
	wxStaticText*			m_staticTextLoad;

	wxButton*				m_buttonOK;
	wxButton*				m_buttonCancel;
	
	wxFilePickerCtrl*		m_filePickerSave;
	wxFilePickerCtrl*		m_filePickerLoad;
	wxFilePickerCtrl*		m_filePickerDiffuseMap;
	wxFilePickerCtrl*		m_filePickerNormalMap;

	wxTextCtrl*				m_textCtrlAmbientA;
	wxTextCtrl*				m_textCtrlDiffuseA;
	wxTextCtrl*				m_textCtrlSpecularA;

	wxColourPickerCtrl*		m_colourPickerAmbient;
	wxColourPickerCtrl*		m_colourPickerDiffuse;
	wxColourPickerCtrl*		m_colourPickerSpecular;

private:
	CRenderComponent*		m_selectedRenderComp;
	CMaterial				m_tempMaterial;
	CMaterial*				m_tempExternMaterial;

private:
	CRendererPanel*			m_pParent;
};

#endif // !_MATERIAL_DIALOG_H_