#ifndef __DISPLAY
#define __DISPLAY

#include "dll.h"
#include "NaviMapIOApi.h"
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "NaviDisplayApi.h"

#include <wx/fileconf.h>
#include "serial.h"

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

class NAVIDISPLAYAPI CDisplayPlugin: public CNaviDiaplayApi 
{
	
	CNaviBroker *Broker;
	CMapPlugin *MapPlugin;
	wxCheckListBox *TrackList;
	wxListBox *TrackData;
	wxPanel *Panel;
	int Radius;
	int CenterX ,CenterY;
	wxFont	*Font;
	wxString buf;
	int ControlType, FormatType;
	wxString action;
	int Precision;
	int Direction;
	wxArrayString ArrayOfTypes;
	wxString Name;
	wxString ConfigPath;
	int _Radius;
	
	
	wxString GetCaption();
	bool CheckGpsValid(wxGCDC &dc);
	double FormatValue(double data, int type);
	void OnMenu(wxContextMenuEvent &event);
	void DrawQuality(wxGCDC &dc);
	void DrawFix(wxGCDC &dc);
	void DrawData(wxGCDC &dc, wxString caption,wxString text);
	void DrawSatellites(wxGCDC &dc);
	void DrawDirection(wxGCDC &dc);
	void DrawDate(wxGCDC &dc);
	void DrawTime(wxGCDC &dc);
	void Draw(wxGCDC &dc);
	void DrawBackground(wxGCDC &dc);
	void DrawSpeed(wxGCDC &dc);
	void DrawLon(wxGCDC &dc);
	void DrawLat(wxGCDC &dc);
	void DrawStatus(wxGCDC &dc);
	void DrawTracks(wxGCDC &dc);
	void DrawSearchSatellites(wxGCDC &dc);
	void OnMenuRange(wxCommandEvent &event);
	void OnMouseWheel(wxMouseEvent & event);
	void OnMouse(wxMouseEvent & event);
	void OnListCheck(wxCommandEvent &event);
	void OnListBox(wxCommandEvent &event);
	

public:
	
	CDisplayPlugin(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("DisplayApiPanel") );
	~CDisplayPlugin();
	
	virtual bool IsValidSignal(CDisplaySignal *SignalID);
	virtual void OnWork(CDisplaySignal *Signal);
	virtual void BeforeWork(CDisplaySignal *Signal);
	virtual void AfterWork(CDisplaySignal *Signal);
	virtual void OnRender(wxGCDC &dc);

	enum
	{
		ID_ABOUT,
		ID_SPEED = 1000,
		ID_DATE,
		ID_TIME,
		ID_FIX,
		ID_DIRECTION,
		ID_LON,
		ID_LAT,
		ID_PDOP,
		ID_HDOP,
		ID_VDOP,
		ID_QUALITY,
		ID_SATELLITES,
		ID_STATUS,
		ID_TRACKS,
		// buttons DrawTracks
		ID_DELETE,
		ID_TRACK_LIST,
	};
	
	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif

#endif