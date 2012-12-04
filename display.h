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
#include "item.h"
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
	
	CMySerial *m_SelectedDevice;
	CItem *m_SelectedItem;
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
	wxImageList *ImageListSmall;
	
	wxString GetCaption();
	void SetData();
	void InitDisplay();
	void GetSignal();
	void OnTreeMenu(wxTreeEvent &event);
	void DrawData(wxGCDC &dc, wxString caption,wxString text);
	void DrawBackground(wxGCDC &dc);
	void OnMouseWheel(wxMouseEvent & event);
	void OnMouse(wxMouseEvent & event);
	void OnStop(wxCommandEvent &event);
	void OnStart(wxCommandEvent &event);
	void OnRemove(wxCommandEvent &event);
	void OnConfigure(wxCommandEvent &event);
	void OnAdd(wxCommandEvent &event);
	

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
		ID_TREE = 4500,
		ID_STOP,
		ID_START,
		ID_CONFIGURE,
		ID_REMOVE,
		ID_ADD
	};


	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif




#endif