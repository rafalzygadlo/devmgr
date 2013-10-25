#include <wx/mstream.h>
#include "conf.h"
#include "devices.h"
#include "serialreader.h"
#include "tools.h"
#include "start.h"
#include "stop.h"
#include "computer.h"
#include "info.h"
#include "deviceconfig.h"
#include "status.h"

BEGIN_EVENT_TABLE(CDevices,wxPanel)
	EVT_TREE_ITEM_MENU(ID_DEVICE,OnTreeMenu)
	EVT_TREE_SEL_CHANGED(ID_DEVICE,OnItemActivated)
	EVT_MENU(ID_STOP,OnStop)
	EVT_MENU(ID_START,OnStart)
	EVT_MENU(ID_CONFIGURE_DEVICE,OnConfigureDevice)
	EVT_MENU(ID_UNINSTALL,OnUninstall)
	EVT_MENU(ID_ADD,OnAdd)
	EVT_MENU(ID_STATUS,OnStatus)
END_EVENT_TABLE()

CDevices::CDevices(CDisplayPlugin *parent, wxString key_name, bool writer)
:wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize ) 
{
	SelectedDevice = NULL;
	Parent = parent;
	KeyName = key_name;
	Writer = writer;
	SetGui();
	ReadConfig();
}

CDevices::~CDevices(void)
{
	WriteConfig();
		
	for(size_t i = 0; i < vDevices.size(); i++)
	{
		if(vDevices[i]->GetIsRunning())
		{
			CMyInfo Info(NULL,wxString::Format(GetMsg(MSG_STOPPING_DEVICE),vDevices[i]->GetDeviceName()));
			vDevices[i]->Stop();
			wxMilliSleep(50);
		}
		
		delete vDevices[i];
	}
    
}

void CDevices::WriteConfig()
{
	FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigPath(),wxEmptyString);
	wxString name,port;
	int baud;
	bool running;
	
	FileConfig->DeleteGroup(KeyName);
	
	for(size_t i = 0; i < vDevices.size(); i++)
	{
	
		CSerialReader *Serial = vDevices[i];
		name = Serial->GetDeviceName();
		running = Serial->GetIsRunning();
		wxString port(Serial->GetPortName(),wxConvUTF8);
		baud = Serial->GetBaudRate();
		wxString index = wxString::Format(_("%d"),i);
						
		FileConfig->Write(wxString::Format(_("%s/%s/%s"),KeyName,index,_(KEY_NAME)),name);
		FileConfig->Write(wxString::Format(_("%s/%s/%s"),KeyName,index,_(KEY_PORT)),port);
		FileConfig->Write(wxString::Format(_("%s/%s/%s"),KeyName,index,_(KEY_BAUD)),baud);
		FileConfig->Write(wxString::Format(_("%s/%s/%s"),KeyName,index,_(KEY_RUNNING)),running);
	
	}
	
	delete FileConfig;
	
}

void CDevices::ReadConfig()
{
	FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigPath(),wxEmptyString);
	size_t len = FileConfig->GetNumberOfGroups();
	
	wxArrayString devices = GetDevicesConfig(KeyName);
	wxString port, device, data, name;
	int baud;
	bool running;
	
	for(size_t i = 0; i < devices.size(); i++)
	{
		wxString index = wxString::Format(_("%d"),i);				
		FileConfig->Read(wxString::Format(_("%s/%s/%s"),KeyName,index,_(KEY_NAME)),&name);
		FileConfig->Read(wxString::Format(_("%s/%s/%s"),KeyName,index,_(KEY_PORT)),&port);
		FileConfig->Read(wxString::Format(_("%s/%s/%s"),KeyName,index,_(KEY_BAUD)),&baud);
		FileConfig->Read(wxString::Format(_("%s/%s/%s"),KeyName,index,_(KEY_RUNNING)),&running);

		CSerialReader *serial = CreateNewDevice(name,port.char_str(),baud,running);
				
		AddDevice(serial);
	
	}
			
	delete FileConfig;
	Devices->ExpandAll();
	
}


size_t CDevices::GetDevicesCount()
{
	return vDevices.size();
}

CSerialReader *CDevices::GetDevice(size_t idx)
{
	if(idx > vDevices.size())
		return NULL;
	else
		return vDevices[idx];
}


