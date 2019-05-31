#ifndef _MAIN_H_
#define _MAIN_H_

//#include <wx/wx.h>

class MainApp : public wxApp {
protected:

public:
	virtual bool OnInit() override;
	virtual int OnExit() override;
};


#endif
