#include <wx/wx.h>
#include <wx/mstream.h>
#include "conf.h"
#include "tools.h"
#include "display.h"
#include "item.h"
#include "device_config.h"
#include "data_config.h"
#include "warning.h"
#include "battery.h"

DEFINE_EVENT_TYPE(EVT_SET_LOGGER)

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
	EVT_TREE_ITEM_MENU(ID_TREE, OnTreeMenu)
	EVT_TREE_SEL_CHANGED(ID_TREE, OnTreeSelChanged)
	EVT_MENU(ID_STOP,OnStop)
	EVT_MENU(ID_START,OnStart)
	EVT_MENU(ID_CONFIGURE_DEVICE,OnConfigureDevice)
	EVT_MENU(ID_CONFIGURE_DATA,OnConfigureData)
	EVT_MENU(ID_REMOVE,OnRemove)
	EVT_MENU(ID_ADD,OnAdd)
	EVT_COMMAND(ID_LOGGER,EVT_SET_LOGGER,OnSetLogger)
	//EVT_TOOL(ID_TOOL_STOP,
END_EVENT_TABLE()



CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	m_SelectedDevice = NULL;
	SetDisplayID(NDS_DEVICE_MANAGER);
	m_Broker = NULL;
	
	m_Sizer = new wxBoxSizer(wxVERTICAL);
	
	//wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	//wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	//m_Sizer->Add(Panel,1,wxALL|wxEXPAND,25);


	//m_ScrollSizer = new wxBoxSizer(wxVERTICAL);
	//m_Scroll = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//m_Sizer->Add(m_Scroll,1,wxALL|wxEXPAND,5);

	//wxButton *but = new wxButton(Scroll,wxID_ANY,wxEmptyString);
	//m_ScrollSizer->Add(but,0,wxALL,5);

	//m_Scroll->SetFocusIgnoringChildren();
	//m_Scroll->SetSizer(m_ScrollSizer);
	
	
	//m_Scroll->SetScrollbars(20, 20, 20, 20);



	
	m_Devices = new wxTreeCtrl(this,ID_TREE,wxDefaultPosition,wxDefaultSize);

	m_ImageListSmall = new wxImageList(16, 16);
	//m_ToolBar = new wxToolBar(this,wxID_ANY,wxDefaultPosition,wxDefaultSize, wxTB_FLAT| wxTB_TEXT| wxTB_NOICONS);

	//m_ToolBar->AddTool(ID_START , _("Start"),wxNullBitmap,wxNullBitmap,wxITEM_NORMAL);
	//m_ToolBar->AddTool(ID_STOP , _("Stop"),wxNullBitmap,wxNullBitmap,wxITEM_NORMAL);
    //m_ToolBar->Realize();
	//m_Sizer->Add(m_ToolBar,0,wxEXPAND|wxALL,0);
	//wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    //wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_1);

	wxMemoryInputStream in_2((const unsigned char*)battery,battery_size);
    wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_2);
	
	wxMemoryInputStream in_3((const unsigned char*)warning,warning_size);
    wxImage myImage_3(in_3, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_3);
	

	m_Devices->AssignImageList(m_ImageListSmall);
	
	m_Root = m_Devices->AddRoot(_("Devices"));
	m_Sizer->Add(m_Devices,1,wxALL|wxEXPAND);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this);
	Panel->SetSizer(PanelSizer);
	m_Sizer->Add(Panel,0,wxEXPAND,0);
	//Panel->SetBackgroundColour(*wxRED);
	
	//wxStaticText *LabelConnected = new wxStaticText(Panel,wxID_ANY,_("is connected ?"));
	//PanelSizer->Add(LabelConnected,0,wxEXPAND|wxALL,2);

	//wxStaticText *LabelRunning = new wxStaticText(Panel,wxID_ANY,_("is running ?"));
	//PanelSizer->Add(LabelRunning,0,wxEXPAND|wxALL,2);

	//wxStaticText *LabelHasSignal = new wxStaticText(Panel,wxID_ANY,_("has signal ?"));
	//PanelSizer->Add(LabelHasSignal,0,wxEXPAND|wxALL,2);

	//m_Logger = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
	//m_Sizer->Add(m_Logger,0,wxALL|wxEXPAND);
		
	
	this->SetSizer(m_Sizer);
	m_FirstTime = true;
	m_SelectedItem = NULL;

};

CDisplayPlugin::~CDisplayPlugin()
{

}

void CDisplayPlugin::OnTreeSelChanged(wxTreeEvent &event)
{
	m_SelectedItemId = event.GetItem();
	m_SelectedItem = (CItem*)m_Devices->GetItemData(event.GetItem());
	if(m_SelectedItem == NULL)
	{
		m_ToolBar->EnableTool(ID_START,false);
		m_ToolBar->EnableTool(ID_STOP,false);
		return;
	}

	if(m_SelectedItem->GetSerial()->IsRunning())
	{	
		m_ToolBar->EnableTool(ID_START,false);
		m_ToolBar->EnableTool(ID_STOP,true);
	
	}else{
		
		m_ToolBar->EnableTool(ID_START,true);
		m_ToolBar->EnableTool(ID_STOP,false);
	}

}

