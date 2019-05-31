#include "stdafx.h"
#include "..\..\stdafx.h"
#include "MaterialDialog.h"

#include <Resource\ResourceMgr.h>
#include <Core\StringHelper.h>

#include "..\RendererPanel.h"

CMaterialDialog::CMaterialDialog(CRendererPanel* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_pParent(parent)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_bSizer = new wxBoxSizer(wxVERTICAL);

	m_fgSizerColor = new wxFlexGridSizer(0, 4, 0, 0);
	m_fgSizerColor->SetFlexibleDirection(wxBOTH);
	m_fgSizerColor->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticTextAmbient = new wxStaticText(this, wxID_ANY, wxT("Ambient"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextAmbient->Wrap(-1);
	m_fgSizerColor->Add(m_staticTextAmbient, 0, wxALIGN_CENTER | wxALL, 5);

	m_colourPickerAmbient = new wxColourPickerCtrl(this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE);
	m_fgSizerColor->Add(m_colourPickerAmbient, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticTextAmbientA = new wxStaticText(this, wxID_ANY, wxT("Alpha"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextAmbientA->Wrap(-1);
	m_fgSizerColor->Add(m_staticTextAmbientA, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrlAmbientA = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizerColor->Add(m_textCtrlAmbientA, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticTextDiffuse = new wxStaticText(this, wxID_ANY, wxT("Diffuse"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextDiffuse->Wrap(-1);
	m_fgSizerColor->Add(m_staticTextDiffuse, 0, wxALIGN_CENTER | wxALL, 5);

	m_colourPickerDiffuse = new wxColourPickerCtrl(this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE);
	m_fgSizerColor->Add(m_colourPickerDiffuse, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticTextDiffuseA = new wxStaticText(this, wxID_ANY, wxT("Alpha"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextDiffuseA->Wrap(-1);
	m_fgSizerColor->Add(m_staticTextDiffuseA, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrlDiffuseA = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizerColor->Add(m_textCtrlDiffuseA, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticTextSpecular = new wxStaticText(this, wxID_ANY, wxT("Specular"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextSpecular->Wrap(-1);
	m_fgSizerColor->Add(m_staticTextSpecular, 0, wxALIGN_CENTER | wxALL, 5);

	m_colourPickerSpecular = new wxColourPickerCtrl(this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE);
	m_fgSizerColor->Add(m_colourPickerSpecular, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticTextSpecularA = new wxStaticText(this, wxID_ANY, wxT("Specular Power"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextSpecularA->Wrap(-1);
	m_fgSizerColor->Add(m_staticTextSpecularA, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrlSpecularA = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizerColor->Add(m_textCtrlSpecularA, 0, wxALIGN_CENTER | wxALL, 5);


	m_bSizer->Add(m_fgSizerColor, 1, wxEXPAND, 5);



	m_fgSizerMap = new wxFlexGridSizer(0, 2, 0, 0);
	m_fgSizerMap->AddGrowableCol(1);
	m_fgSizerMap->SetFlexibleDirection(wxBOTH);
	m_fgSizerMap->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticTextDiffuseMap = new wxStaticText(this, wxID_ANY, wxT("DiffuseMap"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextDiffuseMap->Wrap(-1);
	m_fgSizerMap->Add(m_staticTextDiffuseMap, 1, wxALIGN_CENTER | wxALL, 5);

	m_filePickerDiffuseMap = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE);
	m_fgSizerMap->Add(m_filePickerDiffuseMap, 1, wxALIGN_CENTER | wxALL | wxEXPAND, 5);

	m_staticTextNormalMap = new wxStaticText(this, wxID_ANY, wxT("NormalMap"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextNormalMap->Wrap(-1);
	m_fgSizerMap->Add(m_staticTextNormalMap, 1, wxALIGN_CENTER | wxALL, 5);

	m_filePickerNormalMap = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE);
	m_fgSizerMap->Add(m_filePickerNormalMap, 1, wxALIGN_CENTER | wxALL | wxEXPAND, 5);


	m_bSizer->Add(m_fgSizerMap, 0, wxEXPAND, 5);




	m_fgSizerButton = new wxFlexGridSizer(0, 6, 0, 0);
	m_fgSizerButton->SetFlexibleDirection(wxBOTH);
	m_fgSizerButton->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_buttonOK = new wxButton(this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxSize(-1, -1), 0);
	m_fgSizerButton->Add(m_buttonOK, 0, wxALIGN_CENTER | wxALL, 5);

	m_buttonCancel = new wxButton(this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxSize(-1, -1), 0);
	m_fgSizerButton->Add(m_buttonCancel, 0, wxALL, 5);

	m_staticTextSave = new wxStaticText(this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextSave->Wrap(-1);
	m_fgSizerButton->Add(m_staticTextSave, 0, wxALIGN_CENTER | wxALL, 5);

	m_filePickerSave = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Save a file"), wxT("*.material"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_SMALL);
	m_fgSizerButton->Add(m_filePickerSave, 0, wxALL, 5);

	m_staticTextLoad = new wxStaticText(this, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticTextLoad->Wrap(-1);
	m_fgSizerButton->Add(m_staticTextLoad, 0, wxALIGN_CENTER | wxALL, 5);

	m_filePickerLoad = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_SMALL);
	m_fgSizerButton->Add(m_filePickerLoad, 0, wxALL, 5);

	WCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);
	m_filePickerSave->SetInitialDirectory(wxString(currentDir));
	m_filePickerLoad->SetInitialDirectory(wxString(currentDir));


	m_bSizer->Add(m_fgSizerButton, 0, wxEXPAND, 5);


	this->SetSizer(m_bSizer);
	this->Layout();
	m_bSizer->Fit(this);

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(CMaterialDialog::MaterialDialogOnClose));
	m_colourPickerAmbient->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CMaterialDialog::m_colourPickerAmbientOnColourChanged), NULL, this);
	m_textCtrlAmbientA->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CMaterialDialog::m_textCtrlAmbientAOnTextEnter), NULL, this);
	m_colourPickerDiffuse->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CMaterialDialog::m_colourPickerDiffuseOnColourChanged), NULL, this);
	m_textCtrlDiffuseA->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CMaterialDialog::m_textCtrlDiffuseAOnTextEnter), NULL, this);
	m_colourPickerSpecular->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CMaterialDialog::m_colourPickerSpecularOnColourChanged), NULL, this);
	m_textCtrlSpecularA->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CMaterialDialog::m_textCtrlSpecularAOnTextEnter), NULL, this);
	m_filePickerDiffuseMap->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMaterialDialog::m_filePickerDiffuseMapOnFileChanged), NULL, this);
	m_filePickerNormalMap->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMaterialDialog::m_filePickerNormalMapOnFileChanged), NULL, this);
	m_buttonOK->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMaterialDialog::m_buttonOKOnButtonClick), NULL, this);
	m_buttonCancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMaterialDialog::m_buttonCancelOnButtonClick), NULL, this);
	m_filePickerSave->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMaterialDialog::m_filePickerSaveOnFileChanged), NULL, this);
	m_filePickerLoad->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMaterialDialog::m_filePickerLoadOnFileChanged), NULL, this);
}


