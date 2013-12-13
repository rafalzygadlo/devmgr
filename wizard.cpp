#include "conf.h"
#include "wizard.h"
#include "thread.h"
#include "tools.h"
#include "talkers.h"
#include "serial_port.h"


BEGIN_EVENT_TABLE(CWizard,wxDialog)
	EVT_BUTTON(ID_1_NEXT,CWizard::OnButton1Next)
	EVT_BUTTON(ID_2_PREV,CWizard::OnButton2Prev)
	EVT_BUTTON(ID_2_NEXT,CWizard::OnButton2Next)
END_EVENT_TABLE()


CWizard::CWizard()
:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(500,400), wxCAPTION)
{
	SetGui();
}	

CWizard::~CWizard()
{

}

void CWizard::SetGui()
{
	m_MainSizer = new wxBoxSizer(wxVERTICAL);
	
	m_Page1 = Page1();
	m_MainSizer->Add(m_Page1,0,wxALL|wxEXPAND,5);
	m_Page2 = Page2();
	m_MainSizer->Add(m_Page2,0,wxALL|wxEXPAND,5);
	
	m_Page2->Hide();
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);
	ButtonSizer->AddStretchSpacer(1);
	
	wxButton *ButtonClose = new wxButton(this,wxID_OK,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
	
	this->SetSizer(m_MainSizer);
	m_MainSizer->SetSizeHints(this);
	Center();
}

wxPanel *CWizard::Page1()
{
	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxStaticText *Text = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DEVICE_WIZARD));
	PanelSizer->Add(Text,0,wxALL,10);
		
	m_LogBox = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,200),wxTE_MULTILINE);
	PanelSizer->Add(m_LogBox,0,wxALL|wxEXPAND,5);

	m_ButtonP1Next = new wxButton(Panel,ID_1_NEXT,GetMsg(MSG_NEXT));
	PanelSizer->Add(m_ButtonP1Next,0,wxALL|wxALIGN_RIGHT,5);

	return Panel;
}

wxPanel *CWizard::Page2()
{
	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);

	wxStaticText *Text = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DEVICE_WIZARD));
	PanelSizer->Add(Text,0,wxALL,10);

	m_ListBox = new wxListBox(Panel,wxID_ANY,wxDefaultPosition,wxSize(300,200),NULL,wxLB_MULTIPLE);
	PanelSizer->Add(m_ListBox,0,wxALL|wxEXPAND,5);
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	PanelSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,0);
	ButtonSizer->AddStretchSpacer(1);
	
	m_ButtonP2Prev = new wxButton(Panel,ID_2_PREV,GetMsg(MSG_PREV));
	ButtonSizer->Add(m_ButtonP2Prev,0,wxALL|wxALIGN_RIGHT,5);

	m_ButtonP2Next = new wxButton(Panel,ID_2_NEXT,GetMsg(MSG_NEXT));
	ButtonSizer->Add(m_ButtonP2Next,0,wxALL|wxALIGN_RIGHT,5);

	return Panel;
}

void CWizard::Start()
{
	m_ButtonP1Next->Disable();
	
	m_ListBox->Clear();
	CSerial *Serial = new CSerial();
    Serial->ScanPorts();
    m_Count = Serial->GetPortInfoLength();
	m_BaudCount = Serial->GetBaudInfoLength() - 1;
    
	for(int i = 0; i < m_Count; i++)
    {
		for(int j = 0; j < m_BaudCount; j++)
		{
			char *port_name = Serial->GetPortInfo(i).port_name;
			
			m_Searcher = new CSearcher(this);
			m_Searcher->_SetPort(port_name);
			m_Searcher->SetParseLine(true);
			m_Searcher->SetCheckCRC(true);
			m_Searcher->SetBaud(m_Searcher->GetBaudInfo(j));
			m_Searcher->Start();
			
			wxString port(port_name,wxConvUTF8);
			m_LogBox->AppendText(wxString::Format(_("Scaning %s %d\n"),port.wc_str(),m_Searcher->GetBaudInfo(j)));

			WaitForSingleObject(m_Searcher->GetHandle(),INFINITE);
			
			SetDeviceType();
			delete m_Searcher;
		}
		
    }

	m_ButtonP1Next->Enable();
	delete Serial;

	m_Page1->Hide();
	m_Page2->Show();
	
	m_MainSizer->SetSizeHints(this);
	this->Layout();
}

void CWizard::SetDeviceType()
{
	CTalkers Talkers;
	
	int count = m_Searcher->GetTalkerCount();
	STalkers *Talker = NULL;
	
	for(size_t i = 0; i < count; i++)
	{
		Talker = Talkers.GetByIdTalker(m_Searcher->GetTalker(i));
		if(Talker)
		{
			if(Talker->id_device > -1)
			{
				CMySerial *Serial = new CMySerial();
				Serial->_SetPort(m_Searcher->GetPortName());
				Serial->SetBaud(m_Searcher->GetBaudRate());
				Serial->SetDeviceType(Talker->id_device);
				vDevices.push_back(Serial);
				wxString port(m_Searcher->GetPortName(),wxConvUTF8);
				wxString talker(Talker->name,wxConvUTF8);
				m_ListBox->Append(wxString::Format(_("%s %d %s"),port.wc_str(),m_Searcher->GetBaudRate(),talker.wc_str()));
			}
			
		}

	}

}


void CWizard::OnButton2Next(wxCommandEvent &event)
{
	for(size_t i = 0; i < m_ListBox->GetCount(); i++)
	{
		m_ListBox->GetSelection();
	}
}

void CWizard::OnButton2Prev(wxCommandEvent &event)
{
	m_Page1->Show();
	m_Page2->Hide();
	m_MainSizer->SetSizeHints(this);
	this->Layout();
}

void CWizard::OnButton1Next(wxCommandEvent &event)
{
	CThread *Thread = new CThread(this);
	Thread->SetWorkId(WORK_WIZARD);
	Thread->Start();
}

void CWizard::ThreadBegin(int work_id)
{
	switch(work_id)
	{
		case WORK_WIZARD: Start(); break;
	}
}

void CWizard::ThreadEnd(int work_id)
{
	switch(work_id)
	{
		case WORK_WIZARD: break;
	}
}