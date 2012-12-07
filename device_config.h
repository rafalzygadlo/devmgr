#ifndef __DEVICE_CONFIG
#define __DEVICE_CONFIG

#include <wx/wx.h>
#include "conf.h"
#include "dll.h"
#include "tools.h"
#include <vector>

class CDeviceConfig: public wxDialog
{
	
	wxBoxSizer *MainSizer;
	wxComboBox *BaudCombo;
	wxComboBox *PortCombo;
	wxTextCtrl *NameText;
	wxTextCtrl *DataDefinition;
		
	bool Validate();
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	
	
public:

	CDeviceConfig();
	~CDeviceConfig();
	void ShowWindow(bool show);	
	int GetBaud();
	wxString GetDeviceName();
	wxString GetDataDefinition();
	wxString GetPort();

	void SetDeviceName(wxString name);
	void SetPort(char *port);
	void SetBaud(int baud);
	
	
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE,
	};

};


#endif