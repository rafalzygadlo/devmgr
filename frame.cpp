#include "frame.h"
#include "conf.h"
#include "dll.h"
#include <wx/statline.h>
#include <wx/dirdlg.h>
#include "NaviMapIOApi.h"
#include "tools.h"
#include "ais.h"


BEGIN_EVENT_TABLE(CMyFrame,wxDialog)
	EVT_BUTTON(ID_CLOSE,CMyFrame::OnCloseButton)
//	EVT_BUTTON(ID_SAVE,CMyFrame::OnSaveButton)
END_EVENT_TABLE()

extern CNaviMapIOApi *ThisPtr;
extern CNaviBroker *BrokerPtr;
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//FRAME

CMyFrame::CMyFrame(void *Parent, wxWindow *ParentPtr)
	:wxDialog(ParentPtr,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize)
{
	m_DLL = (CMapPlugin*)Parent;
	_ParentPtr = ParentPtr;
	AfterInit = false;
	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);
	Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	// Page1
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
		
	Panel->SetSizer(PanelSizer);
	
	Html = new wxHtmlWindow(Panel,wxID_ANY,wxDefaultPosition,wxSize(300,400));
	PanelSizer->Add(Html,1,wxALL|wxEXPAND,0);
			
	//Other
	MainSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	//ButtonClose = new wxButton(this,ID_CLOSE,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	//MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);
		
	this->SetSizer(MainSizer);
		
	if(GetSizer())
		GetSizer()->SetSizeHints(this);
		
	Center();
	//this->SetTransparent(200);
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

void CMyFrame::SetHtml(wxString html)
{
	Html->AppendToPage(html);
}

void CMyFrame::ClearHtml()
{
	Html->SetPage(wxEmptyString);
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
			
		this->SetPosition(pt);
	
		ClearHtml();
		SetHtml(_("<a name='top'></a><br>"));
		ais_t *ais = (ais_t*)SelectedPtr->ais_ptr;
		SetHtml(PrintHtmlAnchors(ais));
	
		for(size_t i = 0; i < AIS_MESSAGES_LENGTH; i++)
		{
			if(ais->valid[i])
			{
				SetHtml(PrintHtmlMsg(ais,i));
			}
		}
		
	}
	
	Show(show);
	if(show)
		Html->SetFocus();
}

