#include <wx/wx.h>
#include <wx/notebook.h>

#include "conf.h"
#include "tools.h"
#include "ais_list.h"
#include "listctrl.h"
#include "ais.h"
#include "thread.h"

BEGIN_EVENT_TABLE(CAisList,wxPanel)
	EVT_TIMER(ID_TIMER,OnTimer)
	EVT_SEARCHCTRL_SEARCH_BTN(ID_SEARCH,OnSearchButton)
	EVT_TEXT(ID_SEARCH,OnSearchText)
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
	m_Timer->Start(2000);
	SetList();
}

CAisList::~CAisList()
{
	m_Timer->Stop();
	delete m_Timer;
}

void CAisList::OnTimer(wxTimerEvent &event)
{
	SetList();
	//fprintf(stdout,"%d\n",c);
}

void CAisList::SetSignal(int signal)
{
	switch(signal)
	{
		case CLEAR_AIS_LIST:	ClearList();	break;
	}
}

void CAisList::ClearList()
{
	m_List->SetItemCount(0);
}

void CAisList::SetList()
{
	int count = ais_get_search_item_count();

	if(count > 0)
		m_List->SetItemCount(count);
	else
		m_List->SetItemCount(ais_get_item_count());
}

void CAisList::SetHtml(wxString html)
{
	m_Html->AppendToPage(html);
}

void CAisList::ClearHtml()
{
	m_Html->SetPage(wxEmptyString);
}

void CAisList::ShowHtmlPanel()
{
	m_Html->Show();
	m_Page1Sizer->Layout();
}

void CAisList::OnSearchButton(wxCommandEvent &event)
{
	CThread *Thread = new CThread(this);
	Thread->SetWorkId(WORK_SEARCH);
	Thread->Start();
}

void CAisList::OnSearchText(wxCommandEvent &event)
{
	CThread *Thread = new CThread(this);
	Thread->SetWorkId(WORK_SEARCH);
	Thread->Start();

}

void CAisList::ThreadBegin()
{
	ais_set_search_buffer(m_SearchText->GetValue().char_str());
}

void CAisList::ThreadEnd()
{
	int c = ais_get_search_item_count();
	m_List->SetItemCount(c);
	m_List->Refresh();
}

void CAisList::GetPanel()
{

	wxBoxSizer *m_Sizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Sizer->Add(Notebook,1,wxALL|wxEXPAND,0);
	wxPanel *Page1 = new wxPanel(Notebook);
	m_Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(m_Page1Sizer);
	Notebook->AddPage(Page1,GetMsg(MSG_AIS_TARGETS));

	m_SearchText = new wxSearchCtrl(Page1,ID_SEARCH,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);
	m_Page1Sizer->Add(m_SearchText,0,wxALL|wxEXPAND,0);
	//m_SearchText->SetValue(m_SearchText);

	m_List = new CListCtrl(Page1,this,wxLC_REPORT | wxLC_HRULES | wxLC_VIRTUAL);
	wxListItem item;
	item.SetWidth(65);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(0,item);
	item.SetWidth(65);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(1,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_SHIPNAME));	m_List->InsertColumn(2,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(3,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(4,item);
	m_Page1Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	m_Html = new wxHtmlWindow(Page1,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Page1Sizer->Add(m_Html,1,wxALL|wxEXPAND,0);
	m_Html->Hide();

	this->SetSizer(m_Sizer);

}