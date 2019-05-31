#include "stdafx.h"
#include "..\..\stdafx.h"
#include "AnimatorPanel.h"

#include <Core\StringHelper.h>

CAnimatorPanel::CAnimatorPanel(wxWindow* parent)
	: wxPanel(parent)
	, m_selectedAnimComponent(NULL)
{
	//sbSizer
	m_sbSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Animator")), wxVERTICAL);

	//track
	m_fgSizer_track = new wxFlexGridSizer(0, 1, 0, 0);
	m_fgSizer_track->AddGrowableCol(0);
	m_fgSizer_track->SetFlexibleDirection(wxBOTH);
	m_fgSizer_track->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	//track_kind
	m_fgSizer_trackKind = new wxFlexGridSizer(0, 2, 0, 0);
	m_fgSizer_trackKind->SetFlexibleDirection(wxBOTH);
	m_fgSizer_trackKind->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	//trackName
	m_staticText_TrackName = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Track"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_TrackName->Wrap(-1);
	m_fgSizer_trackKind->Add(m_staticText_TrackName, 0, wxALL, 5);

	//trackChoice
	wxArrayString m_choice_TrackChoices;
	m_choice_Track = new wxChoice(m_sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_TrackChoices, 0);
	m_choice_Track->SetSelection(0);
	m_fgSizer_trackKind->Add(m_choice_Track, 0, wxALL, 5);

	m_fgSizer_track->Add(m_fgSizer_trackKind, 1, wxEXPAND, 5);

	//slider
	m_fgSizer_Slider = new wxFlexGridSizer(0, 1, 0, 0);
	m_fgSizer_Slider->AddGrowableCol(0);
	m_fgSizer_Slider->SetFlexibleDirection(wxBOTH);
	m_fgSizer_Slider->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_slider = new wxSlider(m_sbSizer->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	m_fgSizer_Slider->Add(m_slider, 0, wxALL | wxEXPAND, 5);

	m_fgSizer_track->Add(m_fgSizer_Slider, 1, wxEXPAND, 5);

	//sliderSec
	m_fgSizer_SliderSec = new wxFlexGridSizer(0, 3, 0, 0);
	m_fgSizer_SliderSec->AddGrowableCol(0);
	m_fgSizer_SliderSec->AddGrowableCol(1);
	m_fgSizer_SliderSec->AddGrowableCol(2);
	m_fgSizer_SliderSec->SetFlexibleDirection(wxBOTH);
	m_fgSizer_SliderSec->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_StartTime = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("StartTime"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_StartTime->Wrap(-1);
	m_fgSizer_SliderSec->Add(m_staticText_StartTime, 0, wxALIGN_LEFT | wxALL, 5);

	m_staticText_PlayTime = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("PlayTime"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_PlayTime->Wrap(-1);
	m_fgSizer_SliderSec->Add(m_staticText_PlayTime, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticText_EndTime = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("EndTime"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_EndTime->Wrap(-1);
	m_fgSizer_SliderSec->Add(m_staticText_EndTime, 0, wxALIGN_RIGHT | wxALL, 5);


	m_fgSizer_track->Add(m_fgSizer_SliderSec, 1, wxEXPAND, 5);

	//playButton
	m_fgSizer_PlayButton = new wxFlexGridSizer(0, 3, 0, 0);
	m_fgSizer_PlayButton->AddGrowableCol(0);
	m_fgSizer_PlayButton->AddGrowableCol(1);
	m_fgSizer_PlayButton->AddGrowableCol(2);
	m_fgSizer_PlayButton->SetFlexibleDirection(wxBOTH);
	m_fgSizer_PlayButton->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_button_play = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Play"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_PlayButton->Add(m_button_play, 0, wxALL | wxEXPAND, 5);

	m_button_pause = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Pause"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_PlayButton->Add(m_button_pause, 0, wxALL | wxEXPAND, 5);

	m_button_stop = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_PlayButton->Add(m_button_stop, 0, wxALL | wxEXPAND, 5);


	m_fgSizer_track->Add(m_fgSizer_PlayButton, 1, wxEXPAND, 5);

	//use clip
	m_fgSizer_useClip = new wxFlexGridSizer(0, 2, 0, 0);
	m_fgSizer_useClip->SetFlexibleDirection(wxBOTH);
	m_fgSizer_useClip->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_useClip = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("UseClip"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_useClip->Wrap(-1);
	m_fgSizer_useClip->Add(m_staticText_useClip, 0, wxALL, 5);

	m_checkBox_useClip = new wxCheckBox(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_useClip->Add(m_checkBox_useClip, 0, wxALL, 5);


	m_fgSizer_track->Add(m_fgSizer_useClip, 1, wxEXPAND, 5);


	m_sbSizer->Add(m_fgSizer_track, 0, wxEXPAND, 5);

	//clip
	m_fgSizer_clip = new wxFlexGridSizer(0, 1, 0, 0);
	m_fgSizer_clip->AddGrowableCol(0);
	m_fgSizer_clip->SetFlexibleDirection(wxBOTH);
	m_fgSizer_clip->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	//clipName
	m_fgSizer_clipName = new wxFlexGridSizer(0, 2, 0, 0);
	m_fgSizer_clipName->AddGrowableCol(0);
	m_fgSizer_clipName->SetFlexibleDirection(wxBOTH);
	m_fgSizer_clipName->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_fgSizer_clipText = new wxFlexGridSizer(0, 2, 0, 0);
	m_fgSizer_clipText->AddGrowableCol(0);
	m_fgSizer_clipText->SetFlexibleDirection(wxBOTH);
	m_fgSizer_clipText->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_clip = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Clip"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_clip->Wrap(-1);
	m_fgSizer_clipText->Add(m_staticText_clip, 0, wxALL, 5);

	wxArrayString m_choice_clipChoices;
	m_choice_clip = new wxChoice(m_sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_clipChoices, 0);
	m_choice_clip->SetSelection(0);
	m_fgSizer_clipText->Add(m_choice_clip, 0, wxALL, 5);

	m_fgSizer_clipName->Add(m_fgSizer_clipText, 0, wxALL, 5);

	m_button_clipPlay = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Play"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_clipName->Add(m_button_clipPlay, 0, wxALL, 5);


	m_fgSizer_clip->Add(m_fgSizer_clipName, 1, wxEXPAND, 5);

	//add Clip
	m_fgSizer_addClip = new wxFlexGridSizer(0, 2, 0, 0);
	m_fgSizer_addClip->SetFlexibleDirection(wxBOTH);
	m_fgSizer_addClip->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_AddClip_clipName = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Clip Name"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_AddClip_clipName->Wrap(-1);
	m_fgSizer_addClip->Add(m_staticText_AddClip_clipName, 0, wxALL, 5);

	m_textCtrl_AddClip_clipName = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_addClip->Add(m_textCtrl_AddClip_clipName, 0, wxALL, 5);


	m_fgSizer_addClip_choice = new wxFlexGridSizer(0, 2, 0, 0);
	m_fgSizer_addClip_choice->SetFlexibleDirection(wxBOTH);
	m_fgSizer_addClip_choice->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_AddClip_trackName = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Track"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_AddClip_trackName->Wrap(-1);
	m_fgSizer_addClip_choice->Add(m_staticText_AddClip_trackName, 0, wxALL | wxEXPAND, 5);

	wxArrayString m_choice_AddClip_trackChoices;
	m_choice_AddClip_track = new wxChoice(m_sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_AddClip_trackChoices, 0);
	m_choice_AddClip_track->SetSelection(0);
	m_fgSizer_addClip_choice->Add(m_choice_AddClip_track, 0, wxALL, 5);

	m_fgSizer_addClip->Add(m_fgSizer_addClip_choice, 1, wxEXPAND, 5);
	m_fgSizer_addClip->AddSpacer(0);

	m_staticText_AddClip_StartTime = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Start Time"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_AddClip_StartTime->Wrap(-1);
	m_fgSizer_addClip->Add(m_staticText_AddClip_StartTime, 0, wxALL, 5);

	m_textCtrl_AddClip_startTime = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_addClip->Add(m_textCtrl_AddClip_startTime, 0, wxALL, 5);

	m_staticText_AddClip_EndTime = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("End Time"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_AddClip_EndTime->Wrap(-1);
	m_fgSizer_addClip->Add(m_staticText_AddClip_EndTime, 0, wxALL, 5);

	m_textCtrl_AddClip_endTime = new wxTextCtrl(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_addClip->Add(m_textCtrl_AddClip_endTime, 0, wxALL, 5);

	m_staticText_AddClip_isLoop = new wxStaticText(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Is Loop"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_AddClip_isLoop->Wrap(-1);
	m_fgSizer_addClip->Add(m_staticText_AddClip_isLoop, 0, wxALL, 5);

	m_checkBox_AddClip_isLoop = new wxCheckBox(m_sbSizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_addClip->Add(m_checkBox_AddClip_isLoop, 0, wxALL, 5);

	m_button_AddClip_Add = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_addClip->Add(m_button_AddClip_Add, 0, wxALL, 5);

	m_button_AddClip_delete = new wxButton(m_sbSizer->GetStaticBox(), wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0);
	m_fgSizer_addClip->Add(m_button_AddClip_delete, 0, wxALL, 5);


	m_fgSizer_clip->Add(m_fgSizer_addClip, 1, wxEXPAND, 5);


	m_sbSizer->Add(m_fgSizer_clip, 1, wxEXPAND, 5);

	this->SetSizer(m_sbSizer);
	this->Layout();
	this->Fit();

	// Connect Events
	m_choice_Track->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CAnimatorPanel::m_choice_TrackOnChoice), NULL, this);
	m_button_play->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_playOnButtonClick), NULL, this);
	m_button_pause->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_pauseOnButtonClick), NULL, this);
	m_button_stop->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_stopOnButtonClick), NULL, this);
	m_checkBox_useClip->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_checkBox_useClipOnCheckBox), NULL, this);
	m_choice_clip->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CAnimatorPanel::m_choice_clipOnChoice), NULL, this);
	m_button_clipPlay->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_clipPlayOnButtonClick), NULL, this);
	m_button_AddClip_Add->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_AddClip_AddOnButtonClick), NULL, this);
	m_button_AddClip_delete->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_AddClip_deleteOnButtonClick), NULL, this);
}


