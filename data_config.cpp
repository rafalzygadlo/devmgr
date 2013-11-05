#include "conf.h"
#include "dll.h"
#include "data_config.h"
#include "markers.h"
//#include "NaviMapIOApi.h"

BEGIN_EVENT_TABLE(CDataConfig,wxDialog)
	EVT_BUTTON(ID_CLOSE,CDataConfig::OnCloseButton)
	EVT_BUTTON(ID_NEW,CDataConfig::OnButtonNew)
	EVT_CHECKLISTBOX(ID_MARKER,CDataConfig::OnMarkerCheck )
END_EVENT_TABLE()


CDataConfig::CDataConfig(CMySerial *serial)
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize )
{
	m_Serial = serial;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(400,300);

	wxPanel *Panel1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	m_Marker = new wxCheckListBox(Panel1,ID_MARKER);
	Panel1Sizer->Add(m_Marker,1,wxALL|wxEXPAND,5);
		
	for(size_t i = 0; i < (size_t)GetLen(); i++)
	{
		TDataDefinition_s *item = GetItem(i);
		wxString marker(item->Marker,wxConvUTF8);
		wxString name(item->Name,wxConvUTF8);
		m_Marker->Append(wxString::Format(_("[%s] - %s"),marker.wc_str(),name.wc_str()));
	}

	wxBoxSizer *VSizer = new wxBoxSizer(wxVERTICAL);
	Panel1Sizer->Add(VSizer,0,wxALL|wxEXPAND,0);

	wxButton *ButtonNew = new wxButton(Panel1,ID_NEW,GetMsg(MSG_NEW));
	VSizer->Add(ButtonNew,0,wxALL,5);

	wxButton *ButtonDelete = new wxButton(Panel1,ID_DELETE,GetMsg(MSG_DELETE));
	VSizer->Add(ButtonDelete,0,wxALL,5);
	
	this->SetSizer(MainSizer);

	MainSizer->Add(Panel1,1,wxALL|wxEXPAND,5);
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

CDataConfig::~CDataConfig(void)
{

}

bool CDataConfig::Validate()
{
	return true;	
}

void CDataConfig::ShowWindow(bool show)
{
	Show(show);
}

void CDataConfig::OnButtonNew(wxCommandEvent &event)
{

}

void CDataConfig::OnMarkerCheck(wxCommandEvent &event)
{
	TDataDefinition_s *item = GetItem(event.GetSelection());
	m_Serial->AddMarker(*item);

}


void CDataConfig::OnCloseButton(wxCommandEvent &event)
{	
	Hide();
}

void CDataConfig::OnClose(wxCloseEvent &event)
{
	Destroy();
}
