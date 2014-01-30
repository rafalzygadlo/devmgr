#ifndef __AIS_LIST_H
#define __AIS_LIST_H

#include <wx/wx.h>
#include "NaviMapIOApi.h"
#include "NaviDisplayApi.h"
#include "dll.h"
#include "listctrl.h"
#include <wx/html/htmlwin.h>


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
	void GetPanel();
	void SetList();
	void ClearList();
	void OnTimer(wxTimerEvent &event);

public:
	
	CAisList(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display);
	~CAisList();
	void SetSignal(int signal);
	void SetHtml(wxString html);
	void ClearHtml();

	enum 
	{
		ID_TIMER = 3872,
	};

	DECLARE_EVENT_TABLE();
};


#endif