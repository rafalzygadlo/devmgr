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
#include "config.h"

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

class NAVIDISPLAYAPI CDisplayPlugin: public CNaviDiaplayApi 
{
	
	CConfig *m_DeviceConfig;
	CMySerial *m_SelectedDevice;
	CItem *m_SelectedItem;
	wxTreeItemId m_SelectedItemId;
	CNaviBroker *m_Broker;
	CMapPlugin *m_MapPlugin;
	wxBoxSizer *Page1Sizer;
	wxString m_Name;
	int m_SignalType;
	int m_DeviceId;
	wxToolBar *m_ToolBar;
	wxTreeCtrl *m_Devices;
	wxTreeItemId m_Root;
	wxTextCtrl *m_Logger;
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
	void AddDevice();				// odebrano sygna� nowego urzadzenia
	void SetLogger(wxString txt);	// ustawia komunikaty w logerze
	void SetLoggerEvent();			// ustawia komunikaty w logerze to jest event logera
	void RemoveDevice();
	
	void SetSignals();
	void ShowInfoPanel(bool show);
	void AddTreeItem(int item_id);
	void SetIconEvent(int icon_id);
	void GetSignal();

	void OnConnected();
	void OnNMEALine();
	void OnData();
	void OnReconnect();
	void OnNewSignal();
	void OnNoSignal();
	void OnTreeMenu(wxTreeEvent &event);
	void OnTreeSelChanged(wxTreeEvent &event);
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
	void OnSetIcon(wxCommandEvent &event);

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
		ID_CONFIGURE_DEVICE,
		ID_UNINSTALL,
		ID_NEW_DEVICE,
		ID_STATUS,
		ID_LOGGER,
		ID_DEVICE_TYPES,
		ID_ICON,
	};


	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif




#endif