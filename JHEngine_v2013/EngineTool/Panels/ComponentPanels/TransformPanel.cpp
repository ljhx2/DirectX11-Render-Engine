#include "stdafx.h"
#include "..\..\stdafx.h"
#include "TransformPanel.h"



CTransformPanel::CTransformPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition)
	, m_selectedTransComp(NULL), m_editByCode(false), m_isUpdate(true)
{
	m_sbSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Transform");

	m_fgSizer = new wxFlexGridSizer(0, 7, 0, 0);
	m_fgSizer->AddGrowableCol(2, 1);
	m_fgSizer->AddGrowableCol(4, 1);
	m_fgSizer->AddGrowableCol(6, 1);
	//m_fgSizer->SetFlexibleDirection(wxBOTH);
	//m_fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	CreateCtrlPos();
	CreateCtrlRot();
	CreateCtrlScale();
	m_sbSizer->Add(m_fgSizer, 1, wxEXPAND, 5);
	m_fgSizer->Layout();
	m_fgSizer->Fit(this);

	CreateDelta();

	m_sbSizer->Layout();
	m_sbSizer->Fit(this);

	this->SetSizer(m_sbSizer);
	this->Layout();
	this->Fit();
	this->SetAutoLayout(true);

}


CTransformPanel::~CTransformPanel()
{
	//m_textPosX->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_posXOnText), NULL, this);
	//m_textPosY->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_posYOnText), NULL, this);
	//m_textPosZ->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_posZOnText), NULL, this);
	//		
	//m_textRotX->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_rotXOnText), NULL, this);
	//m_textRotY->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_rotYOnText), NULL, this);
	//m_textRotZ->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_rotZOnText), NULL, this);
	//		
	//m_textScaX->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_scaXOnText), NULL, this);
	//m_textScaY->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_scaYOnText), NULL, this);
	//m_textScaZ->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_scaZOnText), NULL, this);

	m_textPosX->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_posXOnText), NULL, this);
	m_textPosY->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_posYOnText), NULL, this);
	m_textPosZ->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_posZOnText), NULL, this);

	m_textRotX->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_rotXOnText), NULL, this);
	m_textRotY->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_rotYOnText), NULL, this);
	m_textRotZ->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_rotZOnText), NULL, this);

	m_textScaX->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_scaXOnText), NULL, this);
	m_textScaY->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_scaYOnText), NULL, this);
	m_textScaZ->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_scaZOnText), NULL, this);

	//Focus
	m_textScaX->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textScaX->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textScaY->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textScaY->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textScaZ->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textScaZ->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);

	m_textRotX->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textRotX->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textRotY->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textRotY->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textRotZ->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textRotZ->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);

	m_textPosX->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textPosX->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textPosY->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textPosY->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textPosZ->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textPosZ->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);

	//Delta
	m_textCtrl_delta->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_textCtrl_deltaOnTextEnter), NULL, this);
	m_choice_mode->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CTransformPanel::m_choice_modeOnChoice), NULL, this);
	m_button_x_up->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_x_upOnButtonClick), NULL, this);
	m_button_y_up->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_y_upOnButtonClick), NULL, this);
	m_button_z_up->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_z_upOnButtonClick), NULL, this);
	m_button_x_down->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_x_downOnButtonClick), NULL, this);
	m_button_y_down->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_y_downOnButtonClick), NULL, this);
	m_button_z_down->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_z_downOnButtonClick), NULL, this);
	m_radioBtn_global->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CTransformPanel::m_radioBtn_globalOnRadioButton), NULL, this);
	m_radioBtn_local->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CTransformPanel::m_radioBtn_localOnRadioButton), NULL, this);
}

void CTransformPanel::CreateCtrlPos()
{

	m_stextPosition = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Position"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer->Add(m_stextPosition, 0, wxALL, 5);

	m_stextPosX = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("X"));
	m_fgSizer->Add(m_stextPosX, 0, wxALL, 5);
	m_textPosX = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textPosX, 1, wxALL | wxEXPAND, 5);


	m_stextPosY = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Y"));
	m_fgSizer->Add(m_stextPosY, 0, wxALL, 5);
	m_textPosY = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textPosY, 1, wxALL | wxEXPAND, 5);

	m_stextPosZ = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Z"));
	m_fgSizer->Add(m_stextPosZ, 0, wxALL, 5);
	m_textPosZ = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textPosZ, 1, wxALL | wxEXPAND, 5);

	//m_textPosX->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_posXOnText), NULL, this);
	//m_textPosY->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_posYOnText), NULL, this);
	//m_textPosZ->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_posZOnText), NULL, this);

	m_textPosX->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textPosX->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textPosY->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textPosY->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textPosZ->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textPosZ->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);

	m_textPosX->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_posXOnText), NULL, this);
	m_textPosY->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_posYOnText), NULL, this);
	m_textPosZ->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_posZOnText), NULL, this);
}

