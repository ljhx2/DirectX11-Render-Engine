#pragma once

#ifndef _LIGHT_PANEL_H_
#define _LIGHT_PANEL_H_

#include <wx/filepicker.h>
#include <wx/clrpicker.h>
#include <wx/colour.h>

#include <GameObject\Component\LightComponent\DirectionalLightComponent.h>

class CLightPanel : public wxPanel
{
public:
	void			SetLightComponent(CDirectionalLightComponent* lightComp);

public:
	//¿Ã∫•∆Æ
	virtual void m_colourPickerAmbientOnColourChanged(wxColourPickerEvent& event);
	virtual void m_colourPickerDiffuseOnColourChanged(wxColourPickerEvent& event);
	virtual void m_colourPickerSpecularOnColourChanged(wxColourPickerEvent& event);

public:
	CLightPanel(wxWindow* parent);
	~CLightPanel();

private:
	wxStaticBoxSizer*	sbSizer;
	wxFlexGridSizer*	fgSizer;

	wxStaticText*		m_stextType;
	wxTextCtrl*			m_textType;

	wxStaticText*		m_stextAmbient;
	wxStaticText*		m_stextDiffuse;
	wxStaticText*		m_stextSpecular;

	wxColourPickerCtrl* m_colourPickerAmbient;
	wxColourPickerCtrl* m_colourPickerDiffuse;
	wxColourPickerCtrl* m_colourPickerSpecular;

private:
	CDirectionalLightComponent*		m_dirLightComp;
};

#endif // !_LIGHT_PANEL_H_