#include "conf.h"
#include "wizard.h"
#include "thread.h"
#include "tools.h"
#include "talkers.h"
#include "serial_port.h"


BEGIN_EVENT_TABLE(CWizard,wxDialog)
	EVT_BUTTON(ID_START,CWizard::OnButtonStart)
END_EVENT_TABLE()


CWizard::CWizard()
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION)
{
	SetGui();
}	

void CWizard::SetGui()
{
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText *Text = new wxStaticText(this,wxID_ANY,GetMsg(MSG_DEVICE_WIZARD));
	MainSizer->Add(Text,0,wxALL,10);
	
	wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(HSizer,0,wxALL|wxEXPAND,5);
	
	m_ListBox = new wxListBox(this,wxID_ANY,wxDefaultPosition,wxSize(200,250));
	HSizer->Add(m_ListBox,0,wxALL|wxEXPAND,5);
	m_ButtonStart = new wxButton(this,ID_START,GetMsg(MSG_START));
	HSizer->Add(m_ButtonStart,0,wxALL|wxALIGN_RIGHT,10);
	
	m_LogBox = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(-1,120),wxTE_MULTILINE);
	MainSizer->Add(m_LogBox,0,wxALL|wxEXPAND,5);

	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);
	ButtonSizer->AddStretchSpacer(1);
	wxButton *ButtonOk = new wxButton(this,wxID_OK,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);


	this->SetSizer(MainSizer);
	MainSizer->SetSizeHints(this);
	Center();
}

CWizard::~CWizard()
{

}

void CWizard::Start()
{
	m_ButtonStart->Disable();
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

	m_ButtonStart->Enable();
	delete Serial;
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
			wxString port(m_Searcher->GetPortName(),wxConvUTF8);
			wxString talker(Talker->name,wxConvUTF8);
			m_ListBox->Append(wxString::Format(_("%s %d %s"),port.wc_str(),m_Searcher->GetBaudRate(),talker.wc_str()));
		}

	}
	
	
	//{
		//		wxString port(Searcher->GetPortName(),wxConvUTF8);
			//	m_ListBox->Append(wxString::Format(_("%s %d"),port.wc_str(),Searcher->GetBaudRate()));
			//}
}


void CWizard::OnButtonStart(wxCommandEvent &event)
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