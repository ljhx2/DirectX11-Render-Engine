#pragma once

#ifndef _ANIMATOR_PANEL_H_
#define _ANIMATOR_PANEL_H_

#include <GameObject\Component\AnimationComponent\AnimComponent.h>

class CAnimatorPanel : public wxPanel
{
public:
	void			SetAnimatorComp(CAnimComponent* animComp);

private:	//SetAnimatorComp함수에서 사용할 함수들
	void			ChangeTrackChoiceControl();
	void			ChangeSliderControlAndTime();
	void			ChangeUseClipControl();

	void			ChangeClipChoiceControl();



public:
	void			Update();


public:
	//이벤트
	virtual void m_choice_TrackOnChoice(wxCommandEvent& event);
	virtual void m_button_playOnButtonClick(wxCommandEvent& event);
	virtual void m_button_pauseOnButtonClick(wxCommandEvent& event);
	virtual void m_button_stopOnButtonClick(wxCommandEvent& event);
	virtual void m_checkBox_useClipOnCheckBox(wxCommandEvent& event);
	virtual void m_choice_clipOnChoice(wxCommandEvent& event);
	virtual void m_button_clipPlayOnButtonClick(wxCommandEvent& event);
	virtual void m_button_AddClip_AddOnButtonClick(wxCommandEvent& event);
	virtual void m_button_AddClip_deleteOnButtonClick(wxCommandEvent& event);

public:
	CAnimatorPanel(wxWindow* parent);
	~CAnimatorPanel();

protected:
	wxStaticBoxSizer* m_sbSizer;

	
	//track
	wxFlexGridSizer* m_fgSizer_track;

	wxFlexGridSizer* m_fgSizer_trackKind;
	wxStaticText* m_staticText_TrackName;
	wxChoice* m_choice_Track;

	wxFlexGridSizer* m_fgSizer_Slider;
	wxSlider* m_slider;

	wxFlexGridSizer* m_fgSizer_SliderSec;
	wxStaticText* m_staticText_StartTime;
	wxStaticText* m_staticText_PlayTime;
	wxStaticText* m_staticText_EndTime;

	wxFlexGridSizer* m_fgSizer_PlayButton;
	wxButton* m_button_play;
	wxButton* m_button_pause;
	wxButton* m_button_stop;

	wxFlexGridSizer* m_fgSizer_useClip;
	wxStaticText* m_staticText_useClip;
	wxCheckBox* m_checkBox_useClip;

	//clip
	wxFlexGridSizer* m_fgSizer_clip;

	wxFlexGridSizer* m_fgSizer_clipName;
	wxFlexGridSizer* m_fgSizer_clipText;
	wxStaticText* m_staticText_clip;
	wxChoice* m_choice_clip;
	wxButton* m_button_clipPlay;

	wxFlexGridSizer* m_fgSizer_addClip;
	wxStaticText* m_staticText_AddClip_clipName;
	wxTextCtrl* m_textCtrl_AddClip_clipName;

	wxFlexGridSizer* m_fgSizer_addClip_choice;
	wxStaticText* m_staticText_AddClip_trackName;
	wxChoice* m_choice_AddClip_track;

	wxStaticText* m_staticText_AddClip_StartTime;
	wxTextCtrl* m_textCtrl_AddClip_startTime;

	wxStaticText* m_staticText_AddClip_EndTime;
	wxTextCtrl* m_textCtrl_AddClip_endTime;

	wxStaticText* m_staticText_AddClip_isLoop;
	wxCheckBox* m_checkBox_AddClip_isLoop;

	wxButton* m_button_AddClip_Add;
	wxButton* m_button_AddClip_delete;

protected:
	CAnimComponent*					m_selectedAnimComponent;

};

#endif // !_ANIMATOR_PANEL_H_