void CDevices::AddDevice(CSerialReader *serial)
{
	GetMutex()->Lock();

	vDevices.push_back(serial);

	serial->SetDeviceId(vDevices.size() - 1);
	serial->SetParentFrame(Parent);
	serial->SetWriter(Writer);
	serial->SetCheckCRC(true);
	
	if(serial->GetRunOnStart())
		serial->Start();

	int count =	GetDevicesCount() - 1;
	CSerialReader *Serial = GetDevice(count);
	wxString port(Serial->GetPortName(),wxConvUTF8);
	int icon_id = 0;

	bool running = false;
	if(Serial->GetIsRunning())
	{
		icon_id = 1;
		running = true;
	}
	
	wxTreeItemId id = Devices->AppendItem(Root,wxString::Format(_("%s"),Serial->GetDeviceName()),icon_id);
	Devices->SetItemBold(id,running);
	CItem *Item = new CItem();
	Item->SetSerial(Serial);
	Devices->SetItemData(id,Item);

	GetMutex()->Unlock();

}

wxArrayString CDevices::GetDevicesConfig(wxString path)
{
    
    wxArrayString Names;
    long dummy;

    wxString old_path = FileConfig->GetPath();
    FileConfig->SetPath(path);

    bool bCont = FileConfig->GetFirstGroup(path, dummy);

    while ( bCont )
    {
        Names.Add(path);
        bCont = FileConfig->GetNextGroup(path, dummy);
    }

    FileConfig->SetPath(old_path);
    
	return Names;
}

void CDevices::OnTreeMenu(wxTreeEvent &event)
{
	SelectedItemId = event.GetItem();
	if(!SelectedItemId.IsOk())
		return;
	
	SelectedItem = (CItem*)Devices->GetItemData(event.GetItem());

	if(SelectedItem == NULL)
	{
		wxMenu *Menu = new wxMenu();
		Menu->Append(ID_ADD,GetMsg(MSG_NEW_DEVICE));
		PopupMenu(Menu);
		delete Menu;
		return;
	}

	
	CSerialReader *Serial = SelectedItem->GetSerial();
	SelectedDevice = Serial;
	wxMenu *Menu = new wxMenu(wxString::Format(_("%s"),Serial->GetDeviceName().wc_str()));
		
	Menu->Append(ID_START,GetMsg(MSG_START));
	Menu->Append(ID_STOP,GetMsg(MSG_STOP));
	Menu->AppendSeparator();
	Menu->Append(ID_CONFIGURE_DEVICE,GetMsg(MSG_CONFIGURE_DEVICE));
	Menu->AppendSeparator();
	//Menu->Append(ID_STATUS,GetMsg(MSG_STATUS));
	Menu->Append(ID_UNINSTALL,GetMsg(MSG_UNINSTALL));

	bool running = SelectedDevice->GetIsRunning();
	Menu->Enable(ID_CONFIGURE_DEVICE,!running);
	Menu->Enable(ID_STOP,running);
	Menu->Enable(ID_START,!running);
	PopupMenu(Menu);
	
	delete Menu;
	event.Skip();

}

void CDevices::OnItemActivated(wxTreeEvent &event)
{
	SelectedItem = (CItem*)Devices->GetItemData(event.GetItem());

	if(SelectedItem == NULL)
		return;
		
	SelectedDevice = SelectedItem->GetSerial();
	
	Parent->ClearStatus();

	wxString port(SelectedDevice->GetPortName(),wxConvUTF8);
	Parent->SetStatus(wxString::Format(_("%s: %s\n"),GetMsg(MSG_PORT).wc_str(),port.wc_str()));
	Parent->SetStatus(wxString::Format(_("%s: %d\n"),GetMsg(MSG_BAUD).wc_str(),SelectedDevice->GetBaudRate()));

	if(SelectedDevice->IsConnected())
		Parent->SetStatus(wxString::Format(_("%s\n"),GetMsg(MSG_CONNECTED).wc_str()));
	else
		Parent->SetStatus(wxString::Format(_("%s\n"),GetMsg(MSG_DISCONNECTED).wc_str()));
	
	//Parent->SetStatus(wxString::Format(_("%s: %d\n"),GetMsg(MSG_IS_RUNNING),SelectedDevice->GetIsRunning()));
	//Parent->SetStatus(wxString::Format(_("%s: %d\n"),GetMsg(MSG_LINES_WRITEN),SelectedDevice->GetLinesWriten()));

	for(size_t i = 0; i < SelectedDevice->GetSignalCount();i++)
	{
		wxString name((char*)SelectedDevice->GetSignal(i)->name,wxConvUTF8);
		Parent->SetStatus(wxString::Format(_("%s "),name.wc_str()));
	}

}

void CDevices::OnStop(wxCommandEvent &event)
{
	SelectedDevice->Stop();
	Devices->SetItemBold(SelectedItemId ,false);
	Devices->SetItemImage(SelectedItemId,0, wxTreeItemIcon_Normal);
}

