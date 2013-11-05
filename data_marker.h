#ifndef __DATA_MARKERS
#define __DATA_MARKERS

#include <wx/wx.h>
#include "conf.h"
#include "dll.h"
#include "tools.h"
#include <vector>

class CDataMarkers: public wxDialog
{
	
	wxBoxSizer *MainSizer;
	wxTextCtrl *NMEA;
	CMySerial *Serial;
	
	
	bool Validate();
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnComboSignal(wxCommandEvent &event);
	void OnNMEAText(wxCommandEvent &event);
	//void OnTextClick(wxMouseEvent& event);
	
	
public:

	CDataMarkers(CMySerial *serial);
	~CDataMarkers();
	void ShowWindow(bool show);	
	int GetBaud();
	wxString GetDeviceName();
	//wxString GetDataDefinition();
	wxString GetPort();
	
	
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE = 7384,
		ID_SIGNAL,
		ID_NMEA,
	};

};


#endif