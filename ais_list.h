#ifndef __AIS_LIST_H
#define __AIS_LIST_H

#include <wx/wx.h>
#include "NaviMapIOApi.h"
#include "NaviDisplayApi.h"
#include "dll.h"
#include "listctrl.h"
#include <wx/html/htmlwin.h>
#include <wx/srchctrl.h>
#include <wx/clrpicker.h>


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
	wxCheckBox *m_ShipNames;
	wxSlider *m_FontSize;
	wxCheckBox *m_COGLine,*m_HDTLine;
	wxColourPickerCtrl *m_ShipColor0, *m_ShipColor1 , *m_ShipColor2, *m_AtonColor;
	bool m_Working;
	void GetPanel();
	void SetList();
	void ClearList();
	void OnTimer(wxTimerEvent &event);
	void OnSearchButton(wxCommandEvent &event);
	//void OnSearchText(wxCommandEvent &event);
	void OnSearchEnter(wxCommandEvent &event);
	void OnShowNames(wxCommandEvent &event);
	void OnFontSize(wxCommandEvent &event);
	void OnShowHDT(wxCommandEvent &event);
	void OnShowCOG(wxCommandEvent &event);
	void OnColorPicker(wxColourPickerEvent &event);

public:
	
	CAisList(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display);
	~CAisList();
	void SetSignal(int signal);
	void SetHtml(wxString html);
	void ShowHtmlPanel();
	void ClearHtml();
	void ThreadBegin();
	void ThreadEnd();
	void _SetShowNames(bool val);
	void _SetFontSize(int val);

	enum 
	{
		ID_TIMER = 3872,
		ID_SEARCH,
		ID_SHOW_NAMES,
		ID_FONT_SIZE,
		ID_SHOW_HDT,
		ID_SHOW_COG,
		ID_SHIP_COLOR_0,
		ID_SHIP_COLOR_1,
		ID_SHIP_COLOR_2,
		ID_ATON_COLOR,
	};

	DECLARE_EVENT_TABLE();
};


#endif