void CDisplayPlugin::OnTreeMenu(wxTreeEvent &event)
{
		
	m_SelectedItem = (CItem*)m_Devices->GetItemData(event.GetItem());

	if(m_SelectedItem == NULL)
	{
		wxMenu *Menu = new wxMenu();
		Menu->Append(ID_ADD,_("Add device"));
		PopupMenu(Menu);
		delete Menu;
		return;
	}

	
	CMySerial *Serial = m_SelectedItem->GetSerial();
	m_SelectedDevice = Serial;
	wxMenu *Menu = new wxMenu(wxString::Format(_("%s"),Serial->GetDeviceName().wc_str()));
		
	Menu->Append(ID_STOP,_("Stop"));
	Menu->Append(ID_START,_("Start"));
	Menu->AppendSeparator();
	Menu->Append(ID_CONFIGURE_DEVICE,_("Configure Device"));
	Menu->Append(ID_CONFIGURE_DATA,_("Configure Device Data"));
	Menu->AppendSeparator();
	Menu->Append(ID_STATUS,_("Status"));
	Menu->Append(ID_REMOVE,_("Remove"));

	bool running = m_SelectedDevice->IsRunning();
	Menu->Enable(ID_CONFIGURE_DEVICE,!running);
	Menu->Enable(ID_CONFIGURE_DATA,!running);
	Menu->Enable(ID_STOP,running);
	Menu->Enable(ID_START,!running);
	PopupMenu(Menu);
	
	delete Menu;
	event.Skip();

}

void CDisplayPlugin::OnStop(wxCommandEvent &event)
{
	m_SelectedDevice->Stop();
	m_Devices->SetItemImage(m_SelectedItemId,0, wxTreeItemIcon_Normal);
		
}

void CDisplayPlugin::OnStart(wxCommandEvent &event)
{
	m_SelectedDevice->Start();
	m_Devices->SetItemImage(m_SelectedItemId,1, wxTreeItemIcon_Normal);
}

void CDisplayPlugin::OnRemove(wxCommandEvent &event)
{
	m_SelectedDevice->Stop();
	m_MapPlugin->RemoveDevice(m_SelectedDevice);
	
}

void CDisplayPlugin::OnConfigureDevice(wxCommandEvent &event)
{
	if(m_SelectedDevice->IsRunning())
	{
		wxMessageBox(_("Stop the device first."));
		return;

	}

	CDeviceConfig *DeviceConfig = new CDeviceConfig();
	DeviceConfig->SetPort((char*)m_SelectedDevice->GetPortName());
	DeviceConfig->SetBaud(m_SelectedDevice->GetBaudRate());
	DeviceConfig->SetDeviceName(m_SelectedDevice->GetDeviceName());
	
	
	if(DeviceConfig->ShowModal() == wxID_OK)
	{
		m_SelectedDevice->SetPort(DeviceConfig->GetPort().char_str());
		m_SelectedDevice->SetBaud(DeviceConfig->GetBaud());
		m_SelectedDevice->SetDeviceName(DeviceConfig->GetDeviceName());
		
	}	
	
	
	delete DeviceConfig;
}

void CDisplayPlugin::OnConfigureData(wxCommandEvent &event)
{
	CDataConfig *Config = new CDataConfig(m_SelectedDevice);
	
	if(Config->ShowModal() == wxID_OK)
	{
	
	}
	delete Config;
}



void CDisplayPlugin::OnAdd(wxCommandEvent &event)
{
	CDeviceConfig *Config = new CDeviceConfig();
	
	if(Config->ShowModal() == wxID_OK)
	{
		int count = m_MapPlugin->GetDevicesCount(); 
		wxString name = wxString::Format(_("%s"),Config->GetDeviceName().wc_str());
		
		CMySerial *serial = CreateNewDevice(name, Config->GetPort().char_str(),	Config->GetBaud(),true);
				
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_AddDevice",serial);
	}	
	
	delete Config;
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
		m_MapPlugin = (CMapPlugin*)SignalID->GetData();
		m_SignalType = m_MapPlugin->GetDisplaySignalType();
		m_DeviceId = m_MapPlugin->GetDeviceId();
		InitDisplay();
		GetSignal();    // kolejnoœæ initDispaly najpierw dla sygnalu czyszcz¹cego m_firstTime przestawiany na fa³sz i InitDisplay siê inicjuje
		
		return false;
	}
	
	return false;
}

