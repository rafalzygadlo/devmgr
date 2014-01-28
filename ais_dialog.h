#ifndef __AIS_DIALOG_H
#define __AIS_DIALOG_H

#include <wx/wx.h>
#include <wx/html/htmlwin.h>
#include "NaviMapIOApi.h"
#include "NaviDisplayApi.h"
#include "dll.h"

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif

class CAisDialog : public wxDialog
{
	wxHtmlWindow *m_Html;
	void GetPanel();
	void SetList();
	void ClearList();
	void OnTimer(wxTimerEvent &event);

public:
	
	CAisDialog();
	~CAisDialog();
	void SetText(wxString text);
		
	DECLARE_EVENT_TABLE();
};


#endif