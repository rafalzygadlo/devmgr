#include <wx/settings.h>
#include <wx/statline.h>
#include "conf.h"
#include "config.h"
#include "info.h"


BEGIN_EVENT_TABLE(CConfig,wxDialog)
	EVT_BUTTON(ID_CLOSE,OnCloseButton)
	EVT_HYPERLINK(ID_REFRESH,OnScanPorts)
	EVT_COMBOBOX(ID_CONNECTION_TYPE,OnConnectionType)
	EVT_COMBOBOX(ID_DEVICE_TYPE,OnDeviceType)
END_EVENT_TABLE()


CConfig::CConfig()
	:wxDialog(NULL,wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{
	ConnectionType = CONNECTION_TYPE_SERIAL;
	Reader = new CReader();

	MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(300,-1);
						
	this->SetSizer(MainSizer);
	
	ConnectionTypeCombo = new wxComboBox(this,ID_CONNECTION_TYPE,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,wxCB_READONLY);
	ConnectionTypeCombo->Append(GetMsg(MSG_DEVICE_TYPE_SOCKET));
	ConnectionTypeCombo->Append(GetMsg(MSG_DEVICE_TYPE_SERIAL));
	MainSizer->Add(ConnectionTypeCombo,0,wxALL|wxEXPAND,5); 

	SerialPanel = GetSerialPanel();
	SocketPanel = GetSocketPanel();
	DevicePanel = GetDeviceTypePanel();
	SocketPanel->Hide();
	
	ConnectionTypeCombo->SetSelection(CONNECTION_TYPE_SERIAL);
	MainSizer->Add(SerialPanel,0,wxALL|wxEXPAND,5);
	MainSizer->Add(SocketPanel,0,wxALL|wxEXPAND,5);
	MainSizer->Add(DevicePanel,0,wxALL|wxEXPAND,5);

	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
	ButtonSizer->AddStretchSpacer(1);
	
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);
	ButtonSizer->AddStretchSpacer(1);
	wxButton *ButtonOk = new wxButton(this,wxID_OK,GetMsg(MSG_OK),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);

	wxButton *ButtonCancel = new wxButton(this,wxID_CANCEL,GetMsg(MSG_CANCEL),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);

	MainSizer->SetSizeHints(this);
	Center();
		
}	

CConfig::~CConfig(void)
{
	delete Reader;
}

wxPanel *CConfig::GetDeviceTypePanel()
{
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	wxFlexGridSizer *FlexGrid1Sizer = new wxFlexGridSizer(2);
	FlexGrid1Sizer->AddGrowableCol(1);
	PanelSizer->Add(FlexGrid1Sizer,1,wxALL|wxEXPAND,10);
	
	for(size_t i = 0; i < Reader->GetBaudInfoLength(); i++)
		BaudCombo->Append(wxString::Format(_("%d"),Reader->GetBaudInfo(i)));

	wxStaticText *DeviceType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DEVICE_TYPE));
	FlexGrid1Sizer->Add(DeviceType,0,wxALL,5);
	DeviceTypeCombo = new wxComboBox(Panel,ID_DEVICE_TYPE,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,wxCB_READONLY);
	FlexGrid1Sizer->Add(DeviceTypeCombo,0,wxALL,5);

	DeviceTypeCombo->Clear();
	CDevices *Devices = new CDevices();
		
	size_t len = Devices->GetLen();
	for(size_t i = 0; i < len; i++)
	{
		SDevices * device = Devices->Get(i);
		wxString name(device->name,wxConvUTF8);
		DeviceTypeCombo->SetClientData(device);
		DeviceTypeCombo->Append(name);
	}				
	
	delete Devices;

	return Panel;
}


