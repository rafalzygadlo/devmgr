#include <wx/wx.h>
#include <wx/notebook.h>

#include "conf.h"
#include "tools.h"
#include "ais_list.h"
#include "listctrl.h"
#include "ais.h"
#include "thread.h"
#include "options.h"
#include "filter.h"


BEGIN_EVENT_TABLE(CAisList,wxPanel)
	EVT_SEARCHCTRL_SEARCH_BTN(ID_SEARCH,OnSearchButton)
	EVT_TEXT(ID_SEARCH,OnSearchText)
	EVT_TEXT_ENTER(ID_SEARCH,OnSearchEnter)
	EVT_CHECKBOX(ID_SHOW_NAMES,OnShowNames)
	EVT_CHECKBOX(ID_SHOW_COG,OnShowCOG)
	EVT_CHECKBOX(ID_SHOW_HDT,OnShowHDT)
	EVT_CHECKBOX(ID_SHOW_GPS,OnShowGPS)
	EVT_CHECKBOX(ID_SHOW_OBJECTS,OnShowOBJECTS)
	EVT_SLIDER(ID_FONT_SIZE,OnFontSize)
	EVT_COLOURPICKER_CHANGED(wxID_ANY,OnColorPicker)
	EVT_BUTTON(ID_FILTER,OnFilter)
	EVT_SLIDER(ID_VIEW_NAME_SCALE, OnNameScale)
	EVT_SPINCTRL(ID_COG_TIME, OnCOGTime)
	EVT_SPINCTRL(ID_HDT_TIME, OnHDTTime)
	EVT_SPINCTRL(ID_HDT_LINE_WIDTH, OnHDTLineWidth)
	EVT_SPINCTRL(ID_COG_LINE_WIDTH, OnCOGLineWidth)
	EVT_SPINCTRLDOUBLE(ID_CPA, OnCPA)
	EVT_SPINCTRLDOUBLE (ID_TCPA, OnTCPA)
	EVT_COMBOBOX(ID_COG_LINE_STYLE,OnCOGLineStyle)
	EVT_COMBOBOX(ID_HDT_LINE_STYLE,OnHDTLineStyle)
	EVT_SLIDER(wxID_ANY,OnAlpha)
	EVT_HYPERLINK(ID_AIS_CLEAR,OnAisClearBuffer)
END_EVENT_TABLE()


CAisList::CAisList(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display) 
:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Broker = NULL;
	m_Broker = plugin->GetBroker();
	m_Display = display;
	GetPanel();
	m_OldCount = 0;
	m_Working = false;
	SetList();
	//SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	
	//SetDoubleBuffered(true);
}

CAisList::~CAisList()
{
}

//void CAisList::SetSelectedPtr()
//{

//}

void CAisList::OnEraseBackground(wxEraseEvent &event)
{

}
void CAisList::SetSignal(int signal)
{
	switch(signal)
	{
		case CLEAR_AIS_LIST:		ClearList();	break;
		case SIGNAL_UPDATE_LIST:	SetList();		break;
	}
}

void CAisList::Synchro()
{
	m_GPSPoint->SetValue(GetShowGPS());
	m_COGLine->SetValue(GetShowCOG());
	m_HDTLine->SetValue(GetShowHDT());
	m_ShipNames->SetValue(GetShowNames());	
	//m_FontSize->SetValue(GetFontSize());

	wxColor color;
	color.Set(GetColor(COG_COLOR).R,GetColor(COG_COLOR).G,GetColor(COG_COLOR).B,GetColor(COG_COLOR).A);
	m_COGColor->SetColour(color);

	color.Set(GetColor(HDT_COLOR).R,GetColor(HDT_COLOR).G,GetColor(HDT_COLOR).B,GetColor(HDT_COLOR).A);
	m_HDTColor->SetColour(color);

	color.Set(GetColor(GPS_COLOR).R,GetColor(GPS_COLOR).G,GetColor(GPS_COLOR).B,GetColor(GPS_COLOR).A);
	m_GPSColor->SetColour(color);

	color.Set(GetColor(SHIP_COLOR_0A).R,GetColor(SHIP_COLOR_0A).G,GetColor(SHIP_COLOR_0A).B,GetColor(SHIP_COLOR_0A).A);
	m_ShipColor0A->SetColour(color);
		
	color.Set(GetColor(SHIP_COLOR_1A).R,GetColor(SHIP_COLOR_1A).G,GetColor(SHIP_COLOR_1A).B,GetColor(SHIP_COLOR_1A).A);
	m_ShipColor1A->SetColour(color);
		
	//color.Set(GetColor(SHIP_COLOR_2A).R,GetColor(SHIP_COLOR_2A).G,GetColor(SHIP_COLOR_2A).B,GetColor(SHIP_COLOR_2A).A);
	//m_ShipColor2A->SetColour(color);

	color.Set(GetColor(SHIP_COLOR_0B).R,GetColor(SHIP_COLOR_0B).G,GetColor(SHIP_COLOR_0B).B,GetColor(SHIP_COLOR_0B).A);
	m_ShipColor0B->SetColour(color);
		
	color.Set(GetColor(SHIP_COLOR_1B).R,GetColor(SHIP_COLOR_1B).G,GetColor(SHIP_COLOR_1B).B,GetColor(SHIP_COLOR_1B).A);
	m_ShipColor1B->SetColour(color);
		
	//color.Set(GetColor(SHIP_COLOR_2B).R,GetColor(SHIP_COLOR_2B).G,GetColor(SHIP_COLOR_2B).B,GetColor(SHIP_COLOR_2B).A);
	//m_ShipColor2B->SetColour(color);

	m_SearchText->SetValue(GetSearchText());
}