CAnimatorPanel::~CAnimatorPanel()
{
	// Disconnect Events
	m_choice_Track->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CAnimatorPanel::m_choice_TrackOnChoice), NULL, this);
	m_button_play->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_playOnButtonClick), NULL, this);
	m_button_pause->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_pauseOnButtonClick), NULL, this);
	m_button_stop->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_stopOnButtonClick), NULL, this);
	m_checkBox_useClip->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_checkBox_useClipOnCheckBox), NULL, this);
	m_choice_clip->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CAnimatorPanel::m_choice_clipOnChoice), NULL, this);
	m_button_clipPlay->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_clipPlayOnButtonClick), NULL, this);
	m_button_AddClip_Add->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_AddClip_AddOnButtonClick), NULL, this);
	m_button_AddClip_delete->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CAnimatorPanel::m_button_AddClip_deleteOnButtonClick), NULL, this);
}

void CAnimatorPanel::SetAnimatorComp(CAnimComponent* animComp)
{
	m_selectedAnimComponent = animComp;
	
//track
	ChangeTrackChoiceControl();
	ChangeSliderControlAndTime();
	
//clip
	ChangeClipChoiceControl();

//useclip
	ChangeUseClipControl();
	
}

//SetAnimatorComp함수에서 사용할 함수들
void CAnimatorPanel::ChangeTrackChoiceControl()
{
	m_choice_Track->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CAnimatorPanel::m_choice_TrackOnChoice), NULL, this);
	
	delete m_choice_Track;
	delete m_choice_AddClip_track;

	wxArrayString m_choice_TrackChoices;

	int trackCount = m_selectedAnimComponent->GetAnimator()->m_animations.size();
	for (int i = 0; i < trackCount; ++i)
	{
		std::string trackName;
		std::wstring& trackNameW = m_selectedAnimComponent->GetAnimator()->m_animations[i].m_name;
		CStringHelper::WStringToString(trackNameW, trackName);
		m_choice_TrackChoices.Add(wxString(trackName.c_str()));
	}
	m_choice_Track = new wxChoice(m_sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_TrackChoices, 0);
	m_choice_Track->SetSelection(0);
	m_fgSizer_trackKind->Add(m_choice_Track, 0, wxALL, 5);

	m_choice_AddClip_track = new wxChoice(m_sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_TrackChoices, 0);
	m_choice_AddClip_track->SetSelection(0);
	m_fgSizer_addClip_choice->Add(m_choice_AddClip_track, 0, wxALL, 5);
	

	m_choice_Track->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CAnimatorPanel::m_choice_TrackOnChoice), NULL, this);

}

