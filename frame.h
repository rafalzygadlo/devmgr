#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/fileconf.h>
#include <wx/mstream.h>
#include "conf.h"
#include "dll.h"
#include <vector>
#include <wx/html/htmlwin.h>

class CMyIcon;
class CMapPlugin;
class CMyFrame: public wxDialog
{
	SAisData *m_SelectedPtr;
	CMapPlugin *m_DLL;	
	wxPanel *m_Page0,*m_Page1;
	wxStaticText *m_Time;
	int m_ParentX, m_ParentY;
	wxWindow *m_ParentPtr;
	wxHtmlWindow *m_Html0, *m_Html1;
	bool m_AfterInit;
	CTicker *m_Ticker;
	int m_Seconds,m_Minutes;
	
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void SetHtml(wxString html, int page);
	void ShowHtmlPanel();
	void ClearHtml(int page);
	bool IsOnScreen(int x, int y);
	void SetReportTime();
	void SetValues();

public:
		
	void ShowWindow(bool show);		
	CMyFrame(void *Parent, wxWindow *ParentPtr);
	~CMyFrame();
	void OnTickerTick();
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 5312,
	
	};

};

#endif