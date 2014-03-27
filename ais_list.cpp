#include <wx/wx.h>
#include <wx/notebook.h>

#include "conf.h"
#include "tools.h"
#include "ais_list.h"
#include "listctrl.h"
#include "ais.h"
#include "thread.h"
#include "options.h"

BEGIN_EVENT_TABLE(CAisList,wxPanel)
	EVT_TIMER(ID_TIMER,OnTimer)
	EVT_SEARCHCTRL_SEARCH_BTN(ID_SEARCH,OnSearchButton)
//	EVT_TEXT(ID_SEARCH,OnSearchText)
	EVT_TEXT_ENTER(ID_SEARCH,OnSearchEnter)
	EVT_CHECKBOX(ID_SHOW_NAMES,OnShowNames)
	EVT_CHECKBOX(ID_SHOW_COG,OnShowCOG)
	EVT_CHECKBOX(ID_SHOW_HDT,OnShowHDT)
	EVT_SLIDER(ID_FONT_SIZE,OnFontSize)
	EVT_COLOURPICKER_CHANGED(wxID_ANY,OnColorPicker)
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
	m_Working = false;
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
	int count = 0;
	count = ais_get_search_item_count();

	if(count > 0)
	{
		m_List->SetItemCount(count);
		m_List->SetSearch(true);
	
	}else{
	
		m_List->SetItemCount(ais_get_item_count());
		m_List->SetSearch(false);
	
	}
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
	//CThread *Thread = new CThread(this);
	//Thread->SetWorkId(WORK_SEARCH);
	//Thread->Start();
}

void CAisList::OnSearchEnter(wxCommandEvent &event)
{
	if(m_Working)
		return;

	m_Working = true;
	CThread *Thread = new CThread(this);
	Thread->SetWorkId(WORK_SEARCH);
	Thread->Start();

}

void CAisList::ThreadBegin()
{
	if(m_SearchText->GetValue().Length() > 0)
		ais_set_search_buffer(m_SearchText->GetValue().char_str());
	else
		ais_clear_search_buffer();
}

void CAisList::ThreadEnd()
{
	int c = ais_get_search_item_count();
	m_List->SetItemCount(c);
	m_List->Refresh();
	m_List->SetSearch(true);
	m_Working = false;
}

void CAisList::OnShowNames(wxCommandEvent &event)
{
	SetShowNames(event.GetSelection());
	
	if(m_Broker != NULL)
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnSynchro",NULL);
}

void CAisList::_SetShowNames(bool val)
{
	m_ShipNames->SetValue(val);
}

void CAisList::OnFontSize(wxCommandEvent &event)
{
	SetFontSize(event.GetInt());
	if(m_Broker != NULL)
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnSynchro",NULL);
}

void CAisList::_SetFontSize(int val)
{
	m_FontSize->SetValue(val);
}

void CAisList::OnShowCOG(wxCommandEvent &event)
{
	SetShowCOG(event.GetSelection());
	if(m_Broker != NULL)
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnSynchro",NULL);
}

void CAisList::OnShowHDT(wxCommandEvent &event)
{
	SetShowHDT(event.GetSelection());
	if(m_Broker != NULL)
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnSynchro",NULL);
}

