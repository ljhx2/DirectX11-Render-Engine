#pragma once

#ifndef _RENDERER_PANEL_H_
#define _RENDERER_PANEL_H_

#include <GameObject\Component\RendererComponent\RenderComponent.h>

#include "Dialog\MeshDialog.h"
#include "Dialog\MaterialDialog.h"

class CRendererPanel : public wxPanel
{
public:
	void			SetRenderer(CRenderComponent* renderComp);

public:
	//SetRenderer�Լ����� ����ϴ� �Լ�
	void			SetMeshText(wxString meshName);	//MeshDialogŬ���������� ���
	void			SetCastShaowCheckBox(bool castShadow);
	void			SetReceiveShadodwCheckBox(bool receiveShadow);
	void			SetMaterialText(wxString materialName);
	void			SetTextureTrans(int trans);

protected:
	void			CreateCtrlMesh();
	void			CreateCtrlCastShadow();
	void			CreateCtrlReceiveShadow();
	void			CreateCtrlMaterial();
	void			CreateCtrlTextureTrans();
	void			CreateDialog();

public:
	//�̺�Ʈ
	void	m_meshOnButtonClick(wxCommandEvent& event);
	void	m_materialOnButtonClick(wxCommandEvent& event);
	void	m_castShadowOnCheckBox(wxCommandEvent& event);
	void	m_receiveShadowOnCheckBox(wxCommandEvent& event);
	void	m_textureTransOnSlider(wxScrollEvent& event);
	//���̾�α� �̺�Ʈ
	void	m_meshDialogOnInitDialog(wxInitDialogEvent& event);

public:
	CRendererPanel(wxWindow* parent);
	virtual ~CRendererPanel();

protected:
	wxStaticBoxSizer*		m_sbSizer;
	wxFlexGridSizer*		m_fgSizer;

	wxStaticText*			m_stextMesh;
	wxStaticText*			m_stextCastShadow;
	wxStaticText*			m_stextRecieveShadow;
	wxStaticText*			m_stextMaterial;
	wxStaticText*			m_stextTextureTrans;

	wxTextCtrl*				m_textMesh;
	wxTextCtrl*				m_textMaterial;

	wxCheckBox*				m_checkCastShadow;
	wxCheckBox*				m_checkReceiveShadow;

	wxButton*				m_buttonMesh;
	wxButton*				m_buttonMaterial;

	wxSlider*				m_sliderTextureTrans;

protected:
	CRenderComponent*		m_selectedRenderComp;

protected:
	//Dialog
	CMeshDialog*			m_meshDialog;
	CMaterialDialog*		m_materialDialog;
};

#endif // !_RENDERER_PANEL_H_