CMaterialDialog::~CMaterialDialog()
{
	// Disconnect Events
	this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(CMaterialDialog::MaterialDialogOnClose));
	m_colourPickerAmbient->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CMaterialDialog::m_colourPickerAmbientOnColourChanged), NULL, this);
	m_textCtrlAmbientA->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CMaterialDialog::m_textCtrlAmbientAOnTextEnter), NULL, this);
	m_colourPickerDiffuse->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CMaterialDialog::m_colourPickerDiffuseOnColourChanged), NULL, this);
	m_textCtrlDiffuseA->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CMaterialDialog::m_textCtrlDiffuseAOnTextEnter), NULL, this);
	m_colourPickerSpecular->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CMaterialDialog::m_colourPickerSpecularOnColourChanged), NULL, this);
	m_textCtrlSpecularA->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CMaterialDialog::m_textCtrlSpecularAOnTextEnter), NULL, this);
	m_filePickerDiffuseMap->Disconnect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMaterialDialog::m_filePickerDiffuseMapOnFileChanged), NULL, this);
	m_filePickerNormalMap->Disconnect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMaterialDialog::m_filePickerNormalMapOnFileChanged), NULL, this);
	m_buttonOK->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMaterialDialog::m_buttonOKOnButtonClick), NULL, this);
	m_buttonCancel->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMaterialDialog::m_buttonCancelOnButtonClick), NULL, this);
	m_filePickerSave->Disconnect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMaterialDialog::m_filePickerSaveOnFileChanged), NULL, this);
	m_filePickerLoad->Disconnect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(CMaterialDialog::m_filePickerLoadOnFileChanged), NULL, this);
}