void CAisList::ClearList()
{
	m_List->SetItemCount(0);
}

void CAisList::SetList()
{
	int count = 0;
	if(ais_get_search_ready())
	{
		count = ais_get_search_item_count();
		m_List->SetItemCount(count);
		m_List->Refresh(false);
		m_List->SetSearch(true);
		
		if(m_OldCount != count)
			m_Notebook->SetPageText(PAGE_0,wxString::Format(GetMsg(MSG_AIS_TARGETS),count));
		m_OldCount = count;
		
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

}

void CAisList::OnSearchEnter(wxCommandEvent &event)
{
	SetSearchText(m_SearchText->GetValue().char_str());
	SetSearchTextChanged(true);
}

void CAisList::OnSearchText(wxCommandEvent &event)
{
	if(m_SearchText->GetValue().CmpNoCase(GetSearchText()) != 0)
	{
		SetSearchText(m_SearchText->GetValue().char_str());
		Signal();
	}
	
	SetSearchTextChanged(true);
}

void CAisList::ThreadBegin()
{

}

void CAisList::ThreadEnd()
{
	
}

void CAisList::OnShowNames(wxCommandEvent &event)
{
	SetShowNames(event.GetSelection());
	Signal();
}

void CAisList::OnFontSize(wxCommandEvent &event)
{
	SetFontSize(event.GetInt());
	Signal();
}

void CAisList::OnShowCOG(wxCommandEvent &event)
{
	SetShowCOG(event.GetSelection());
	Signal();
}

void CAisList::OnShowHDT(wxCommandEvent &event)
{
	SetShowHDT(event.GetSelection());
	Signal();
}

void CAisList::OnShowGPS(wxCommandEvent &event)
{
	SetShowGPS(event.GetSelection());
	Signal();
}

void CAisList::OnShowOBJECTS(wxCommandEvent &event)
{
	SetShowOBJECTS(event.GetSelection());
	Signal();
}

void CAisList::OnCOGTime(wxSpinEvent &event)
{
	SetCOGTime(event.GetInt());
	Signal();
}

void CAisList::OnHDTTime(wxSpinEvent &event)
{
	SetHDTTime(event.GetInt());
	Signal();
}

void CAisList::OnCOGLineWidth(wxSpinEvent &event)
{
	SetCOGLineWidth(event.GetInt());
	Signal();
}

void CAisList::OnHDTLineWidth(wxSpinEvent &event)
{
	SetHDTLineWidth(event.GetInt());
	Signal();
}

void CAisList::OnCOGLineStyle(wxCommandEvent &event)
{
	SetCOGLineStyle(event.GetInt());
	Signal();
}

void CAisList::OnHDTLineStyle(wxCommandEvent &event)
{
	SetHDTLineStyle(event.GetInt());
	Signal();
}

void CAisList::OnCPA(wxSpinDoubleEvent &event)
{
	SetCPA(event.GetValue());
	Signal();
}

void CAisList::OnTCPA(wxSpinDoubleEvent &event)
{
	SetTCPA(event.GetValue());
	Signal();
}

void CAisList::Signal()
{
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
		case ID_SHIP_BORDER_COLORA:	color.A = GetColor(SHIP_BORDER_COLORA).A;	SetColor(SHIP_BORDER_COLORA,color);		break;	
		case ID_SHIP_COLOR_0A:		color.A = GetColor(SHIP_COLOR_0A).A;		SetColor(SHIP_COLOR_0A,color);			break;
		case ID_SHIP_COLOR_1A:		color.A = GetColor(SHIP_COLOR_1A).A;		SetColor(SHIP_COLOR_1A,color);			break;
		case ID_SHIP_COLOR_2A:		color.A = GetColor(SHIP_COLOR_2A).A;		SetColor(SHIP_COLOR_2A,color);			break;

		//case ID_SHIP_BORDER_COLORB:	color.A = GetColor(SHIP_BORDER_COLORB).A;	SetColor(SHIP_BORDER_COLORB,color);		break;	
		case ID_SHIP_COLOR_0B:		color.A = GetColor(SHIP_COLOR_0B).A;		SetColor(SHIP_COLOR_0B,color);			break;
		case ID_SHIP_COLOR_1B:		color.A = GetColor(SHIP_COLOR_1B).A;		SetColor(SHIP_COLOR_1B,color);			break;
		case ID_SHIP_COLOR_2B:		color.A = GetColor(SHIP_COLOR_2B).A;		SetColor(SHIP_COLOR_2B,color);			break;

		case ID_ATON_COLOR:			color.A = GetColor(ATON_COLOR).A;			SetColor(ATON_COLOR,color);				break;
		case ID_COG_COLOR:			color.A = GetColor(COG_COLOR).A;			SetColor(COG_COLOR,color);				break;
		case ID_HDT_COLOR:			color.A = GetColor(HDT_COLOR).A;			SetColor(HDT_COLOR,color);				break;
		case ID_GPS_COLOR:			color.A = GetColor(GPS_COLOR).A;			SetColor(GPS_COLOR,color);				break;
		case ID_BASE_STATION_COLOR: color.A = GetColor(BASE_STATION_COLOR).A;	SetColor(BASE_STATION_COLOR,color);		break;
		case ID_SHIP_TRACK_COLOR:	color.A = GetColor(SHIP_TRACK_COLOR).A;		SetColor(SHIP_TRACK_COLOR,color);		break;
	}

	Signal();

		
}

