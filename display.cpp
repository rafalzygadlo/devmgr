#include <wx/wx.h>
#include <wx/mstream.h>
#include <wx/notebook.h>
#include "conf.h"
#include "tools.h"
#include "display.h"
#include "item.h"
#include "config.h"
#include "status.h"
#include "info.h"
#include "wizard.h"
#include "devices.h"

//DEFINE_EVENT_TYPE(EVT_SET_LOGGER)
//DEFINE_EVENT_TYPE(EVT_SET_ICON)
//DEFINE_EVENT_TYPE(EVT_SET_TEXT)

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
	//EVT_TREE_ITEM_MENU(ID_TREE, CDisplayPlugin::OnTreeMenu)
	//EVT_TREE_SEL_CHANGED(ID_TREE, CDisplayPlugin::OnTreeSelChanged)
	//EVT_MENU(ID_STOP,CDisplayPlugin::OnStop)
	//EVT_MENU(ID_START,CDisplayPlugin::OnStart)
	//EVT_MENU(ID_CONFIGURE_DEVICE,CDisplayPlugin::OnConfigureDevice)
	//EVT_MENU(ID_UNINSTALL,CDisplayPlugin::OnUninstall)
	//EVT_MENU(ID_NEW_DEVICE,CDisplayPlugin::OnNewDevice)
	//EVT_MENU(ID_DEVICE_WIZARD,CDisplayPlugin::OnDeviceWizard)
	//EVT_MENU(ID_STATUS,CDisplayPlugin::OnStatus)
	//EVT_MENU(ID_START,CDisplayPlugin::OnStart)
	
	//EVT_HYPERLINK(ID_STOP,CDisplayPlugin::OnStop)
	//EVT_HYPERLINK(ID_START,CDisplayPlugin::OnStart)
//	EVT_HYPERLINK(ID_CONFIGURE_DEVICE,CDisplayPlugin::OnConfigureDevice)
	//EVT_HYPERLINK(ID_MONITOR,CDisplayPlugin::OnMonitor)
	
	EVT_MENU_RANGE(ID_MENU_BEGIN,ID_MENU_END,CDisplayPlugin::OnMenuRange)
	EVT_CONTEXT_MENU(CDisplayPlugin::OnMenu)

	//EVT_COMMAND(ID_LOGGER,EVT_SET_LOGGER,CDisplayPlugin::OnSetLogger)
	//EVT_COMMAND(ID_ICON,EVT_SET_ICON,CDisplayPlugin::OnSetIcon)
	//EVT_COMMAND(ID_TEXT,EVT_SET_TEXT,CDisplayPlugin::OnSetText)
	//EVT_TOOL(ID_TOOL_STOP,
END_EVENT_TABLE()


CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	m_SelectedDevice = NULL;
	SetDisplayID(NDS_DEVICE_MANAGER);
	m_Broker = NULL;
	m_SignalsPanel = NULL;
	m_Sizer = NULL;
	SetDoubleBuffered(true);
		
	this->Disable();
	m_FirstTime = true;
	m_SelectedItem = NULL;
	
	m_ControlType = -1;
		
	m_DevicesList = NULL;
	m_AisList = NULL;

	ArrayOfTypes.Add(_("Device Manager - Configurator"));
	ArrayOfTypes.Add(_("Ais Targets list"));
	ArrayOfTypes.Add(_("Speed"));
	ArrayOfTypes.Add(_("Date"));
	ArrayOfTypes.Add(_("Time"));
	ArrayOfTypes.Add(_("Fix"));
	ArrayOfTypes.Add(_("Direction"));
	ArrayOfTypes.Add(_("Longitude"));
	ArrayOfTypes.Add(_("Latitude"));
	ArrayOfTypes.Add(_("PDOP"));
	ArrayOfTypes.Add(_("HDOP"));
	ArrayOfTypes.Add(_("VDOP"));
	ArrayOfTypes.Add(_("Quality"));
	ArrayOfTypes.Add(_("Sattelites"));
	ArrayOfTypes.Add(_("Status"));


}

CDisplayPlugin::~CDisplayPlugin()
{
	//RemoveControl(m_ControlType);
}

int CDisplayPlugin::GetControlType()
{
	return m_ControlType - ID_MENU_BEGIN;
}

void  CDisplayPlugin::GetDevicesList()
{
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	m_DevicesList = new CDevicesList(this,m_MapPlugin);
	MainSizer->Add(m_DevicesList,1,wxALL|wxEXPAND);
	this->SetSizer(MainSizer);
	this->Layout();
}

void  CDisplayPlugin::GetAisList()
{
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	m_AisList = new CAisList(this,m_MapPlugin,this);
	MainSizer->Add(m_AisList,1,wxALL|wxEXPAND);
	this->SetSizer(MainSizer);
	this->Layout();
}

void CDisplayPlugin::RemoveControl(int type)
{
	switch(type)
	{
		case CONTROL_DEVICES_LIST:	FreeDevicesList();	break;
		case CONTROL_AIS_LIST:		FreeAisList();		break;
	}
}

