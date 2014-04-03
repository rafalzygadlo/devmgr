#include "frame.h"
#include "conf.h"
#include "dll.h"
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include "tools.h"
#include "ais.h"
#include "GeometryTools.h"


BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
//	EVT_BUTTON(ID_SAVE,CMyFrame::OnSaveButton)
END_EVENT_TABLE()

extern CNaviMapIOApi *ThisPtr;
extern CNaviBroker *BrokerPtr;
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//FRAME

CMyFrame::CMyFrame(void *Parent, wxWindow *ParentPtr)
	:wxDialog(ParentPtr,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_3D)
{
	m_DLL = (CMapPlugin*)Parent;
	_ParentPtr = ParentPtr;
	AfterInit = false;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	wxNotebook *m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME|wxCLIP_CHILDREN);
	//m_Notebook->SetDoubleBuffered(true);
	MainSizer->Add(m_Notebook,1,wxALL|wxEXPAND,0);
	
	// Page0
	Page0 = new wxPanel(m_Notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Notebook->AddPage(Page0,(GetMsg(MSG_AIS_INFO_SIMPLE)));
	wxBoxSizer *Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page0->SetSizer(Page1Sizer);
	m_Html0 = new wxHtmlWindow(Page0,wxID_ANY,wxDefaultPosition,wxSize(350,400));
	Page1Sizer->Add(m_Html0,1,wxALL|wxEXPAND,0);
			
	// Page2
	Page1 = new wxPanel(m_Notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Notebook->AddPage(Page1,(GetMsg(MSG_AIS_INFO_ALL)));
	wxBoxSizer *Page2Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(Page2Sizer);
	m_Html1 = new wxHtmlWindow(Page1,wxID_ANY,wxDefaultPosition,wxSize(350,400));
	Page2Sizer->Add(m_Html1,1,wxALL|wxEXPAND,0);
	
	//Html = new wxHtmlWindow(Page1,wxID_ANY,wxDefaultPosition,wxSize(350,400));
	//Page2Sizer->Add(Html,1,wxALL|wxEXPAND,0);
		
	//Other
	//ButtonClose = new wxButton(this,ID_CLOSE,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	//MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
		
	this->SetSizer(MainSizer);
		
	if(GetSizer())
		GetSizer()->SetSizeHints(this);
		
	Center();
	//this->SetTransparent(220);
	AfterInit = true;
}

CMyFrame::~CMyFrame(void)
{

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

void CMyFrame::ShowWindow(bool show)
{
	if(show)
	{
		
		ParentX = _ParentPtr->GetScreenPosition().x;
		ParentY = _ParentPtr->GetScreenPosition().y;
		
		double to_x, to_y;
		SelectedPtr = m_DLL->GetSelectedPtr();
		if(SelectedPtr == NULL)
			return;
		
		m_DLL->GetBroker()->Unproject(SelectedPtr->lon,SelectedPtr->lat,&to_x,&to_y);
		
		double vm[4];
		m_DLL->GetBroker()->GetVisibleMap(vm);
		
		float scale = m_DLL->GetBroker()->GetMapScale();
		wxPoint pt;
		pt.x = (int)((-vm[0] + to_x) * scale) + ParentX;
		pt.y = (int)((-vm[1] + -to_y) * scale) + ParentY;
		
		
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
	
		ais_t *ais = (ais_t*)SelectedPtr->ais_ptr;
		ClearHtml(PAGE_0);
		SetHtml(_("<a name='top'></a><br>"),PAGE_0);
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