void CAnimatorPanel::ChangeSliderControlAndTime()
{
	//Slider
	float startTime = m_selectedAnimComponent->GetStartTime();
	float endTime = m_selectedAnimComponent->GetEndTime();
	float currTime = m_selectedAnimComponent->GetAccumTime();

	int currSliderPos = currTime / (endTime - startTime) * 100;

	m_slider->SetValue(currSliderPos);

	//Time
	m_staticText_StartTime->SetLabel(wxString::Format("%.2f", startTime));
	m_staticText_PlayTime->SetLabel(wxString::Format("%.2f", currTime));
	m_staticText_EndTime->SetLabel(wxString::Format("%.2f", endTime));
}

void CAnimatorPanel::ChangeUseClipControl()
{
	bool value = m_selectedAnimComponent->GetUseClip();
	m_checkBox_useClip->SetValue(value);

	if (value)
	{
		m_sbSizer->Show(m_fgSizer_clip);
	}
	else
	{
		m_sbSizer->Hide(m_fgSizer_clip);
	}
}

void CAnimatorPanel::ChangeClipChoiceControl()
{
	m_choice_clip->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CAnimatorPanel::m_choice_clipOnChoice), NULL, this);

	delete m_choice_clip;

	wxArrayString m_choice_clipChoices;
	for (auto iter : m_selectedAnimComponent->GetAnimator()->m_animClips)
	{
		std::string clipName;
		std::wstring& clipNameW = iter.second->GetName();
		CStringHelper::WStringToString(clipNameW, clipName);
		m_choice_clipChoices.Add(wxString(clipName.c_str()));
	}
	
	m_choice_clip = new wxChoice(m_sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_clipChoices, 0);
	m_choice_clip->SetSelection(0);
	m_fgSizer_clipText->Add(m_choice_clip, 1, wxALL , 5);

	m_choice_clip->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CAnimatorPanel::m_choice_clipOnChoice), NULL, this);

}

