#include <wx/wx.h>
#include <wx/mstream.h>
#include <wx/notebook.h>
#include "conf.h"
#include "tools.h"
#include "devices_list.h"
#include "item.h"
#include "config.h"
#include "status.h"
#include "info.h"
#include "wizard.h"


#include "images/computer.img"
#include "images/stop.img"
#include "images/start.img"
#include "images/types.img"


DEFINE_EVENT_TYPE(EVT_SET_LOGGER)
DEFINE_EVENT_TYPE(EVT_SET_ICON)
DEFINE_EVENT_TYPE(EVT_SET_TEXT)

BEGIN_EVENT_TABLE(CDevicesList,wxPanel)
	EVT_TREE_ITEM_MENU(ID_TREE, CDevicesList::OnTreeMenu)
	EVT_TREE_SEL_CHANGED(ID_TREE, CDevicesList::OnTreeSelChanged)
	EVT_MENU(ID_STOP,CDevicesList::OnStop)
	EVT_MENU(ID_START,CDevicesList::OnStart)
	EVT_MENU(ID_CONFIGURE_DEVICE,CDevicesList::OnConfigureDevice)
	EVT_MENU(ID_UNINSTALL,CDevicesList::OnUninstall)
	EVT_MENU(ID_NEW_DEVICE,CDevicesList::OnNewDevice)
	EVT_MENU(ID_DEVICE_WIZARD,CDevicesList::OnDeviceWizard)
	EVT_MENU(ID_STATUS,CDevicesList::OnStatus)
	EVT_MENU(ID_START,CDevicesList::OnStart)
	
	EVT_HYPERLINK(ID_STOP,CDevicesList::OnStop)
	EVT_HYPERLINK(ID_START,CDevicesList::OnStart)
//	EVT_HYPERLINK(ID_CONFIGURE_DEVICE,CDisplayPlugin::OnConfigureDevice)
	EVT_HYPERLINK(ID_MONITOR,CDevicesList::OnMonitor)

	EVT_COMMAND(ID_LOGGER,EVT_SET_LOGGER,CDevicesList::OnSetLogger)
	EVT_COMMAND(ID_ICON,EVT_SET_ICON,CDevicesList::OnSetIcon)
	EVT_COMMAND(ID_TEXT,EVT_SET_TEXT,CDevicesList::OnSetText)
	//EVT_TOOL(ID_TOOL_STOP,
END_EVENT_TABLE()


CDevicesList::CDevicesList(wxWindow *parent, CMapPlugin *plugin) 
:wxPanel(parent)

{
	m_SelectedDevice = NULL;
	m_Broker = NULL;
	m_SignalsPanel = NULL;
	m_Sizer = NULL;
	m_MapPlugin = plugin;
	SetDoubleBuffered(true);
	
	
	m_FirstTime = true;
	m_SelectedItem = NULL;
	m_DeviceConfig = NULL;
	m_Broker = plugin->GetBroker();

	GetPanel();
	SetDevices();

}

CDevicesList::~CDevicesList()
{
	if(m_DeviceConfig != NULL)
		delete m_DeviceConfig;
		
}

