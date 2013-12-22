#include <wx/settings.h>
#include <wx/wx.h>
#include <wx/statline.h>
#include "NaviMapIOApi.h"
#include "conf.h"
#include "dll.h"
#include "config.h"
#include "info.h"
#include "protocol.h"


BEGIN_EVENT_TABLE(CConfig,wxDialog)
	EVT_BUTTON(ID_CLOSE,OnCloseButton)
	EVT_HYPERLINK(ID_REFRESH,OnScanPorts)
END_EVENT_TABLE()


CConfig::CConfig()
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize )
{
	mySerial = new CMySerial();

	MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(300,-1);
	
	wxPanel *Panel1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel1->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer *FlexGrid1Sizer = new wxFlexGridSizer(2);
	FlexGrid1Sizer->AddGrowableCol(1);
	Panel1Sizer->Add(FlexGrid1Sizer,1,wxALL|wxEXPAND,10);
	
	wxStaticText *NameLabel = new wxStaticText(Panel1,wxID_ANY,GetMsg(MSG_DEVICE_NAME));
	FlexGrid1Sizer->Add(NameLabel,0,wxALL,5);
	NameText = new wxTextCtrl(Panel1,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(NameText,0,wxALL|wxEXPAND,5);


	wxStaticText *PortLabel = new wxStaticText(Panel1,wxID_ANY,GetMsg(MSG_PORT));
	FlexGrid1Sizer->Add(PortLabel,0,wxALL,5);

	wxBoxSizer *PortSizer = new wxBoxSizer(wxVERTICAL);
	PortCombo = new wxComboBox(Panel1,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(PortSizer,0,wxALL,0);
	PortSizer->Add(PortCombo,0,wxALL,5);
	wxStaticText *ScanInfo = new wxStaticText(Panel1,wxID_ANY,GetMsg(MSG_PORT_INFO));
	PortSizer->Add(ScanInfo,0,wxALL|wxEXPAND,5);
	wxHyperlinkCtrl *Scan = new wxHyperlinkCtrl(Panel1,ID_REFRESH,GetMsg(MSG_SCAN),wxEmptyString);
	PortSizer->Add(Scan,0,wxALL,5);
	
	Panel1->SetSizer(Panel1Sizer);
		
	wxStaticText *BaudLabel = new wxStaticText(Panel1,wxID_ANY,GetMsg(MSG_BAUD));
	FlexGrid1Sizer->Add(BaudLabel,0,wxALL,5);
	BaudCombo = new wxComboBox(Panel1,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(BaudCombo,0,wxALL,5);
	
	for(size_t i = 0; i < mySerial->GetBaudInfoLength(); i++)
		BaudCombo->Append(wxString::Format(_("%d"),mySerial->GetBaudInfo(i)));


	wxStaticText *DeviceType = new wxStaticText(Panel1,wxID_ANY,GetMsg(MSG_DEVICE_TYPE));
	FlexGrid1Sizer->Add(DeviceType,0,wxALL,5);
	DeviceTypeCombo = new wxComboBox(Panel1,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,wxCB_READONLY);
	FlexGrid1Sizer->Add(DeviceTypeCombo,0,wxALL,5);

	CDevices *Devices = new CDevices();
	//Devices->Sort();
	
	size_t len = Devices->GetLen();
	for(size_t i = 0; i < len; i++)
	{
		SDevices * device = Devices->Get(i);
		wxString name(device->name,wxConvUTF8);
		DeviceTypeCombo->SetClientData(device);
		DeviceTypeCombo->Append(name);
	}				
	
	delete Devices;
	
	this->SetSizer(MainSizer);
	
	MainSizer->Add(Panel1,1,wxALL|wxEXPAND,0);
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
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
	delete mySerial;
}

bool CConfig::Validate()
{
	bool result = true;
	
	if(NameText->GetValue().empty())
	{
		NameText->SetBackgroundColour(*wxRED);
		result = false;
	}else{
		NameText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
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

void CConfig::OnScanPorts(wxHyperlinkEvent &event)
{
	wxWindowDisabler();
	CMyInfo Info(this,GetMsg(MSG_SCANNING_PORTS));
	mySerial->ScanPorts();
	wxString value = PortCombo->GetValue();
	PortCombo->Clear();
	
	for(size_t i = 0; i < mySerial->GetPortInfoLength(); i++)
	{
		wxString port(mySerial->GetPortInfo(i).port_name,wxConvUTF8);
		PortCombo->Append(wxString::Format(_("%s"),port.wc_str()));
	}

	PortCombo->SetValue(value);
}

wxString CConfig::GetDeviceName()
{
	return NameText->GetValue();
}

wxString CConfig::GetPort()
{
	return PortCombo->GetValue();
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

void CConfig::SetDeviceName(wxString name)
{
	NameText->SetLabel(name);
}

int CConfig::GetDeviceType()
{
	return DeviceTypeCombo->GetSelection();
}

void CConfig::SetDeviceType(int type)
{
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