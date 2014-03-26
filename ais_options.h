#ifndef __AIS_OPTIONS_H
#define __AIS_OPTIONS_H

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
class CAisOptions : public wxPanel
{
	CNaviBroker *m_Broker;
	CDisplayPlugin *m_Display;
	wxBoxSizer *m_Page1Sizer;
	wxSearchCtrl *m_SearchText;
	void GetPanel();
	
public:
	
	CAisOptions(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display);
	~CAisOptions();
		
	enum 
	{
		ID_TIMER = 3872,
		ID_SEARCH,
	};

	DECLARE_EVENT_TABLE();
};


#endif