void CAnimatorPanel::Update()
{
	ChangeSliderControlAndTime();
}

//이벤트
void CAnimatorPanel::m_choice_TrackOnChoice(wxCommandEvent& event)
{
	int index = m_choice_Track->GetSelection();
	wxString selectTrackName = m_choice_Track->GetString(index);

	std::wstring selectTrackNameW;
	CStringHelper::StringToWString(selectTrackName.c_str().AsChar(), selectTrackNameW);

	m_selectedAnimComponent->ChangeAnimation(selectTrackNameW);
}

void CAnimatorPanel::m_button_playOnButtonClick(wxCommandEvent& event)
{
	m_selectedAnimComponent->PlayAnim();
}

void CAnimatorPanel::m_button_pauseOnButtonClick(wxCommandEvent& event)
{
	m_selectedAnimComponent->PauseAnim();
}

void CAnimatorPanel::m_button_stopOnButtonClick(wxCommandEvent& event)
{
	m_selectedAnimComponent->StopAnim();
}

void CAnimatorPanel::m_checkBox_useClipOnCheckBox(wxCommandEvent& event)
{
	bool value = m_checkBox_useClip->GetValue();
	m_selectedAnimComponent->SetUseClip(value);

	if (value)
	{
		m_sbSizer->Show(m_fgSizer_clip);
		
	}
	else
	{
		m_sbSizer->Hide(m_fgSizer_clip);
	}
	
	this->GetParent()->Layout();
}

