#include "stdafx.h"
#include "..\..\stdafx.h"
#include "LightPanel.h"


CLightPanel::CLightPanel(wxWindow* parent)
	: wxPanel(parent)
	, m_dirLightComp(NULL)
{
	
	sbSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Light")), wxVERTICAL);

	
	fgSizer = new wxFlexGridSizer(0, 2, 0, 0);
	fgSizer->AddGrowableCol(0);
	fgSizer->SetFlexibleDirection(wxBOTH);
	fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_stextType = new wxStaticText(sbSizer->GetStaticBox(), wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0);
	m_stextType->Wrap(-1);
	fgSizer->Add(m_stextType, 0, wxALL, 5);

	m_textType = new wxTextCtrl(sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE | wxTE_READONLY);
	fgSizer->Add(m_textType, 0, wxALL, 5);

	m_stextAmbient = new wxStaticText(sbSizer->GetStaticBox(), wxID_ANY, wxT("Ambient"), wxDefaultPosition, wxDefaultSize, 0);
	m_stextAmbient->Wrap(-1);
	fgSizer->Add(m_stextAmbient, 0, wxALL, 5);

	m_colourPickerAmbient = new wxColourPickerCtrl(sbSizer->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE);
	fgSizer->Add(m_colourPickerAmbient, 0, wxALL, 5);

	m_stextDiffuse = new wxStaticText(sbSizer->GetStaticBox(), wxID_ANY, wxT("Diffuse"), wxDefaultPosition, wxDefaultSize, 0);
	m_stextDiffuse->Wrap(-1);
	fgSizer->Add(m_stextDiffuse, 0, wxALL, 5);

	m_colourPickerDiffuse = new wxColourPickerCtrl(sbSizer->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE);
	fgSizer->Add(m_colourPickerDiffuse, 0, wxALL, 5);

	m_stextSpecular = new wxStaticText(sbSizer->GetStaticBox(), wxID_ANY, wxT("Specular"), wxDefaultPosition, wxDefaultSize, 0);
	m_stextSpecular->Wrap(-1);
	fgSizer->Add(m_stextSpecular, 0, wxALL, 5);

	m_colourPickerSpecular = new wxColourPickerCtrl(sbSizer->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE);
	fgSizer->Add(m_colourPickerSpecular, 0, wxALL, 5);


	sbSizer->Add(fgSizer, 1, wxEXPAND, 5);


	this->SetSizer(sbSizer);
	this->Layout();

	// Connect Events
	m_colourPickerAmbient->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CLightPanel::m_colourPickerAmbientOnColourChanged), NULL, this);
	m_colourPickerDiffuse->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CLightPanel::m_colourPickerDiffuseOnColourChanged), NULL, this);
	m_colourPickerSpecular->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CLightPanel::m_colourPickerSpecularOnColourChanged), NULL, this);

}


CLightPanel::~CLightPanel()
{
	// Disconnect Events
	m_colourPickerAmbient->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CLightPanel::m_colourPickerAmbientOnColourChanged), NULL, this);
	m_colourPickerDiffuse->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CLightPanel::m_colourPickerDiffuseOnColourChanged), NULL, this);
	m_colourPickerSpecular->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler(CLightPanel::m_colourPickerSpecularOnColourChanged), NULL, this);
}

void CLightPanel::SetLightComponent(CDirectionalLightComponent* lightComp)
{
	m_dirLightComp = lightComp;
	
	m_textType->SetValue(wxT("Directional"));

	int r, g, b;
	XMFLOAT4 color = m_dirLightComp->GetAmbient();
	r = color.x * 255;
	g = color.y * 255;
	b = color.z * 255;
	m_colourPickerAmbient->SetColour(RGB(r, g, b));

	color = m_dirLightComp->GetDiffuse();
	r = color.x * 255;
	g = color.y * 255;
	b = color.z * 255;
	m_colourPickerDiffuse->SetColour(RGB(r, g, b));

	color = m_dirLightComp->GetSpecular();
	r = color.x * 255;
	g = color.y * 255;
	b = color.z * 255;
	m_colourPickerSpecular->SetColour(RGB(r, g, b));
}


//ÀÌº¥Æ®
void CLightPanel::m_colourPickerAmbientOnColourChanged(wxColourPickerEvent& event)
{
	wxColour color;
	XMFLOAT4 value;

	color = m_colourPickerAmbient->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;
	value.w = 1.0f;

	m_dirLightComp->SetAmbient(value);
}

void CLightPanel::m_colourPickerDiffuseOnColourChanged(wxColourPickerEvent& event)
{
	wxColour color;
	XMFLOAT4 value;

	color = m_colourPickerDiffuse->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;
	value.w = 1.0f;

	m_dirLightComp->SetDiffuse(value);
}

void CLightPanel::m_colourPickerSpecularOnColourChanged(wxColourPickerEvent& event)
{
	wxColour color;
	XMFLOAT4 value;

	color = m_colourPickerSpecular->GetColour();
	value.x = (int)(color.Red()) / 255.0f;
	value.y = (int)(color.Green()) / 255.0f;
	value.z = (int)(color.Blue()) / 255.0f;
	value.w = 1.0f;

	m_dirLightComp->SetSpecular(value);
}