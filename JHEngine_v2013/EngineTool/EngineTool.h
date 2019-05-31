#pragma once
class EngineTool : public wxApp
{
public:
	EngineTool();
	~EngineTool();

	virtual bool OnInit();
	virtual int OnExit();
};

DECLARE_APP(EngineTool);