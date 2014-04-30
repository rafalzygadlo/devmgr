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
	EVT_COMBOBOX(ID_COG_LINE_STYLE,OnCOGLineStyle)
	EVT_COMBOBOX(ID_HDT_LINE_STYLE,OnHDTLineStyle)
END_EVENT_TABLE()


CAisList::CAisList(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display) 
:wxPanel(parent)
{
	m_Broker = NULL;
	//SetDoubleBuffered(true);
	m_Broker = plugin->GetBroker();
	m_Display = display;
	GetPanel();
	m_OldCount = 0;
	m_Working = false;
	SetList();
}

CAisList::~CAisList()
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

	color.Set(GetColor(SHIP_COLOR_0).R,GetColor(SHIP_COLOR_0).G,GetColor(SHIP_COLOR_0).B,GetColor(SHIP_COLOR_0).A);
	m_ShipColor0->SetColour(color);
		
	color.Set(GetColor(SHIP_COLOR_1).R,GetColor(SHIP_COLOR_1).G,GetColor(SHIP_COLOR_1).B,GetColor(SHIP_COLOR_1).A);
	m_ShipColor1->SetColour(color);
		
	color.Set(GetColor(SHIP_COLOR_2).R,GetColor(SHIP_COLOR_2).G,GetColor(SHIP_COLOR_2).B,GetColor(SHIP_COLOR_2).A);
	m_ShipColor2->SetColour(color);

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
		m_List->RefreshItems(m_List->_GetFrom(),m_List->_GetTo());
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
}

void CAisList::OnSearchText(wxCommandEvent &event)
{
	SetSearchText(m_SearchText->GetValue().char_str());
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
		case ID_SHIP_BORDER_COLOR:	color.A = GetColor(SHIP_BORDER_COLOR).A;	SetColor(SHIP_BORDER_COLOR,color);	break;	
		case ID_SHIP_COLOR_0:		color.A = GetColor(SHIP_COLOR_0).A;			SetColor(SHIP_COLOR_0,color);		break;
		case ID_SHIP_COLOR_1:		color.A = GetColor(SHIP_COLOR_1).A;			SetColor(SHIP_COLOR_1,color);		break;
		case ID_SHIP_COLOR_2:		color.A = GetColor(SHIP_COLOR_2).A;			SetColor(SHIP_COLOR_2,color);		break;
		case ID_ATON_COLOR:			color.A = GetColor(ATON_COLOR).A;			SetColor(ATON_COLOR,color);			break;
		case ID_COG_COLOR:			color.A = GetColor(COG_COLOR).A;			SetColor(COG_COLOR,color);			break;
		case ID_HDT_COLOR:			color.A = GetColor(HDT_COLOR).A;			SetColor(HDT_COLOR,color);			break;
		case ID_GPS_COLOR:			color.A = GetColor(GPS_COLOR).A;			SetColor(GPS_COLOR,color);			break;
	}

	if(m_Broker != NULL)
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnSynchro",NULL);
		
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

	if(m_Broker != NULL)
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnSynchro",NULL);
}