void CDisplayPlugin::FreeDevicesList()
{
	delete m_DevicesList;
	m_DevicesList = NULL;
}

void CDisplayPlugin::FreeAisList()
{
	delete m_AisList;
	m_AisList = NULL;
}

void CDisplayPlugin::OnMenuRange(wxCommandEvent &event)
{
	if(m_ControlType == event.GetId())
	{
		wxMessageBox(_("The same type of control ?"));
		return;
	}
	
	RemoveControl(m_ControlType);
		
	switch(event.GetId())
	{
		case CONTROL_DEVICES_LIST:	GetDevicesList();	break;
		case CONTROL_AIS_LIST:		GetAisList();		break;
	}
	
	m_ControlType = event.GetId(); // ustawiamy po zbudowaniu gui
	m_Caption = ArrayOfTypes[GetControlType()];

}

void CDisplayPlugin::OnMenu(wxContextMenuEvent &event)
{
	
	wxMenu *Menu = new wxMenu();
	
	for(int i = 0; i < ArrayOfTypes.size(); i++)
		Menu->AppendRadioItem(i + ID_MENU_BEGIN ,ArrayOfTypes[i]);
	
	if(m_ControlType != -1)
		Menu->Check(m_ControlType, true);
	
	PopupMenu(Menu);
	delete Menu;
	
}

bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) {

	if(SignalID->GetSignalID() == NDS_BROKER_BROADCAST && m_Broker == NULL)
	{
		m_Broker = (CNaviBroker*)SignalID->GetData();
		m_MapPlugin = (CMapPlugin*)m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_GetParentPtr",NULL);
		if(m_MapPlugin != NULL)
			InitDisplay();
		return false;
	}

	if(SignalID->GetSignalID() == NDS_DEVICE_MANAGER)
	{
		
		m_Reader = (CReader*)SignalID->GetData();
		m_SignalType = SignalID->GetTag();
		InitDisplay();
		
		GetSignal();    // kolejnoœæ initDispaly najpierw dla sygnalu czyszcz¹cego m_firstTime przestawiany na fa³sz i InitDisplay siê inicjuje
		
		return false;
	}
	
	return false;
}

void CDisplayPlugin::GetSignal()
{
	// kontrolki GUI
	switch(m_ControlType)
	{
		case CONTROL_DEVICES_LIST:	SetDevicesListSignal(m_SignalType,m_Reader);	break;
		case CONTROL_AIS_LIST:		SetAisListSignal(m_SignalType);					break;

	}
	
	switch(m_SignalType)
	{
		case CLEAR_DISPLAY: 			ClearDisplay(); 	break;		// czysci listê urz¹dzeñ (np przy wy³¹czeniu plugina)
		case INIT_SIGNAL:				InitDisplay();		break;		// inicjuje listê urzadzeñ
	}
	
}

void CDisplayPlugin::SetDevicesListSignal(int type, CReader *reader)
{
	if(m_DevicesList)
		m_DevicesList->SetSignal(type,reader);
}

void CDisplayPlugin::SetAisListSignal(int type)
{
	if(m_AisList)
		m_AisList->SetSignal(type);
}



void CDisplayPlugin::OnNMEALine()
{
	//CReader *reader = m_MapPlugin->GetReader(m_DeviceId);
	//SetLoggerEvent();
}

void CDisplayPlugin::OnData()
{
	//SData *data = m_MapPlugin->GetData();
	//fprintf(stdout,"%d %s\n",data->id,data->marker);
}

void CDisplayPlugin::StartDevice()
{
	//SetIconEvent(ICON_STOP);
	//ShowInfoPanel(true);  // refresh panela
}

void CDisplayPlugin::StopDevice()
{
	//SetIconEvent(ICON_START);
	//ShowInfoPanel(true); // refresh panela
}

void CDisplayPlugin::OnConnected()
{
	//SetTextEvent(TEXT_OK);
}

void CDisplayPlugin::OnNoSignal()
{
	//SetTextEvent(TEXT_ERROR);
}

void CDisplayPlugin::OnReconnect()
{
	//SetTextEvent(TEXT_ERROR);
}

void CDisplayPlugin::ClearDisplay()
{
	m_FirstTime = true;
	this->Disable();
	
	if(m_DevicesList != NULL)
	{
		delete m_DevicesList;
		m_DevicesList = NULL;
	}
}

void CDisplayPlugin::InitDisplay()
{
	if(m_FirstTime)
	{
		m_FirstTime = false;
		this->Enable();
//		SetDevices();
	}

}

void CDisplayPlugin::AddDevice()
{
	int id = m_MapPlugin->GetDevicesCount() - 1;
	//AddTreeItem(id);	
}

void CDisplayPlugin::RemoveDevice()
{
//	SetDevices();
}