void CDisplayPlugin::GetSignal()
{
	m_SignalType = m_MapPlugin->GetDisplaySignalType();
	
	switch(m_SignalType)
	{
		case CLEAR_DISPLAY: 
			ClearDisplay(); 
		break;		// czysci listê urz¹dzeñ (np przy wy³¹czeniu plugina)
		
		case INIT_SIGNAL:	
			InitDisplay();	
		break;		// inicjuje listê urzadzeñ
		
		case ADD_DEVICE:	
			AddDevice();	
		break;		// dodano nowe urzadzenie

		case REMOVE_DEVICE:
			RemoveDevice();
		break;
		
		case SERIAL_SIGNAL_RECONNECT: 
		case SERIAL_SIGNAL_ONDATA: 	
		case SERIAL_SIGNAL_NEW_SIGNAL:
		case SERIAL_SIGNAL_NO_SIGNAL:
			SetLoggerEvent();									
		break;
	}
	
}

void CDisplayPlugin::ClearDisplay()
{
	m_FirstTime = true;
	m_Devices->DeleteChildren(m_Root);
}

void CDisplayPlugin::InitDisplay()
{
	if(m_FirstTime)
	{
		m_FirstTime = false;
		SetDevices();
	}

}

void CDisplayPlugin::AddDevice()
{
	int count =	m_MapPlugin->GetDevicesCount() - 1;
	CMySerial *Serial = m_MapPlugin->GetDevice(count);
	wxString port(Serial->GetPortName(),wxConvUTF8);
	int icon_id = 0;
	if(Serial->IsRunning())
		icon_id = 1;
	
	wxTreeItemId id = m_Devices->AppendItem(m_Root,wxString::Format(_("%s"),Serial->GetDeviceName()),icon_id);
	CItem *Item = new CItem();
	Item->SetSerial(Serial);
	m_Devices->SetItemData(id,Item);

}

void CDisplayPlugin::RemoveDevice()
{
	SetDevices();
	//int count =	m_MapPlugin->GetDevicesCount() - 1;
	//CMySerial *Serial = m_MapPlugin->GetDevice(count);
	//wxString port(Serial->GetPortName(),wxConvUTF8);
	//wxTreeItemId id = m_Devices->AppendItem(m_Root,wxString::Format(_("%s [%s][%d]"),Serial->GetDeviceName(),port.wc_str(),Serial->GetBaudRate()));
	//CItem *Item = new CItem();
	//Item->SetSerial(Serial);
	//m_Devices->SetItemData(id,Item);

}



void CDisplayPlugin::OnSetLogger(wxCommandEvent &event)
{
	//GetMutex()->Lock();
	//SetLogger(event.GetString());
	//GetMutex()->Unlock();
}

void CDisplayPlugin::SetLoggerEvent()
{
	wxCommandEvent evt(EVT_SET_LOGGER,ID_LOGGER);
	evt.SetString(wxString::Format(_("[%d]: %d\n"),m_DeviceId,m_SignalType));
	if(m_SignalType == SERIAL_SIGNAL_ONDATA)
	{
		CMySerial *serial = m_MapPlugin->GetDevice(m_DeviceId);
		wxString buf((char*)serial->GetBuffer(),wxConvUTF8);
		evt.SetString(buf);
	}
	
	//evt.SetId(m_DeviceId);
    wxPostEvent(this,evt);
	
}
void CDisplayPlugin::SetLogger(wxString txt)
{

	m_Logger->AppendText(txt);
		

}

void CDisplayPlugin::SetDevices() 
{

	//for(size_t i = 0; i < m_MapPlugin->GetDevicesCount(); i++)
	//{
		//wxPanel *Panel = m_MapPlugin->GetDevice(i)->CreateConfigPanel(m_Scroll);
		//
		//Panel->SetParent();
		//m_ScrollSizer->Add(Panel,0,wxALL|wxEXPAND,10);
		//Panel->SetBackgroundColour(*wxRED);
		//wxString port(Serial->GetPortName(),wxConvUTF8);
		//m_ScrollSizer->Layout();
	
	//}
	//m_Scroll->SetScrollbars(20, 20, 20, 20);
	//return;
	m_Devices->DeleteChildren(m_Root);
	
	for(size_t i = 0; i < m_MapPlugin->GetDevicesCount(); i++)
	{
		CMySerial *Serial = m_MapPlugin->GetDevice(i);
		wxString port(Serial->GetPortName(),wxConvUTF8);
		wxTreeItemId id = m_Devices->AppendItem(m_Root,wxString::Format(_("%s"),Serial->GetDeviceName()));
		//SetDevicesData(Serial,id);
		CItem *Item = new CItem();
		Item->SetSerial(Serial);
		m_Devices->SetItemData(id,Item);
	}


}

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
			return L"devmgr";
			break;

		default:
			return L"devmgr";
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