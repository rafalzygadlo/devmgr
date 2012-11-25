#include "frame.h"
#include "conf.h"
#include "dll.h"
#include "serial.h"
#include "tools.h"
#include <wx/statline.h>
#include "NaviMapIOApi.h"

DEFINE_EVENT_TYPE(nvEVT_SET_LOG)
DEFINE_EVENT_TYPE(nvEVT_SET_PORT)
DEFINE_EVENT_TYPE(nvEVT_SET_BAUD)

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
	EVT_CLOSE(CMyFrame::OnClose)
	EVT_LISTBOX(ID_LIST,CMyFrame::OnList)
END_EVENT_TABLE()


CMyFrame::CMyFrame(CMapPlugin *_MapPlugin)
:wxDialog(NULL, wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{
	PortSelection = 0;
	MapPlugin = _MapPlugin;
	ConfigPath = wxString::Format(wxT("%s%s"),GetWorkDir().wc_str(),_(PLUGIN_CONFIG_FILE));
	FileConfig = new wxFileConfig(_("gps"),wxEmptyString,ConfigPath,wxEmptyString);
	_Start = false;
	_Stop = false;
	_Close = false;
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	
	wxListBox *list = new wxListBox(Panel,ID_LIST,wxDefaultPosition,wxDefaultSize);

	for(size_t i =0; i < MapPlugin->GetDevicesCount(); i++)
	{
		CMySerial *Serial = MapPlugin->GetDevice(i);
		wxString port(Serial->GetPortName(),wxConvUTF8);
		list->Append(wxString::Format(_("%s - %d"),port.wc_str(),Serial->GetBaudRate()));
	}

	PanelSizer->Add(list,0,wxALL|wxEXPAND,5);

	// button close
	wxButton *ButtonClose = new wxButton(Panel,ID_CLOSE,_("Close"),wxDefaultPosition,wxDefaultSize);
	PanelSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);

	Panel->SetSizer(PanelSizer);

	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	this->SetSizer(MainSizer);

	
	Center();
}

CMyFrame::~CMyFrame(void)
{
	delete FileConfig;
}

void CMyFrame::OnList(wxCommandEvent &event)
{
	CMySerial *Serial = MapPlugin->GetDevice(event.GetSelection());
	if(Serial->IsRunning())
		Serial->Stop();
	else
		Serial->Start();
}

void CMyFrame::OnCloseButton(wxCommandEvent &event)
{
	_Close = true;
	//FileConfig->Write(_(KEY_PORT),wxString::Format(_("COM%d"),MapPlugin->GetMySerial()->GetPortName()));
	//FileConfig->Write(_(KEY_BAUD),MapPlugin->GetMySerial()->GetBaudRate());
	FileConfig->Flush();
	Close();

}
void CMyFrame::OnClose(wxCloseEvent &event)
{
	Destroy();
}