void CTransformPanel::CreateCtrlRot()
{
	m_stextRotation = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Rotation"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer->Add(m_stextRotation, 0, wxALL, 5);

	m_stextRotX = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("X"));
	m_fgSizer->Add(m_stextRotX, 0, wxALL, 5);
	m_textRotX = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textRotX, 1, wxALL | wxEXPAND, 5);

	m_stextRotY = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Y"));
	m_fgSizer->Add(m_stextRotY, 0, wxALL, 5);
	m_textRotY = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textRotY, 1, wxALL | wxEXPAND, 5);

	m_stextRotZ = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Z"));
	m_fgSizer->Add(m_stextRotZ, 0, wxALL, 5);
	m_textRotZ = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textRotZ, 1, wxALL | wxEXPAND, 5);

	//m_textRotX->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_rotXOnText), NULL, this);
	//m_textRotY->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_rotYOnText), NULL, this);
	//m_textRotZ->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_rotZOnText), NULL, this);

	m_textRotX->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textRotX->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textRotY->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textRotY->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textRotZ->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textRotZ->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);

	m_textRotX->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_rotXOnText), NULL, this);
	m_textRotY->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_rotYOnText), NULL, this);
	m_textRotZ->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_rotZOnText), NULL, this);
}

void CTransformPanel::CreateCtrlScale()
{
	m_stextScale = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Scale"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer->Add(m_stextScale, 0, wxALL, 5);

	m_stextScaX = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("X"));
	m_fgSizer->Add(m_stextScaX, 0, wxALL, 5);
	m_textScaX = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textScaX, 1, wxALL | wxEXPAND, 5);

	m_stextScaY = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Y"));
	m_fgSizer->Add(m_stextScaY, 0, wxALL, 5);
	m_textScaY = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textScaY, 1, wxALL | wxEXPAND, 5);

	m_stextScaZ = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Z"));
	m_fgSizer->Add(m_stextScaZ, 0, wxALL, 5);
	m_textScaZ = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxTE_PROCESS_ENTER);
	m_fgSizer->Add(m_textScaZ, 1, wxALL | wxEXPAND, 5);

	//m_textScaX->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_scaXOnText), NULL, this);
	//m_textScaY->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_scaYOnText), NULL, this);
	//m_textScaZ->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CTransformPanel::m_scaZOnText), NULL, this);

	m_textScaX->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textScaX->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textScaY->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textScaY->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);
	m_textScaZ->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnSetFocus), NULL, this);
	m_textScaZ->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(CTransformPanel::OnTextOnKillFocus), NULL, this);

	m_textScaX->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_scaXOnText), NULL, this);
	m_textScaY->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_scaYOnText), NULL, this);
	m_textScaZ->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_scaZOnText), NULL, this);
}