void CAnimatorPanel::m_choice_clipOnChoice(wxCommandEvent& event)
{
	int index = m_choice_clip->GetSelection();
	wxString selecClipName = m_choice_clip->GetString(index);

	std::wstring selectClipNameW;
	CStringHelper::StringToWString(selecClipName.c_str().AsChar(), selectClipNameW);

	m_selectedAnimComponent->SelectClip(selectClipNameW);
}

void CAnimatorPanel::m_button_clipPlayOnButtonClick(wxCommandEvent& event)
{
	m_choice_clipOnChoice(event);

	m_selectedAnimComponent->PlayAnim();
}

void CAnimatorPanel::m_button_AddClip_AddOnButtonClick(wxCommandEvent& event)
{
	//이름
	wxString clipName = m_textCtrl_AddClip_clipName->GetValue();
	std::wstring clipNameW(clipName.c_str().AsWChar());
	if (clipNameW == L"")
	{
		wxMessageBox("Clip Name Invalid", "Error");
		return;
	}
	if (m_selectedAnimComponent->GetAnimClip(clipNameW) != NULL)
	{
		wxMessageBox("Clip Name Overlap", "Error");
		return;
	}
		

	//track
	wxString trackName = m_choice_AddClip_track->GetStringSelection();
	std::wstring trackNameW(trackName.c_str().AsWChar());
	CAnimEvaluator* track = m_selectedAnimComponent->GetAnimator()->GetAnimation(trackNameW);
	if (track == NULL)
	{
		wxMessageBox("Track Invalid", "Error");
		return;
	}	

	//StartTime
	wxString startTime = m_textCtrl_AddClip_startTime->GetValue();
	double startTimeD;
	startTime.ToDouble(&startTimeD);
	float trackEndTime = track->m_duration / track->m_tickPerSecond;
	if (startTimeD > trackEndTime || startTimeD < 0)
	{
		wxMessageBox("StartTime Invalid", "Error");
		return;
	}

	//EndTime
	wxString endTime = m_textCtrl_AddClip_endTime->GetValue();
	double endTimeD;
	endTime.ToDouble(&endTimeD);
	if (endTimeD > trackEndTime || endTimeD < 0)
	{
		wxMessageBox("EndTime Invalid", "Error");
		return;
	}

	//isLoop
	bool isLoop = m_checkBox_AddClip_isLoop->GetValue();

	//AddClip
	m_selectedAnimComponent->AddClip(clipNameW, track, startTimeD, endTimeD, isLoop);

	//ClipChoice새로고침
	ChangeClipChoiceControl();

	this->GetParent()->Layout();

}

void CAnimatorPanel::m_button_AddClip_deleteOnButtonClick(wxCommandEvent& event)
{
	wxString selectClipName = m_choice_clip->GetStringSelection();
	std::wstring selectClipNameW(selectClipName.c_str().AsWChar());

	m_selectedAnimComponent->DeleteClip(selectClipNameW);

	//ClipChoice새로고침
	ChangeClipChoiceControl();
}