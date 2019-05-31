#pragma once

#ifndef _TRANSFORM_PANEL_H_
#define _TRANSFORM_PANEL_H_

#include <GameObject\Component\TransformComponent.h>

class CTransformPanel : public wxPanel
{
public:
	void					SetTransform(CTransformComponent* transComp);

private:
	//SetTransform 함수에서 사용하는 함수
	void					SetPosition(float x, float y, float z);
	void					SetRotation(float x, float y, float z);
	void					SetScale(float x, float y, float z);

	

public:
	void					Update();

public:
	//Event
	void					m_posXOnText(wxCommandEvent& event);
	void					m_posYOnText(wxCommandEvent& event);
	void					m_posZOnText(wxCommandEvent& event);
	void					m_rotXOnText(wxCommandEvent& event);
	void					m_rotYOnText(wxCommandEvent& event);
	void					m_rotZOnText(wxCommandEvent& event);
	void					m_scaXOnText(wxCommandEvent& event);
	void					m_scaYOnText(wxCommandEvent& event);
	void					m_scaZOnText(wxCommandEvent& event);
	
	virtual void OnTextOnSetFocus(wxFocusEvent& event) { m_isUpdate = false; event.Skip(); }
	virtual void OnTextOnKillFocus(wxFocusEvent& event) { m_isUpdate = true; event.Skip(); }
	
	//Delta
	virtual void m_textCtrl_deltaOnTextEnter(wxCommandEvent& event) { event.Skip(); }
	virtual void m_choice_modeOnChoice(wxCommandEvent& event) { event.Skip(); }
	virtual void m_button_x_upOnButtonClick(wxCommandEvent& event);
	virtual void m_button_y_upOnButtonClick(wxCommandEvent& event);
	virtual void m_button_z_upOnButtonClick(wxCommandEvent& event);
	virtual void m_button_x_downOnButtonClick(wxCommandEvent& event);
	virtual void m_button_y_downOnButtonClick(wxCommandEvent& event);
	virtual void m_button_z_downOnButtonClick(wxCommandEvent& event);
	virtual void m_radioBtn_globalOnRadioButton(wxCommandEvent& event) { event.Skip(); }
	virtual void m_radioBtn_localOnRadioButton(wxCommandEvent& event) { event.Skip(); }

private:
	void					CreateCtrlPos();
	void					CreateCtrlRot();
	void					CreateCtrlScale();

	void					CreateDelta();
public:
	CTransformPanel(wxWindow* parent);
	~CTransformPanel();

private:
	wxStaticBoxSizer*		m_sbSizer;
	wxFlexGridSizer*		m_fgSizer;

	wxStaticText*			m_stextPosition;
	wxStaticText*			m_stextPosX;
	wxStaticText*			m_stextPosY;
	wxStaticText*			m_stextPosZ;
	wxStaticText*			m_stextRotation;
	wxStaticText*			m_stextRotX;
	wxStaticText*			m_stextRotY;
	wxStaticText*			m_stextRotZ;
	wxStaticText*			m_stextScale;
	wxStaticText*			m_stextScaX;
	wxStaticText*			m_stextScaY;
	wxStaticText*			m_stextScaZ;

	wxTextCtrl*				m_textPosX;
	wxTextCtrl*				m_textPosY;
	wxTextCtrl*				m_textPosZ;
	wxTextCtrl*				m_textRotX;
	wxTextCtrl*				m_textRotY;
	wxTextCtrl*				m_textRotZ;
	wxTextCtrl*				m_textScaX;
	wxTextCtrl*				m_textScaY;
	wxTextCtrl*				m_textScaZ;

	//Delta
	wxFlexGridSizer* m_fgSizer_delta;

	wxStaticText* m_staticText_delta;
	wxTextCtrl* m_textCtrl_delta;

	wxStaticText* m_staticText_mode;
	wxChoice* m_choice_mode;

	wxFlexGridSizer* m_fgSizer_deltaButton;

	wxButton* m_button_x_up;
	wxButton* m_button_y_up;
	wxButton* m_button_z_up;
	wxButton* m_button_x_down;
	wxButton* m_button_y_down;
	wxButton* m_button_z_down;

	wxRadioButton* m_radioBtn_global;
	wxRadioButton* m_radioBtn_local;

private:
	CTransformComponent*			m_selectedTransComp;

	bool							m_editByCode;

	bool							m_isUpdate;
};


#endif // !_TRANSFORM_PANEL_H_
