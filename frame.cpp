#include "frame.h"
#include "conf.h"
#include "dll.h"
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include "tools.h"
#include "ais.h"
#include "GeometryTools.h"

DEFINE_EVENT_TYPE(EVT_SHOW_WINDOW)

BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
//	EVT_BUTTON(ID_SAVE,CMyFrame::OnSaveButton)
	EVT_COMMAND(ID_SHOW,EVT_SHOW_WINDOW,CMyFrame::OnShowWindow)
END_EVENT_TABLE()


extern CNaviMapIOApi *ThisPtr;
extern CNaviBroker *BrokerPtr;
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//FRAME

CMyFrame::CMyFrame(void *Parent, wxWindow *ParentPtr)
	:wxDialog(ParentPtr,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_3D)
{
	m_DLL = (CMapPlugin*)Parent;
	m_ParentPtr = ParentPtr;
	m_AfterInit = false;
	m_SelectedPtr = NULL;
	m_Minutes = m_Seconds = 0;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxNotebook *m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME|wxCLIP_CHILDREN);
	//m_Notebook->SetDoubleBuffered(true);
	MainSizer->Add(m_Notebook,1,wxALL|wxEXPAND,0);
	
	// Page0
	m_Page0 = new wxPanel(m_Notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Notebook->AddPage(m_Page0,(GetMsg(MSG_AIS_INFO_SIMPLE)));
	wxBoxSizer *Page1Sizer = new wxBoxSizer(wxVERTICAL);
	m_Page0->SetSizer(Page1Sizer);

	m_Html0 = new wxHtmlWindow(m_Page0,wxID_ANY,wxDefaultPosition,wxSize(300,350));
	Page1Sizer->Add(m_Html0,1,wxALL|wxEXPAND,0);
		
	// Page2
	m_Page1 = new wxPanel(m_Notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Notebook->AddPage(m_Page1,(GetMsg(MSG_AIS_INFO_ALL)));
	wxBoxSizer *Page2Sizer = new wxBoxSizer(wxVERTICAL);
	m_Page1->SetSizer(Page2Sizer);
	m_Html1 = new wxHtmlWindow(m_Page1,wxID_ANY,wxDefaultPosition,wxSize(300,350));
	Page2Sizer->Add(m_Html1,1,wxALL|wxEXPAND,0);
	
	//MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
		
	m_Time = new wxStaticText(this,wxID_ANY,wxEmptyString);
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
	ShowWindowEvent(event.GetInt());
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
	SetReportTime();
}

void CMyFrame::SetReportTime()
{
	if(m_SelectedPtr == NULL)
		return;
		
	ais_t *ais = (ais_t*)m_SelectedPtr->ais_ptr;
	m_Seconds = (GetTickCount() - ais->timeout)/1000;
		
	int minutes = m_Seconds/60;
	div_t _div = div(m_Seconds,60);
	m_Time->SetLabel(wxString::Format(_("Last Report Timeout: %02d:%02d"),minutes,_div.rem));

	if(m_Seconds == 0)
		SetValues();
	
}

void CMyFrame::SetValues()
{
	m_ParentX = m_ParentPtr->GetScreenPosition().x;
	m_ParentY = m_ParentPtr->GetScreenPosition().y;
		
	double to_x, to_y;
	m_SelectedPtr = m_DLL->GetSelectedPtr();
	if(m_SelectedPtr == NULL)
		return;
		
	m_DLL->GetBroker()->Unproject(m_SelectedPtr->lon,m_SelectedPtr->lat,&to_x,&to_y);
		
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
	
	ais_t *ais = (ais_t*)m_SelectedPtr->ais_ptr;
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

}


void CMyFrame::ShowWindow(bool show)
{
	if(show)
		SetValues();
	
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