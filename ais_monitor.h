#ifndef __AIS_MONITOR_H
#define __AIS_MONITOR_H

#include <wx/wx.h>
#include "reader.h"

class CAisMonitor : public wxPanel
{
	wxStaticText *m_Slot, *m_Channel, *m_MID;
	wxArrayPtrVoid m_Channels;

	void OnClear(wxCommandEvent &event);
	void OnClose(wxCommandEvent &event);
	void OnDevice(wxCommandEvent &event);

public:
	
	CAisMonitor(wxWindow *parent);
	~CAisMonitor();
	
	void SetValues();

	enum
	{
		ID_CLEAR = 4552,
		ID_CLOSE,
		ID_DEVICE,
	};
	
	DECLARE_EVENT_TABLE();

};


class CAisChannel : public wxPanel
{
	wxTimer *m_Timer;
	int m_Id;
	int m_Col,m_Row;
	bool m_Selected;
	CAisMonitor *m_Parent;
	CReader *m_Device;
	float m_CellWidth,m_CellHeight;
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnMouse(wxMouseEvent &event);
	void OnMouseLeave(wxMouseEvent &event);
	void OnTimer(wxTimerEvent &event);
	void DrawSelected(int row, int col, wxPaintDC &dc);
	void DrawCells( wxPaintDC &dc);
	void SetColor(int mid,wxPaintDC &dc);

public:
	
	CAisChannel(CAisMonitor *parent, int id);
	~CAisChannel();
	void SetDevice(void *device);
		
	enum
	{
		ID_TIMER = 1234,
	};

	DECLARE_EVENT_TABLE();
};


#endif
