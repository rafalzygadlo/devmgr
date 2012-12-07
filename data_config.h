#ifndef __DATA_CONFIG
#define __DATA_CONFIG

#include <wx/wx.h>
#include "conf.h"
#include "dll.h"
#include "tools.h"
#include <vector>

class CDataConfig: public wxDialog
{
	
	wxBoxSizer *MainSizer;
	wxTextCtrl *DataDefinition;
	
	
	bool Validate();
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	
	
public:

	CDataConfig(CMySerial *serial);
	~CDataConfig();
	void ShowWindow(bool show);	
	int GetBaud();
	wxString GetDeviceName();
	wxString GetDataDefinition();
	wxString GetPort();
	
	
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE,
	};

};


#endif