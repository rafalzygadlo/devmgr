#ifndef __AIS_MONITOR_H
#define __AIS_MONITOR_H

#include <wx/wx.h>

class CAisMonitor : public wxDialog
{
	wxStaticText *m_Slot, *m_Channel, *m_MID;

	void OnClear(wxCommandEvent &event);
	void OnClose(wxCommandEvent &event);

public:
	
	CAisMonitor();
	~CAisMonitor();
	
	void SetValues();

	enum
	{
		ID_CLEAR = 4552,
		ID_CLOSE,
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
		
	enum
	{
		ID_TIMER = 1234,
	};

	DECLARE_EVENT_TABLE();
};


#endif
