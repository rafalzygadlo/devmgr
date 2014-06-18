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
	EVT_BUTTON(ID_3_PREV,CWizard::OnButton3Prev)
END_EVENT_TABLE()

CWizard::CWizard()
:wxDialog(NULL,wxID_ANY, GetMsg(MSG_DEVICE_WIZARD), wxDefaultPosition, wxSize(500,400), wxCAPTION)
{
	m_Found = false;
	m_Count = 0;
	m_Counter = 0;
	SetGui();
}

CWizard::~CWizard()
{
	for(size_t i = 0; i < vDevices.size(); i++)
	{
		delete 	vDevices[i];
	}
	
	vDevices.clear();
}

void CWizard::SetGui()
{
	m_MainSizer = new wxBoxSizer(wxVERTICAL);
	
	m_Page1 = Page1();
	m_MainSizer->Add(m_Page1,0,wxALL|wxEXPAND,5);
	m_Page2 = Page2();
	m_MainSizer->Add(m_Page2,0,wxALL|wxEXPAND,5);
	m_Page3 = Page3();
	m_MainSizer->Add(m_Page3,0,wxALL|wxEXPAND,5);
	
	m_Page2->Hide();
	m_Page3->Hide();
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_MainSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
			
	m_ButtonClose = new wxButton(this,wxID_CANCEL,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(m_ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
	
	this->SetSizer(m_MainSizer);
	m_MainSizer->SetSizeHints(this);
	Center();
}

wxPanel *CWizard::Page1()
{
	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	m_Page1Text = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DEVICE_WIZARD));
	PanelSizer->Add(m_Page1Text,0,wxALL,5);
		
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

	m_Page2Text = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NO_DEVICE_FOUND));
	PanelSizer->Add(m_Page2Text,0,wxALL,5);

	m_ListBox = new wxListBox(Panel,wxID_ANY,wxDefaultPosition,wxSize(300,200),0,NULL, wxLB_MULTIPLE);
	//m_ListBox->set
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

wxPanel *CWizard::Page3()
{
	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);

	m_Page3Text = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DEVICE_WIZARD));
	PanelSizer->Add(m_Page3Text,0,wxALL,5);

	m_NewListBox = new wxListBox(Panel,wxID_ANY,wxDefaultPosition,wxSize(300,200),NULL);
	PanelSizer->Add(m_NewListBox,0,wxALL|wxEXPAND,5);
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	PanelSizer->Add(ButtonSizer,0,wxALL|wxEXPAND,0);
	ButtonSizer->AddStretchSpacer(1);
	
	m_ButtonP3Prev = new wxButton(Panel,ID_3_PREV,GetMsg(MSG_PREV));
	ButtonSizer->Add(m_ButtonP3Prev,0,wxALL|wxALIGN_RIGHT,5);

	m_ButtonP3Next = new wxButton(Panel,wxID_OK,GetMsg(MSG_FINISH));
	ButtonSizer->Add(m_ButtonP3Next,0,wxALL|wxALIGN_RIGHT,5);

	return Panel;
}


void CWizard::Start()
{
	m_Counter = 0;
	m_ButtonP1Next->Disable();
	m_ButtonClose->Disable();
	m_ListBox->Clear();
	CSerial *Serial = new CSerial();
    Serial->ScanPorts();
    m_Count = Serial->GetPortInfoLength();
	m_BaudCount = Serial->GetBaudInfoLength();
	m_LogBox->Clear();
    
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
			m_LogBox->AppendText(wxString::Format(GetMsg(MSG_SCANNING) ,port.wc_str(),m_Searcher->GetBaudInfo(j)));

			WaitForSingleObject(m_Searcher->GetHandle(),INFINITE);
			
			SetDeviceType();
			delete m_Searcher;
		}
		
    }

	if(m_Found)
	{
		m_ButtonP2Next->Enable();
		m_Page2Text->SetLabel(wxString::Format(GetMsg(MSG_DEVICE_FOUND),m_Counter));
	}else{
		m_ButtonP2Next->Disable();
	}
	
	m_ButtonP1Next->Enable();
	m_ButtonClose->Enable();
	
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
		m_Found = true;
		Talker = Talkers.GetByIdTalker(m_Searcher->GetTalker(i));
		if(Talker)
		{
			if(Talker->id_device > -1)
			{
				CReader *Reader = new CReader();
				Reader->SetPort(m_Searcher->GetPortName());
				Reader->SetBaud(m_Searcher->GetBaudRate());
				Reader->SetDeviceType(Talker->id_device);
				
				CDevices devices;
				wxString talker(devices.GetById(Talker->id_device)->name ,wxConvUTF8);
				Reader->SetDeviceName(talker);
				vDevices.push_back(Reader);
				wxString port(m_Searcher->GetPortName(),wxConvUTF8);
				
				m_ListBox->Append(wxString::Format(_("%s %d %s"),port.wc_str(),m_Searcher->GetBaudRate(),talker.wc_str()));
				m_Counter++;
			}
			
		}

	}

}

size_t CWizard::GetCount()
{
	return vNewDevices.size();
}

CReader *CWizard::GetDevice(int id)
{
	return vNewDevices[id];
}

void CWizard::OnButton3Prev(wxCommandEvent &event)
{
	
	m_Page2->Show();
	m_Page3->Hide();
	m_MainSizer->SetSizeHints(this);
	this->Layout();

}

void CWizard::OnButton2Next(wxCommandEvent &event)
{
	
	wxArrayInt items;
	m_ListBox->GetSelections(items);
	m_NewListBox->Clear();
	vNewDevices.clear();

	for(size_t i = 0; i < items.size(); i++)
	{
		int id = items[i];
		CReader *ptr = vDevices[id];	
		vNewDevices.push_back(vDevices[id]);
		wxString port(ptr->GetPortName(),wxConvUTF8);
		CDevices devices;
		wxString talker(devices.GetById(ptr->GetDeviceType())->name ,wxConvUTF8);
		m_NewListBox->Append(wxString::Format(_("%s %d %s"),port.wc_str(),ptr->GetBaudRate(),talker.wc_str()));
	}

	m_Page3Text->SetLabel(wxString::Format(GetMsg(MSG_SELECTED_DEVICES),items.size()));
	m_Page2->Hide();
	m_Page3->Show();
	m_MainSizer->SetSizeHints(this);
	this->Layout();

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