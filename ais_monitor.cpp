#include <wx/wx.h>
#include "ais_monitor.h"
#include "conf.h"


CAisMonitor::CAisMonitor() 
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER|wxCAPTION)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	SetSizer(Sizer);
	
	CAisChannel *Channel = new CAisChannel(this);

	Sizer->Add(Channel,1,wxALL|wxEXPAND,5);

}

CAisMonitor::~CAisMonitor()
{

}

BEGIN_EVENT_TABLE(CAisChannel,wxPanel)
	EVT_PAINT(OnPaint)
	EVT_SIZE(OnSize)
END_EVENT_TABLE()


CAisChannel::CAisChannel(wxWindow *parent) 
:wxPanel(parent)
{
	
}

CAisChannel::~CAisChannel()
{

}

void CAisChannel::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	wxColor color(255,255,255);
	SetBackgroundColour(color);
	int width = GetSize().GetWidth() - 5;
	int height = GetSize().GetHeight() - 5;

	for(size_t i = 0; i < 50; i++)
	{
		//hline
		int ox = int(width/50) * i;
		dc.DrawLine(ox,5,ox,height);
	}
	
	dc.DrawLine(0 + width,0,0 + width,height);

	for(size_t i = 0; i < 3; i++)
	{
		//vline
		int oy = (height/2) * i;
		dc.DrawLine(5,5 + oy,width,oy);
	}

	//dc.DrawLine(0,0,x2,0);
	//dc.DrawLine(0,0,x2/2,0);
	event.Skip();
}

void CAisChannel::OnSize(wxSizeEvent &event)
{
	Refresh();
	event.Skip();
}