/*
void CDisplayPlugin::AddTreeItem(int item_id)
{

	CReader *ptr = m_MapPlugin->GetReader(item_id);
	wxString port(ptr->GetPortName(),wxConvUTF8);
	wxString host(ptr->GetHost(),wxConvUTF8);
	int icon_id = ICON_START;
	bool running = false;
	
	if(ptr->IsRunning())
	{
		icon_id = ICON_STOP;
		running = true;
	}
	
	wxTreeItemId id;

	if(ptr->GetConnectionType() == CONNECTION_TYPE_SERIAL)
		id = m_Devices->AppendItem(m_Root,wxString::Format(_("[%s:%d] %s"),port.wc_str(),ptr->GetBaudRate(),ptr->GetDeviceName().wc_str()),icon_id);
	if(ptr->GetConnectionType() == CONNECTION_TYPE_SOCKET)
		id = m_Devices->AppendItem(m_Root,wxString::Format(_("[%s:%d] %s"),host,ptr->GetPort(), ptr->GetDeviceName().wc_str()),icon_id);

	CItem *Item = new CItem();
	Item->SetReader(ptr);
	m_Devices->SetItemData(id,Item);

}

void CDisplayPlugin::OnSetIcon(wxCommandEvent &event)
{

	CReader *ptr = (CReader*)event.GetClientData();
	wxTreeItemIdValue cookie;
	
	wxTreeItemId id = m_Devices->GetFirstChild(m_Root,cookie);	
	
	while(id.IsOk())
	{
		
		CItem *item  = (CItem*)m_Devices->GetItemData(id);
		CReader *reader = item->GetReader();
		if(ptr == reader)
			m_Devices->SetItemImage(id,event.GetInt(), wxTreeItemIcon_Normal);
				
		id = m_Devices->GetNextChild(id,cookie);

	}
	
}

void CDisplayPlugin::SetIconEvent(int icon_id)
{
	wxCommandEvent evt(EVT_SET_ICON,ID_ICON);
	evt.SetClientData(m_Reader);
	evt.SetInt(icon_id);
	wxPostEvent(this,evt);
}

void CDisplayPlugin::OnSetText(wxCommandEvent &event)
{
	
	CReader *ptr = (CReader*)event.GetClientData();
	wxTreeItemIdValue cookie;
		
	wxTreeItemId id = m_Devices->GetFirstChild(m_Root,cookie);	
	
	while(id.IsOk())
	{
		
		CItem *item  = (CItem*)m_Devices->GetItemData(id);
		if(item == NULL)
			return;
		
		CSerial *reader = item->GetReader();
		if(ptr == reader)
		{
			if(event.GetInt())
				m_Devices->SetItemTextColour(id,*wxRED);
			else
				m_Devices->SetItemTextColour(id,wxSYS_COLOUR_WINDOWTEXT);
		}
		
		id = m_Devices->GetNextChild(id,cookie);

	}
	
}

void CDisplayPlugin::SetTextEvent(int icon_id)
{
	wxCommandEvent evt(EVT_SET_TEXT,ID_TEXT);
	evt.SetClientData(m_Reader);
	evt.SetInt(icon_id);
	wxPostEvent(this,evt);
}

void CDisplayPlugin::OnSetLogger(wxCommandEvent &event)
{
	SetLogger(event.GetString());
}

void CDisplayPlugin::SetLoggerEvent()
{
		
	wxCommandEvent evt(EVT_SET_LOGGER,ID_LOGGER);
	evt.SetString(wxString::Format(_("[%d]: %d\n"),m_DeviceId,m_SignalType));
	
	if(m_SignalType == SIGNAL_NMEA_LINE)
	{
		CReader *ptr = m_Reader;
		wxString buf(ptr->GetLineBuffer(),wxConvUTF8);
		evt.SetString(buf);
	
	}
	
	evt.SetInt(m_DeviceId);
    wxPostEvent(this,evt);
	
}
void CDisplayPlugin::SetLogger(wxString txt)
{
	//GetMutex()->Lock();
	m_Logger->SetValue(txt);
	//GetMutex()->Unlock();
}

void CDisplayPlugin::SetDevices() 
{

	m_Devices->DeleteChildren(m_Root);
	
	for(size_t i = 0; i < m_MapPlugin->GetDevicesCount(); i++)
		AddTreeItem(i);
	
	m_Devices->ExpandAll();

}
*/

void CDisplayPlugin::SetDevicesData()
{

}

void CDisplayPlugin::OnRender(wxGCDC &dc) 
{

}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal) 
{
		
	Refresh();
	wxMilliSleep(50);

}

void CDisplayPlugin::AfterWork(CDisplaySignal *Signal)
{
	
}

void CDisplayPlugin::BeforeWork(CDisplaySignal *Signal)
{
	
}

const wchar_t *NaviDisplayIntroduce(int LanguageID) 
{

	switch( LanguageID ) 
	{

		case 0: 
			return TEXT(PRODUCT_NAME);
			break;

		default:
			return TEXT(PRODUCT_NAME);
	}

}

const int NaviDisplayID()
{
	return NDS_DEVICE_MANAGER;
}

CNaviDiaplayApi *CreateDisplayInstance(wxWindow *Parent, wxWindowID WindowID,int LangID) 
{
	CDisplayPlugin *SimplePlugin = new CDisplayPlugin(Parent, WindowID);
	return SimplePlugin;
}