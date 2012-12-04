#include "frame.h"
#include "conf.h"
#include "dll.h"
#include "serial.h"
#include "tools.h"
#include "config.h"
#include <wx/mstream.h>
#include "warning.h"


#include "NaviMapIOApi.h"

DEFINE_EVENT_TYPE(nvEVT_SET_ITEM)

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnButtonClose)
//	EVT_BUTTON(ID_STOP,CMyFrame::OnButtonStop)
//	EVT_BUTTON(ID_START,CMyFrame::OnButtonStart)
//	EVT_BUTTON(ID_NEW,CMyFrame::OnButtonNew)
//	EVT_BUTTON(ID_DELETE,CMyFrame::OnButtonDelete)
	EVT_CLOSE(CMyFrame::OnClose)
//	EVT_COMMAND(ID_SET_ITEM,nvEVT_SET_ITEM,CMyFrame::OnSetItem)	//my own defined event
//	EVT_LIST_ITEM_ACTIVATED(ID_LIST,CMyFrame::OnActivate)
//	EVT_LIST_ITEM_SELECTED(ID_LIST,CMyFrame::OnSelected)
END_EVENT_TABLE()


CMyFrame::CMyFrame(CMapPlugin *_MapPlugin)
:wxDialog(NULL, wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{
	PortSelection = 0;
	m_MapPlugin = _MapPlugin;
	m_ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
	m_FileConfig = new wxFileConfig(_("devmgr"),wxEmptyString,m_ConfigPath,wxEmptyString);
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(500,-1);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer *HSizerLeft = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(HSizerLeft,1,wxALL|wxEXPAND,5);
//	m_DevicesList = new wxListCtrl(Panel,ID_LIST,wxDefaultPosition,wxSize(-1,200),wxLC_REPORT);

	wxImageList *ImageListSmall = new wxImageList(20, 20, true);
		
	
	//wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    //wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_1);

	//wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    //wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_2);
	
	//wxMemoryInputStream in_3((const unsigned char*)warning,warning_size);
    //wxImage myImage_3(in_3, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_3);
	
	
	//m_DevicesList->SetImageList(ImageListSmall, wxIMAGE_LIST_SMALL);
	
	wxListItem item;
	
	item.SetWidth(150); 
	item.SetText(_("Name")); 
	//m_DevicesList->InsertColumn(0,item);
	
	item.SetWidth(50); 
	item.SetText(_("Port")); 
	//m_DevicesList->InsertColumn(1,item);

	item.SetWidth(50);	
	item.SetText(_("Baud")); 
	//m_DevicesList->InsertColumn(2,item);
		
	//SetDevicesList();
	
	//HSizerLeft->Add(m_DevicesList,1,wxALL|wxEXPAND,5);

	wxBoxSizer *HSizerRight = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(HSizerRight,0,wxALL|wxEXPAND,5);

	wxButton *NewDevice = new wxButton(Panel,ID_NEW,_("New"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(NewDevice,0,wxALL|wxALIGN_RIGHT,2);
	
	//m_ButtonStart = new wxButton(Panel,ID_START,_("Start"),wxDefaultPosition,wxDefaultSize);
	//HSizerRight->Add(m_ButtonStart,0,wxALL|wxALIGN_RIGHT,2);

	//m_ButtonStop = new wxButton(Panel,ID_STOP,_("Stop"),wxDefaultPosition,wxDefaultSize);
	//HSizerRight->Add(m_ButtonStop,0,wxALL|wxALIGN_RIGHT,2);

	wxButton *ButtonConfig = new wxButton(Panel,ID_DELETE,_("Delete"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(ButtonConfig,0,wxALL|wxALIGN_RIGHT,2);
		
	//m_DeviceLog = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(-1,200),wxTE_MULTILINE);
	//MainSizer->Add(m_DeviceLog,0,wxALL|wxEXPAND,5);

	wxButton *ButtonClose = new wxButton(this,ID_CLOSE,_("Close"),wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);

	Panel->SetSizer(PanelSizer);
		
	this->SetSizer(MainSizer);
	MainSizer->SetSizeHints(this);
}

CMyFrame::~CMyFrame(void)
{
	delete m_FileConfig;
}


void CMyFrame::OnButtonClose(wxCommandEvent &event)
{
	
	//FileConfig->Write(_(KEY_PORT),wxString::Format(_("COM%d"),MapPlugin->GetMySerial()->GetPortName()));
	//FileConfig->Write(_(KEY_BAUD),MapPlugin->GetMySerial()->GetBaudRate());
	//m_FileConfig->Flush();
	Close();

}

void CMyFrame::SetDeviceStatus(CMySerial *Serial)
{
	wxCommandEvent evt(nvEVT_SET_ITEM,ID_SET_ITEM);
	evt.SetInt(Serial->GetDeviceId());
	evt.SetString(_("Reconnect"));
    wxPostEvent(this,evt);
}

void CMyFrame::OnClose(wxCloseEvent &event)
{
	Hide();
	//Destroy();
}

