#include "stdafx.h"
#include "main.h"
#include "simple.h"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit() 
{
	Simple *simple = new Simple(wxT("Simple"));
	simple->Show(true);
	return true;
}

int MainApp::OnExit() 
{

	return wxApp::OnExit();
}

