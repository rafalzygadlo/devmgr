#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include <wx/hyperlink.h>
#include <wx/settings.h>
#include "conf.h"
#include "dll.h"
#include "status.h"
#include "NaviMapIOApi.h"

BEGIN_EVENT_TABLE(CStatus,wxDialog)
	EVT_BUTTON(ID_CLOSE,OnCloseButton)
	EVT_CHECKBOX(ID_SHOW_LOG,OnShowLog)
END_EVENT_TABLE()


CStatus::CStatus()
	:wxDialog(NULL,wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{

	MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(300,-1);
	
	wxPanel *Panel1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel1->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxVERTICAL);
	
	Panel1->SetSizer(Panel1Sizer);
		
	m_Status = new wxTextCtrl(Panel1,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(400,100),wxTE_MULTILINE | wxTE_READONLY);
	Panel1Sizer->Add(m_Status,0,wxALL|wxEXPAND,0);
		
	m_ShowLog = new wxCheckBox(Panel1,ID_SHOW_LOG,GetMsg(MSG_SHOW_LOG),wxDefaultPosition,wxDefaultSize);
	Panel1Sizer->Add(m_ShowLog,0,wxALL,5);

	m_NMEA = new wxTextCtrl(Panel1,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(400,200),wxTE_MULTILINE | wxTE_READONLY | wxTE_DONTWRAP);
	Panel1Sizer->Add(m_NMEA,0,wxALL|wxEXPAND,0);

	this->SetSizer(MainSizer);
	
	MainSizer->Add(Panel1,1,wxALL|wxEXPAND,0);
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
	ButtonSizer->AddStretchSpacer(1);
		
	wxButton *ButtonOk = new wxButton(this,wxID_OK,GetMsg(MSG_OK),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
			
	MainSizer->SetSizeHints(this);
	Center();
		
}	

CStatus::~CStatus(void)
{
	
}

void CStatus::SetReader(CReader *ptr)
{
	Reader = ptr;
	m_Status->Clear();
	m_NMEA->Clear();
	wxString port(ptr->GetPortName(),wxConvUTF8);
	
	int type = ptr->GetConnectionType();

	if(ptr->GetIsRunning())
		m_Status->AppendText(wxString::Format(_("%s: %s\n"),GetMsg(MSG_IS_RUNNING),GetMsg(MSG_YES)));
	else
		m_Status->AppendText(wxString::Format(_("%s: %s\n"),GetMsg(MSG_IS_RUNNING),GetMsg(MSG_NO)));


	if(ptr->IsConnected())
		m_Status->AppendText(wxString::Format(_("%s: %s\n"),GetMsg(MSG_IS_CONNECTED),GetMsg(MSG_YES)));
	else
		m_Status->AppendText(wxString::Format(_("%s: %s\n"),GetMsg(MSG_IS_CONNECTED),GetMsg(MSG_NO)));
		
	if(type == CONNECTION_TYPE_SERIAL)
	{
		wxString port(ptr->GetPortName(),wxConvUTF8);

		m_Status->AppendText(wxString::Format(_("%s: %s\n"),GetMsg(MSG_PORT),port.wc_str()));
		m_Status->AppendText(wxString::Format(_("%s: %d\n"),GetMsg(MSG_BAUD),ptr->GetBaudRate()));
	}
	
	if(type == CONNECTION_TYPE_SOCKET)
	{
		wxString host(ptr->GetHost(),wxConvUTF8);
		m_Status->AppendText(wxString::Format(_("%s: %s\n"),GetMsg(MSG_HOST),host.wc_str()));
		m_Status->AppendText(wxString::Format(_("%s: %d\n"),GetMsg(MSG_PORT),ptr->GetPort()));
	}
	
	m_Status->AppendText(wxString::Format(_("%s: %d\n"),GetMsg(MSG_BAD_CRC),ptr->GetBadCRC()));

	if(ptr->GetLinesCount() == 0)
		m_Status->AppendText(_("N/A"));
	else
		m_Status->AppendText(wxString::Format(_("%s: %d%%\n\n"),GetMsg(MSG_SIGNAL_QUALITY),ptr->GetSignalQuality()));

	for(size_t i = 0; i < ptr->GetSignalCount();i++)
	{
		wxString name((char*)ptr->GetSignal(i)->name,wxConvUTF8);
		m_Status->AppendText(wxString::Format(_("%s\n"),name.wc_str()));
	}
}


void CStatus::AppendText(wxString text)
{
	m_NMEA->AppendText(text);
}

void CStatus::SetShowLog(bool val)
{
	m_ShowLog->SetValue(val);
}

void CStatus::OnShowLog(wxCommandEvent &event)
{
	Reader->SetLineEvent(event.GetSelection());
}

void CStatus::ShowWindow(bool show)
{
	Show(show);
}

void CStatus::OnCloseButton(wxCommandEvent &event)
{	
	Hide();
}

void CStatus::OnClose(wxCloseEvent &event)
{
	Destroy();
}