void CAisList::GetPanel()
{

	wxBoxSizer *m_Sizer = new wxBoxSizer(wxVERTICAL);

	m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME|wxCLIP_CHILDREN);
	//m_Notebook->SetDoubleBuffered(true);
	m_Sizer->Add(m_Notebook,1,wxALL|wxEXPAND,0);
	wxPanel *Page1 = new wxPanel(m_Notebook);
	m_Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(m_Page1Sizer);
	m_Notebook->AddPage(Page1,(GetMsg(MSG_AIS_TARGETS)));

	wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
	m_Page1Sizer->Add(hSizer,0,wxALL|wxEXPAND,0);

	m_SearchText = new wxSearchCtrl(Page1,ID_SEARCH,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);
	hSizer->Add(m_SearchText,1,wxALL|wxEXPAND,0);

	wxButton *BFilter = new wxButton(Page1,ID_FILTER,GetMsg(MSG_FILTER),wxDefaultPosition,wxSize(20,-1));
	hSizer->Add(BFilter,0,wxALL,0);

	//m_SearchText->SetValue(m_SearchText);
	

	m_List = new CListCtrl(Page1,this,wxLC_REPORT | wxLC_HRULES | wxLC_VIRTUAL);
	wxListItem item;
	item.SetWidth(65);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(0,item);
	item.SetWidth(80);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(1,item);
	item.SetWidth(200);	item.SetText(GetMsg(MSG_SHIPNAME));	m_List->InsertColumn(2,item);
	//item.SetWidth(100);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(3,item);
	//item.SetWidth(100);	item.SetText(GetMsg(MSG_MMSI));	m_List->InsertColumn(4,item);
	m_Page1Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	m_Html = new wxHtmlWindow(Page1,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Page1Sizer->Add(m_Html,1,wxALL|wxEXPAND,0);
	m_Html->Hide();
	
	//Page2
	wxPanel *Page2 = new wxPanel(m_Notebook);
	wxBoxSizer *m_Page2Sizer = new wxBoxSizer(wxVERTICAL);
	Page2->SetSizer(m_Page2Sizer);
	m_Notebook->AddPage(Page2,GetMsg(MSG_AIS_OPTIONS));

	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *Scroll = new wxScrolledWindow(Page2, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_Page2Sizer->Add(Scroll,1,wxALL|wxEXPAND,0);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(ScrollSizer);
		
	m_ShipNames = new wxCheckBox(Scroll,ID_SHOW_NAMES,GetMsg(MSG_SHOW_NAMES));
	m_ShipNames->SetValue(GetShowNames());
	ScrollSizer->Add(m_ShipNames,0,wxALL,5);
		
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexSizer,0,wxALL,5);
			
	wxStaticText *TextFontSize = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_FONT_SIZE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextFontSize,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_FontSize = new wxSlider(Scroll,ID_FONT_SIZE,0,0,0,wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(m_FontSize,0,wxALL|wxALIGN_RIGHT,2);
	m_FontSize->SetMin(50);
	m_FontSize->SetMax(200);
	m_FontSize->SetValue(GetFontSize() * 10);

	wxStaticText *TextViewNameScale = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_VIEW_NAME_SCALE),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextViewNameScale,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_ViewNameScale = new wxSlider(Scroll,ID_VIEW_NAME_SCALE,0,0,0,wxDefaultPosition,wxDefaultSize);
	m_ViewNameScale->SetMin(1);
	m_ViewNameScale->SetMax(10000);
	m_ViewNameScale->SetValue(GetViewFontScale());
	FlexSizer->Add(m_ViewNameScale,0,wxALL|wxALIGN_RIGHT,2);
	
	//OBJECTS
	m_ShowObjects = new wxCheckBox(Scroll,ID_SHOW_OBJECTS,GetMsg(MSG_SHOW_OBJECTS));
	m_ShowObjects->SetValue(GetShowOBJECTS());
	ScrollSizer->Add(m_ShowObjects,0,wxALL,5);

	wxGridSizer *FlexOBJECTSSizer = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexOBJECTSSizer,0,wxALL,5);
	
	wxStaticText *TextShipBorderColor = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_BORDER_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexOBJECTSSizer->Add(TextShipBorderColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipBorderColor = new wxColourPickerCtrl(Scroll,ID_SHIP_BORDER_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	wxColor color;
	color.Set(GetColor(SHIP_BORDER_COLOR).R,GetColor(SHIP_BORDER_COLOR).G,GetColor(SHIP_BORDER_COLOR).B,GetColor(SHIP_BORDER_COLOR).A);
	m_ShipBorderColor->SetColour(color);
	FlexOBJECTSSizer->Add(m_ShipBorderColor,0,wxALL,2);

	wxStaticText *TextShipColor0 = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_COLOR_0),wxDefaultPosition,wxDefaultSize);
	FlexOBJECTSSizer->Add(TextShipColor0,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipColor0 = new wxColourPickerCtrl(Scroll,ID_SHIP_COLOR_0,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	color.Set(GetColor(SHIP_COLOR_0).R,GetColor(SHIP_COLOR_0).G,GetColor(SHIP_COLOR_0).B,GetColor(SHIP_COLOR_0).A);
	m_ShipColor0->SetColour(color);
	FlexOBJECTSSizer->Add(m_ShipColor0,0,wxALL,2);

	wxStaticText *TextShipColor1 = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_COLOR_1),wxDefaultPosition,wxDefaultSize);
	FlexOBJECTSSizer->Add(TextShipColor1,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipColor1 = new wxColourPickerCtrl(Scroll,ID_SHIP_COLOR_1,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	color.Set(GetColor(SHIP_COLOR_1).R,GetColor(SHIP_COLOR_1).G,GetColor(SHIP_COLOR_1).B,GetColor(SHIP_COLOR_1).A);
	m_ShipColor1->SetColour(color);
	FlexOBJECTSSizer->Add(m_ShipColor1,0,wxALL,2);
		
	wxStaticText *TextShipColor2 = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SHIP_COLOR_2),wxDefaultPosition,wxDefaultSize);
	FlexOBJECTSSizer->Add(TextShipColor2,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_ShipColor2 = new wxColourPickerCtrl(Scroll,ID_SHIP_COLOR_2,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	color.Set(GetColor(SHIP_COLOR_2).R,GetColor(SHIP_COLOR_2).G,GetColor(SHIP_COLOR_2).B,GetColor(SHIP_COLOR_2).A);
	m_ShipColor2->SetColour(color);
	FlexOBJECTSSizer->Add(m_ShipColor2,0,wxALL,2);
	
	wxStaticText *TextAtonColor = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_ATON_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexOBJECTSSizer->Add(TextAtonColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_AtonColor = new wxColourPickerCtrl(Scroll,ID_ATON_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	color.Set(GetColor(ATON_COLOR).R,GetColor(ATON_COLOR).G,GetColor(SHIP_COLOR_1).B,GetColor(SHIP_COLOR_1).A);
	m_AtonColor->SetColour(color);
	FlexOBJECTSSizer->Add(m_AtonColor,0,wxALL,2);
	
	//COG
	m_COGLine = new wxCheckBox(Scroll,ID_SHOW_COG,GetMsg(MSG_SHOW_COG));
	m_COGLine->SetValue(GetShowCOG());
	ScrollSizer->Add(m_COGLine,0,wxALL,5);
	
	wxFlexGridSizer *FlexCOGSizer = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexCOGSizer,0,wxALL|wxEXPAND,5);
	wxStaticText *TextCOGColor = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_COG_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexCOGSizer->Add(TextCOGColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_COGColor = new wxColourPickerCtrl(Scroll,ID_COG_COLOR, *wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL );
	color.Set(GetColor(COG_COLOR).R,GetColor(COG_COLOR).G,GetColor(COG_COLOR).B,GetColor(COG_COLOR).A);
	m_COGColor->SetColour(color);
	FlexCOGSizer->Add(m_COGColor,0,wxALL,2);

	wxStaticText *TextCOGTime = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_COG_TIME),wxDefaultPosition,wxDefaultSize);
	FlexCOGSizer->Add(TextCOGTime,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_COGTime = new wxSpinCtrl(Scroll,ID_COG_TIME,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_COGTime->SetMin(0);
	m_COGTime->SetMax(3600);
	m_COGTime->SetValue(GetCOGTime());
	FlexCOGSizer->Add(m_COGTime,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	wxStaticText *TextCOGLineWidth = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_COG_LINE_WIDTH),wxDefaultPosition,wxDefaultSize);
	FlexCOGSizer->Add(TextCOGLineWidth,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_COGLineWidth = new wxSpinCtrl(Scroll,ID_COG_LINE_WIDTH,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_COGLineWidth->SetMin(0);
	m_COGLineWidth->SetMax(50);
	m_COGLineWidth->SetValue(GetCOGLineWidth());
	FlexCOGSizer->Add(m_COGLineWidth,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	wxStaticText *TextCOGLineStyle = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_COG_LINE_STYLE),wxDefaultPosition,wxDefaultSize);
	FlexCOGSizer->Add(TextCOGLineStyle,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_COGLineStyle = new CPenStyleComboBox(Scroll,ID_COG_LINE_STYLE);
	m_COGLineStyle->SetSelection(GetCOGLineStyle());
	FlexCOGSizer->Add(m_COGLineStyle,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	//HDT
	m_HDTLine = new wxCheckBox(Scroll,ID_SHOW_HDT,GetMsg(MSG_SHOW_HDT));
	m_HDTLine->SetValue(GetShowHDT());
	ScrollSizer->Add(m_HDTLine,0,wxALL,5);

	wxFlexGridSizer *FlexHDTSizer = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexHDTSizer,0,wxALL,5);

	wxStaticText *TextHDTColor = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_HDT_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexHDTSizer->Add(TextHDTColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_HDTColor = new wxColourPickerCtrl(Scroll,ID_HDT_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	color.Set(GetColor(HDT_COLOR).R,GetColor(HDT_COLOR).G,GetColor(HDT_COLOR).B,GetColor(HDT_COLOR).A);
	m_HDTColor->SetColour(color);
	FlexHDTSizer->Add(m_HDTColor,0,wxALL,2);

	wxStaticText *TextHDTTime = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_HDT_TIME),wxDefaultPosition,wxDefaultSize);
	FlexHDTSizer->Add(TextHDTTime,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_HDTTime = new wxSpinCtrl(Scroll,ID_HDT_TIME,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_HDTTime->SetMin(0);
	m_HDTTime->SetMax(3600);
	m_HDTTime->SetValue(GetHDTTime());
	FlexHDTSizer->Add(m_HDTTime,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	wxStaticText *TextHDTLineWidth = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_HDT_LINE_WIDTH),wxDefaultPosition,wxDefaultSize);
	FlexHDTSizer->Add(TextHDTLineWidth,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	m_HDTLineWidth = new wxSpinCtrl(Scroll,ID_HDT_LINE_WIDTH,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_HDTLineWidth->SetMin(0);
	m_HDTLineWidth->SetMax(50);
	m_HDTLineWidth->SetValue(GetHDTLineWidth());
	FlexHDTSizer->Add(m_HDTLineWidth,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	wxStaticText *TextHDTLineStyle = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_HDT_LINE_STYLE),wxDefaultPosition,wxDefaultSize);
	FlexHDTSizer->Add(TextHDTLineStyle,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_HDTLineStyle = new CPenStyleComboBox(Scroll,ID_HDT_LINE_STYLE);
	m_HDTLineStyle->SetSelection(GetHDTLineStyle());
	FlexHDTSizer->Add(m_HDTLineStyle,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	//GPS
	m_GPSPoint = new wxCheckBox(Scroll,ID_SHOW_GPS,GetMsg(MSG_SHOW_GPS));
	m_GPSPoint->SetValue(GetShowGPS());
	ScrollSizer->Add(m_GPSPoint,0,wxALL,5);

	wxFlexGridSizer *FlexGPSSizer = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexGPSSizer,0,wxALL|wxEXPAND,5);

	wxStaticText *TextGPSColor = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_GPS_COLOR),wxDefaultPosition,wxDefaultSize);
	FlexGPSSizer->Add(TextGPSColor,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_GPSColor = new wxColourPickerCtrl(Scroll,ID_GPS_COLOR,*wxBLACK,wxDefaultPosition,wxDefaultSize,wxCLRP_SHOW_LABEL);
	color.Set(GetColor(GPS_COLOR).R,GetColor(GPS_COLOR).G,GetColor(GPS_COLOR).B,GetColor(GPS_COLOR).A);
	m_GPSColor->SetColour(color);
	FlexGPSSizer->Add(m_GPSColor,0,wxALL,2);
	

	Scroll->SetScrollbars(20, 20, 20, 20);


	this->SetSizer(m_Sizer);

}