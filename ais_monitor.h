#ifndef __AIS_MONITOR_H
#define __AIS_MONITOR_H

#include <wx/wx.h>

class CAisMonitor : public wxDialog
{
	
public:
	
	CAisMonitor();
	~CAisMonitor();
	
	
};


class CAisChannel : public wxPanel
{
	
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);

public:
	
	CAisChannel(wxWindow *parent);
	~CAisChannel();
		
	DECLARE_EVENT_TABLE();
};


#endif