void CDevicesList::GetPanel()
{
	
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

	wxMemoryInputStream in_3((const unsigned char*)types,types_size);
    wxImage myImage_3(in_3, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_3);	
	
		//m_ToolBar->set
	wxBitmap stop(myImage_0);
	wxBitmap start(myImage_1);
	wxBitmap computer(myImage_2);
	wxBitmap types(myImage_3);


	m_Sizer = new wxBoxSizer(wxVERTICAL);

	//wxPanel *Panel = new wxPanel(this);
	//m_Sizer->Add(Panel,1,wxALL|wxEXPAND,0);
	//wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	
	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Sizer->Add(Notebook,1,wxALL|wxEXPAND,0);
	wxPanel *Page1 = new wxPanel(Notebook);
	Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(Page1Sizer);
	Notebook->AddPage(Page1,GetMsg(MSG_DEVICES));

	m_ToolBar = new wxToolBar(Page1,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxTB_FLAT);
		
	m_ToolBar->AddTool(ID_START, GetMsg(MSG_START), start, wxNullBitmap,wxITEM_NORMAL,GetMsg(MSG_START));
	m_ToolBar->AddTool(ID_STOP, GetMsg(MSG_START), stop, wxNullBitmap,wxITEM_NORMAL,GetMsg(MSG_STOP));
	m_ToolBar->AddSeparator();
	m_ToolBar->AddTool(ID_NEW_DEVICE, GetMsg(MSG_NEW_DEVICE), computer, wxNullBitmap,wxITEM_NORMAL,GetMsg(MSG_NEW_DEVICE));
	//m_ToolBar->AddTool(ID_DEVICE_TYPES, GetMsg(MSG_DEVICE_TYPES), types, wxNullBitmap,wxITEM_NORMAL,GetMsg(MSG_DEVICE_TYPES));
	m_ToolBar->AddTool(ID_DEVICE_WIZARD, GetMsg(MSG_DEVICE_WIZARD), types, wxNullBitmap,wxITEM_NORMAL,GetMsg(MSG_DEVICE_WIZARD));

	m_ToolBar->EnableTool(ID_STOP, false);
	m_ToolBar->EnableTool(ID_START, false);
	m_ToolBar->Realize();
	Page1Sizer->Add(m_ToolBar,0,wxEXPAND|wxALL,0);


	m_Devices = new wxTreeCtrl(Page1,ID_TREE,wxDefaultPosition,wxDefaultSize);
	m_Devices->AssignImageList(m_ImageListSmall);
	
	m_Root = m_Devices->AddRoot(GetMsg(MSG_DEVICES));
	m_Devices->SetItemImage(m_Root,2, wxTreeItemIcon_Normal);
	Page1Sizer->Add(m_Devices,1,wxALL|wxEXPAND);

	// info panel
	m_InfoPanel = new wxPanel(Page1,wxID_ANY);
	m_InfoPanel->Hide();
	Page1Sizer->Add(m_InfoPanel,0,wxALL|wxEXPAND,0);

	m_InfoPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_InfoPanel->SetSizer(m_InfoPanelSizer);
	
	wxFont font;
	font.SetPointSize(10);
	font.SetWeight(wxBOLD);	
	m_LabelName = new wxStaticText(m_InfoPanel,wxID_ANY,wxEmptyString);
	m_LabelName->SetFont(font);
	m_InfoPanelSizer->Add(m_LabelName,0,wxALL,2);

	m_LabelPort = new wxStaticText(m_InfoPanel,wxID_ANY,wxEmptyString);
	m_InfoPanelSizer->Add(m_LabelPort,0,wxALL,2);

	m_LabelConnected = new wxStaticText(m_InfoPanel,wxID_ANY,wxEmptyString);
	m_InfoPanelSizer->Add(m_LabelConnected,0,wxALL,2);

	font.SetPointSize(8);
	font.SetWeight(wxNORMAL);	
	m_StartButton = new wxHyperlinkCtrl(m_InfoPanel,ID_START,GetMsg(MSG_START),wxEmptyString);
	m_StartButton->SetFont(font);
	m_InfoPanelSizer->Add(m_StartButton,0,wxALL,2);
		
	m_Monitor = new wxHyperlinkCtrl(m_InfoPanel,ID_MONITOR,GetMsg(MSG_MONITOR),wxEmptyString);
	m_Monitor->SetFont(font);
	m_InfoPanelSizer->Add(m_Monitor,0,wxALL,2);

	m_ConfigureButton = new wxHyperlinkCtrl(m_InfoPanel,ID_CONFIGURE_DEVICE,GetMsg(MSG_CONFIGURE_DEVICE),wxEmptyString);
	m_ConfigureButton->SetFont(font);
	m_InfoPanelSizer->Add(m_ConfigureButton,0,wxALL,2);
	
	m_Logger = new wxTextCtrl(m_InfoPanel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE|wxTE_DONTWRAP);
	m_InfoPanelSizer->Add(m_Logger,0,wxALL|wxEXPAND);
	m_Logger->Hide();
			
	this->SetSizer(m_Sizer);
	m_FirstTime = true;
	m_SelectedItem = NULL;
	m_DeviceConfig = NULL;
	
}
void CDevicesList::SetSignal(int stype, CReader* reader)
{
	m_Reader = reader;
	m_SignalType = stype;

	switch(m_SignalType)
	{
		case CLEAR_DISPLAY: 			ClearDisplay(); 	break;		// czysci listę urządzeń (np przy wyłączeniu plugina)
		case ADD_DEVICE:				AddDevice();		break;		// dodano nowe urzadzenie
		case REMOVE_DEVICE:				RemoveDevice();		break;
		case START_DEVICE:				StartDevice();		break;
		case STOP_DEVICE:				StopDevice();		break;
		case SIGNAL_RECONNECT: 			OnReconnect();		break;
		case SIGNAL_NO_SIGNAL:			OnNoSignal();		break;
		case SIGNAL_CONNECTED:			OnConnected();		break;
//		case SIGNAL_NMEA_LINE:			OnNMEALine();		break;
		//case DATA_SIGNAL:				OnData();			break;
	}


}

