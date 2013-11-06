#include <wx/wx.h>
#include <wx/mstream.h>
#include <wx/notebook.h>
#include "conf.h"
#include "tools.h"
#include "display.h"
#include "item.h"
#include "device_config.h"
#include "data_config.h"
#include "status.h"
#include "computer.h"
#include "stop.h"
#include "start.h"

DEFINE_EVENT_TYPE(EVT_SET_LOGGER)

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
	EVT_TREE_ITEM_MENU(ID_TREE, CDisplayPlugin::OnTreeMenu)
	EVT_TREE_SEL_CHANGED(ID_TREE, CDisplayPlugin::OnTreeSelChanged)
	EVT_MENU(ID_STOP,CDisplayPlugin::OnStop)
	EVT_MENU(ID_START,CDisplayPlugin::OnStart)
	EVT_MENU(ID_CONFIGURE_DEVICE,CDisplayPlugin::OnConfigureDevice)
	EVT_MENU(ID_CONFIGURE_DATA,CDisplayPlugin::OnConfigureData)
	EVT_MENU(ID_UNINSTALL,CDisplayPlugin::OnUninstall)
	EVT_MENU(ID_NEW_DEVICE,CDisplayPlugin::OnNewDevice)
	EVT_MENU(ID_STATUS,CDisplayPlugin::OnStatus)
	EVT_COMMAND(ID_LOGGER,EVT_SET_LOGGER,CDisplayPlugin::OnSetLogger)
	//EVT_TOOL(ID_TOOL_STOP,
END_EVENT_TABLE()



CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	m_SelectedDevice = NULL;
	SetDisplayID(NDS_DEVICE_MANAGER);
	m_Broker = NULL;
	
	m_Sizer = new wxBoxSizer(wxVERTICAL);
	m_ImageListSmall = new wxImageList(16, 16);
	wxMemoryInputStream in_0((const unsigned char*)stop,stop_size);
    wxImage myImage_0(in_0, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_0);
	
	wxMemoryInputStream in_1((const unsigned char*)start,start_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_1);
	
	wxMemoryInputStream in_2((const unsigned char*)computer,computer_size);
    wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_2);	

	
	
	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Sizer->Add(Notebook,1,wxALL|wxEXPAND,0);
	wxPanel *Page1 = new wxPanel(Notebook);
	wxBoxSizer *Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(Page1Sizer);
	Notebook->AddPage(Page1,GetMsg(MSG_DEVICES));

	m_ToolBar = new wxToolBar(Page1,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTB_FLAT);
	//m_ToolBar->set
	wxBitmap stop(myImage_0);
	wxBitmap start(myImage_1);
	wxBitmap computer(myImage_2);

	m_ToolBar->AddTool(ID_NEW_DEVICE, GetMsg(MSG_NEW_DEVICE), computer, wxNullBitmap,wxITEM_NORMAL,GetMsg(MSG_NEW_DEVICE));
	m_ToolBar->AddTool(ID_START, GetMsg(MSG_START), start, wxNullBitmap,wxITEM_NORMAL,GetMsg(MSG_START));
	m_ToolBar->AddTool(ID_STOP, GetMsg(MSG_START), stop, wxNullBitmap,wxITEM_NORMAL,GetMsg(MSG_STOP));
	m_ToolBar->EnableTool(ID_STOP, false);
	m_ToolBar->EnableTool(ID_START, false);
	m_ToolBar->Realize();
	Page1Sizer->Add(m_ToolBar,0,wxEXPAND|wxALL,0);


	m_Devices = new wxTreeCtrl(Page1,ID_TREE,wxDefaultPosition,wxDefaultSize);
	m_Devices->AssignImageList(m_ImageListSmall);
	
	m_Root = m_Devices->AddRoot(GetMsg(MSG_DEVICES));
	m_Devices->SetItemImage(m_Root,2, wxTreeItemIcon_Normal);
	Page1Sizer->Add(m_Devices,1,wxALL|wxEXPAND);

	m_InfoPanel = new wxPanel(Page1,wxID_ANY);
	Page1Sizer->Add(m_InfoPanel,0,wxALL|wxEXPAND,0);

	wxBoxSizer *InfoPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_InfoPanel->SetSizer(InfoPanelSizer);
	//m_InfoPanel->Hide();
	
	wxFont font;
	font.SetPointSize(14);
		
	wxStaticText *LabelConnected = new wxStaticText(m_InfoPanel,wxID_ANY,_("is connected ?"));
	InfoPanelSizer->Add(LabelConnected,0,wxEXPAND|wxALL,2);

	wxStaticText *LabelRunning = new wxStaticText(m_InfoPanel,wxID_ANY,_("is running ?"));
	InfoPanelSizer->Add(LabelRunning,0,wxEXPAND|wxALL,2);

	wxStaticText *LabelHasSignal = new wxStaticText(m_InfoPanel,wxID_ANY,_("has signal ?"));
	InfoPanelSizer->Add(LabelHasSignal,0,wxEXPAND|wxALL,2);
	
