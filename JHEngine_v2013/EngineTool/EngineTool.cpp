#include "stdafx.h"
#include "EngineTool.h"

#include "Frame\cMainFrame.h"

IMPLEMENT_APP(EngineTool);

EngineTool::EngineTool()
{
}


EngineTool::~EngineTool()
{
}

bool EngineTool::OnInit()
{
	wxFrame* mainFrame = new cMainFrame(NULL, wxID_ANY, wxT("JHEngine"));
	SetTopWindow(mainFrame);
	mainFrame->Show(true);


	return true;
}

int EngineTool::OnExit()
{
	return wxApp::OnExit();
}