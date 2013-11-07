#ifndef __DEVICE_CONFIG
#define __DEVICE_CONFIG

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"
#include "dll.h"
#include "tools.h"
#include <vector>

class CDeviceConfig: public wxDialog
{
	
	CMySerial *mySerial;
	wxBoxSizer *MainSizer;
	wxComboBox *BaudCombo;
	wxComboBox *PortCombo;
	wxComboBox *DeviceTypeCombo;
	wxTextCtrl *NameText;
	wxTextCtrl *DataDefinition;
		
	bool Validate();
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnScanPorts(wxHyperlinkEvent &event);
	
	
public:

	CDeviceConfig();
	~CDeviceConfig();
	void ShowWindow(bool show);	
	int GetBaud();
	wxString GetDeviceName();
	wxString GetDataDefinition();
	wxString GetPort();
	int GetDeviceType();


	void SetDeviceName(wxString name);
	void SetPort(char *port);
	void SetBaud(int baud);
	void SetDeviceType(int type);
	
	
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE,
		ID_REFRESH,
	};

};


#endif