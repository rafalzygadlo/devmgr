#ifndef __STATUS
#define __STATUS

#include <wx/wx.h>
#include "conf.h"
#include "dll.h"
#include "tools.h"
#include <vector>

class CStatus: public wxDialog
{
	
	wxBoxSizer *MainSizer;
	wxTextCtrl *DataDefinition;
		
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	
	
public:

	CStatus(CMySerial *serial);
	~CStatus();
	void ShowWindow(bool show);	
	int GetBaud();
	
	
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE,
	};

};


#endif