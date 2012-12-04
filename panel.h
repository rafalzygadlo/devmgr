#ifndef __PANEL
#define __PANEL

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "serial.h"

class CMySerial;
class CPanel: public wxPanel
{
	wxListCtrl *m_DevicesList;
	wxString m_ConfigPath;
	wxButton *m_ButtonStart;
	wxButton *m_ButtonStop;
	wxTextCtrl *m_DeviceLog;
	CMySerial *m_Serial;
	
public:
	CPanel(wxWindow *Parent, CMySerial *Serial);
	~CPanel();
	void SetDevice(CSerial *dev);
	
	enum
	{
		ID_START = 12345,
		ID_STOP,
		ID_DELETE,
		ID_CLOSE,
		ID_LIST,
		ID_NEW,
		ID_SET_ITEM,
	};
	
	DECLARE_EVENT_TABLE();

};

#endif