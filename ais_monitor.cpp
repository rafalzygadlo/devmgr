#include <wx/wx.h>
#include "ais_monitor.h"
#include "conf.h"
#include "tools.h"
#include "ais.h"

CAisMonitor::CAisMonitor() 
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER|wxCAPTION|wxCLOSE_BOX)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	
	for(size_t i = 0; i < 15; i++)
	{
		wxBoxSizer *ChannelSizer = new wxBoxSizer(wxHORIZONTAL);
		Sizer->Add(ChannelSizer,1,wxALL|wxEXPAND,2);

		CAisChannel *Channel = new CAisChannel(this,i);
		ChannelSizer->Add(Channel,1,wxALL|wxEXPAND,2);
	}

	wxPanel *Panel = new wxPanel(this,wxID_ANY);
	Sizer->Add(Panel,0,wxALL|wxEXPAND,5);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	m_Slot = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	PanelSizer->Add(m_Slot,0,wxALL|wxEXPAND,5);
		
	m_Channel = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	PanelSizer->Add(m_Channel,0,wxALL|wxEXPAND,5);

	

}

CAisMonitor::~CAisMonitor()
{

}

void CAisMonitor::SetValues()
{
	m_Slot->SetLabel(wxString::Format(_("%d"),GetSelectedSlot()));
	m_Channel->SetLabel(wxString::Format(_("%d"),GetSelectedChannel()));
}

BEGIN_EVENT_TABLE(CAisChannel,wxPanel)
	EVT_PAINT(OnPaint)
	EVT_SIZE(OnSize)
	EVT_MOUSE_EVENTS(OnMouse)
	EVT_LEAVE_WINDOW(OnMouseLeave)
	EVT_TIMER(ID_TIMER,OnTimer)
END_EVENT_TABLE()


CAisChannel::CAisChannel(CAisMonitor *parent,int id)
:wxPanel(parent)
{
	m_Parent = parent;
	m_Id = id;
	m_CellWidth = 0;
	m_CellHeight = 0;
	SetDoubleBuffered(true);
	m_Timer = new wxTimer(this,ID_TIMER);
	m_Timer->Start(1000);
}

CAisChannel::~CAisChannel()
{

}

void CAisChannel::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	wxColor color(255,255,255);
	SetBackgroundColour(color);
	float width = GetSize().GetWidth();
	float height = GetSize().GetHeight();

	wxPen pen;
	color.Set(150,150,150);
	pen.SetColour(color);

	dc.SetPen(pen);

	m_CellWidth = width/150;
	m_CellHeight = height/2;

	for(size_t i = 1; i < 150; i++)
	{
		//hline
		int x = m_CellWidth * i;
		dc.DrawLine(x,0,x,height);
	}
				
	//vline
	dc.DrawLine(0,0 + m_CellHeight,width,0 + m_CellHeight);
		
	if(m_Selected)
	{
		DrawSelected(m_Row, m_Col, dc);
	}
	
	wxBrush brush;
	brush.SetColour(*wxRED);
	dc.SetBrush(brush);

	for(size_t i = 0; i < 150; i++)
	{
		int id = (m_Id*150) + i;
		if(	ais_get_slot(id))
			dc.DrawRectangle(i * m_CellWidth , 0 * m_CellHeight ,m_CellWidth+2,m_CellHeight+2);
	}

	event.Skip();
}

void CAisChannel::DrawSelected(int row, int col, wxPaintDC &dc)
{
	wxBrush brush;
	brush.SetColour(*wxGREEN);
	dc.SetBrush(brush);

	wxPen pen;
	pen.SetColour(*wxGREEN);
	dc.SetPen(pen);

	dc.DrawRectangle(col * m_CellWidth , row * m_CellHeight ,m_CellWidth+2,m_CellHeight+2);
	
}

void CAisChannel::OnSize(wxSizeEvent &event)
{
	Refresh();
	event.Skip();
}

void CAisChannel::OnMouse(wxMouseEvent &event) 
{
	int x = event.GetX();
	int y = event.GetY();

	m_Col = x/m_CellWidth;
	m_Row = y/m_CellHeight;
	m_Selected = true;	
	
	SetSelectedSlot((m_Id * 150) + m_Col);
	SetSelectedChannel(m_Row);

	Refresh();
	m_Parent->SetValues();

	event.Skip();
}

void CAisChannel::OnMouseLeave(wxMouseEvent &event)
{
	m_Selected = false;
	
	SetSelectedSlot(-1);
	SetSelectedChannel(-1);
	
	m_Parent->SetValues();

	Refresh();
	event.Skip();
}

void CAisChannel::OnTimer(wxTimerEvent &event)
{
	Refresh();
}
