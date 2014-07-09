#include <wx/wx.h>
#include "ais_monitor.h"
#include "conf.h"
#include "tools.h"
#include "ais.h"

BEGIN_EVENT_TABLE(CAisMonitor,wxPanel)
	EVT_BUTTON(ID_CLEAR,OnClear)
	EVT_COMBOBOX(ID_DEVICE,OnDevice)
END_EVENT_TABLE()

CAisMonitor::CAisMonitor(wxWindow *parent) 
	:wxPanel(parent,wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
			
	
	wxComboBox *Device = new wxComboBox(this,ID_DEVICE,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	
	Sizer->Add(Device,0,wxALL,5);
	
	int counter = 0;
	for(size_t i = 0; i < GetDevices()->size(); i++)
	{
		CReader *reader = (CReader*)GetDevices()->Item(i);
		if(reader->GetDeviceType() == DEVICE_TYPE_AIS)
		{

			if(reader->GetConnectionType() == CONNECTION_TYPE_SERIAL)
				Device->Append(wxString::Format(_("[%s:%d] %s"),reader->GetSerialPort(),reader->GetBaudRate(),reader->GetDeviceName()));
			
			if(reader->GetConnectionType() == CONNECTION_TYPE_SOCKET)
				Device->Append(wxString::Format(_("[%s::%d] %s"),reader->GetHost() ,reader->GetSocketPort(), reader->GetDeviceName()));

			Device->SetClientData(counter,reader);
			counter++;
		}
	}


	for(size_t i = 0; i < 15; i++)
	{
		wxBoxSizer *ChannelSizer = new wxBoxSizer(wxHORIZONTAL);
		Sizer->Add(ChannelSizer,1,wxALL|wxEXPAND,2);

		CAisChannel *Channel = new CAisChannel(this,i);
		ChannelSizer->Add(Channel,1,wxALL|wxEXPAND,2);
		m_Channels.Add(Channel);
	}

	wxPanel *Panel = new wxPanel(this,wxID_ANY);
	Sizer->Add(Panel,0,wxALL|wxEXPAND,5);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(PanelSizer);
	
	wxBoxSizer *LeftSizer = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(LeftSizer,0,wxALL|wxEXPAND,5);

	m_Slot = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	LeftSizer->Add(m_Slot,0,wxALL|wxEXPAND,5);
		
	m_Channel = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	LeftSizer->Add(m_Channel,0,wxALL|wxEXPAND,5);

	m_MID = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	LeftSizer->Add(m_MID,0,wxALL|wxEXPAND,5);
	
	PanelSizer->AddStretchSpacer(1);
	wxBoxSizer *RightSizer = new wxBoxSizer(wxVERTICAL);
	PanelSizer->Add(RightSizer,0,wxALL|wxEXPAND,5);
	
	wxButton *ButtonClear = new wxButton(Panel,ID_CLEAR,GetMsg(MSG_CLEAR));
	RightSizer->Add(ButtonClear,0,wxALL|wxEXPAND,5);
	
}

CAisMonitor::~CAisMonitor()
{
	m_Channels.Clear();
}

void CAisMonitor::OnDevice(wxCommandEvent &event)
{
	CReader *reader =  (CReader*)event.GetClientData();
				
	for(size_t i = 0; i < m_Channels.size();i++)
	{
		CAisChannel *ptr = (CAisChannel*)m_Channels.Item(i);
		ptr->SetDevice(reader);
	}
	
}

void CAisMonitor::OnClear(wxCommandEvent &event)
{
	//ais_unset_communication_state();
}

void CAisMonitor::OnClose(wxCommandEvent &event)
{

}

void CAisMonitor::SetValues()
{
	m_Slot->SetLabel(wxString::Format(_("%d"),GetSelectedSlot()));
	m_Channel->SetLabel(wxString::Format(_("%d"),GetSelectedChannel()));
	m_MID->SetLabel(wxString::Format(_("%d"),GetSelectedMID()));
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
	m_Device = NULL;
	
}

CAisChannel::~CAisChannel()
{
	m_Timer->Stop();
	delete m_Timer;
}

void CAisChannel::SetDevice(void *device)
{
	m_Device = (CReader*)device;
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
		
	DrawCells(dc);
	DrawSelected(m_Row, m_Col, dc);
		
	event.Skip();
}

void CAisChannel::DrawCells(wxPaintDC &dc)
{

	wxBrush brush;
	brush.SetColour(*wxRED);
	dc.SetBrush(brush);
	
	if(m_Device == NULL)
		return;
	SAisState *ptr = m_Device->GetAisStatePtr();
	
	for(size_t i = 0; i < 150; i++)
	{
		int id = (m_Id*150) + i;
		if(	ptr->slot_a[id])
		{
			int mid = ptr->slot_a_mid[id];
			SetColor(mid,dc);
			dc.DrawRectangle(i * m_CellWidth , 0 * m_CellHeight ,m_CellWidth+2,m_CellHeight+2);
		}
		
		if(	ptr->slot_b[id])
		{
			int mid = ptr->slot_b_mid[id];
			SetColor(mid,dc);
			dc.DrawRectangle(i * m_CellWidth , 1 * m_CellHeight ,m_CellWidth+2,m_CellHeight+2);
		}
	}


}
void CAisChannel::DrawSelected(int row, int col, wxPaintDC &dc)
{
	if(!m_Selected)
		return;

	wxBrush brush;
	brush.SetColour(*wxGREEN);
	dc.SetBrush(brush);

	wxPen pen;
	pen.SetColour(*wxGREEN);
	dc.SetPen(pen);

	dc.DrawRectangle(col * m_CellWidth , row * m_CellHeight ,m_CellWidth+2,m_CellHeight+2);
	
}

void CAisChannel::SetColor(int mid,wxPaintDC &dc)
{
	
	wxColor color;
	
	switch(mid)
	{
		case AIS_MSG_1:	
		case AIS_MSG_2: 
		case AIS_MSG_3:		color.Set(0,255,0);	break;
		case AIS_MSG_4:		color.Set(255,0,0); break;
		case AIS_MSG_11:	color.Set(0,0,255); break;
		case AIS_MSG_9:		color.Set(0,0,255);	break;
		case AIS_MSG_18:	color.Set(0,0,255);	break;
	}
	
	wxBrush brush;
	brush.SetColour(color);
	dc.SetBrush(brush);

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
	
	int slot = (m_Id * 150) + m_Col;
	int channel = m_Row;
	char _channel = ais_get_channel(channel);

	SetSelectedSlot(slot);
	SetSelectedChannel(channel);

	if(m_Device == NULL)
		return;
	SAisState *ptr = m_Device->GetAisStatePtr();
	
	int mid = ais_get_message_id(slot,_channel,ptr);
	SetSelectedMID(mid);

	Refresh();
	m_Parent->SetValues();

	event.Skip();
}

void CAisChannel::OnMouseLeave(wxMouseEvent &event)
{
	m_Selected = false;
	
	SetSelectedSlot(-1);
	SetSelectedChannel(-1);
	SetSelectedMID(-1);
	
	m_Parent->SetValues();

	Refresh();
	event.Skip();
}

void CAisChannel::OnTimer(wxTimerEvent &event)
{
	
	Refresh();
}