wxPanel *CConfig::GetSerialPanel()
{
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer *FlexGrid1Sizer = new wxFlexGridSizer(2);
	FlexGrid1Sizer->AddGrowableCol(1);
	PanelSizer->Add(FlexGrid1Sizer,1,wxALL|wxEXPAND,10);
	
	wxStaticText *NameLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DEVICE_NAME));
	FlexGrid1Sizer->Add(NameLabel,0,wxALL,5);
	SerialNameText = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(SerialNameText,0,wxALL|wxEXPAND,5);

	wxStaticText *PortLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_PORT));
	FlexGrid1Sizer->Add(PortLabel,0,wxALL,5);

	wxBoxSizer *PortSizer = new wxBoxSizer(wxVERTICAL);
	PortCombo = new wxComboBox(Panel,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(PortSizer,0,wxALL,0);
	PortSizer->Add(PortCombo,0,wxALL,5);
	//wxStaticText *ScanInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_PORT_INFO));
	//PortSizer->Add(ScanInfo,0,wxALL|wxEXPAND,5);
	wxHyperlinkCtrl *Scan = new wxHyperlinkCtrl(Panel,ID_REFRESH,GetMsg(MSG_SCAN),wxEmptyString);
	PortSizer->Add(Scan,0,wxALL,5);
	
	Panel->SetSizer(PanelSizer);
		
	wxStaticText *BaudLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BAUD));
	FlexGrid1Sizer->Add(BaudLabel,0,wxALL,5);
	BaudCombo = new wxComboBox(Panel,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(BaudCombo,0,wxALL,5);
	
	return Panel;
}

wxPanel *CConfig::GetSocketPanel()
{
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxFlexGridSizer *FlexGrid1Sizer = new wxFlexGridSizer(2);
	FlexGrid1Sizer->AddGrowableCol(1);
	PanelSizer->Add(FlexGrid1Sizer,1,wxALL|wxEXPAND,10);
	
	wxStaticText *NameLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DEVICE_NAME));
	FlexGrid1Sizer->Add(NameLabel,0,wxALL,5);
	SocketNameText = new wxTextCtrl(Panel,wxID_ANY,_(DEFAULT_SOCKET_NAME));
	FlexGrid1Sizer->Add(SocketNameText,0,wxALL|wxEXPAND,5);
	
	wxStaticText *HostLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_HOST));
	FlexGrid1Sizer->Add(HostLabel,0,wxALL,5);
	HostText = new wxTextCtrl(Panel,wxID_ANY,_(DEFAULT_SOCKET_HOST));
	FlexGrid1Sizer->Add(HostText,0,wxALL|wxEXPAND,5);
	
	//wxStaticText *UserLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_USER));
	//FlexGrid1Sizer->Add(UserLabel,0,wxALL,5);
	//UserText = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	//FlexGrid1Sizer->Add(UserText,0,wxALL|wxEXPAND,5);

	//wxStaticText *PassLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_PASS));
	//FlexGrid1Sizer->Add(PassLabel,0,wxALL,5);
	//PassText = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	//FlexGrid1Sizer->Add(PassText,0,wxALL|wxEXPAND,5);
		
	wxStaticText *PortLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_PORT));
	FlexGrid1Sizer->Add(PortLabel,0,wxALL,5);
	PortText = new wxTextCtrl(Panel,wxID_ANY,_(DEFAULT_SOCKET_PORT));
	//PortText->SetValue(wxString::Format(_("%d"),SOCKET_DEFAULT_PORT));
	FlexGrid1Sizer->Add(PortText,0,wxALL,5);
			
	//wxStaticText *MountLabel = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_MOUNT));
	//FlexGrid1Sizer->Add(MountLabel,0,wxALL,5);
	//MountText = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	//FlexGrid1Sizer->Add(MountText,0,wxALL,5);

	return Panel;
}


bool CConfig::Validate()
{
	bool result = true;

	switch(ConnectionType)
	{
		case CONNECTION_TYPE_SERIAL:	return ValidateSerial();
		case CONNECTION_TYPE_SOCKET:	return ValidateSocket();

	}

	return false;
}


bool CConfig::ValidateSerial()
{
	bool result = true;

	if(SerialNameText->GetValue().empty())
	{
		SerialNameText->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		SerialNameText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	}

	if(PortCombo->GetValue().empty())
	{
		PortCombo->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		PortCombo->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	}

	if(BaudCombo->GetValue().empty())
	{
		BaudCombo->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		BaudCombo->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	}

	if(DeviceTypeCombo->GetValue().empty())
	{
		DeviceTypeCombo->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		DeviceTypeCombo->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	}
	
	
	
	Refresh();
	
	return result;
}

