#ifndef __DISPLAY
#define __DISPLAY

#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/treectrl.h>
#include <vector>
#include "NaviMapIOApi.h"
#include "NaviDisplayApi.h"
#include "dll.h"
#include "serial.h"
#include "item.h"
#include "device_config.h"
#include "data_markers.h"

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

class NAVIDISPLAYAPI CDisplayPlugin: public CNaviDiaplayApi 
{
	
	CDeviceConfig *m_DeviceConfig;
	CDataMarkers *m_DataMarkers;
	CMySerial *m_SelectedDevice;
	CItem *m_SelectedItem;
	wxTreeItemId m_SelectedItemId;
	CNaviBroker *m_Broker;
	CMapPlugin *m_MapPlugin;
	wxString m_Name;
	int m_SignalType;
	int m_DeviceId;
	wxTreeCtrl *m_Devices;
	wxTreeItemId m_Root;
	wxTextCtrl *m_Logger;
	wxToolBar *m_ToolBar;
	bool m_FirstTime;
	wxImageList *m_ImageListSmall;
	wxBoxSizer *m_Sizer;
	wxScrolledWindow *m_Scroll;
	wxBoxSizer *m_ScrollSizer;
	wxPanel *m_InfoPanel;

	wxString GetCaption();
	void SetDevicesData();
	void SetDevices();
	void InitDisplay();
	void ClearDisplay();
	void AddDevice();				// odebrano sygna³ nowego urzadzenia
	void SetLogger(wxString txt);	// ustawia komunikaty w logerze
	void SetLoggerEvent();			// ustawia komunikaty w logerze to jest event logera
	void RemoveDevice();
	void NewSignal();
	void SetSignals();
	
	void GetSignal();
	void OnTreeMenu(wxTreeEvent &event);
	void OnTreeSelChanged(wxTreeEvent &event);
	//void DrawData(wxGCDC &dc, wxString caption,wxString text);
	//void DrawBackground(wxGCDC &dc);
	//void OnMouseWheel(wxMouseEvent & event);
	void OnMouse(wxMouseEvent & event);
	void OnStop(wxCommandEvent &event);
	void OnStart(wxCommandEvent &event);
	void OnUninstall(wxCommandEvent &event);
	void OnConfigureDevice(wxCommandEvent &event);
	void OnConfigureData(wxCommandEvent &event);
	void OnNewDevice(wxCommandEvent &event);
	void OnNewMarker(wxCommandEvent &event);
	void OnSetLogger(wxCommandEvent &event);
	void OnStatus(wxCommandEvent &event);
	

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
		ID_CONFIGURE_DATA,
		ID_CONFIGURE_DEVICE,
		ID_UNINSTALL,
		ID_NEW_DEVICE,
		ID_NEW_MARKER,
		ID_STATUS,
		ID_LOGGER,
	};


	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif




#endif