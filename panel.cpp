#include "panel.h"
#include "conf.h"
#include <wx/listctrl.h>

BEGIN_EVENT_TABLE(CPanel,wxPanel)
END_EVENT_TABLE()

CPanel::CPanel(wxWindow *Parent)
	:wxPanel(Parent,wxID_ANY,wxDefaultPosition,wxDefaultSize )
{

	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(500,-1);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer *HSizerLeft = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(HSizerLeft,1,wxALL|wxEXPAND,5);
	m_DevicesList = new wxListCtrl(Panel,ID_LIST,wxDefaultPosition,wxSize(-1,200),wxLC_REPORT);

		
	wxListItem item;
	
	item.SetWidth(150); 
	item.SetText(_("Name")); 
	m_DevicesList->InsertColumn(0,item);
	
	item.SetWidth(50); 
	item.SetText(_("Port")); 
	m_DevicesList->InsertColumn(1,item);

	item.SetWidth(50);	
	item.SetText(_("Baud")); 
	m_DevicesList->InsertColumn(2,item);
		
	
	HSizerLeft->Add(m_DevicesList,1,wxALL|wxEXPAND,5);

	wxBoxSizer *HSizerRight = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(HSizerRight,0,wxALL|wxEXPAND,5);

	wxButton *NewDevice = new wxButton(Panel,ID_NEW,_("New"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(NewDevice,0,wxALL|wxALIGN_RIGHT,2);
	
	m_ButtonStart = new wxButton(Panel,ID_START,_("Start"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(m_ButtonStart,0,wxALL|wxALIGN_RIGHT,2);

	m_ButtonStop = new wxButton(Panel,ID_STOP,_("Stop"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(m_ButtonStop,0,wxALL|wxALIGN_RIGHT,2);

	wxButton *ButtonConfig = new wxButton(Panel,ID_DELETE,_("Delete"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(ButtonConfig,0,wxALL|wxALIGN_RIGHT,2);
		
	m_DeviceLog = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(-1,200),wxTE_MULTILINE);
	MainSizer->Add(m_DeviceLog,0,wxALL|wxEXPAND,5);

	wxButton *ButtonClose = new wxButton(this,ID_CLOSE,_("Close"),wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);

	Panel->SetSizer(PanelSizer);
		
	this->SetSizer(MainSizer);
	MainSizer->SetSizeHints(this);
	
}


CPanel::~CPanel()
{

}

void CPanel::SetDevice(CSerial *dev)
{
	m_Serial = dev;
}

void CPanel::OnButtonStart(wxCommandEvent &event)
{
	m_Serial->Start();
}

void CPanel::SetButtons(CMySerial *Serial)
{
	if(Serial->IsRunning())
	{
		m_ButtonStart->Enable(false);
		m_ButtonStop->Enable(true);
		
	}else{
		
		m_ButtonStart->Enable(true);
		m_ButtonStop->Enable(false);
	}

}
