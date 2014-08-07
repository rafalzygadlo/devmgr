#include "frame.h"
#include "conf.h"
#include "dll.h"
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include "tools.h"
#include "ais_html.h"
#include "GeometryTools.h"
#include "options.h"
#include <wx/dialog.h>


DEFINE_EVENT_TYPE(EVT_SHOW_WINDOW)

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
//	EVT_BUTTON(ID_SAVE,CMyFrame::OnSaveButton)
	EVT_COMMAND(ID_SHOW,EVT_SHOW_WINDOW,CMyFrame::OnShowWindow)
END_EVENT_TABLE()

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//FRAME

CMyFrame::CMyFrame(void *Parent, wxWindow *ParentPtr)
:wxDialog(ParentPtr,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER)
{
	m_DLL = (CMapPlugin*)Parent;
	m_ParentPtr = ParentPtr;
	m_AfterInit = false;
	m_Minutes = m_Seconds = 0;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxNotebook *m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	//m_Notebook->SetDoubleBuffered(true);
	MainSizer->Add(m_Notebook,1,wxALL|wxEXPAND,0);
	
	// Page1
	m_Page0 = new wxPanel(m_Notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Notebook->AddPage(m_Page0,(GetMsg(MSG_AIS_INFO_SIMPLE)));
	wxBoxSizer *Page1Sizer = new wxBoxSizer(wxVERTICAL);
	m_Page0->SetSizer(Page1Sizer);
		
	wxBitmap bmp;
	m_ShipImage = new wxStaticBitmap(m_Page0,wxID_ANY,bmp,wxDefaultPosition,wxSize(300,150));
	Page1Sizer->Add(m_ShipImage,0,wxALL,0);
		
	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *Scroll = new wxScrolledWindow(m_Page0, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	Page1Sizer->Add(Scroll,1,wxALL|wxEXPAND,0);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(ScrollSizer);
	/*		
	wxFont font;
	font.SetPointSize(14);
	font.SetWeight(wxBOLD);
	m_Name = new wxTextCtrl(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_READONLY|wxNO_BORDER);
	m_Name->SetFont(font);
	ScrollSizer->Add(m_Name,0,wxALL|wxEXPAND,0);
	
	wxFlexGridSizer *FlexSizer0 = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexSizer0,0,wxALL|wxEXPAND,0);
		
	font.SetPointSize(11);
	//mmsi
	wxStaticText *MMSIText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_MMSI),wxDefaultPosition,wxDefaultSize);
	FlexSizer0->Add(MMSIText,0,wxALL,5);
	m_MMSI = new wxTextCtrl(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_READONLY|wxNO_BORDER);
	m_MMSI->SetFont(font);
	FlexSizer0->Add(m_MMSI,0,wxALL,5);
	
	wxStaticText *CALLSIGNText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_CALLSIGN),wxDefaultPosition,wxDefaultSize);
	FlexSizer0->Add(CALLSIGNText,0,wxALL,5);
	m_CALLSIGN = new wxTextCtrl(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_READONLY|wxNO_BORDER);
	m_CALLSIGN->SetFont(font);
	FlexSizer0->Add(m_CALLSIGN,0,wxALL,5);

	wxStaticText *IMOText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_IMO_NUMBER),wxDefaultPosition,wxDefaultSize);
	FlexSizer0->Add(IMOText,0,wxALL,5);
	m_IMO = new wxTextCtrl(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_READONLY|wxNO_BORDER);
	m_IMO->SetFont(font);
	FlexSizer0->Add(m_IMO,0,wxALL,5);

	wxStaticLine *Line = new wxStaticLine(Scroll,wxID_ANY);
	ScrollSizer->Add(Line,0,wxALL|wxEXPAND,0);

	wxFlexGridSizer *FlexSizer1 = new wxFlexGridSizer(2);
	ScrollSizer->Add(FlexSizer1,0,wxALL|wxEXPAND,0);
	
	font.SetPointSize(10);
	wxStaticText *FlagText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_FLAG),wxDefaultPosition,wxDefaultSize);
	FlexSizer1->Add(FlagText,0,wxALL,3);
	m_Flag = new wxStaticText(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_Flag->SetFont(font);
	FlexSizer1->Add(m_Flag,0,wxALL,3);
	
	wxStaticText *COGText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_COG),wxDefaultPosition,wxDefaultSize);
	FlexSizer1->Add(COGText,0,wxALL,3);
	m_COG = new wxStaticText(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_COG->SetFont(font);
	FlexSizer1->Add(m_COG,0,wxALL,3);
	
	wxStaticText *HDTText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_HEADING),wxDefaultPosition,wxDefaultSize);
	FlexSizer1->Add(HDTText,0,wxALL,3);
	m_HDT = new wxStaticText(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_HDT->SetFont(font);
	FlexSizer1->Add(m_HDT,0,wxALL,3);
	
	wxStaticText *SOGText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_SPEED),wxDefaultPosition,wxDefaultSize);
	FlexSizer1->Add(SOGText,0,wxALL,3);
	m_SOG = new wxStaticText(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_SOG->SetFont(font);
	FlexSizer1->Add(m_SOG,0,wxALL,3);

	wxStaticText *LONText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_LON),wxDefaultPosition,wxDefaultSize);
	FlexSizer1->Add(LONText,0,wxALL,2);
	m_LON = new wxStaticText(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_LON->SetFont(font);
	FlexSizer1->Add(m_LON,0,wxALL,3);
	
	wxStaticText *LATText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_LAT),wxDefaultPosition,wxDefaultSize);
	FlexSizer1->Add(LATText,0,wxALL,3);
	m_LAT = new wxStaticText(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_LAT->SetFont(font);
	FlexSizer1->Add(m_LAT,0,wxALL,3);

	wxStaticText *DraughtText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_DRAUGHT),wxDefaultPosition,wxDefaultSize);
	FlexSizer1->Add(DraughtText,0,wxALL,3);
	m_Draught = new wxStaticText(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_Draught->SetFont(font);
	FlexSizer1->Add(m_Draught,0,wxALL,3);

	wxStaticText *TurnText = new wxStaticText(Scroll,wxID_ANY,GetMsg(MSG_TURN),wxDefaultPosition,wxDefaultSize);
	FlexSizer1->Add(TurnText,0,wxALL,3);
	m_Turn = new wxStaticText(Scroll,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_Turn->SetFont(font);
	FlexSizer1->Add(m_Turn,0,wxALL,3);

	
	/*
	str.Append(wxString::Format(_("<font size=2><tr><td><b>%s</b></td><td>%s</td></tr></font>"),GetMsg(MSG_COG),ar.Item(5)));
	str.Append(wxString::Format(_("<font size=2><tr><td><b>%s</b></td><td>%s</td></tr></font>"),GetMsg(MSG_HEADING),ar.Item(6)));
	str.Append(wxString::Format(_("<font size=2><tr><td><b>%s</b></td><td>%s</td></tr></font>"),GetMsg(MSG_SPEED),ar.Item(7)));
	str.Append(wxString::Format(_("<font size=2><tr><td><b>%s</b></td><td>%s</td></tr></font>"),GetMsg(MSG_LON),ar.Item(8)));
	str.Append(wxString::Format(_("<font size=2><tr><td><b>%s</b></td><td>%s</td></tr></font>"),GetMsg(MSG_LAT),ar.Item(9)));
	str.Append(wxString::Format(_("<font size=2><tr><td><b>%s</b></td><td>%s</td></tr></font>"),GetMsg(MSG_DRAUGHT),ar.Item(10)));
	str.Append(wxString::Format(_("<font size=2><tr><td><b>%s</b></td><td>%s</td></tr></font>"),GetMsg(MSG_TURN),ar.Item(11)));
	*/


	m_Html0 = new wxHtmlWindow(Scroll,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	ScrollSizer->Add(m_Html0,1,wxALL|wxEXPAND,0);
		
	Scroll->SetScrollbars(20, 20, 20, 20);
	
	// Page2
	m_Page1 = new wxPanel(m_Notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Notebook->AddPage(m_Page1,(GetMsg(MSG_AIS_INFO_ALL)));
	wxBoxSizer *Page2Sizer = new wxBoxSizer(wxVERTICAL);
	m_Page1->SetSizer(Page2Sizer);
	m_Html1 = new wxHtmlWindow(m_Page1,wxID_ANY,wxDefaultPosition,wxSize(300,350));
	Page2Sizer->Add(m_Html1,1,wxALL|wxEXPAND,0);
	
	//MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
		
	m_Time = new wxStaticText(this,wxID_ANY,wxEmptyString);
	m_Time->SetDoubleBuffered(true);
	MainSizer->Add(m_Time,0,wxALL|wxALIGN_LEFT,5);

	this->SetSizer(MainSizer);
		
	if(GetSizer())
		GetSizer()->SetSizeHints(this);
		
	Center();
	//this->SetTransparent(220);

	m_Ticker = new CTicker(this,TICK_WINDOW_REFRESH);
	m_Ticker->Start(WINDOW_REFRESH_INTERVAL);

	m_AfterInit = true;
}

CMyFrame::~CMyFrame(void)
{
	m_Ticker->Stop();
	delete m_Ticker;
}

void CMyFrame::OnCloseButton(wxCommandEvent &event)
{	/*
	wcscpy_s(MarkerSelectedPtr->name,MARKER_NAME_SIZE, textname->GetValue().wc_str()); 
	wcscpy_s(MarkerSelectedPtr->description, MARKER_DESCRIPTION_SIZE, textdescription->GetValue().wc_str()); 
	*/
	Hide();
	
}

void CMyFrame::OnClose(wxCloseEvent &event)
{
	Hide();
}

void CMyFrame::ShowWindowEvent(bool show)
{
	wxCommandEvent evt(EVT_SHOW_WINDOW,ID_SHOW);
	evt.SetInt(show);
	wxPostEvent(this,evt);

}

void CMyFrame::OnShowWindow(wxCommandEvent &event)
{
	ShowWindow(event.GetInt());
}

void CMyFrame::SetData(SAisData *ptr)
{
/*	
	if(ptr->valid_name)
		m_Name->SetLabel(wxString::Format(_("%s"),ptr->name));
	else
		m_Name->SetLabel(GetMsg(MSG_NA));
	
	m_MMSI->SetLabel(wxString::Format(_("%d"), ptr->mmsi));
	m_CALLSIGN->SetLabel(wxString::Format(_("%s"), ptr->callsign));
	m_IMO->SetLabel(wxString::Format(_("%d"), ptr->imo));

	ais_mid *mid = ais_get_mid(ptr->mmsi);
	if(mid)
		m_Flag->SetLabel(mid->name);	
	else
		m_Flag->SetLabel(GetMsg(MSG_NA));

	if(ptr->valid_cog)	
		m_COG->SetLabel(wxString::Format(_("%4.2f"), ptr->cog)); 
	else
		m_COG->SetLabel(GetMsg(MSG_NA)); 

	if(ptr->valid_hdg)	
		m_HDT->SetLabel(wxString::Format(_("%4.2f"), ptr->hdg)); 
	else
		m_HDT->SetLabel(GetMsg(MSG_NA)); 

	if(ptr->valid_sog)	
		m_SOG->SetLabel(wxString::Format(_("%4.2f"), ptr->sog)); 
	else
		m_SOG->SetLabel(GetMsg(MSG_NA)); 

	if(ptr->valid_pos)
	{	
		m_LON->SetLabel(wxString::Format(_("%4.2f"), ptr->lon)); 
		m_LAT->SetLabel(wxString::Format(_("%4.2f"), ptr->lat)); 
	
	}else{
	
		m_LON->SetLabel(GetMsg(MSG_NA)); 
		m_LAT->SetLabel(GetMsg(MSG_NA)); 
	}

	if(ptr->valid_draught)	
		m_Draught->SetLabel(wxString::Format(_("%d"), ptr->draught)); 
	else
		m_Draught->SetLabel(GetMsg(MSG_NA)); 

	m_Turn->SetLabel(GetTurn(ptr->turn)); 
	
	*/
}

void CMyFrame::SetHtml(wxString html,int page)
{
	switch(page)
	{
		case PAGE_0: m_Html0->AppendToPage(html); break;
		case PAGE_1: m_Html1->AppendToPage(html); break;
	}
}

void CMyFrame::ClearHtml(int page)
{
	switch(page)
	{
		case PAGE_0: m_Html0->SetPage(wxEmptyString); break;
		case PAGE_1: m_Html1->SetPage(wxEmptyString); break;
	}
}

void CMyFrame::OnTickerTick()
{	
	if(this->IsShown())
		SetReportTime();
}

void CMyFrame::SetReportTime()
{
	SAisData *ptr = GetSelectedPtr();
	if(ptr == NULL)
		return;
		
	ais_t *ais = (ais_t*)ptr->ais_ptr;
	m_Seconds = (GetTickCount() - ais->timeout)/1000;
		
	int minutes = m_Seconds/60;
	div_t _div = div(m_Seconds,60);
	m_Time->SetLabel(wxString::Format(_("%s: %02d:%02d"),GetMsg(MSG_AGE), minutes,_div.rem));

	if(m_Seconds == 0)
	{
		SetValues();
		this->Layout();
	}
	
}

void CMyFrame::SetValues()
{
	m_ParentX = m_ParentPtr->GetScreenPosition().x;
	m_ParentY = m_ParentPtr->GetScreenPosition().y;
		
	double to_x, to_y;
	SAisData *ptr = GetSelectedPtr();
	if(ptr == NULL)
		return;
		
	m_DLL->GetBroker()->Unproject(ptr->lon,ptr->lat,&to_x,&to_y);
		
	double vm[4];
	m_DLL->GetBroker()->GetVisibleMap(vm);
		
	float scale = m_DLL->GetBroker()->GetMapScale();
	wxPoint pt;
	pt.x = (int)((-vm[0] + to_x) * scale) + m_ParentX;
	pt.y = (int)((-vm[1] + -to_y) * scale) + m_ParentY;
		
		
	wxPoint p2,p4;
	wxSize size = this->GetSize();
				
	p2.x = pt.x + size.GetWidth(); p2.y = pt.y;
				
	if(!IsOnScreen(p2.x,p2.y))
	{
		pt.x = pt.x - size.GetWidth();
		pt.y = pt.y;
	}
						
	p4.x = pt.x; p4.y = pt.y + size.GetHeight();

	if(!IsOnScreen(p4.x,p4.y))
	{
		pt.x = pt.x;
		pt.y = pt.y - size.GetHeight();
	}
		
	this->SetPosition(pt);
	
	ais_t *ais = (ais_t*)ptr->ais_ptr;

// HTML	
		
	int spos0 = m_Html0->GetScrollPos(wxVERTICAL);
	int spos1 = m_Html1->GetScrollPos(wxVERTICAL);
	
	m_Html0->Freeze();
	m_Html1->Freeze();
	ClearHtml(PAGE_0);
	SetHtml(PrintHtmlSimple(ais),PAGE_0);
		
	ClearHtml(PAGE_1);
	SetHtml(_("<a name='top'></a><br>"),PAGE_1);
	SetHtml(PrintHtmlAnchors(ais),PAGE_1);
		
	for(size_t i = 0; i < AIS_MESSAGES_LENGTH; i++)
	{
		if(ais->valid[i])
		{
			SetHtml(PrintHtmlMsg(ais,i),PAGE_1);
		}
	}
	m_Html0->Scroll(0,spos0);
	m_Html1->Scroll(0,spos1);
	m_Html0->Thaw();
	m_Html1->Thaw();
		
}

void CMyFrame::SetImage()
{
	SAisData *ptr = GetSelectedPtr();
	if(ptr == NULL)
		return;
	
	char *buffer = NULL;
	int size;
	
	if(GetShipImage(ptr->mmsi,buffer,&size))
	{
		if(buffer == NULL)
			return;
		wxMemoryInputStream in_0(buffer, size);
		wxImage img_0(in_0,wxBITMAP_TYPE_ANY);

		img_0.ResampleNearest(100,150);
		free(buffer);		
		
		if(img_0.IsOk())
		{
			wxBitmap bmp_0(img_0);
			m_ShipImage->SetBitmap(bmp_0);
			m_ShipImage->Show();
			m_Page0->Layout();
		}

	}else{
	
		m_ShipImage->Hide();
		m_Page0->Layout();
	
	}

	if(GetSizer())
			GetSizer()->SetSizeHints(this);
	
}


void CMyFrame::ShowWindow(bool show)
{
	if(show)
	{
		SetImage();
		SetValues();
	}
	
	Show(show);
	
}

bool CMyFrame::IsOnScreen(int x, int y)
{
	int sWidth;
	int sHeight;
	wxDisplaySize(&sWidth,&sHeight);
	
	if(IsPointInsideBox(x, y, 0 , 0, sWidth, sHeight))
		return true;

	return false;
}