void CTransformPanel::CreateDelta()
{
	
	m_fgSizer_delta = new wxFlexGridSizer(0, 4, 0, 0);
	m_fgSizer_delta->SetFlexibleDirection(wxBOTH);
	m_fgSizer_delta->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_delta = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Delta"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_delta->Wrap(-1);
	m_fgSizer_delta->Add(m_staticText_delta, 0, wxALL, 5);

	m_textCtrl_delta = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_delta->Add(m_textCtrl_delta, 0, wxALL, 5);

	m_staticText_mode = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Mode"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_mode->Wrap(-1);
	m_fgSizer_delta->Add(m_staticText_mode, 0, wxALL, 5);

	wxString m_choice_modeChoices[] = { wxT("Position"), wxT("Rotation"), wxT("Scale") };
	int m_choice_modeNChoices = sizeof(m_choice_modeChoices) / sizeof(wxString);
	m_choice_mode = new wxChoice(m_sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_modeNChoices, m_choice_modeChoices, 0);
	m_choice_mode->SetSelection(0);
	m_fgSizer_delta->Add(m_choice_mode, 0, wxALL, 5);

	m_radioBtn_global = new wxRadioButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Global"), wxDefaultPosition, wxDefaultSize, 0);
	m_radioBtn_global->SetValue(true);
	m_fgSizer_delta->Add(m_radioBtn_global, 0, wxALL, 5);

	m_radioBtn_local = new wxRadioButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Local"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_delta->Add(m_radioBtn_local, 0, wxALL, 5);

	m_sbSizer->Add(m_fgSizer_delta, 0, wxEXPAND, 5);

	
	m_fgSizer_deltaButton = new wxFlexGridSizer(0, 3, 0, 0);
	m_fgSizer_deltaButton->SetFlexibleDirection(wxBOTH);
	m_fgSizer_deltaButton->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_button_x_up = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("X¡è"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_deltaButton->Add(m_button_x_up, 0, wxALL, 5);

	m_button_y_up = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Y¡è"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_deltaButton->Add(m_button_y_up, 0, wxALL, 5);

	m_button_z_up = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Z¡è"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_deltaButton->Add(m_button_z_up, 0, wxALL, 5);

	m_button_x_down = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("X¡é"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_deltaButton->Add(m_button_x_down, 0, wxALL, 5);

	m_button_y_down = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Y¡é"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_deltaButton->Add(m_button_y_down, 0, wxALL, 5);

	m_button_z_down = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Z¡é"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_deltaButton->Add(m_button_z_down, 0, wxALL, 5);


	m_sbSizer->Add(m_fgSizer_deltaButton, 0, wxEXPAND, 5);


	m_textCtrl_delta->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(CTransformPanel::m_textCtrl_deltaOnTextEnter), NULL, this);
	m_choice_mode->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CTransformPanel::m_choice_modeOnChoice), NULL, this);
	m_button_x_up->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_x_upOnButtonClick), NULL, this);
	m_button_y_up->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_y_upOnButtonClick), NULL, this);
	m_button_z_up->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_z_upOnButtonClick), NULL, this);
	m_button_x_down->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_x_downOnButtonClick), NULL, this);
	m_button_y_down->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_y_downOnButtonClick), NULL, this);
	m_button_z_down->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CTransformPanel::m_button_z_downOnButtonClick), NULL, this);
	m_radioBtn_global->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CTransformPanel::m_radioBtn_globalOnRadioButton), NULL, this);
	m_radioBtn_local->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CTransformPanel::m_radioBtn_localOnRadioButton), NULL, this);
}


void CTransformPanel::SetTransform(CTransformComponent* transComp)
{
	m_editByCode = true;

	m_selectedTransComp = transComp;

	XMFLOAT3 value;

	XMStoreFloat3(&value, transComp->GetLocalPosition());
	SetPosition(value.x, value.y, value.z);

	XMStoreFloat3(&value, transComp->GetLocalRotation());
	SetRotation(XMConvertToDegrees(value.x), XMConvertToDegrees(value.y), XMConvertToDegrees(value.z));

	XMStoreFloat3(&value, transComp->GetLocalScale());
	SetScale(value.x, value.y, value.z);

	m_editByCode = false;

}

void CTransformPanel::SetPosition(float x, float y, float z)
{
	wxString value;

	value = wxString::Format(wxT("%f"), x);
	m_textPosX->SetValue(value);

	value = wxString::Format(wxT("%f"), y);
	m_textPosY->SetValue(value);

	value = wxString::Format(wxT("%f"), z);
	m_textPosZ->SetValue(value);
}

void CTransformPanel::SetRotation(float x, float y, float z)
{
	wxString value;

	value = wxString::Format(wxT("%f"), x);
	m_textRotX->SetValue(value);

	value = wxString::Format(wxT("%f"), y);
	m_textRotY->SetValue(value);

	value = wxString::Format(wxT("%f"), z);
	m_textRotZ->SetValue(value);
}

void CTransformPanel::SetScale(float x, float y, float z)
{
	wxString value;

	value = wxString::Format(wxT("%f"), x);
	m_textScaX->SetValue(value);

	value = wxString::Format(wxT("%f"), y);
	m_textScaY->SetValue(value);

	value = wxString::Format(wxT("%f"), z);
	m_textScaZ->SetValue(value);
}

void CTransformPanel::Update()
{
	if (m_isUpdate == false) return;

	XMFLOAT3 value;

	XMStoreFloat3(&value, m_selectedTransComp->GetLocalPosition());
	SetPosition(value.x, value.y, value.z);

	XMStoreFloat3(&value, m_selectedTransComp->GetLocalRotation());
	SetRotation(XMConvertToDegrees(value.x), XMConvertToDegrees(value.y), XMConvertToDegrees(value.z));

	XMStoreFloat3(&value, m_selectedTransComp->GetLocalScale());
	SetScale(value.x, value.y, value.z);
}

//Event
void CTransformPanel::m_posXOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textPosX->GetValue();
	double posX;
	text.ToDouble(&posX);

	XMFLOAT3 pos;
	XMStoreFloat3(&pos, m_selectedTransComp->GetLocalPosition());

	m_selectedTransComp->SetPosition(posX, pos.y, pos.z);	
}

