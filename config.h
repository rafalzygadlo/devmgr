#ifndef __DEVICECONFIG
#define __DEVICECONFIG

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"
#include "tools.h"
#include <vector>

class CReader;
class CConfig: public wxDialog
{
		
	CReader *Reader;
	wxBoxSizer *MainSizer;
	wxComboBox *BaudCombo;
	wxComboBox *PortCombo;
	wxTextCtrl *SerialNameText, *SocketNameText, *PortText, *HostText;
		//*UserText,*PassText;
	wxComboBox *ComboDeviceType;

	wxPanel *SocketPanel,*SerialPanel;
	int DeviceType;
		
	bool Validate();
	bool ValidateSerial();
	bool ValidateSocket();
	wxPanel *GetSerialPanel();
	wxPanel *GetSocketPanel();
	void ShowDevicePanel(int type);
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnScanPorts(wxHyperlinkEvent &event);
	void OnDeviceType(wxCommandEvent &event);
	
	
public:

	CConfig();
	~CConfig();
	void ShowWindow(bool show);	
	int GetBaud();
	wxString GetDeviceName();
	wxString GetSerialPort();
	wxString GetSocketPort();
	int GetDeviceType();
	wxString GetHost();
	wxString GetMount();
	
	void SetDeviceType(int type);
	void SetDeviceName(wxString name);
	void SetPort(char *port);
	void SetBaud(int baud);
	
	void SetPort(int port);
	void SetHost(char *host);
		
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE = 24138,
		ID_REFRESH,
		ID_TYPE
	};

};


#endif