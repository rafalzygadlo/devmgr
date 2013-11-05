#ifndef __DATA_CONFIG
#define __DATA_CONFIG

#include <wx/wx.h>
#include "conf.h"
#include "dll.h"
#include "tools.h"

class CDataConfig: public wxDialog
{
			
	wxCheckListBox *m_Marker;
	CMySerial *m_Serial;

	bool Validate();
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnButtonNew(wxCommandEvent &event);
	void OnMarkerCheck(wxCommandEvent &event);
		
public:

	CDataConfig(CMySerial *serial);
	~CDataConfig();
	void ShowWindow(bool show);	
			
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE = 7384,
		ID_NEW,
		ID_DELETE,
		ID_MARKER
	};

};


#endif