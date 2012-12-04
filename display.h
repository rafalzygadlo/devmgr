#ifndef __DISPLAY
#define __DISPLAY

#include "dll.h"
#include "NaviMapIOApi.h"
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "NaviDisplayApi.h"

#include <wx/fileconf.h>
#include "serial.h"
#include <wx/treectrl.h>

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

class NAVIDISPLAYAPI CDisplayPlugin: public CNaviDiaplayApi 
{
	
	CNaviBroker *m_Broker;
	CMapPlugin *m_MapPlugin;
	int ControlType, FormatType;
	wxArrayString ArrayOfTypes;
	wxString Name;
	wxString ConfigPath;
	int m_SignalType;
	int m_DeviceId;
	wxTreeCtrl *m_Devices;
	wxTreeItemId m_Root;
	bool m_FirstTime;
	
	wxString GetCaption();


	void OnMenu(wxContextMenuEvent &event);
		
	void DrawData(wxGCDC &dc, wxString caption,wxString text);
	void DrawBackground(wxGCDC &dc);
	
	void OnMenuRange(wxCommandEvent &event);
	void OnMouseWheel(wxMouseEvent & event);
	void OnMouse(wxMouseEvent & event);
	void OnListCheck(wxCommandEvent &event);
	void OnListBox(wxCommandEvent &event);
	

public:
	
	CDisplayPlugin(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("DisplayApiPanel") );
	~CDisplayPlugin();
	
	virtual bool IsValidSignal(CDisplaySignal *SignalID);
	virtual void OnWork(CDisplaySignal *Signal);
	virtual void BeforeWork(CDisplaySignal *Signal);
	virtual void AfterWork(CDisplaySignal *Signal);
	virtual void OnRender(wxGCDC &dc);

	enum
	{
		ID_ABOUT,
		ID_SPEED = 1000,
		ID_DATE,
		ID_TIME,
		ID_FIX,
		ID_DIRECTION,
		ID_LON,
		ID_LAT,
		ID_PDOP,
		ID_HDOP,
		ID_VDOP,
		ID_QUALITY,
		ID_SATELLITES,
		ID_STATUS,
		ID_TRACKS,
		// buttons DrawTracks
		ID_DELETE,
		ID_TRACK_LIST,
	};
	
	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif


class CList :public wxTreeItemData
{
	
	wxString m_FullPath,m_FilePath;;
	bool m_IsDir;
	CMySerial *m_Serial;

public:

	CList();
	~CList();

	void SetFullPath(wxString &str);
	wxString GetFullPath();
	void SetFilePath(wxString &str);
	wxString GetFilePath();
	void SetSerial(CMySerial *serial);
	void SetIsDir(bool val);
	bool GetIsDir();


};


#endif