void CMaterialDialog::SetColor()
{
	m_tempMaterial.Clone(m_selectedRenderComp->GetMaterial());
	m_tempExternMaterial = m_selectedRenderComp->GetExternMaterial();
	int r, g, b;
	XMFLOAT4 color;

	color = m_tempMaterial.GetAmbient();
	r = color.x * 255;
	g = color.y * 255;
	b = color.z * 255;

	m_colourPickerAmbient->SetColour(RGB(r, g, b));
	m_textCtrlAmbientA->SetValue(wxString::Format("%.3f", color.w));

	color = m_tempMaterial.GetDiffuse();
	r = color.x * 255;
	g = color.y * 255;
	b = color.z * 255;

	m_colourPickerDiffuse->SetColour(RGB(r, g, b));
	m_textCtrlDiffuseA->SetValue(wxString::Format("%.3f", color.w));

	color = m_tempMaterial.GetSpecular();
	r = color.x * 255;
	g = color.y * 255;
	b = color.z * 255;

	m_colourPickerSpecular->SetColour(RGB(r, g, b));
	m_textCtrlSpecularA->SetValue(wxString::Format("%.3f", color.w));
}

void CMaterialDialog::SetDirPicker()
{
	CTexture* diffuseMap = m_tempMaterial.GetDiffuseMap();
	if (diffuseMap == NULL)
	{
		m_filePickerDiffuseMap->SetPath(wxT(" "));
	}
	else
	{
		m_filePickerDiffuseMap->SetPath(wxString(diffuseMap->GetID().c_str()));
	}

	CTexture* normalMap = m_tempMaterial.GetNormalMap();
	if (normalMap == NULL)
	{
		m_filePickerNormalMap->SetPath(wxT(" "));
	}
	else
	{
		m_filePickerNormalMap->SetPath(wxString(normalMap->GetID().c_str()));
	}
}

//이벤트
void CMaterialDialog::MaterialDialogOnClose(wxCloseEvent& event)
{
	event.Skip();
}

void CMaterialDialog::m_colourPickerAmbientOnColourChanged(wxColourPickerEvent& event)
{
	CMaterial& material = m_selectedRenderComp->GetMaterial();
	XMFLOAT4 value;
	wxColour color;
	wxString text;
	double alpha;

	//Ambient
	color = m_colourPickerAmbient->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;

	text = m_textCtrlAmbientA->GetValue();
	text.ToDouble(&alpha);
	value.w = alpha;

	material.SetAmbient(value);
}

void CMaterialDialog::m_textCtrlAmbientAOnTextEnter(wxCommandEvent& event)
{
	CMaterial& material = m_selectedRenderComp->GetMaterial();
	XMFLOAT4 value;
	wxColour color;
	wxString text;
	double alpha;

	//Ambient
	color = m_colourPickerAmbient->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;

	text = m_textCtrlAmbientA->GetValue();
	text.ToDouble(&alpha);
	value.w = alpha;

	material.SetAmbient(value);
}

void CMaterialDialog::m_colourPickerDiffuseOnColourChanged(wxColourPickerEvent& event)
{
	CMaterial& material = m_selectedRenderComp->GetMaterial();
	XMFLOAT4 value;
	wxColour color;
	wxString text;
	double alpha;

	//Diffuse
	color = m_colourPickerDiffuse->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;

	text = m_textCtrlDiffuseA->GetValue();
	text.ToDouble(&alpha);
	value.w = alpha;

	material.SetDiffuse(value);
}

void CMaterialDialog::m_textCtrlDiffuseAOnTextEnter(wxCommandEvent& event)
{
	CMaterial& material = m_selectedRenderComp->GetMaterial();
	XMFLOAT4 value;
	wxColour color;
	wxString text;
	double alpha;

	//Diffuse
	color = m_colourPickerDiffuse->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;

	text = m_textCtrlDiffuseA->GetValue();
	text.ToDouble(&alpha);
	value.w = alpha;

	material.SetDiffuse(value);
}

