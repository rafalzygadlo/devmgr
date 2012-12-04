#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>

#include "NaviMapIOApi.h"
#include "dll.h"
#include "serial.h"


class CMapPlugin;
class CMyFrame: public wxDialog
{
	int PortSelection;
	CMapPlugin *m_MapPlugin;
	wxString m_ConfigPath;
	wxFileConfig *m_FileConfig;

		
	//void SetButtonStart(wxString label,int id);
	//void SetDevicesList();
	//long GetSelection();
	//void SetButtons(CMySerial *Serial);
	//void SetDeviceLog(CMySerial *Serial);

	void OnButtonClose(wxCommandEvent &event);	
	//void OnButtonStart(wxCommandEvent &event);			
	//void OnButtonStop(wxCommandEvent &event);			
	//void OnButtonDelete(wxCommandEvent &event);
	//void OnButtonNew(wxCommandEvent &event);	

	void OnClose(wxCloseEvent &event);
	//void OnSetItem(wxCommandEvent &event);
	//void OnActivate(wxListEvent &event);
	//void OnSelected(wxListEvent &event);
	

public:

	CMyFrame(CMapPlugin *_MapPlugin);
	~CMyFrame();
	void SetDeviceStatus(CMySerial *Serial);
	
	DECLARE_EVENT_TABLE();

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
};

#endif
