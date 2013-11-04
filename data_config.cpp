#include "conf.h"
#include "dll.h"
#include "data_config.h"
#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include <wx/hyperlink.h>
#include <wx/settings.h>

BEGIN_EVENT_TABLE(CDataConfig,wxDialog)
	EVT_BUTTON(ID_CLOSE,CDataConfig::OnCloseButton)
	EVT_COMBOBOX(ID_SIGNAL,CDataConfig::OnComboSignal)
	EVT_TEXT(ID_NMEA,CDataConfig::OnNMEAText)
END_EVENT_TABLE()


CDataConfig::CDataConfig(CMySerial *serial)
	:wxDialog(NULL,wxID_ANY, _("New Device"), wxDefaultPosition, wxDefaultSize )
{
	Serial = serial;
	MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(300,-1);
	
	wxPanel *Panel1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxVERTICAL);
	Panel1->SetSizer(Panel1Sizer);
		
	
	wxComboBox *Signal = new wxComboBox(Panel1,ID_SIGNAL);
	Panel1Sizer->Add(Signal,0,wxALL|wxEXPAND,5);
	
	for(size_t i = 0; i < serial->GetSignalCount(); i++)
	{
		wxString name((char*)serial->GetSignal(i)->name,wxConvUTF8);
		Signal->Append(name);
	}
	
	NMEA = new wxTextCtrl(Panel1,ID_NMEA,wxEmptyString,wxDefaultPosition,wxSize(400,-1));
//	NMEA->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CDataConfig::OnTextClick), NULL, this);
	Panel1Sizer->Add(NMEA,0,wxALL|wxEXPAND,5);


	this->SetSizer(MainSizer);
	
	MainSizer->Add(Panel1,1,wxALL|wxEXPAND,5);
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

CDataConfig::~CDataConfig(void)
{

}

bool CDataConfig::Validate()
{
	return true;	
}

//wxString CDataConfig::GetDataDefinition()
//{
//	return DataDefinition->GetValue();
//}

void CDataConfig::ShowWindow(bool show)
{
	Show(show);
}

void CDataConfig::OnCloseButton(wxCommandEvent &event)
{	
	Hide();
}

void CDataConfig::OnClose(wxCloseEvent &event)
{
	Destroy();
}

void CDataConfig::OnComboSignal(wxCommandEvent &event)
{
	wxString nmea((char*)Serial->GetSignal(event.GetSelection())->nmea,wxConvUTF8);
	NMEA->SetValue(nmea);
}

void CDataConfig::OnNMEAText(wxCommandEvent &event)
{
	int id = event.GetSelection();

	wxCaret *caret =  NMEA->GetCaret();

	//caret
}