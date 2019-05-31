#include "stdafx.h"
#include "..\stdafx.h"
#include "LogPanel.h"

#include "..\Frame\cMainFrame.h"

CLogPanel::CLogPanel(cMainFrame* parent)
	: wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500, 250), wxALL | wxEXPAND)
	, m_mainFrame(parent)
{
	m_logOld = wxLog::SetActiveTarget(new wxLogTextCtrl(this));
}


CLogPanel::~CLogPanel()
{
	delete wxLog::SetActiveTarget(m_logOld);


	//wxLogMessage(wxT("Message"));
	//wxLogSysError(wxT("sysError"));
	//wxLogError(wxT("error"));
	////wxLogFatalError(wxT("fatalError"));
	//wxLogWarning(wxT("warning"));
}