void CMaterialDialog::m_colourPickerSpecularOnColourChanged(wxColourPickerEvent& event)
{
	CMaterial& material = m_selectedRenderComp->GetMaterial();
	XMFLOAT4 value;
	wxColour color;
	wxString text;
	double alpha;

	//Specular
	color = m_colourPickerSpecular->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;

	text = m_textCtrlSpecularA->GetValue();
	text.ToDouble(&alpha);
	value.w = alpha;

	material.SetSpecular(value);
}

void CMaterialDialog::m_textCtrlSpecularAOnTextEnter(wxCommandEvent& event)
{
	CMaterial& material = m_selectedRenderComp->GetMaterial();
	XMFLOAT4 value;
	wxColour color;
	wxString text;
	double alpha;

	//Specular
	color = m_colourPickerSpecular->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;

	text = m_textCtrlSpecularA->GetValue();
	text.ToDouble(&alpha);
	value.w = alpha;

	material.SetSpecular(value);
}

void CMaterialDialog::m_filePickerDiffuseMapOnFileChanged(wxFileDirPickerEvent& event)
{
	wxString filepath = event.GetPath();

	g_pResouceMgr->AddTexture(filepath.c_str().AsWChar());
	CTexture* loadTexture = g_pResouceMgr->GetTexture(filepath.c_str().AsWChar());
	if (loadTexture == NULL)
	{
		wxMessageBox(wxT("Create Texture Failed"), wxT("Error"));
		return;
	}

	CMaterial& material = m_selectedRenderComp->GetMaterial();
	material.SetDiffuseMap(loadTexture);
	

}

void CMaterialDialog::m_filePickerNormalMapOnFileChanged(wxFileDirPickerEvent& event)
{
	wxString filepath = event.GetPath();

	g_pResouceMgr->AddTexture(filepath.c_str().AsWChar());
	CTexture* loadTexture = g_pResouceMgr->GetTexture(filepath.c_str().AsWChar());
	if (loadTexture == NULL)
	{
		wxMessageBox(wxT("Create Texture Failed"), wxT("Error"));
		return;
	}

	CMaterial& material = m_selectedRenderComp->GetMaterial();
	material.SetNormalMap(loadTexture);


}

void CMaterialDialog::m_buttonOKOnButtonClick(wxCommandEvent& event)
{


	Close();
}

void CMaterialDialog::m_buttonCancelOnButtonClick(wxCommandEvent& event)
{
	m_selectedRenderComp->SetExternMaterial(m_tempExternMaterial);
	m_selectedRenderComp->GetMaterial().Clone(m_tempMaterial);

	//RendererPanel에 텍스트 바꾸기
	if (m_tempExternMaterial)
	{
		m_pParent->SetMaterialText(CStringHelper::PickFileNameFromFullPath(m_tempExternMaterial->GetID()).c_str());
	}
	else
	{
		m_pParent->SetMaterialText(wxT("default_material"));
	}

	Close();
}

void CMaterialDialog::m_filePickerSaveOnFileChanged(wxFileDirPickerEvent& event)
{
	wxString filepath = event.GetPath();

	CMaterial& material = m_selectedRenderComp->GetMaterial();
	CMaterial::SaveMaterial(filepath.c_str().AsWChar(), &material);

	wxLogMessage("Save Material");

}

void CMaterialDialog::m_filePickerLoadOnFileChanged(wxFileDirPickerEvent& event)
{
	wxString filepath = event.GetPath();

	CMaterial* material = g_pResouceMgr->GetMaterial(filepath.c_str().AsWChar());

	if (material == NULL)
	{
		
		bool b = g_pResouceMgr->AddMaterial(filepath.c_str().AsWChar());
		if (b == false)
		{
			wxMessageBox(wxT("Create Material Failed"), wxT("Error"));
			return;
		}
		material = g_pResouceMgr->GetMaterial(filepath.c_str().AsWChar());
	}
	
	m_selectedRenderComp->SetExternMaterial(material);

	//RendererPanel에 텍스트 바꾸기
	if (material)
	{
		m_pParent->SetMaterialText(CStringHelper::PickFileNameFromFullPath(material->GetID()).c_str());
	}
	else
	{
		m_pParent->SetMaterialText(wxT("default_material"));
	}

	wxLogMessage("Load Material");
	
}