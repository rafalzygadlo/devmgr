#include "conf.h"
#include "dll.h"
#include "device_config.h"
#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include <wx/hyperlink.h>
#include <wx/settings.h>

BEGIN_EVENT_TABLE(CDeviceConfig,wxDialog)
	EVT_BUTTON(ID_CLOSE,CDeviceConfig::OnCloseButton)
END_EVENT_TABLE()


CDeviceConfig::CDeviceConfig()
	:wxDialog(NULL,wxID_ANY, _("Device"), wxDefaultPosition, wxDefaultSize )
{
	
	MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(300,-1);
	
	wxPanel *Panel1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel1->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer *FlexGrid1Sizer = new wxFlexGridSizer(2);
	FlexGrid1Sizer->AddGrowableCol(1);
	Panel1Sizer->Add(FlexGrid1Sizer,1,wxALL|wxEXPAND,10);
	
	wxStaticText *NameLabel = new wxStaticText(Panel1,wxID_ANY,_("Name:"));
	FlexGrid1Sizer->Add(NameLabel,0,wxALL,5);
	NameText = new wxTextCtrl(Panel1,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(NameText,0,wxALL|wxEXPAND,5);


	wxStaticText *PortLabel = new wxStaticText(Panel1,wxID_ANY,_("Port:"));
	FlexGrid1Sizer->Add(PortLabel,0,wxALL,5);
	PortCombo = new wxComboBox(Panel1,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(PortCombo,0,wxALL,5);


	Panel1->SetSizer(Panel1Sizer);
	CMySerial *mySerial = new CMySerial();
	mySerial->ScanPorts();

	for(size_t i = 0; i < mySerial->GetPortInfoLength(); i++)
	{
		wxString port(mySerial->GetPortInfo(i).port_name,wxConvUTF8);
		PortCombo->Append(wxString::Format(_("%s"),port.wc_str()));
	}
		
	wxStaticText *BaudLabel = new wxStaticText(Panel1,wxID_ANY,_("Baud:"));
	FlexGrid1Sizer->Add(BaudLabel,0,wxALL,5);
	BaudCombo = new wxComboBox(Panel1,wxID_ANY,wxEmptyString);
	FlexGrid1Sizer->Add(BaudCombo,0,wxALL,5);
	
	for(size_t i = 0; i < mySerial->GetBaudInfoLength(); i++)
		BaudCombo->Append(wxString::Format(_("%d"),mySerial->GetBaudInfo(i)));

	delete mySerial;
				
	this->SetSizer(MainSizer);
	
	MainSizer->Add(Panel1,1,wxALL|wxEXPAND,0);
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);
	ButtonSizer->AddStretchSpacer(1);
	wxButton *ButtonOk = new wxButton(this,wxID_OK,_("Ok"),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);

	wxButton *ButtonCancel = new wxButton(this,wxID_CANCEL,_("Cancel"),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);

	MainSizer->SetSizeHints(this);
	Center();
		
}	

CDeviceConfig::~CDeviceConfig(void)
{

}

bool CDeviceConfig::Validate()
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
	
	
	Refresh();
	
	return result;
}

wxString CDeviceConfig::GetDeviceName()
{
	return NameText->GetValue();
}

wxString CDeviceConfig::GetPort()
{
	return PortCombo->GetValue();
}

int CDeviceConfig::GetBaud()
{
	long val;
	BaudCombo->GetValue().ToLong(&val);
	
	return val;
}

void CDeviceConfig::SetPort(char *port)
{
	wxString str(port,wxConvUTF8);
	PortCombo->SetValue(str);
}

void CDeviceConfig::SetBaud(int baud)
{
	BaudCombo->SetValue(wxString::Format(_("%d"),baud));
}

void CDeviceConfig::SetDeviceName(wxString name)
{
	NameText->SetLabel(name);
}

void CDeviceConfig::ShowWindow(bool show)
{
	Show(show);
}

void CDeviceConfig::OnCloseButton(wxCommandEvent &event)
{	
	Hide();
}

void CDeviceConfig::OnClose(wxCloseEvent &event)
{
	Destroy();
}