//	m_Logger = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
//	m_Sizer->Add(m_Logger,0,wxALL|wxEXPAND);
		
	
	this->Disable();
	this->SetSizer(m_Sizer);
	m_FirstTime = true;
	m_SelectedItem = NULL;
	m_DeviceConfig = NULL;

}

CDisplayPlugin::~CDisplayPlugin()
{
	if(m_DeviceConfig != NULL)
		delete m_DeviceConfig;
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
	
	m_SelectedDevice = m_SelectedItem->GetSerial();
	if(m_SelectedDevice->IsRunning())
	{	
		m_ToolBar->EnableTool(ID_START,false);
		m_ToolBar->EnableTool(ID_STOP,true);
	
	}else{
		
		m_ToolBar->EnableTool(ID_START,true);
		m_ToolBar->EnableTool(ID_STOP,false);
	}
	ShowInfoPanel(true);
}

void CDisplayPlugin::OnTreeMenu(wxTreeEvent &event)
{
	m_SelectedItemId = event.GetItem();
	m_SelectedItem = (CItem*)m_Devices->GetItemData(event.GetItem());
	m_Devices->SelectItem(event.GetItem());

	if(m_SelectedItem == NULL)
	{
		wxMenu *Menu = new wxMenu();
		Menu->Append(ID_NEW_DEVICE,GetMsg(MSG_NEW_DEVICE));
		PopupMenu(Menu);
		delete Menu;
		return;
	}

	
	CMySerial *Serial = m_SelectedItem->GetSerial();
	m_SelectedDevice = Serial;
	wxMenu *Menu = new wxMenu(wxString::Format(_("%s"),Serial->GetDeviceName().wc_str()));
		
	Menu->Append(ID_START,GetMsg(MSG_START));
	Menu->Append(ID_STOP,GetMsg(MSG_STOP));
	Menu->AppendSeparator();
	Menu->Append(ID_CONFIGURE_DEVICE,GetMsg(MSG_CONFIGURE_DEVICE));
	Menu->Append(ID_CONFIGURE_DATA,GetMsg(MSG_CONFIGURE_DEVICE_DATA));

	Menu->AppendSeparator();
	Menu->Append(ID_STATUS,GetMsg(MSG_STATUS));
	Menu->Append(ID_UNINSTALL,GetMsg(MSG_UNINSTALL));

	bool running = m_SelectedDevice->IsRunning();
	Menu->Enable(ID_CONFIGURE_DEVICE,!running);
	Menu->Enable(ID_CONFIGURE_DATA,!running);
	Menu->Enable(ID_STOP,running);
	Menu->Enable(ID_START,!running);
	PopupMenu(Menu);
	
	delete Menu;
	event.Skip();

}

void CDisplayPlugin::OnStatus(wxCommandEvent &event)
{
	CStatus *_Status = new CStatus(m_SelectedDevice);
	_Status->ShowModal();
	delete _Status;
}

void CDisplayPlugin::OnStop(wxCommandEvent &event)
{
	m_SelectedDevice->Stop();
	m_Devices->SetItemBold(m_SelectedItemId,false);
	m_Devices->SetItemImage(m_SelectedItemId,ICON_START, wxTreeItemIcon_Normal);
		
}

void CDisplayPlugin::OnStart(wxCommandEvent &event)
{
	m_SelectedDevice->Start();
	m_Devices->SetItemBold(m_SelectedItemId,true);
	m_Devices->SetItemImage(m_SelectedItemId,ICON_STOP, wxTreeItemIcon_Normal);
}

void CDisplayPlugin::OnUninstall(wxCommandEvent &event)
{
//	m_SelectedDevice->Stop();
	m_MapPlugin->RemoveDevice(m_SelectedDevice);
}

void CDisplayPlugin::OnConfigureDevice(wxCommandEvent &event)
{
	if(m_SelectedDevice->IsRunning())
	{
		wxMessageBox(GetMsg(MSG_STOP_THE_DEVICE));
		return;
	}
	
	if(m_DeviceConfig == NULL)
		m_DeviceConfig = new CDeviceConfig();
	m_DeviceConfig->SetPort((char*)m_SelectedDevice->GetPortName());
	m_DeviceConfig->SetBaud(m_SelectedDevice->GetBaudRate());
	m_DeviceConfig->SetDeviceName(m_SelectedDevice->GetDeviceName());
	
	
	if(m_DeviceConfig->ShowModal() == wxID_OK)
	{
		m_SelectedDevice->_SetPort(m_DeviceConfig->GetPort().char_str());
		m_SelectedDevice->SetBaud(m_DeviceConfig->GetBaud());
		m_SelectedDevice->SetDeviceName(m_DeviceConfig->GetDeviceName());
		m_Devices->SetItemText(m_SelectedItemId,m_DeviceConfig->GetDeviceName());
	}	
			
}

void CDisplayPlugin::OnConfigureData(wxCommandEvent &event)
{
	CDataConfig *Config = new CDataConfig(m_SelectedDevice);
	
	if(Config->ShowModal() == wxID_OK)
	{
	
	}
	delete Config;
}



