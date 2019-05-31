#pragma once

#ifndef _LOG_PANEL_H_
#define _LOG_PANEL_H_

class cMainFrame;


class CLogPanel : public wxTextCtrl
{
public:
	CLogPanel(cMainFrame* parent);
	~CLogPanel();

private:

	cMainFrame*					m_mainFrame;

	wxLog *m_logOld;

};

#endif // !_LOG_PANEL_H_