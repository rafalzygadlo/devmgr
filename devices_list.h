#ifndef __DEVICES_LIST_H
#define __DEVICES_LIST_H

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

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif

class CDevicesList : public wxPanel
{
	
	CConfig *m_DeviceConfig;
	CReader *m_SelectedDevice;
	CItem *m_SelectedItem;
	wxTreeItemId m_SelectedItemId;
	CNaviBroker *m_Broker;
	CMapPlugin *m_MapPlugin;
	wxBoxSizer *Page1Sizer;
	wxString m_Name;
	int m_SignalType;
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
	wxStaticText *m_LabelName,*m_LabelPort,*m_LabelConnected;
	wxPanel *m_SignalsPanel;
	wxBoxSizer *m_InfoPanelSizer;
	wxHyperlinkCtrl *m_StartButton;
	wxHyperlinkCtrl *m_ConfigureButton;
	wxHyperlinkCtrl *m_Monitor;
	int m_ControlType;
	wxString m_Caption;
	CReader *m_Reader;
	wxSlider *m_Frequency;
		
	int GetControlType();
	void GetPanel();
	wxString GetCaption();
	void SetDevicesData();
	void SetDevices();
	void AddDevice();				// odebrano sygna³ nowego urzadzenia
	//void SetLogger(wxString txt);	// ustawia komunikaty w logerze
	void SetLoggerEvent();			// ustawia komunikaty w logerze to jest event logera
	void RemoveDevice();
	void ClearDisplay();
	wxPanel *GetSignalsPanel(CReader *reader);
	
	void Stop();
	void Start();
	void ConfigureDevice();
	void SetSignals();
	void ShowInfoPanel(bool show);
	void AddTreeItem(int item_id);
	void SetIconEvent(int icon_id);
	void SetTextEvent(int icon_id);
	void StartDevice();
	void StopDevice();
		
	void OnDeviceWizard(wxCommandEvent &event);
	void OnTreeMenu(wxTreeEvent &event);
	void OnTreeSelChanged(wxTreeEvent &event);
	void OnMouse(wxMouseEvent & event);
	void OnStop(wxCommandEvent &event);
	void OnStop(wxHyperlinkEvent &event);
	void OnStart(wxCommandEvent &event);
	void OnStart(wxHyperlinkEvent &event);
	
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
	void OnFrequency(wxCommandEvent &event);
	void OnConnected();
	void OnNoSignal();
	void OnReconnect();


public:
	
	CDevicesList(wxWindow *parent, CMapPlugin *plugin);
	~CDevicesList();
	void SetSignal(int stype, CReader* reader);
	
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
		ID_FREQUENCY,
	};


	DECLARE_EVENT_TABLE();
};


#endif