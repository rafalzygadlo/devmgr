#include <wx/wx.h>
#include <wx/notebook.h>
#include "conf.h"
#include "tools.h"
#include "ais_list.h"
#include "listctrl.h"
#include "ais.h"

BEGIN_EVENT_TABLE(CAisList,wxPanel)
	EVT_TIMER(ID_TIMER,OnTimer)
END_EVENT_TABLE()


CAisList::CAisList(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display) 
:wxPanel(parent)
{
	m_Broker = NULL;
	SetDoubleBuffered(true);
	m_Broker = plugin->GetBroker();
	m_Display = display;
	GetPanel();
	m_Timer = new wxTimer(this,ID_TIMER);
	m_Timer->Start(5000);

}

CAisList::~CAisList()
{
	m_Timer->Stop();
	delete m_Timer;
}

void CAisList::OnTimer(wxTimerEvent &event)
{
	int c = ais_get_item_count();
	fprintf(stdout,"%d\n",c);
	m_List->SetItemCount(c);
}

void CAisList::SetSignal(int signal)
{
	switch(signal)
	{
		case SIGNAL_NEW_AIS_OBJECT :	SetList();		break;
		case CLEAR_AIS_LIST:			ClearList();	break;
	}
}

void CAisList::ClearList()
{
	m_List->SetItemCount(0);
}

void CAisList::SetList()
{
	
}

void CAisList::GetPanel()
{
		
	wxBoxSizer *m_Sizer = new wxBoxSizer(wxVERTICAL);
		
	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Sizer->Add(Notebook,1,wxALL|wxEXPAND,0);
	wxPanel *Page1 = new wxPanel(Notebook);
	wxBoxSizer *Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(Page1Sizer);
	Notebook->AddPage(Page1,GetMsg(MSG_AIS_TARGETS));
	
	m_List = new CListCtrl(Page1,m_Display,wxLC_REPORT | wxLC_HRULES | wxLC_VIRTUAL);
	wxListItem item;
	item.SetWidth(65);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(0,item);	
	item.SetWidth(100);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(1,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(2,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(3,item);
	Page1Sizer->Add(m_List,1,wxALL|wxEXPAND,5);


	this->SetSizer(m_Sizer);
	
	
}