bool CConfig::ValidateSocket()
{

	bool result = true;

	if(SocketNameText->GetValue().empty())
	{
		SocketNameText->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		SocketNameText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	}

	if(HostText->GetValue().empty())
	{
		HostText->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		HostText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	}

	if(PortText->GetValue().empty())
	{
		PortText->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		PortText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	}

	if(DeviceTypeCombo->GetValue().empty())
	{
		DeviceTypeCombo->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		DeviceTypeCombo->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	}
	

	Refresh();
	
	return result;


}

wxString CConfig::GetHost()
{
	return HostText->GetValue();
}

int CConfig::GetDeviceType()
{
	return DeviceType;
}

int CConfig::GetConnectionType()
{
	return ConnectionType;
}

void CConfig::ShowConnectionPanel(int type)
{
	SocketPanel->Hide();
	SerialPanel->Hide();
	

	if(type == CONNECTION_TYPE_SOCKET)
	{
		SocketPanel->Show();
		MainSizer->SetSizeHints(this);
		this->Layout();
	}

	if(type == CONNECTION_TYPE_SERIAL)
	{
		SerialPanel->Show();
		MainSizer->SetSizeHints(this);
		this->Layout();
	}

}

void CConfig::OnDeviceType(wxCommandEvent &event)
{
	DeviceType = event.GetSelection();
}


void CConfig::OnConnectionType(wxCommandEvent &event)
{
	ConnectionType = event.GetSelection();
	ShowConnectionPanel(event.GetSelection());
}

void CConfig::OnScanPorts(wxHyperlinkEvent &event)
{
	wxWindowDisabler();
	CMyInfo Info(this,GetMsg(MSG_SCANNING_PORTS));
	Reader->ScanPorts();
	wxString value = PortCombo->GetValue();
	PortCombo->Clear();
	
	for(size_t i = 0; i < Reader->GetPortInfoLength(); i++)
	{
		wxString port(Reader->GetPortInfo(i).port_name,wxConvUTF8);
		PortCombo->Append(wxString::Format(_("%s"),port.wc_str()));
	}

	PortCombo->SetValue(value);
}

wxString CConfig::GetDeviceName()
{
	if(ConnectionType == CONNECTION_TYPE_SOCKET)
		return SocketNameText->GetValue();
	if(ConnectionType == CONNECTION_TYPE_SERIAL)
		return SerialNameText->GetValue();
	
	return wxEmptyString;
}

wxString CConfig::GetSerialPort()
{
	return PortCombo->GetValue();
}

wxString CConfig::GetSocketPort()
{
	return PortText->GetValue();
}

int CConfig::GetBaud()
{
	long val;
	BaudCombo->GetValue().ToLong(&val);
	
	return val;
}

void CConfig::SetPort(char *port)
{
	wxString str(port,wxConvUTF8);
	PortCombo->SetValue(str);
}

void CConfig::SetBaud(int baud)
{
	BaudCombo->SetValue(wxString::Format(_("%d"),baud));
}

void CConfig::SetPort(int port)
{
	PortText->SetValue(wxString::Format(_("%d"),port));
}

void CConfig::SetHost(char *host)
{
	wxString str(host,wxConvUTF8);
	HostText->SetValue(str);
}

void CConfig::SetDeviceName(wxString name)
{
	switch(ConnectionType)
	{
		case CONNECTION_TYPE_SERIAL:	SerialNameText->SetLabel(name); break;
		case CONNECTION_TYPE_SOCKET:	SocketNameText->SetLabel(name); break;
	}
}

void CConfig::SetConnectionType(int type)
{
	ConnectionType = type;
	ConnectionTypeCombo->SetSelection(type);
	//ConnectionTypeCombo->Disable();
	ShowConnectionPanel(type);
}

void CConfig::SetDeviceType(int type)
{
	DeviceType = type;
	DeviceTypeCombo->SetSelection(type);
	
}

void CConfig::ShowWindow(bool show)
{
	Show(show);
}

void CConfig::OnCloseButton(wxCommandEvent &event)
{	
	Hide();
}

void CConfig::OnClose(wxCloseEvent &event)
{
	Destroy();
}