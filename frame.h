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

	CMapPlugin *m_DLL;	
	wxPanel *m_Page0,*m_Page1;
	wxStaticText *m_Time;
	int m_ParentX, m_ParentY;
	wxWindow *m_ParentPtr;
	wxHtmlWindow *m_Html0, *m_Html1;
	bool m_AfterInit;
	CTicker *m_Ticker;
	int m_Seconds,m_Minutes;
	wxStaticBitmap *m_ShipImage;
	//wxTextCtrl *m_MMSI, *m_CALLSIGN, *m_IMO, *m_Name;
	//wxStaticText *m_Flag;
	//wxStaticText *m_COG, *m_HDT, *m_SOG , *m_LON, *m_LAT, *m_Draught, *m_Turn;
	
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void SetHtml(wxString html, int page);
	void ShowHtmlPanel();
	void ClearHtml(int page);
	bool IsOnScreen(int x, int y);
	void SetReportTime();
	void SetValues();
	void ShowWindow(bool show);
	void SetImage();
	void SetData(SAisData *ptr);
	
public:
		
	CMyFrame(void *Parent, wxWindow *ParentPtr);
	~CMyFrame();
	void OnTickerTick();
	void OnShowWindow(wxCommandEvent &event);
	void ShowWindowEvent(bool show);
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 5312,
		ID_SHOW,
	
	};

};

#endif