void CTransformPanel::m_posYOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textPosY->GetValue();
	double posY;
	text.ToDouble(&posY);

	XMFLOAT3 pos;
	XMStoreFloat3(&pos, m_selectedTransComp->GetLocalPosition());

	m_selectedTransComp->SetPosition(pos.x, posY, pos.z);
}

void CTransformPanel::m_posZOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textPosZ->GetValue();
	double posZ;
	text.ToDouble(&posZ);

	XMFLOAT3 pos;
	XMStoreFloat3(&pos, m_selectedTransComp->GetLocalPosition());

	m_selectedTransComp->SetPosition(pos.x, pos.y, posZ);
}

void CTransformPanel::m_rotXOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textRotX->GetValue();
	double rotX;
	text.ToDouble(&rotX);
	rotX = XMConvertToRadians(rotX);

	XMFLOAT3 rot;
	XMStoreFloat3(&rot, m_selectedTransComp->GetLocalRotation());

	m_selectedTransComp->SetRotation(rotX, rot.y, rot.z);
}

void CTransformPanel::m_rotYOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textRotY->GetValue();
	double rotY;
	text.ToDouble(&rotY);
	rotY = XMConvertToRadians(rotY);

	XMFLOAT3 rot;
	XMStoreFloat3(&rot, m_selectedTransComp->GetLocalRotation());

	m_selectedTransComp->SetRotation(rot.x, rotY, rot.z);
}

void CTransformPanel::m_rotZOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textRotZ->GetValue();
	double rotZ;
	text.ToDouble(&rotZ);
	rotZ = XMConvertToRadians(rotZ);

	XMFLOAT3 rot;
	XMStoreFloat3(&rot, m_selectedTransComp->GetLocalRotation());

	m_selectedTransComp->SetRotation(rot.x, rot.y, rotZ);
}

void CTransformPanel::m_scaXOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textScaX->GetValue();
	double scaleX;
	text.ToDouble(&scaleX);

	XMFLOAT3 scale;
	XMStoreFloat3(&scale, m_selectedTransComp->GetLocalScale());

	m_selectedTransComp->SetScale(scaleX, scale.y, scale.z);
}

void CTransformPanel::m_scaYOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textScaY->GetValue();
	double scaleY;
	text.ToDouble(&scaleY);

	XMFLOAT3 scale;
	XMStoreFloat3(&scale, m_selectedTransComp->GetLocalScale());

	m_selectedTransComp->SetScale(scale.x, scaleY, scale.z);
}

void CTransformPanel::m_scaZOnText(wxCommandEvent& event)
{
	if (m_editByCode) return;

	wxString text = m_textScaZ->GetValue();
	double scaleZ;
	text.ToDouble(&scaleZ);

	XMFLOAT3 scale;
	XMStoreFloat3(&scale, m_selectedTransComp->GetLocalScale());

	m_selectedTransComp->SetScale(scale.x, scale.y, scaleZ);

}

