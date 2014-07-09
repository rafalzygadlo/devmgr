#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/treectrl.h>
#include <vector>
#include "NaviMapIOApi.h"
#include "NaviDisplayApi.h"
#include "dll.h"
#include "reader.h"
#include "item.h"
#include "config.h"
#include "devices_list.h"
#include "ais_list.h"
#include "ais_monitor.h"

#ifdef __cplusplus
extern "C" {
#endif
class CAisList;
class NAVIDISPLAYAPI CDisplayPlugin: public CNaviDiaplayApi 
{
	
	CConfig *m_DeviceConfig;
	CReader *m_SelectedDevice;
	CItem *m_SelectedItem;
	CNaviBroker *m_Broker;
	CMapPlugin *m_MapPlugin;
	CAisMonitor *m_AisMonitor;
	wxString m_Name;
	int m_SignalType;
	bool m_GUI;
	int m_DeviceID;
	
	CDevicesList *m_DevicesList;
	CAisList *m_AisList;
	int m_ControlType;
		
	bool m_FirstTime;
	wxBoxSizer *m_Sizer;
	wxPanel *m_SignalsPanel;
	//int m_ControlType;
	wxString m_Caption;
	//wxArrayString ArrayOfTypes;
	wxBoxSizer *m_MainSizer;
	SData *m_Data;
	wxMutex mutex;
	wxMenu *m_Menu;
	wxString Name;
	bool m_ShowNames;
	int m_RefreshTick, m_RefreshInterval;
	CTicker *m_Ticker;

	int GetControlType();
	wxString GetCaption();
	void SetDevicesData();
	//void SetDevices();
	void InitDisplay();
	void ClearDisplay();
	void AddDevice();				// odebrano sygna³ nowego urzadzenia
	void SetLogger(wxString txt);	// ustawia komunikaty w logerze
	void SetLoggerEvent();			// ustawia komunikaty w logerze to jest event logera
	void GetDevicesList();
	void GetAisList();
	void GetAisMonitor();
	void RemoveControl(int type);
	void FreeDevicesList();
	void FreeAisList();
	void FreeAisMonitor();
	void FreeAisMessages();
	void SetDevicesListSignal(int type, CDisplaySignal *sig);
	void SetAisListSignal(int type);
	void RemoveDevice();
	void Stop();
	void Start();
	void ConfigureDevice();
	void SetSignals();
	void ShowInfoPanel(bool show);
	void AddTreeItem(int item_id);
	void SetIconEvent(int icon_id);
	void SetTextEvent(int icon_id);
	void GetGUIControl(CDisplaySignal *sig);
	void GetSignal(CDisplaySignal *sig);
	void StartDevice();
	void StopDevice();
	void DataSignal(CDisplaySignal *sig);
	void DrawData(wxGCDC &dc, wxString caption, wxString text);
	int GetControlId();
	void SynchroOptions();

	void OnData();
	void OnNMEALine();
	void OnConnected();
	void OnReconnect();
	void OnNoSignal();
	void OnDeviceWizard(wxCommandEvent &event);
	void OnTreeMenu(wxTreeEvent &event);
	void OnTreeSelChanged(wxTreeEvent &event);
	void OnMouse(wxMouseEvent & event);
	void OnStop(wxCommandEvent &event);
	void OnStop(wxHyperlinkEvent &event);
	void OnStart(wxCommandEvent &event);
	void OnStart(wxHyperlinkEvent &event);
	void OnMenuRange(wxCommandEvent &event);
	void OnMenu(wxContextMenuEvent &event);

	void OnUninstall(wxCommandEvent &event);
	void OnConfigureDevice(wxCommandEvent &event);
	void OnMonitor(wxHyperlinkEvent &event);
	void OnConfigureData(wxCommandEvent &event);
	void OnNewDevice(wxCommandEvent &event);
	void OnNewMarker(wxCommandEvent &event);
	void OnSetLogger(wxCommandEvent &event);
	void OnStatus(wxCommandEvent &event);
	void OnSetIcon(wxCommandEvent &event);
	void OnSetText(wxCommandEvent &event);
	

public:
	
	CDisplayPlugin(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("DisplayApiPanel") );
	~CDisplayPlugin();
	
	void OnTickerStart();
	void OnTickerStop();
	void OnTickerTick();

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
		ID_MONITOR,
		ID_UNINSTALL,
		ID_NEW_DEVICE,
		ID_STATUS,
		ID_LOGGER,
		ID_DEVICE_TYPES,
		ID_ICON,
		ID_TEXT,
		ID_DEVICE_WIZARD,
		CONTROL_DEVICES_LIST = 1000,
		CONTROL_AIS_LIST,
		CONTROL_AIS_MONITOR,
	};


	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif




#endif