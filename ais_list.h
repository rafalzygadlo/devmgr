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
#include <wx/spinctrl.h>
#include "combo.h"

class CMapPlugin;
class CDisplayPlugin;
class CListCtrl;
class CAisList : public wxPanel
{
	wxHtmlWindow *m_Html;
	CNaviBroker *m_Broker;
	CDisplayPlugin *m_Display;
	CListCtrl *m_List;
	wxNotebook *m_Notebook;
	wxBoxSizer *m_Page1Sizer;
	wxSearchCtrl *m_SearchText;
	wxSlider *m_FontSize;
	wxCheckBox *m_ShipNames,*m_COGLine,*m_HDTLine,*m_GPSPoint,*m_ShowObjects;
	wxColourPickerCtrl *m_ShipColor0, *m_ShipColor1 , *m_ShipColor2, *m_AtonColor,*m_ShipBorderColor;
	wxColourPickerCtrl *m_COGColor,*m_HDTColor,*m_GPSColor;
	wxSlider *m_ViewNameScale;
	wxSpinCtrl *m_HDTTime,*m_COGTime,*m_COGLineWidth,*m_HDTLineWidth;
	CPenStyleComboBox *m_HDTLineStyle, *m_COGLineStyle;
	int m_OldCount;
	bool m_Working;
	void GetPanel();
	void SetList();
	void ClearList();
	void Signal();
	//void StartThread();
	void OnTimer(wxTimerEvent &event);
	void OnSearchButton(wxCommandEvent &event);
	void OnSearchText(wxCommandEvent &event);
	void OnSearchEnter(wxCommandEvent &event);
	void OnShowNames(wxCommandEvent &event);
	void OnFontSize(wxCommandEvent &event);
	void OnShowHDT(wxCommandEvent &event);
	void OnShowCOG(wxCommandEvent &event);
	void OnShowGPS(wxCommandEvent &event);
	void OnShowOBJECTS(wxCommandEvent &event);
	void OnColorPicker(wxColourPickerEvent &event);
	void OnFilter(wxCommandEvent &event);
	void OnNameScale(wxCommandEvent &event);
	void OnCOGTime(wxSpinEvent &event);
	void OnHDTTime(wxSpinEvent &event);
	void OnCOGLineWidth(wxSpinEvent &event);
	void OnHDTLineWidth(wxSpinEvent &event);
	void OnCOGLineStyle(wxCommandEvent &event);
	void OnHDTLineStyle(wxCommandEvent &event);

public:
	
	CAisList(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display);
	~CAisList();
	void SetSignal(int signal);
	void SetHtml(wxString html);
	void ShowHtmlPanel();
	void ClearHtml();
	void ThreadBegin();
	void ThreadEnd();
	void Synchro();

	enum 
	{
		ID_TIMER = 3872,
		ID_SEARCH,
		ID_SHOW_NAMES,
		ID_FONT_SIZE,
		ID_SHOW_HDT,
		ID_SHOW_COG,
		ID_SHIP_BORDER_COLOR,
		ID_SHIP_COLOR_0,
		ID_SHIP_COLOR_1,
		ID_SHIP_COLOR_2,
		ID_ATON_COLOR,
		ID_FILTER,
		ID_VIEW_NAME_SCALE,
		ID_COG_COLOR,
		ID_HDT_COLOR,
		ID_GPS_COLOR,
		ID_SHOW_GPS,
		ID_SHOW_OBJECTS,
		ID_COG_TIME,
		ID_HDT_TIME,
		ID_COG_LINE_WIDTH,
		ID_HDT_LINE_WIDTH,
		ID_COG_LINE_STYLE,
		ID_HDT_LINE_STYLE,
	};

	DECLARE_EVENT_TABLE();
};


#endif