void CTransformPanel::m_button_x_upOnButtonClick(wxCommandEvent& event)
{
	wxString delta = m_textCtrl_delta->GetValue();
	double deltaD;
	delta.ToDouble(&deltaD);

	bool global = m_radioBtn_global->GetValue();

	int mode = m_choice_mode->GetSelection();

	switch (mode)
	{
	case 0:	//position
	{
		if (global)
			m_selectedTransComp->Translation_World(deltaD, 0.0f, 0.0f);
		else
			m_selectedTransComp->Translation_Self(deltaD, 0.0f, 0.0f);
	}
		break;
	case 1:	//rotation
	{
		if (global)
			m_selectedTransComp->Rotate_World(XMConvertToRadians(deltaD), 0.0f, 0.0f);
		else
			m_selectedTransComp->Rotate_Self(XMConvertToRadians(deltaD), 0.0f, 0.0f);
	}
		break;
	case 2:	//scale
		m_selectedTransComp->Scaling(deltaD, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void CTransformPanel::m_button_y_upOnButtonClick(wxCommandEvent& event)
{
	wxString delta = m_textCtrl_delta->GetValue();
	double deltaD;
	delta.ToDouble(&deltaD);

	bool global = m_radioBtn_global->GetValue();

	int mode = m_choice_mode->GetSelection();

	switch (mode)
	{
	case 0:	//position
	{
		if (global)
			m_selectedTransComp->Translation_World(0.0f, deltaD, 0.0f);
		else
			m_selectedTransComp->Translation_Self(0.0f, deltaD, 0.0f);
	}
		break;
	case 1:	//rotation
	{
		if (global)
			m_selectedTransComp->Rotate_World(0.0f, XMConvertToRadians(deltaD), 0.0f);
		else
			m_selectedTransComp->Rotate_Self(0.0f, XMConvertToRadians(deltaD), 0.0f);
	}
		
		break;
	case 2:	//scale
		m_selectedTransComp->Scaling(0.0f, deltaD, 0.0f);
		break;
	default:
		break;
	}
}

void CTransformPanel::m_button_z_upOnButtonClick(wxCommandEvent& event)
{
	wxString delta = m_textCtrl_delta->GetValue();
	double deltaD;
	delta.ToDouble(&deltaD);

	bool global = m_radioBtn_global->GetValue();

	int mode = m_choice_mode->GetSelection();

	switch (mode)
	{
	case 0:	//position
	{
		if (global)
			m_selectedTransComp->Translation_World(0.0f, 0.0f, deltaD);
		else
			m_selectedTransComp->Translation_Self(0.0f, 0.0f, deltaD);
	}
		break;
	case 1:	//rotation
	{
		if (global)
			m_selectedTransComp->Rotate_World(0.0f, 0.0f, XMConvertToRadians(deltaD));
		else
			m_selectedTransComp->Rotate_Self(0.0f, 0.0f, XMConvertToRadians(deltaD));
	}
		break;
	case 2:	//scale
		m_selectedTransComp->Scaling(0.0f, 0.0f, deltaD);
		break;
	default:
		break;
	}
}

void CTransformPanel::m_button_x_downOnButtonClick(wxCommandEvent& event)
{
	wxString delta = m_textCtrl_delta->GetValue();
	double deltaD;
	delta.ToDouble(&deltaD);

	bool global = m_radioBtn_global->GetValue();

	int mode = m_choice_mode->GetSelection();

	switch (mode)
	{
	case 0:	//position
	{
		if (global)
			m_selectedTransComp->Translation_World(-deltaD, 0.0f, 0.0f);
		else
			m_selectedTransComp->Translation_Self(-deltaD, 0.0f, 0.0f);
	}
	break;
	case 1:	//rotation
	{
		if (global)
			m_selectedTransComp->Rotate_World(-XMConvertToRadians(deltaD), 0.0f, 0.0f);
		else
			m_selectedTransComp->Rotate_Self(-XMConvertToRadians(deltaD), 0.0f, 0.0f);
	}
	break;
	case 2:	//scale
		m_selectedTransComp->Scaling(-deltaD, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void CTransformPanel::m_button_y_downOnButtonClick(wxCommandEvent& event)
{
	wxString delta = m_textCtrl_delta->GetValue();
	double deltaD;
	delta.ToDouble(&deltaD);

	bool global = m_radioBtn_global->GetValue();

	int mode = m_choice_mode->GetSelection();

	switch (mode)
	{
	case 0:	//position
	{
		if (global)
			m_selectedTransComp->Translation_World(0.0f, -deltaD, 0.0f);
		else
			m_selectedTransComp->Translation_Self(0.0f, -deltaD, 0.0f);
	}
	break;
	case 1:	//rotation
	{
		if (global)
			m_selectedTransComp->Rotate_World(0.0f, -XMConvertToRadians(deltaD), 0.0f);
		else
			m_selectedTransComp->Rotate_Self(0.0f, -XMConvertToRadians(deltaD), 0.0f);
	}

	break;
	case 2:	//scale
		m_selectedTransComp->Scaling(0.0f, -deltaD, 0.0f);
		break;
	default:
		break;
	}
}

void CTransformPanel::m_button_z_downOnButtonClick(wxCommandEvent& event)
{
	wxString delta = m_textCtrl_delta->GetValue();
	double deltaD;
	delta.ToDouble(&deltaD);

	bool global = m_radioBtn_global->GetValue();

	int mode = m_choice_mode->GetSelection();

	switch (mode)
	{
	case 0:	//position
	{
		if (global)
			m_selectedTransComp->Translation_World(0.0f, 0.0f, -deltaD);
		else
			m_selectedTransComp->Translation_Self(0.0f, 0.0f, -deltaD);
	}
	break;
	case 1:	//rotation
	{
		if (global)
			m_selectedTransComp->Rotate_World(0.0f, 0.0f, -XMConvertToRadians(deltaD));
		else
			m_selectedTransComp->Rotate_Self(0.0f, 0.0f, -XMConvertToRadians(deltaD));
	}
	break;
	case 2:	//scale
		m_selectedTransComp->Scaling(0.0f, 0.0f, -deltaD);
		break;
	default:
		break;
	}
}
/// end event /////