void CDevices::OnStart(wxCommandEvent &event)
{
	SelectedDevice->Start();
	Devices->SetItemBold(SelectedItemId,true);
	Devices->SetItemImage(SelectedItemId,1, wxTreeItemIcon_Normal);
}

void CDevices::OnUninstall(wxCommandEvent &event)
{
	SelectedDevice->Stop();
	RemoveDevice(SelectedDevice);
}

void CDevices::OnConfigureDevice(wxCommandEvent &event)
{
	if(SelectedDevice->GetIsRunning())
	{
		wxMessageBox(GetMsg(MSG_STOP_THE_DEVICE));
		return;
	}
		
	CDeviceConfig *DeviceConfig = new CDeviceConfig();
	DeviceConfig->SetPort((char*)SelectedDevice->GetPortName());
	DeviceConfig->SetBaud(SelectedDevice->GetBaudRate());
	DeviceConfig->SetDeviceName(SelectedDevice->GetDeviceName());
		
	if(DeviceConfig->ShowModal() == wxID_OK)
	{
		SelectedDevice->SetPort(DeviceConfig->GetPort().char_str());
		SelectedDevice->SetBaud(DeviceConfig->GetBaud());
		SelectedDevice->SetDeviceName(DeviceConfig->GetDeviceName());
		Devices->SetItemText(SelectedItemId,DeviceConfig->GetDeviceName());
	}

	delete DeviceConfig;
}

void CDevices::RemoveDevice(CSerialReader *serial) 
{
	GetMutex()->Lock();
	
	for(size_t i = 0; i < vDevices.size(); i++)
	{
		if(vDevices[i] == serial)
		{
			vDevices[i]->Stop();
			delete vDevices[i];
			vDevices.erase(vDevices.begin() + i);
			SetDevices();
		}
	}

	ReindexDevices();

	GetMutex()->Unlock();
}

void CDevices::ReindexDevices()
{
	for(size_t i = 0; i < vDevices.size(); i++)
		vDevices[i]->SetDeviceId(i);
}


void CDevices::SetDevices() 
{
	Devices->DeleteChildren(Root);
	
	for(size_t i = 0; i < GetDevicesCount(); i++)
	{
		CSerialReader *Serial = GetDevice(i);
		wxString port(Serial->GetPortName(),wxConvUTF8);

		int icon_id = 0;
		if(Serial->GetIsRunning())
			icon_id = 1;

		wxTreeItemId id = Devices->AppendItem(Root,wxString::Format(_("%s"),Serial->GetDeviceName()),icon_id);
		Devices->SetItemBold(id,true);
		CItem *Item = new CItem();
		Item->SetSerial(Serial);
		Devices->SetItemData(id,Item);
	}
	
	Devices->ExpandAll();

}


void CDevices::OnAdd(wxCommandEvent &event)
{
	CDeviceConfig *DeviceConfig = new CDeviceConfig();

	if(DeviceConfig->ShowModal() == wxID_OK)
	{
		wxString name = wxString::Format(_("%s"),DeviceConfig->GetDeviceName().wc_str());
		CSerialReader *serial = CreateNewDevice(name, DeviceConfig->GetPort().char_str(), DeviceConfig->GetBaud(),true);
		AddDevice(serial);
		WriteConfig();
		
	}	

	delete DeviceConfig;
}

void CDevices::OnSetLogger(wxCommandEvent &event)
{

}

void CDevices::OnStatus(wxCommandEvent &event)
{
	CStatus *_Status = new CStatus(SelectedDevice);
	_Status->ShowModal();
	delete _Status;
}

void CDevices::SetRootName(wxString value)
{
	Devices->SetItemText(Root,value);
}

void CDevices::SetGui()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);

	wxImageList *ImageListSmall = new wxImageList(16, 16);
	Devices = new wxTreeCtrl(this,ID_DEVICE,wxDefaultPosition,wxSize(200,250));
	
	Root = Devices->AddRoot(GetMsg(MSG_DEVICES));
	Devices->SetItemImage(Root,2, wxTreeItemIcon_Normal);
	Sizer->Add(Devices,1,wxALL|wxEXPAND,10);

	wxMemoryInputStream in_1((const unsigned char*)stop,stop_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    	
	wxMemoryInputStream in_2((const unsigned char*)start,start_size);
    wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    
	wxMemoryInputStream in_3((const unsigned char*)computer,computer_size);
    wxImage myImage_3(in_3, wxBITMAP_TYPE_PNG);
    		
	ImageListSmall->Add(myImage_1);
	ImageListSmall->Add(myImage_2);
	ImageListSmall->Add(myImage_3);
	
	Devices->AssignImageList(ImageListSmall);
		
	this->SetSizer(Sizer);
	
}
