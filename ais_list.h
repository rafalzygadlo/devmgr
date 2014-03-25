#ifndef __AIS_LIST_H
#define __AIS_LIST_H

#include <wx/wx.h>
#include "NaviMapIOApi.h"
#include "NaviDisplayApi.h"
#include "dll.h"
#include "listctrl.h"
#include <wx/html/htmlwin.h>
#include <wx/srchctrl.h>


class CMapPlugin;
class CDisplayPlugin;
class CListCtrl;
class CAisList : public wxPanel
{
	wxHtmlWindow *m_Html;
	CNaviBroker *m_Broker;
	CDisplayPlugin *m_Display;
	CListCtrl *m_List;
	wxTimer *m_Timer;
	wxBoxSizer *m_Page1Sizer;
	wxSearchCtrl *m_SearchText;
	void GetPanel();
	void SetList();
	void ClearList();
	void OnTimer(wxTimerEvent &event);
	void OnSearchButton(wxCommandEvent &event);
	void OnSearchText(wxCommandEvent &event);

public:
	
	CAisList(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display);
	~CAisList();
	void SetSignal(int signal);
	void SetHtml(wxString html);
	void ShowHtmlPanel();
	void ClearHtml();
	void ThreadBegin();
	void ThreadEnd();

	enum 
	{
		ID_TIMER = 3872,
		ID_SEARCH,
	};

	DECLARE_EVENT_TABLE();
};


#endif