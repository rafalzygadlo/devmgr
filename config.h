#ifndef __CONFIG
#define __CONFIG

#include <wx/wx.h>
#include "conf.h"
#include "dll.h"
#include "tools.h"
#include <vector>

class CMyConfig: public wxDialog
{
	
	wxBoxSizer *MainSizer;
	wxComboBox *BaudCombo;
	wxComboBox *PortCombo;
	wxTextCtrl *NameText;
	
	bool Validate();
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	
public:

	CMyConfig();
	~CMyConfig();
	void ShowWindow(bool show);	
	wxString GetPort();
	int GetBaud();
	wxString GetDeviceName();
	
	
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE,
	};

};


#endif