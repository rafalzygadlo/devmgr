#ifndef __CONFIG_H
#define __CONFIG_H

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
	wxComboBox *ConnectionTypeCombo, *DeviceTypeCombo;
	wxPanel *SocketPanel,*SerialPanel,*DevicePanel;
	int DeviceType;
	int ConnectionType;
		
	bool Validate();
	bool ValidateSerial();
	bool ValidateSocket();
	wxPanel *GetSerialPanel();
	wxPanel *GetSocketPanel();
	wxPanel *GetDeviceTypePanel();
	void ShowConnectionPanel(int type);
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnScanPorts(wxHyperlinkEvent &event);
	void OnConnectionType(wxCommandEvent &event);
	void OnDeviceType(wxCommandEvent &event);
	
	
public:

	CConfig();
	~CConfig();
	
	int GetBaud();
	int GetDeviceType();
	int GetConnectionType();
	wxString GetHost();
	wxString GetDeviceName();
	wxString GetSerialPort();
	wxString GetSocketPort();
	void ShowWindow(bool show);
	void SetConnectionType(int type);
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
		ID_CONNECTION_TYPE,
		ID_DEVICE_TYPE
	};

};


#endif