#include "conf.h"
#include "dll.h"
#include "data_config.h"
#include "devices.h"
//#include "NaviMapIOApi.h"

BEGIN_EVENT_TABLE(CDataConfig,wxDialog)
	EVT_BUTTON(ID_CLOSE,CDataConfig::OnCloseButton)
	EVT_BUTTON(ID_NEW,CDataConfig::OnButtonNew)
	EVT_CHECKLISTBOX(ID_MARKER,CDataConfig::OnMarkerCheck )
	EVT_LISTBOX(ID_MARKER,CDataConfig::OnMarkerList)
END_EVENT_TABLE()


CDataConfig::CDataConfig(CMySerial *serial)
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize )
{
	m_Serial = serial;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(400,300);

	wxPanel *Panel1 = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Panel1->SetBackgroundColour(*wxWHITE);
	MainSizer->Add(Panel1,1,wxALL|wxEXPAND,0);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	m_Marker = new wxCheckListBox(Panel1,ID_MARKER,wxDefaultPosition,wxDefaultSize,NULL);
	Panel1Sizer->Add(m_Marker,1,wxALL|wxEXPAND,5);
		
	Sort();
	for(size_t i = 0; i < (size_t)GetLen(); i++)
	{
		TDataDefinition_s *item = GetItem(i);
		wxString name(item->Name,wxConvUTF8);
		int id = m_Marker->Append(wxString::Format(_("%s"),name.wc_str()));

	//	m_Marker->SetClientObject(id, (wxClientData*)item);
		if(m_Serial->GetMarker(item->DataID) != NULL)
			m_Marker->Check(id,true);
	}

	m_InfoPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_InfoPanel->Hide();
	MainSizer->Add(m_InfoPanel,0,wxALL|wxEXPAND,5);
	wxBoxSizer *InfoPanelSizer = new wxBoxSizer(wxVERTICAL);
	m_InfoPanel->SetSizer(InfoPanelSizer);

	LabelId = new wxStaticText(m_InfoPanel,wxID_ANY,wxEmptyString);
	InfoPanelSizer->Add(LabelId,0,wxALL|wxEXPAND,2);
	
	LabelName = new wxStaticText(m_InfoPanel,wxID_ANY,wxEmptyString);
	InfoPanelSizer->Add(LabelName,0,wxALL|wxEXPAND,2);
	
	LabelMarker = new wxStaticText(m_InfoPanel,wxID_ANY,wxEmptyString);
	InfoPanelSizer->Add(LabelMarker,0,wxALL|wxEXPAND,2);
	
	wxBoxSizer *VSizer = new wxBoxSizer(wxVERTICAL);
	Panel1Sizer->Add(VSizer,0,wxALL|wxEXPAND,0);

	wxButton *ButtonNew = new wxButton(Panel1,ID_NEW,GetMsg(MSG_NEW));
	VSizer->Add(ButtonNew,0,wxALL,5);

	wxButton *ButtonDelete = new wxButton(Panel1,ID_DELETE,GetMsg(MSG_DELETE));
	VSizer->Add(ButtonDelete,0,wxALL,5);
	
	this->SetSizer(MainSizer);


	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
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

void CDataConfig::OnMarkerList(wxCommandEvent &event)
{
	m_InfoPanel->Show();
	this->Layout();

	TDataDefinition_s *item = GetItem(event.GetSelection());

	wxString id = wxString::Format(_("%d"),item->DataID);
	wxString name(item->Name,wxConvUTF8);
	wxString marker(item->Marker,wxConvUTF8);

	LabelId->SetLabel(id);
	LabelName->SetLabel(name);
	LabelMarker->SetLabel(marker);
	GetSizer()->SetSizeHints(this);
}

void CDataConfig::OnCloseButton(wxCommandEvent &event)
{	
	Hide();
}

void CDataConfig::OnClose(wxCloseEvent &event)
{
	Destroy();
}