int CDevicesList::GetControlType()
{
	return m_ControlType - ID_MENU_BEGIN;
}

void CDevicesList::OnTreeSelChanged(wxTreeEvent &event)
{
	m_SelectedItemId = event.GetItem();
	m_SelectedItem = (CItem*)m_Devices->GetItemData(event.GetItem());
	
	if(m_SelectedItem == NULL)
	{
		m_ToolBar->EnableTool(ID_START,false);
		m_ToolBar->EnableTool(ID_STOP,false);
		ShowInfoPanel(false);
		return;
	}
	
	m_SelectedDevice = m_SelectedItem->GetReader();
	
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

void CDevicesList::OnTreeMenu(wxTreeEvent &event)
{
	m_SelectedItemId = event.GetItem();
	
	if(!m_SelectedItemId.IsOk())
		return;

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
		
	CReader *Reader = m_SelectedItem->GetReader();
	m_SelectedDevice = Reader;
	wxMenu *Menu = new wxMenu(wxString::Format(_("%s"),Reader->GetDeviceName().wc_str()));
		
	Menu->Append(ID_START,GetMsg(MSG_START));
	Menu->Append(ID_STOP,GetMsg(MSG_STOP));
	Menu->AppendSeparator();
	Menu->Append(ID_CONFIGURE_DEVICE,GetMsg(MSG_CONFIGURE_DEVICE));
	Menu->AppendSeparator();
	Menu->Append(ID_STATUS,GetMsg(MSG_STATUS));
	Menu->Append(ID_UNINSTALL,GetMsg(MSG_UNINSTALL));

	bool running = m_SelectedDevice->IsRunning();
	Menu->Enable(ID_CONFIGURE_DEVICE,!running);
	Menu->Enable(ID_STOP,running);
	Menu->Enable(ID_START,!running);
	PopupMenu(Menu);
	
	delete Menu;
	//event.Skip();

}

void CDevicesList::OnStatus(wxCommandEvent &event)
{
	
}

void CDevicesList::OnStop(wxCommandEvent &event)
{
	Stop();
}

void CDevicesList::OnStop(wxHyperlinkEvent &event)
{
	Stop();
}

void CDevicesList::Stop()
{
	m_SelectedDevice->Stop();

	CMyInfo Info(NULL,wxString::Format(GetMsg(MSG_STOPPING_DEVICE),m_SelectedDevice->GetDeviceName().wc_str()));
	while(m_SelectedDevice->GetWorkingFlag())
		wxMilliSleep(150);
		
	m_MapPlugin->StopDevice(m_SelectedDevice);
}

void CDevicesList::OnStart(wxCommandEvent &event)
{
	Start();
}

void CDevicesList::OnStart(wxHyperlinkEvent &event)
{
	Start();
}

void CDevicesList::Start()
{
	m_SelectedDevice->Start();
	m_MapPlugin->StartDevice(m_SelectedDevice);
}

void CDevicesList::OnUninstall(wxCommandEvent &event)
{
	m_MapPlugin->RemoveDevice(m_SelectedDevice);
}

void CDevicesList::OnConfigureDevice(wxCommandEvent &event)
{
	ConfigureDevice();
}

void CDevicesList::OnMonitor(wxHyperlinkEvent &event)
{
	m_SelectedDevice->SetLineEvent();
	m_Logger->Show();
	m_InfoPanelSizer->Layout();
	Page1Sizer->Layout();

}

void CDevicesList::ConfigureDevice()
{
	if(m_SelectedDevice->IsRunning())
	{
		wxMessageBox(GetMsg(MSG_STOP_THE_DEVICE));
		return;
	}
	
	if(m_DeviceConfig == NULL)
		m_DeviceConfig = new CConfig();
	m_DeviceConfig->SetPort((char*)m_SelectedDevice->GetPortName());
	m_DeviceConfig->SetBaud(m_SelectedDevice->GetBaudRate());
	m_DeviceConfig->SetHost(m_SelectedDevice->GetHost());
	m_DeviceConfig->SetPort(m_SelectedDevice->GetPort());
	m_DeviceConfig->SetConnectionType(m_SelectedDevice->GetConnectionType());
	m_DeviceConfig->SetDeviceType(m_SelectedDevice->GetDeviceType());
	

	// zalezy od typu polaczenia
	m_DeviceConfig->SetDeviceName(m_SelectedDevice->GetDeviceName());
	
	if(m_DeviceConfig->ShowModal() == wxID_OK)
	{
		
		m_SelectedDevice->SetDeviceName(m_DeviceConfig->GetDeviceName());
		m_SelectedDevice->SetDeviceType(m_DeviceConfig->GetDeviceType());
		m_SelectedDevice->SetConnectionType(m_DeviceConfig->GetConnectionType());
		m_SelectedDevice->SetDefinition();

		if(m_DeviceConfig->GetConnectionType() == CONNECTION_TYPE_SERIAL)
		{
			m_SelectedDevice->SetPort(m_DeviceConfig->GetSerialPort().char_str());
			m_SelectedDevice->SetBaud(m_DeviceConfig->GetBaud());
			m_Devices->SetItemText(m_SelectedItemId,wxString::Format(_("[%s] %s"),m_DeviceConfig->GetSerialPort().wc_str(),m_DeviceConfig->GetDeviceName().wc_str()));
		}
		
		if(m_DeviceConfig->GetConnectionType() == CONNECTION_TYPE_SOCKET)
		{
			long port; 
			m_DeviceConfig->GetSocketPort().ToLong(&port);
			m_SelectedDevice->SetPort(port);
			m_SelectedDevice->SetHost(m_DeviceConfig->GetHost().char_str());
			m_Devices->SetItemText(m_SelectedItemId,wxString::Format(_("[%s::%s] %s"),m_DeviceConfig->GetHost().wc_str() ,m_DeviceConfig->GetSocketPort().wc_str(), m_DeviceConfig->GetDeviceName().wc_str()));
		}
	
	
	}	
}

void CDevicesList::OnConfigureData(wxCommandEvent &event)
{
	//CDataConfig *Config = new CDataConfig(m_SelectedDevice);
	
	//if(Config->ShowModal() == wxID_OK)
	//{
	
//	}
	//delete Config;
}


void CDevicesList::OnDeviceWizard(wxCommandEvent &event)
{
	CWizard *Wizard = new CWizard();
	
	if(Wizard->ShowModal() == wxID_OK)
	{
		size_t count = Wizard->GetCount();
		for(size_t i = 0; i < count; i++)
		{
			CReader *newreader = Wizard->GetDevice(i);
			CReader *reader = CreateSerialDevice(newreader->GetDeviceName(), (char*)newreader->GetPortName(), newreader->GetBaudRate(), newreader->GetDeviceType() ,true);
			m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_AddDevice",reader);
		}
	}
	
	delete Wizard;
}

void CDevicesList::OnNewDevice(wxCommandEvent &event)
{
	if(m_DeviceConfig == NULL)
		m_DeviceConfig = new CConfig();
	
	if(m_DeviceConfig->ShowModal() == wxID_OK)
	{
		CReader *reader = NULL;
		int count = m_MapPlugin->GetDevicesCount(); 
		wxString name = wxString::Format(_("%s"),m_DeviceConfig->GetDeviceName().wc_str());
		
		switch(m_DeviceConfig->GetConnectionType())
		{
			case CONNECTION_TYPE_SERIAL:
				reader = CreateSerialDevice(name, m_DeviceConfig->GetSerialPort().char_str(),m_DeviceConfig->GetBaud(),m_DeviceConfig->GetDeviceType(), true);
			break;
			case CONNECTION_TYPE_SOCKET:
				long port;
				m_DeviceConfig->GetSocketPort().ToLong(&port);
				reader = CreateSocketDevice(name, m_DeviceConfig->GetHost(),port,m_DeviceConfig->GetDeviceType(),true);
			break;
				
		}
		
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_AddDevice",reader);
	}
	
}

void CDevicesList::ShowInfoPanel(bool show)
{
	if(!m_SelectedItemId.IsOk())
		return;

	if(show)
	{
		CItem *item  = (CItem*)m_Devices->GetItemData(m_SelectedItemId);
		if(item == NULL)
			return;
		CReader *ptr = item->GetReader();

		m_LabelName->SetLabel(ptr->GetDeviceName());
		wxString port(ptr->GetPortName(),wxConvUTF8);
		wxString host(ptr->GetHost(),wxConvUTF8);

		switch(ptr->GetConnectionType())
		{
			case CONNECTION_TYPE_SERIAL: m_LabelPort->SetLabel(wxString::Format(_("%s %d"),port.wc_str(),ptr->GetBaudRate())); break;
			case CONNECTION_TYPE_SOCKET: m_LabelPort->SetLabel(wxString::Format(_("%s %d"),host.wc_str(),ptr->GetPort())); break;
		}
		
		if(ptr->IsRunning())
		{
			m_StartButton->SetLabel(GetMsg(MSG_STOP));
			m_StartButton->SetId(ID_STOP);
			m_ConfigureButton->Hide();
					
		}else{
			
			m_StartButton->SetLabel(GetMsg(MSG_START));
			m_StartButton->SetId(ID_START);
			m_ConfigureButton->Show();
			
		}

		if(ptr->IsConnected())
			m_LabelConnected->SetLabel(GetMsg(MSG_CONNECTED));
		else
			m_LabelConnected->SetLabel(GetMsg(MSG_DISCONNECTED));
	
		if(m_SignalsPanel != NULL)
		{
			m_InfoPanelSizer->Detach(m_SignalsPanel);
			delete m_SignalsPanel;
		}

		m_SignalsPanel = GetSignalsPanel(ptr);
		m_InfoPanelSizer->Add(m_SignalsPanel,0,wxALL|wxEXPAND|wxCENTER,0);
	}
	
	m_InfoPanelSizer->Layout();
	m_InfoPanel->Show(show);
	Page1Sizer->Layout();

}

wxPanel *CDevicesList::GetSignalsPanel(CReader *reader)
{

	int cols = this->GetSize().GetWidth()/30;

	wxPanel *Panel = new wxPanel(m_InfoPanel,wxID_ANY);
	wxFlexGridSizer *grid = new wxFlexGridSizer(cols,0);
	
	Panel->SetSizer(grid);
	wxFont font;
	font.SetPointSize(10);
	
	size_t len = reader->GetSignalCount();
	for(size_t i = 0; i < len; i++)
	{
		wxString str((char*)reader->GetSignal(i)->name,wxConvUTF8);
		wxHyperlinkCtrl *signal = new wxHyperlinkCtrl(Panel,wxID_ANY,str,wxEmptyString);
		signal->SetFont(font);
		grid->Add(signal,1,wxALL|wxEXPAND,1);
		
	}
	
	return Panel;

}

void CDevicesList::StartDevice()
{
	SetIconEvent(ICON_STOP);
	ShowInfoPanel(true);  // refresh panela
}

void CDevicesList::StopDevice()
{
	SetIconEvent(ICON_START);
	ShowInfoPanel(true); // refresh panela
}

void CDevicesList::OnConnected()
{
	SetTextEvent(TEXT_OK);
}

void CDevicesList::OnNoSignal()
{
	SetTextEvent(TEXT_ERROR);
}

void CDevicesList::OnReconnect()
{
	SetTextEvent(TEXT_ERROR);
}

void CDevicesList::ClearDisplay()
{


}

void CDevicesList::AddTreeItem(int item_id)
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

void CDevicesList::AddDevice()
{
	int id = m_MapPlugin->GetDevicesCount() - 1;
	AddTreeItem(id);	
}

void CDevicesList::RemoveDevice()
{
	SetDevices();
}

void CDevicesList::OnSetIcon(wxCommandEvent &event)
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

void CDevicesList::SetIconEvent(int icon_id)
{
	wxCommandEvent evt(EVT_SET_ICON,ID_ICON);
	evt.SetClientData(m_Reader);
	evt.SetInt(icon_id);
	wxPostEvent(this,evt);
}

void CDevicesList::OnSetText(wxCommandEvent &event)
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

void CDevicesList::SetTextEvent(int icon_id)
{
	wxCommandEvent evt(EVT_SET_TEXT,ID_TEXT);
	evt.SetClientData(m_Reader);
	evt.SetInt(icon_id);
	wxPostEvent(this,evt);
}

void CDevicesList::OnSetLogger(wxCommandEvent &event)
{
//	SetLogger(event.GetString());
}

void CDevicesList::SetLoggerEvent()
{
/*		
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
	*/
}

void CDevicesList::SetDevices()
{

	m_Devices->DeleteChildren(m_Root);
	
	for(size_t i = 0; i < m_MapPlugin->GetDevicesCount(); i++)
		AddTreeItem(i);
	
	m_Devices->ExpandAll();

}

void CDevicesList::SetDevicesData()
{

}