void CAisList::OnFilter(wxCommandEvent &event)
{
	CFilter *Filter = new CFilter();
	Filter->ShowModal();
	delete Filter;
	//StartThread();	
}

void CAisList::OnNameScale(wxCommandEvent &event)
{
	SetViewFontScale(event.GetInt());
	Signal();
	
}

void CAisList::OnAlpha(wxCommandEvent &event)
{
	switch(event.GetId())
	{
		case ID_SHIP_BORDER_ALPHA:	SetAlpha(SHIP_BORDER_COLORA,event.GetInt());	break;
		case ID_ATON_ALPHA:			SetAlpha(ATON_COLOR,event.GetInt());			break;
		case ID_BASE_STATION_ALPHA: SetAlpha(BASE_STATION_COLOR,event.GetInt());	break;
		case ID_SHIP_ALPHA_0A:		SetAlpha(SHIP_COLOR_0A,event.GetInt());			break;
		case ID_SHIP_ALPHA_1A:		SetAlpha(SHIP_COLOR_1A,event.GetInt());			break;
		case ID_SHIP_ALPHA_2A:		SetAlpha(SHIP_COLOR_2A,event.GetInt());			break;
		case ID_SHIP_ALPHA_0B:		SetAlpha(SHIP_COLOR_0B,event.GetInt());			break;
		case ID_SHIP_ALPHA_1B:		SetAlpha(SHIP_COLOR_1B,event.GetInt());			break;
		case ID_SHIP_ALPHA_2B:		SetAlpha(SHIP_COLOR_2B,event.GetInt());			break;
		
	}

	Signal();
	
}

void CAisList::OnAisClearBuffer(wxHyperlinkEvent &event)
{
	GetMutex()->Lock();
	ais_free_list();
	//ais_free_buffer();
	//ais_free_track();
	//ais_free_collision(); 
	//ais_free_collision_CPA();
	//ais_free_collision_TCPA();
	//ais_state_free();
	GetMutex()->Unlock();
}

void CAisList::GetPanel()
{

	wxBoxSizer *m_Sizer = new wxBoxSizer(wxVERTICAL);

	m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME); //wxNB_NOPAGETHEME wersja 2.8
	m_Sizer->Add(m_Notebook,1,wxALL|wxEXPAND,0);
	
	m_Notebook->AddPage(GetPage1(),GetMsg(MSG_AIS_TARGETS));
	m_Notebook->AddPage(GetPage2(),GetMsg(MSG_AIS_OPTIONS));
	m_Notebook->AddPage(GetPage3(),GetMsg(MSG_VTS_OPTIONS));
	
	this->SetSizer(m_Sizer);

}


