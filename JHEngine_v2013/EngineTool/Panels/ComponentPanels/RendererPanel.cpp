#include "stdafx.h"
#include "..\..\stdafx.h"
#include "RendererPanel.h"

#include <Core\StringHelper.h>

CRendererPanel::CRendererPanel(wxWindow* parent)
	: wxPanel(parent)
	, m_selectedRenderComp(NULL)
{
	m_sbSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Mesh Renderer");

	m_fgSizer = new wxFlexGridSizer(0, 3, 0, 0);
	m_fgSizer->AddGrowableCol(1);

	CreateCtrlMesh();
	CreateCtrlCastShadow();
	CreateCtrlReceiveShadow();
	CreateCtrlMaterial();
	CreateCtrlTextureTrans();
	CreateDialog();

	m_sbSizer->Add(m_fgSizer, 1, wxEXPAND, 5);

	m_fgSizer->Layout();
	m_fgSizer->Fit(this);

	m_sbSizer->Layout();
	m_sbSizer->Fit(this);

	this->SetSizer(m_sbSizer);
	this->Layout();
	this->Fit();
	this->SetAutoLayout(true);
}


CRendererPanel::~CRendererPanel()
{
	m_buttonMesh->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CRendererPanel::m_meshOnButtonClick), NULL, this);
	m_checkCastShadow->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CRendererPanel::m_castShadowOnCheckBox), NULL, this);
	m_checkReceiveShadow->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CRendererPanel::m_receiveShadowOnCheckBox), NULL, this);
	m_buttonMaterial->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CRendererPanel::m_materialOnButtonClick), NULL, this);
	//둘중하나
	m_sliderTextureTrans->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(CRendererPanel::m_textureTransOnSlider), NULL, this);
	//m_sliderTextureTrans->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(CRendererPanel::m_textureTransOnSlider), NULL, this);

	m_meshDialog->Disconnect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(CRendererPanel::m_meshDialogOnInitDialog));
}

void CRendererPanel::CreateCtrlMesh()
{
	m_stextMesh = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Mesh"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer->Add(m_stextMesh, 0, wxALL, 5);

	m_textMesh = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_fgSizer->Add(m_textMesh, 1, wxALL | wxEXPAND, 5);

	m_buttonMesh = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("..."), wxDefaultPosition, wxSize(30, -1), 0);
	m_fgSizer->Add(m_buttonMesh, 0, wxALL, 5);

	m_buttonMesh->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CRendererPanel::m_meshOnButtonClick), NULL, this);
}

void CRendererPanel::CreateCtrlCastShadow()
{
	m_stextCastShadow = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Cast Shadow"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer->Add(m_stextCastShadow, 0, wxALL, 5);

	m_checkCastShadow = new wxCheckBox(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	m_checkCastShadow->SetValue(true);
	m_fgSizer->Add(m_checkCastShadow, 1, wxALL | wxEXPAND, 5);

	m_fgSizer->Add(0, 0, 1, wxEXPAND, 5);

	m_checkCastShadow->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CRendererPanel::m_castShadowOnCheckBox), NULL, this);
}

void CRendererPanel::CreateCtrlReceiveShadow()
{
	m_stextRecieveShadow = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Recieve Shadow"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer->Add(m_stextRecieveShadow, 0, wxALL, 5);

	m_checkReceiveShadow = new wxCheckBox(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	m_checkReceiveShadow->SetValue(true);
	m_fgSizer->Add(m_checkReceiveShadow, 1, wxALL | wxEXPAND, 5);

	m_fgSizer->Add(0, 0, 1, wxEXPAND, 5);

	m_checkReceiveShadow->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CRendererPanel::m_receiveShadowOnCheckBox), NULL, this);
}

void CRendererPanel::CreateCtrlMaterial()
{
	m_stextMaterial = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Material"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer->Add(m_stextMaterial, 0, wxALL, 5);

	m_textMaterial = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("default_material"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_fgSizer->Add(m_textMaterial, 1, wxALL | wxEXPAND , 5);

	m_buttonMaterial = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("..."), wxDefaultPosition, wxSize(30, -1), 0);
	m_fgSizer->Add(m_buttonMaterial, 0, wxALL, 5);

	m_buttonMaterial->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CRendererPanel::m_materialOnButtonClick), NULL, this);
}

