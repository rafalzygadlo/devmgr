#include "frame.h"
#include "conf.h"
#include "dll.h"
#include "serial.h"
#include "tools.h"
#include "config.h"
#include <wx/mstream.h>
#include "warning.h"


#include "NaviMapIOApi.h"

DEFINE_EVENT_TYPE(nvEVT_SET_LOG)
DEFINE_EVENT_TYPE(nvEVT_SET_PORT)
DEFINE_EVENT_TYPE(nvEVT_SET_BAUD)

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnButtonClose)
	EVT_BUTTON(ID_STOP,CMyFrame::OnButtonStop)
	EVT_BUTTON(ID_START,CMyFrame::OnButtonStart)
	EVT_BUTTON(ID_NEW,CMyFrame::OnButtonNew)
	EVT_BUTTON(ID_DELETE,CMyFrame::OnButtonDelete)
	EVT_CLOSE(CMyFrame::OnClose)
	EVT_LISTBOX(ID_LIST,CMyFrame::OnList)
END_EVENT_TABLE()


CMyFrame::CMyFrame(CMapPlugin *_MapPlugin)
:wxDialog(NULL, wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{
	PortSelection = 0;
	MapPlugin = _MapPlugin;
	ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
	FileConfig = new wxFileConfig(_("devmgr"),wxEmptyString,ConfigPath,wxEmptyString);
	_Start = false;
	_Stop = false;
	_Close = false;
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(400,-1);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer *HSizerLeft = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(HSizerLeft,1,wxALL|wxEXPAND,5);
	DevicesList = new wxListCtrl(Panel,ID_LIST,wxDefaultPosition,wxSize(200,300),wxLC_REPORT);

	wxImageList *ImageListSmall = new wxImageList(20, 20, true);
		
	
	//wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    //wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_1);

	//wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    //wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_2);
	
	wxMemoryInputStream in_3((const unsigned char*)warning,warning_size);
    wxImage myImage_3(in_3, wxBITMAP_TYPE_PNG);
    ImageListSmall->Add(myImage_3);
	
	
	DevicesList->SetImageList(ImageListSmall, wxIMAGE_LIST_SMALL);
	
	wxListItem item;
	
	item.SetWidth(150); 
	item.SetText(_("Name")); 
	DevicesList->InsertColumn(0,item);
	
	item.SetWidth(50); 
	item.SetText(_("Port")); 
	DevicesList->InsertColumn(1,item);

	item.SetWidth(50);	
	item.SetText(_("Baud")); 
	DevicesList->InsertColumn(2,item);


	SetDevicesList();
	
	HSizerLeft->Add(DevicesList,1,wxALL|wxEXPAND,5);

	wxBoxSizer *HSizerRight = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(HSizerRight,0,wxALL|wxEXPAND,5);

	wxButton *NewDevice = new wxButton(Panel,ID_NEW,_("New"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(NewDevice,0,wxALL|wxALIGN_RIGHT,5);
	
	ButtonStart = new wxButton(Panel,ID_START,_("Start"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(ButtonStart,0,wxALL|wxALIGN_RIGHT,5);
	
	wxButton *ButtonConfig = new wxButton(Panel,ID_DELETE,_("Delete"),wxDefaultPosition,wxDefaultSize);
	HSizerRight->Add(ButtonConfig,0,wxALL|wxALIGN_RIGHT,5);
		
	wxButton *ButtonClose = new wxButton(this,ID_CLOSE,_("Close"),wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);

	Panel->SetSizer(PanelSizer);
		
	this->SetSizer(MainSizer);
	MainSizer->SetSizeHints(this);
}

CMyFrame::~CMyFrame(void)
{
	delete FileConfig;
}

void CMyFrame::SetDevicesList()
{
	DevicesList->DeleteAllItems();
	long idx = -1;
	
	for(size_t i = 0; i < MapPlugin->GetDevicesCount(); i++)
	{
		CMySerial *Serial = MapPlugin->GetDevice(i);
		wxString port(Serial->GetPortName(),wxConvUTF8);
		idx = DevicesList->InsertItem(DevicesList->GetItemCount(), Serial->GetDeviceName());
		DevicesList->SetItem(idx,1,wxString::Format(_("%s"),port.wc_str()));		
		DevicesList->SetItem(idx,2,wxString::Format(_("%d"),Serial->GetBaudRate()));		
	}
}


void CMyFrame::OnList(wxCommandEvent &event)
{
	CMySerial *Serial = MapPlugin->GetDevice(event.GetSelection());
	if(Serial->IsRunning())
	{
		SetButtonStart(_("Stop"),ID_STOP);
	
	}else{
		
		SetButtonStart(_("Start"),ID_START);
	}

}

void CMyFrame::SetButtonStart(wxString label,int id)
{
	ButtonStart->SetLabel(label);
	ButtonStart->SetId(id);
}

void CMyFrame::OnButtonClose(wxCommandEvent &event)
{
	_Close = true;
	//FileConfig->Write(_(KEY_PORT),wxString::Format(_("COM%d"),MapPlugin->GetMySerial()->GetPortName()));
	//FileConfig->Write(_(KEY_BAUD),MapPlugin->GetMySerial()->GetBaudRate());
	FileConfig->Flush();
	Close();

}

void CMyFrame::OnButtonStart(wxCommandEvent &event)
{
	int n_item = GetSelection();
	if(n_item == -1)
		return;

	CMySerial *Serial = MapPlugin->GetDevice(n_item);
	
	if(Serial == NULL)
		return;
		
	Serial->Start();
}

long CMyFrame::GetSelection()
{
	long n_item = DevicesList->GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	return n_item;
}

void CMyFrame::OnButtonStop(wxCommandEvent &event)
{
	int n_item = GetSelection();
	if(n_item == -1)
		return;

	CMySerial *Serial = MapPlugin->GetDevice(n_item);
	if(Serial == NULL)
		return;
	
	Serial->Stop();
}

void CMyFrame::OnButtonDelete(wxCommandEvent &event)
{
	int n_item = GetSelection();
	if(n_item == -1)
		return;

	CMySerial *Serial = MapPlugin->GetDevice(n_item);
	
	if(Serial == NULL)
		return;

	wxString port(Serial->GetPortName(),wxConvUTF8);
	wxMessageDialog  dlg(this,wxString::Format(_("Delete device on %s"),port.wc_str()),wxEmptyString,wxOK | wxCANCEL);
	
	if(dlg.ShowModal() == wxID_CANCEL)
		return;


	if(Serial->IsRunning())
		Serial->Stop();

	
	
	MapPlugin->DeleteDevice(n_item);
	SetDevicesList();

}

void CMyFrame::OnButtonNew(wxCommandEvent &event)
{
	CMyConfig *MyConfig = new CMyConfig(this,this);

	if(MyConfig->ShowModal() == wxID_CANCEL)
	{
		delete MyConfig;
		return;
	}
	
	wxString str(MyConfig->GetPort());
	MapPlugin->NewDevice(str.char_str(),MyConfig->GetBaud());
	SetDevicesList();

	delete MyConfig;
}




void CMyFrame::OnClose(wxCloseEvent &event)
{
	Destroy();
}