void CAisList::OnColorPicker(wxColourPickerEvent &event)
{
	nvRGBA color;
	wxColor cl = event.GetColour();
		
	color.R = cl.Red();
	color.G = cl.Green();
	color.B = cl.Blue();

	switch(event.GetId())
	{
		case ID_SHIP_COLOR_0:	color.A = GetColor(SHIP_COLOR_0).A;	SetColor(SHIP_COLOR_0,color);	break;
		case ID_SHIP_COLOR_1:	color.A = GetColor(SHIP_COLOR_1).A;	SetColor(SHIP_COLOR_1,color);	break;
		case ID_ATON_COLOR:	    color.A = GetColor(ATON_COLOR).A;	SetColor(ATON_COLOR,color);		break;
	}

	if(m_Broker != NULL)
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnSynchro",NULL);
		
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
	
	wxPanel *Page2 = new wxPanel(Notebook);
	wxBoxSizer *m_Page2Sizer = new wxBoxSizer(wxVERTICAL);
	Page2->SetSizer(m_Page2Sizer);
	Notebook->AddPage(Page2,GetMsg(MSG_AIS_OPTIONS));

	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *Scroll = new wxScrolledWindow(Page2, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_Page2Sizer->Add(Scroll,1,wxALL|wxEXPAND,0);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(ScrollSizer);
	
	m_ShipNames = new wxCheckBox(Scroll,ID_SHOW_NAMES,GetMsg(MSG_SHOW_NAMES));
	m_ShipNames->SetValue(GetShowNames());
	ScrollSizer->Add(m_ShipNames,0,wxALL,5);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexSizer,0,wxALL|wxEXPAND,0);

	wxStaticText *TextFontSize = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_FONT_SIZE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextFontSize,1,wxALL,2);
	
	m_FontSize = new wxSlider(Scroll,ID_FONT_SIZE,0,0,0,wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(m_FontSize,0,wxALL,2);
	m_FontSize->SetMin(50);
	m_FontSize->SetMax(200);
	m_FontSize->SetValue(GetFontSize() * 10);


	wxStaticText *TextShipColor0 = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_COLOR_0),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextShipColor0,0,wxALL,2);
	
	m_ShipColor0 = new wxColourPickerCtrl(Scroll,ID_SHIP_COLOR_0);
	wxColor color;
	color.Set(GetColor(SHIP_COLOR_0).R,GetColor(SHIP_COLOR_0).G,GetColor(SHIP_COLOR_0).B,GetColor(SHIP_COLOR_0).A);
	m_ShipColor0->SetColour(color);
	FlexSizer->Add(m_ShipColor0,0,wxALL,2);

	wxStaticText *TextShipColor1 = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_COLOR_1),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextShipColor1,1,wxALL,2);

	m_ShipColor1 = new wxColourPickerCtrl(Scroll,ID_SHIP_COLOR_1);
	color.Set(GetColor(SHIP_COLOR_1).R,GetColor(SHIP_COLOR_1).G,GetColor(SHIP_COLOR_1).B,GetColor(SHIP_COLOR_1).A);
	m_ShipColor1->SetColour(color);
	FlexSizer->Add(m_ShipColor1,0,wxALL,2);
		
	wxStaticText *TextShipColor2 = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_COLOR_2),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextShipColor2,1,wxALL,2);

	m_ShipColor2 = new wxColourPickerCtrl(Scroll,ID_SHIP_COLOR_2);
	color.Set(GetColor(SHIP_COLOR_2).R,GetColor(SHIP_COLOR_2).G,GetColor(SHIP_COLOR_2).B,GetColor(SHIP_COLOR_2).A);
	m_ShipColor2->SetColour(color);
	FlexSizer->Add(m_ShipColor2,0,wxALL,2);


	wxStaticText *TextAtonColor = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_ATON_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextAtonColor,1,wxALL,2);

	m_AtonColor = new wxColourPickerCtrl(Scroll,ID_ATON_COLOR);
	color.Set(GetColor(ATON_COLOR).R,GetColor(ATON_COLOR).G,GetColor(SHIP_COLOR_1).B,GetColor(SHIP_COLOR_1).A);
	m_AtonColor->SetColour(color);
	FlexSizer->Add(m_AtonColor,0,wxALL,2);
		
	
	m_COGLine = new wxCheckBox(Scroll,ID_SHOW_COG,GetMsg(MSG_SHOW_COG));
	m_COGLine->SetValue(GetShowCOG());
	ScrollSizer->Add(m_COGLine,0,wxALL,5);
	
	m_HDTLine = new wxCheckBox(Scroll,ID_SHOW_HDT,GetMsg(MSG_SHOW_HDT));
	m_HDTLine->SetValue(GetShowHDT());
	ScrollSizer->Add(m_HDTLine,0,wxALL,5);
	
	
	Scroll->SetScrollbars(20, 20, 20, 20);


	this->SetSizer(m_Sizer);

}