wxPanel *CAisList::GetPage1()
{

	wxPanel *Panel = new wxPanel(m_Notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(m_Page1Sizer);
	
	wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
	m_Page1Sizer->Add(hSizer,0,wxALL|wxEXPAND,0);

	m_SearchText = new wxSearchCtrl(Panel,ID_SEARCH,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);

	wxString str(GetSearchText(),wxConvUTF8);
	m_SearchText->SetValue(str);
	hSizer->Add(m_SearchText,1,wxALL|wxEXPAND,0);

	wxButton *BFilter = new wxButton(Panel,ID_FILTER,GetMsg(MSG_FILTER),wxDefaultPosition,wxSize(20,-1));
	hSizer->Add(BFilter,0,wxALL,0);

	//m_SearchText->SetValue(m_SearchText);
	
	m_List = new CListCtrl(Panel,this,wxLC_REPORT |  wxLC_VIRTUAL  );
	wxListItem item;
	item.SetWidth(65);	item.SetText(wxEmptyString);			m_List->InsertColumn(0,item);
	item.SetWidth(80);	item.SetText(GetMsg(MSG_MMSI));			m_List->InsertColumn(1,item);
	item.SetWidth(200);	item.SetText(GetMsg(MSG_SHIPNAME));		m_List->InsertColumn(2,item);
	item.SetWidth(80);	item.SetText(GetMsg(MSG_CALLSIGN));		m_List->InsertColumn(4,item);
	item.SetWidth(80);	item.SetText(GetMsg(MSG_IMO_NUMBER));	m_List->InsertColumn(5,item);
	item.SetWidth(80);	item.SetText(GetMsg(MSG_AGE));			m_List->InsertColumn(6,item);
	m_Page1Sizer->Add(m_List,1,wxALL|wxEXPAND,0);
	
	m_List->SetColumnImage(ais_get_sort_column(), ais_get_sort_order());

	m_Html = new wxHtmlWindow(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Page1Sizer->Add(m_Html,1,wxALL|wxEXPAND,0);
	m_Html->Hide();
	
	return Panel;
}

wxPanel *CAisList::GetPage2()
{
	wxPanel *Panel = new wxPanel(m_Notebook);
	wxBoxSizer *m_Page2Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(m_Page2Sizer);
	
	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	m_Scroll = new wxScrolledWindow(Panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_Page2Sizer->Add(m_Scroll,1,wxALL|wxEXPAND,0);
	m_Scroll->SetFocusIgnoringChildren();
	m_Scroll->SetSizer(ScrollSizer);
		
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(3);
	ScrollSizer->Add(FlexSizer,0,wxALL,5);
	
	//fonty
	ScrollSizer->Add( GetShipNamesPanel(),0,wxALL,2);
	// ship options
	ScrollSizer->Add(GetShipOptionsPanel(),0,wxALL,2);
	// COG
	ScrollSizer->Add(GetCOGPanel(),0,wxALL,2);
	//HDT
	ScrollSizer->Add(GetHDTPanel(),0,wxALL,2);
	//GPS
	ScrollSizer->Add( GetGPSPanel(),0,wxALL,2);
	//Timeout	
	ScrollSizer->Add( GetTimeoutPanel(),0,wxALL,2);
		
	wxStaticBoxSizer *box_sizer = new wxStaticBoxSizer(wxVERTICAL,m_Scroll,_("test"));
	ScrollSizer->Add(box_sizer,0,wxALL,5);
	
	wxHyperlinkCtrl *m_AisClearBuffer = new wxHyperlinkCtrl(m_Scroll,ID_AIS_CLEAR,GetMsg(MSG_AIS_CLEAR_BUFFER),wxEmptyString);
	box_sizer->Add(m_AisClearBuffer,0,wxALL,5);

	m_Scroll->SetScrollbars(20, 20, 20, 20);

	return Panel;

}

wxPanel *CAisList::GetShipNamesPanel()
{
	wxPanel *Panel = new wxPanel(m_Scroll);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_AIS_NAMES));
	PanelSizer->Add(Box,0,wxALL,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	m_ShipNames = new wxCheckBox(Panel,ID_SHOW_NAMES,GetMsg(MSG_SHOW_NAMES));
	m_ShipNames->SetValue(GetShowNames());
	FlexSizer->Add(m_ShipNames,0,wxALL,1);
	FlexSizer->AddSpacer(1);
	wxStaticText *TextFontSize = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_FONT_SIZE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextFontSize,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_FontSize = new wxSlider(Panel,ID_FONT_SIZE,0,0,1,wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(m_FontSize,0,wxALL,2);
	m_FontSize->SetMin(50);
	m_FontSize->SetMax(200);
	m_FontSize->SetValue(GetFontSize() * 10);
	
	wxStaticText *TextViewNameScale = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_VIEW_NAME_SCALE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextViewNameScale,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_ViewNameScale = new wxSlider(Panel,ID_VIEW_NAME_SCALE,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_ViewNameScale->SetMin(1);
	m_ViewNameScale->SetMax(10000);
	m_ViewNameScale->SetValue(GetViewFontScale());
	
	FlexSizer->Add(m_ViewNameScale,0,wxALL,2);
		
	return Panel;

}

wxPanel *CAisList::GetShipOptionsPanel()
{

	wxPanel *Panel = new wxPanel(m_Scroll);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_OBJECT_OPTIONS));
	PanelSizer->Add(Box,0,wxALL,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(3);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	//OBJECTS
	m_ShowObjects = new wxCheckBox(Panel,ID_SHOW_OBJECTS,GetMsg(MSG_SHOW_OBJECTS));
	m_ShowObjects->SetValue(GetShowOBJECTS());
	FlexSizer->Add(m_ShowObjects,0,wxALL,2);
	FlexSizer->AddSpacer(1);
	FlexSizer->AddSpacer(1);
	
	//Class A

	wxStaticText *TextClassA = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_CLASS_A),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextClassA,0,wxALL,2);
	FlexSizer->AddSpacer(1);
	FlexSizer->AddSpacer(1);
	//wxStaticText *TextShipBorderColor = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_BORDER_COLOR),wxDefaultPosition,wxDefaultSize);
	//FlexOBJECTSSizer->Add(TextShipBorderColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	//m_ShipBorderColorA = new wxColourPickerCtrl(Scroll,ID_SHIP_BORDER_COLORA,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	wxColor color;
	//color.Set(GetColor(SHIP_BORDER_COLORA).R,GetColor(SHIP_BORDER_COLORA).G,GetColor(SHIP_BORDER_COLORA).B,GetColor(SHIP_BORDER_COLORA).A);
	//m_ShipBorderColorA->SetColour(color);
	//FlexOBJECTSSizer->Add(m_ShipBorderColorA,0,wxALL,2);
	//m_ShipBorderAlphaA = new wxSlider(Scroll,ID_VIEW_NAME_SCALE,0,0,0,wxDefaultPosition,wxDefaultSize);
	//m_ShipBorderAlphaA->SetMin(0);
	//m_ShipBorderAlphaA->SetMax(255);
	//FlexOBJECTSSizer->Add(m_ShipBorderAlphaA,0,wxALL,2);
	
	wxStaticText *TextShipColor0A = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SHIP_COLOR_0),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextShipColor0A,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipColor0A = new wxColourPickerCtrl(Panel,ID_SHIP_COLOR_0A,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(SHIP_COLOR_0A).R,GetColor(SHIP_COLOR_0A).G,GetColor(SHIP_COLOR_0A).B,GetColor(SHIP_COLOR_0A).A);
	m_ShipColor0A->SetColour(color);
	FlexSizer->Add(m_ShipColor0A,0,wxALL,2);
	m_ShipAlpha0A = new wxSlider(Panel,ID_SHIP_ALPHA_0A,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_ShipAlpha0A->SetMin(0);
	m_ShipAlpha0A->SetMax(255);
	m_ShipAlpha0A->SetValue(GetAlpha(SHIP_COLOR_0A));
	FlexSizer->Add(m_ShipAlpha0A,0,wxALL,2);

	wxStaticText *TextShipColor1A = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SHIP_COLOR_1),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextShipColor1A,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipColor1A = new wxColourPickerCtrl(Panel,ID_SHIP_COLOR_1A,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(SHIP_COLOR_1A).R,GetColor(SHIP_COLOR_1A).G,GetColor(SHIP_COLOR_1A).B);
	m_ShipColor1A->SetColour(color);
	FlexSizer->Add(m_ShipColor1A,0,wxALL,2);
	m_ShipAlpha1A = new wxSlider(Panel,ID_SHIP_ALPHA_1A,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_ShipAlpha1A->SetMin(0);
	m_ShipAlpha1A->SetMax(255);
	m_ShipAlpha1A->SetValue(GetAlpha(SHIP_COLOR_1A));
	FlexSizer->Add(m_ShipAlpha1A,0,wxALL,2);
	
	/*
	wxStaticText *TextShipColor2A = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_COLOR_2),wxDefaultPosition,wxDefaultSize);
	FlexOBJECTSSizer->Add(TextShipColor2A,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipColor2A = new wxColourPickerCtrl(Scroll,ID_SHIP_COLOR_2A,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	color.Set(GetColor(SHIP_COLOR_2A).R,GetColor(SHIP_COLOR_2A).G,GetColor(SHIP_COLOR_2A).B,GetColor(SHIP_COLOR_2A).A);
	m_ShipColor2A->SetColour(color);
	FlexOBJECTSSizer->Add(m_ShipColor2A,0,wxALL,2);
	m_ShipAlpha2A = new wxSlider(Scroll,ID_SHIP_ALPHA_2A,0,0,0,wxDefaultPosition,wxDefaultSize);
	m_ShipAlpha2A->SetMin(0);
	m_ShipAlpha2A->SetMax(255);
	m_ShipAlpha2A->SetValue(GetAlpha(SHIP_COLOR_2A));
	FlexOBJECTSSizer->Add(m_ShipAlpha2A,0,wxALL,2);
	*/
	
	//wxStaticText *TextShipBorderColorB = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_BORDER_COLOR),wxDefaultPosition,wxDefaultSize);
	//FlexOBJECTSSizer->Add(TextShipBorderColorB,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	//m_ShipBorderColorA = new wxColourPickerCtrl(Scroll,ID_SHIP_BORDER_COLORB,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);

	//color.Set(GetColor(SHIP_BORDER_COLORB).R,GetColor(SHIP_BORDER_COLORB).G,GetColor(SHIP_BORDER_COLORA).B,GetColor(SHIP_BORDER_COLORA).A);
	//m_ShipBorderColorA->SetColour(color);
	//FlexOBJECTSSizer->Add(m_ShipBorderColorA,0,wxALL,2);
	//m_ShipBorderAlphaA = new wxSlider(Scroll,ID_SHIP_BORDER_ALPHAA,0,0,0,wxDefaultPosition,wxDefaultSize);
	//m_ShipBorderAlphaA->SetMin(0);
	//m_ShipBorderAlphaA->SetMax(255);
	//FlexOBJECTSSizer->Add(m_ShipBorderAlphaA,0,wxALL,2);

	//Class B
	wxStaticText *TextClassB = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_CLASS_B),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextClassB,0,wxALL,2);
	FlexSizer->AddSpacer(1);
	FlexSizer->AddSpacer(1);
	
	wxStaticText *TextShipColor0B = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SHIP_COLOR_0),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextShipColor0B,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipColor0B = new wxColourPickerCtrl(Panel,ID_SHIP_COLOR_0B,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(SHIP_COLOR_0B).R,GetColor(SHIP_COLOR_0B).G,GetColor(SHIP_COLOR_0B).B,GetColor(SHIP_COLOR_0B).A);
	m_ShipColor0B->SetColour(color);
	FlexSizer->Add(m_ShipColor0B,0,wxALL,2);
	m_ShipAlpha0B = new wxSlider(Panel,ID_SHIP_ALPHA_0B,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_ShipAlpha0B->SetMin(0);
	m_ShipAlpha0B->SetMax(255);
	m_ShipAlpha0B->SetValue(GetAlpha(SHIP_COLOR_0B));
	FlexSizer->Add(m_ShipAlpha0B,0,wxALL,2);

	wxStaticText *TextShipColor1B = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SHIP_COLOR_1),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextShipColor1B,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipColor1B = new wxColourPickerCtrl(Panel,ID_SHIP_COLOR_1B,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(SHIP_COLOR_1B).R,GetColor(SHIP_COLOR_1B).G,GetColor(SHIP_COLOR_1B).B,GetColor(SHIP_COLOR_1B).A);
	m_ShipColor1B->SetColour(color);
	FlexSizer->Add(m_ShipColor1B,0,wxALL,2);
	m_ShipAlpha1B = new wxSlider(Panel,ID_SHIP_ALPHA_1B,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_ShipAlpha1B->SetMin(0);
	m_ShipAlpha1B->SetMax(255);
	m_ShipAlpha1B->SetValue(GetAlpha(SHIP_COLOR_1B));
	FlexSizer->Add(m_ShipAlpha1B,0,wxALL,2);

	//Aton
	wxStaticText *TextAtonColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_ATON_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextAtonColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_AtonColor = new wxColourPickerCtrl(Panel,ID_ATON_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(ATON_COLOR).R,GetColor(ATON_COLOR).G,GetColor(ATON_COLOR).B,GetColor(ATON_COLOR).A);
	m_AtonColor->SetColour(color);
	FlexSizer->Add(m_AtonColor,0,wxALL,2);
	m_AtonAlpha = new wxSlider(Panel,ID_ATON_ALPHA,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_AtonAlpha->SetMin(0);
	m_AtonAlpha->SetMax(255);
	m_AtonAlpha->SetValue(GetAlpha(ATON_COLOR));
	FlexSizer->Add(m_AtonAlpha,0,wxALL,2);

	//Base Station
	wxStaticText *TextBaseStation = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BASE_STATION_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextBaseStation,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_BaseStationColor = new wxColourPickerCtrl(Panel,ID_BASE_STATION_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(BASE_STATION_COLOR).R,GetColor(BASE_STATION_COLOR).G,GetColor(BASE_STATION_COLOR).B,GetColor(BASE_STATION_COLOR).A);
	m_BaseStationColor->SetColour(color);
	FlexSizer->Add(m_BaseStationColor,0,wxALL,2);
	m_BaseStationAlpha = new wxSlider(Panel,ID_BASE_STATION_ALPHA,0,0,1,wxDefaultPosition,wxDefaultSize);
	m_BaseStationAlpha->SetMin(0);
	m_BaseStationAlpha->SetMax(255);
	m_BaseStationAlpha->SetValue(GetAlpha(BASE_STATION_COLOR));
	FlexSizer->Add(m_BaseStationAlpha,0,wxALL,2);

	return Panel;

}

wxPanel *CAisList::GetCOGPanel()
{
	
	wxPanel *Panel = new wxPanel(m_Scroll);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_COG_OPTIONS));
	PanelSizer->Add(Box,0,wxALL,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(3);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
		
	m_COGLine = new wxCheckBox(Panel,ID_SHOW_COG,GetMsg(MSG_SHOW_COG));
	m_COGLine->SetValue(GetShowCOG());
	FlexSizer->Add(m_COGLine,0,wxALL,1);
	FlexSizer->AddSpacer(1);
	FlexSizer->AddSpacer(1);
	//wxFlexGridSizer *FlexCOGSizer = new wxFlexGridSizer(2);
	//ScrollSizer->Add(FlexCOGSizer,0,wxALL|wxEXPAND,5);
	wxStaticText *TextCOGColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_COG_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextCOGColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	wxColor color;
	m_COGColor = new wxColourPickerCtrl(Panel,ID_COG_COLOR, *wxBLACK,wxDefaultPosition,wxDefaultSize );
	color.Set(GetColor(COG_COLOR).R,GetColor(COG_COLOR).G,GetColor(COG_COLOR).B,GetColor(COG_COLOR).A);
	m_COGColor->SetColour(color);
	FlexSizer->Add(m_COGColor,0,wxALL,2);
	FlexSizer->AddSpacer(1);
	
	wxStaticText *TextCOGTime = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_COG_TIME),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextCOGTime,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_COGTime = new wxSpinCtrl(Panel,ID_COG_TIME,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_COGTime->SetMin(0);
	m_COGTime->SetMax(3600);
	m_COGTime->SetValue(GetCOGTime());
	FlexSizer->Add(m_COGTime,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	FlexSizer->AddSpacer(1);
	
	wxStaticText *TextCOGLineWidth = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_COG_LINE_WIDTH),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextCOGLineWidth,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_COGLineWidth = new wxSpinCtrl(Panel,ID_COG_LINE_WIDTH,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_COGLineWidth->SetMin(0);
	m_COGLineWidth->SetMax(50);
	m_COGLineWidth->SetValue(GetCOGLineWidth());
	FlexSizer->Add(m_COGLineWidth,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	FlexSizer->AddSpacer(1);
	
	wxStaticText *TextCOGLineStyle = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_COG_LINE_STYLE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextCOGLineStyle,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_COGLineStyle = new CPenStyleComboBox(Panel,ID_COG_LINE_STYLE);
	m_COGLineStyle->SetSelection(GetCOGLineStyle());
	FlexSizer->Add(m_COGLineStyle,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	FlexSizer->AddSpacer(1);
	
	return Panel;
}

wxPanel *CAisList::GetHDTPanel()
{
	wxPanel *Panel = new wxPanel(m_Scroll);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_HDT_OPTIONS));
	PanelSizer->Add(Box,0,wxALL,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(3);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	m_HDTLine = new wxCheckBox(Panel,ID_SHOW_HDT,GetMsg(MSG_SHOW_HDT));
	m_HDTLine->SetValue(GetShowHDT());
	FlexSizer->Add(m_HDTLine,0,wxALL,1);
	FlexSizer->AddSpacer(1);
	FlexSizer->AddSpacer(1);
	
	wxStaticText *TextHDTColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_HDT_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextHDTColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	wxColor color;
	m_HDTColor = new wxColourPickerCtrl(Panel,ID_HDT_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(HDT_COLOR).R,GetColor(HDT_COLOR).G,GetColor(HDT_COLOR).B,GetColor(HDT_COLOR).A);
	m_HDTColor->SetColour(color);
	FlexSizer->Add(m_HDTColor,0,wxALL,2);
	FlexSizer->AddSpacer(1);

	wxStaticText *TextHDTTime = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_HDT_TIME),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextHDTTime,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_HDTTime = new wxSpinCtrl(Panel,ID_HDT_TIME,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_HDTTime->SetMin(0);
	m_HDTTime->SetMax(3600);
	m_HDTTime->SetValue(GetHDTTime());
	FlexSizer->Add(m_HDTTime,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	FlexSizer->AddSpacer(1);
	
	wxStaticText *TextHDTLineWidth = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_HDT_LINE_WIDTH),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextHDTLineWidth,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_HDTLineWidth = new wxSpinCtrl(Panel,ID_HDT_LINE_WIDTH,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_HDTLineWidth->SetMin(0);
	m_HDTLineWidth->SetMax(50);
	m_HDTLineWidth->SetValue(GetHDTLineWidth());
	FlexSizer->Add(m_HDTLineWidth,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	FlexSizer->AddSpacer(1);
	
	wxStaticText *TextHDTLineStyle = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_HDT_LINE_STYLE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextHDTLineStyle,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_HDTLineStyle = new CPenStyleComboBox(Panel,ID_HDT_LINE_STYLE);
	m_HDTLineStyle->SetSelection(GetHDTLineStyle());
	FlexSizer->Add(m_HDTLineStyle,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	FlexSizer->AddSpacer(1);
	
	return Panel;
}


wxPanel *CAisList::GetGPSPanel()
{

	wxPanel *Panel = new wxPanel(m_Scroll);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_GPS_OPTIONS));
	PanelSizer->Add(Box,0,wxALL,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(3);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	//GPS
	m_GPSPoint = new wxCheckBox(Panel,ID_SHOW_GPS,GetMsg(MSG_SHOW_GPS));
	m_GPSPoint->SetValue(GetShowGPS());
	FlexSizer->Add(m_GPSPoint,0,wxALL,1);
	FlexSizer->AddSpacer(1);
	FlexSizer->AddSpacer(1);
	
	wxStaticText *TextGPSColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_GPS_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextGPSColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	wxColor color;

	m_GPSColor = new wxColourPickerCtrl(Panel,ID_GPS_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize);
	color.Set(GetColor(GPS_COLOR).R,GetColor(GPS_COLOR).G,GetColor(GPS_COLOR).B,GetColor(GPS_COLOR).A);
	m_GPSColor->SetColour(color);
	FlexSizer->Add(m_GPSColor,0,wxALL,2);
	FlexSizer->AddSpacer(1);

	return Panel;

}

wxPanel *CAisList::GetTimeoutPanel()
{

	wxPanel *Panel = new wxPanel(m_Scroll);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_AIS_TIMEOUTS));
	PanelSizer->Add(Box,0,wxALL,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);

	wxStaticText *TextAisTimeout = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_AIS_TIMEOUT),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextAisTimeout,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_AisTimeout = new wxSpinCtrl(Panel,ID_HDT_TIME,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_AisTimeout->SetMin(1);
	m_AisTimeout->SetMax(3600);
	m_AisTimeout->SetValue(GetAisTimeout()/60/1000);
	FlexSizer->Add(m_AisTimeout,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
		
	wxStaticText *TextAisTimeoutRemove = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_AIS_TIMEOUT_REMOVE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextAisTimeoutRemove,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_AisTimeoutRemove = new wxSpinCtrl(Panel,ID_HDT_TIME,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_AisTimeoutRemove->SetMin(1);
	m_AisTimeoutRemove->SetMax(3600);
	m_AisTimeoutRemove->SetValue(GetAisTimeoutRemove()/60/1000);
	FlexSizer->Add(m_AisTimeoutRemove,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	return Panel;
}


wxPanel *CAisList::GetPage3()
{
	
	wxPanel *Panel = new wxPanel(m_Notebook);
	wxBoxSizer *m_Page3Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(m_Page3Sizer);
	
	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *Scroll = new wxScrolledWindow(Panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_Page3Sizer->Add(Scroll,1,wxALL|wxEXPAND,0);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(ScrollSizer);
		
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexSizer,0,wxALL,5);
	
	//VTS
	m_VTS = new wxCheckBox(Scroll,ID_ENABLE_VTS,GetMsg(MSG_ENABLE_VTS_MODE));
	FlexSizer->Add(m_VTS,0,wxALL,1);
	m_VTS->SetValue(GetVTSMode());
	FlexSizer->AddSpacer(1);
			
	wxStaticText *TextCPA = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_CPA),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextCPA,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_CPA = new wxSpinCtrlDouble(Scroll,ID_CPA,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_CPA->SetIncrement(0.5);
	m_CPA->SetValue(GetCPA());
	FlexSizer->Add(m_CPA,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	wxStaticText *TextTCPA = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_TCPA),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextTCPA,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_TCPA = new wxSpinCtrlDouble(Scroll,ID_TCPA,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_TCPA->SetIncrement(0.5);
	m_TCPA->SetValue(GetTCPA());
	FlexSizer->Add(m_TCPA,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	

	Scroll->SetScrollbars(20, 20, 20, 20);
	
	return Panel;

}