void CRendererPanel::CreateCtrlTextureTrans()
{
	m_stextTextureTrans = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Texture Transform"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer->Add(m_stextTextureTrans, 0, wxALL, 5);

	m_sliderTextureTrans = new wxSlider(m_sbSizer->GetStaticBox(), wxID_ANY, 10, 1, 19, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	m_fgSizer->Add(m_sliderTextureTrans, 1, wxALL | wxEXPAND, 5);

	//둘중하나
	m_sliderTextureTrans->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(CRendererPanel::m_textureTransOnSlider), NULL, this);
	//m_sliderTextureTrans->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(CRendererPanel::m_textureTransOnSlider), NULL, this);
}

void CRendererPanel::CreateDialog()
{
	m_meshDialog = new CMeshDialog(this);
	m_materialDialog = new CMaterialDialog(this);

	m_meshDialog->Connect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(CRendererPanel::m_meshDialogOnInitDialog));
}

void CRendererPanel::SetRenderer(CRenderComponent* renderComp)
{
	m_selectedRenderComp = renderComp;

	CMesh* mesh = m_selectedRenderComp->GetMesh();
	if (mesh)
	{
		SetMeshText(CStringHelper::PickFileNameFromFullPath(mesh->GetID()).c_str());
	}
	else
	{
		SetMeshText(wxT("NULL"));
	}
	

	SetCastShaowCheckBox(m_selectedRenderComp->GetCastShadow());
	SetReceiveShadodwCheckBox(m_selectedRenderComp->GetReceiveShadow());

	CMaterial* material = m_selectedRenderComp->GetExternMaterial();
	if (material)
	{
		SetMaterialText(CStringHelper::PickFileNameFromFullPath(material->GetID()).c_str());
	}
	else
	{
		SetMaterialText(wxT("default_material"));
	}

	//0.1 ~ 10 까지
	//0.1 ~ 1 까지는 곱하기 10을 해서 계산
	//2 ~ 10 까지는 더하기 9을 해서 계산
	float valueF = m_selectedRenderComp->GetTexTrans();
	int sliderValue;
	if (valueF <= 1.0f)
	{
		sliderValue = valueF * 10;
	}
	else
	{
		sliderValue = valueF + 9;
	}
	SetTextureTrans(sliderValue);

}

void CRendererPanel::SetMeshText(wxString meshName)
{
	m_textMesh->SetValue(meshName);
}

void CRendererPanel::SetCastShaowCheckBox(bool castShadow)
{
	m_checkCastShadow->SetValue(castShadow);
}

void CRendererPanel::SetReceiveShadodwCheckBox(bool receiveShadow)
{
	m_checkReceiveShadow->SetValue(receiveShadow);
}

void CRendererPanel::SetMaterialText(wxString materialName)
{
	m_textMaterial->SetValue(materialName);
}

void CRendererPanel::SetTextureTrans(int trans)
{
	m_sliderTextureTrans->SetValue(trans);
}

//이벤트
void CRendererPanel::m_meshOnButtonClick(wxCommandEvent& event)
{
	m_meshDialog->Show();
	m_meshDialog->SetRenderComp(m_selectedRenderComp);
	m_meshDialog->SetListBox();
}

void CRendererPanel::m_materialOnButtonClick(wxCommandEvent& event)
{
	m_materialDialog->Show();
	m_materialDialog->SetRenderComp(m_selectedRenderComp);
	m_materialDialog->SetColor();
	m_materialDialog->SetDirPicker();
}

void CRendererPanel::m_castShadowOnCheckBox(wxCommandEvent& event)
{
	bool value = m_checkCastShadow->GetValue();

	m_selectedRenderComp->SetCastShadow(value);
}

void CRendererPanel::m_receiveShadowOnCheckBox(wxCommandEvent& event)
{
	bool value = m_checkReceiveShadow->GetValue();

	m_selectedRenderComp->SetReceiveShadow(value);
}

void CRendererPanel::m_textureTransOnSlider(wxScrollEvent& event)
{
	//1 ~ 20 까지 10은 원래크기
	//1 ~ 10 까지는 나누기 10을 해서 계산
	//11 ~ 19 까지는 빼기 9을 해서 계산
	int value = event.GetInt();
	float valueF;
	if (value < 11)	//1 ~ 10 까지는 나누기 10을 해서 계산
	{
		valueF = value * 0.1f;
	}
	else //11 ~20 까지는 빼기 9을 해서 계산
	{
		valueF = value - 9;
	}
	m_selectedRenderComp->SetTexTrans(valueF);
}

//다이얼로그 이벤트
void CRendererPanel::m_meshDialogOnInitDialog(wxInitDialogEvent& event)
{
	//m_meshDialog->SetRenderComp(m_selectedRenderComp);
	//m_meshDialog->SetListBox();
}