#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>
#include "NaviMapIOApi.h"
#include "dll.h"
#include <wx/listctrl.h>


class CMyPanel;
class CMapPlugin;

class CMyFrame: public wxDialog
{
	int PortSelection;
	CMapPlugin *MapPlugin;
	wxString ConfigPath;
	wxFileConfig *FileConfig;
	wxButton *ButtonStart;
	wxListCtrl *DevicesList;
		
	bool _Start,_Stop , _Close;
	void SetButtonStart(wxString label,int id);
	void SetDevicesList();
	long GetSelection();


	void OnButtonClose(wxCommandEvent &event);	
	void OnButtonStart(wxCommandEvent &event);			
	void OnButtonStop(wxCommandEvent &event);			
	void OnButtonDelete(wxCommandEvent &event);
	void OnButtonNew(wxCommandEvent &event);	

	void OnClose(wxCloseEvent &event);
	void OnList(wxCommandEvent &event);
	

public:

	CMyFrame(CMapPlugin *_MapPlugin);
	~CMyFrame();
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_START = 12345,
		ID_STOP,
		ID_DELETE,
		ID_CLOSE,
		ID_LIST,
		ID_NEW,
	};
};

#endif