void CDisplayPlugin::OnNewDevice(wxCommandEvent &event)
{
	if(m_DeviceConfig == NULL)
		m_DeviceConfig = new CDeviceConfig();
	
	if(m_DeviceConfig->ShowModal() == wxID_OK)
	{
		int count = m_MapPlugin->GetDevicesCount(); 
		wxString name = wxString::Format(_("%s"),m_DeviceConfig->GetDeviceName().wc_str());
		
		CMySerial *serial = CreateNewDevice(name, m_DeviceConfig->GetPort().char_str(),	m_DeviceConfig->GetBaud(),true);
				
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_AddDevice",serial);
	}	
	
	
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
		GetSignal();    // kolejno�� initDispaly najpierw dla sygnalu czyszcz�cego m_firstTime przestawiany na fa�sz i InitDisplay si� inicjuje
		
		return false;
	}
	
	return false;
}

void CDisplayPlugin::ShowInfoPanel(bool show)
{
	if(show)
	{
		m_InfoPanel->Show();
		m_Sizer->Layout();
	}else{
		m_InfoPanel->Hide();
		m_Sizer->Layout();
	
	}
}

void CDisplayPlugin::GetSignal()
{
	m_SignalType = m_MapPlugin->GetDisplaySignalType();
	
	switch(m_SignalType)
	{
		case CLEAR_DISPLAY: 
			ClearDisplay(); 
		break;		// czysci list� urz�dze� (np przy wy��czeniu plugina)
		
		case INIT_SIGNAL:	
			InitDisplay();	
		break;		// inicjuje list� urzadze�
		
		case ADD_DEVICE:	
			AddDevice();	
		break;		// dodano nowe urzadzenie

		case REMOVE_DEVICE:
			RemoveDevice();
		break;
		
		
		case SERIAL_SIGNAL_NEW_SIGNAL:
			NewSignal();
		break;
		
		case SERIAL_SIGNAL_RECONNECT: 
		case SERIAL_SIGNAL_ONDATA: 	
		case SERIAL_SIGNAL_NO_SIGNAL:
			SetLoggerEvent();									
		break;
	}
	
}
void CDisplayPlugin::NewSignal()
{
	
}

void CDisplayPlugin::ClearDisplay()
{
	m_FirstTime = true;
	//m_Devices->DeleteChildren(m_Root);
	this->Disable();
}

void CDisplayPlugin::InitDisplay()
{
	if(m_FirstTime)
	{
		m_FirstTime = false;
		this->Enable();
		SetDevices();
		SetSignals();
	}

}

void CDisplayPlugin::AddDevice()
{
	int count =	m_MapPlugin->GetDevicesCount() - 1;
	CMySerial *Serial = m_MapPlugin->GetDevice(count);
	wxString port(Serial->GetPortName(),wxConvUTF8);
	int icon_id = ICON_START;
	bool running = false;
	
	if(Serial->IsRunning())
	{
		icon_id = ICON_STOP;
		running = true;
	}
	
	wxTreeItemId id = m_Devices->AppendItem(m_Root,wxString::Format(_("%s"),Serial->GetDeviceName()),icon_id);
	CItem *Item = new CItem();
	Item->SetSerial(Serial);
	m_Devices->SetItemData(id,Item);
	m_Devices->SetItemBold(id,running);

}

void CDisplayPlugin::RemoveDevice()
{
	SetDevices();
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
	m_Devices->DeleteChildren(m_Root);
	
	for(size_t i = 0; i < m_MapPlugin->GetDevicesCount(); i++)
	{
		CMySerial *Serial = m_MapPlugin->GetDevice(i);
		wxString port(Serial->GetPortName(),wxConvUTF8);

		int icon_id = ICON_START;
		bool running = false;
		if(Serial->IsRunning())
		{
			icon_id = ICON_STOP;
			running = true;
		}
		
		wxTreeItemId id = m_Devices->AppendItem(m_Root,wxString::Format(_("%s"),Serial->GetDeviceName()),icon_id);
		//SetDevicesData(Serial,id);
		CItem *Item = new CItem();
		Item->SetSerial(Serial);
		m_Devices->SetItemData(id,Item);
		m_Devices->SetItemBold(id,running);
	
	}
	
	m_Devices->ExpandAll();

}

void CDisplayPlugin::SetSignals()
{
	wxTreeItemIdValue cookie;
	wxTreeItemId id = m_Devices->GetFirstChild(m_Root,cookie);	
	while(id.IsOk())
	{
		
		CItem *item  = (CItem*)m_Devices->GetItemData(id);
		CSerial *serial = item->GetSerial();
		for(size_t i = 0; i < serial->GetSignalCount();i++)
		{
			m_Devices->AppendItem(id,wxString::Format(_("%s"),serial->GetSignal(i)->name),0);
		}
	
		id = m_Devices->GetNextChild(id,cookie);
	
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