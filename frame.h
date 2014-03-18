#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/fileconf.h>
#include <wx/mstream.h>
#include "conf.h"
#include "dll.h"
#include <vector>

class CMyIcon;
class CMapPlugin;
class CMyFrame: public wxDialog
{
	SAisData *SelectedPtr;
	wxScrolledWindow *Scroll;
	CMapPlugin *m_DLL;	
	wxTextCtrl *textname;
	wxListBox *markerlistbox;
	wxFlexGridSizer *GridSizer;
	wxPanel *Panel;
	wxBoxSizer *AddFieldSizer;
	wxTextCtrl *Value;
	wxTextCtrl *textdescription;
	wxButton *ButtonClose;
	wxPanel *PanelIcon;
	CMyIcon *MarkerIcon;
	wxTextCtrl *textlon;
	wxTextCtrl *textlat;
	int ParentX, ParentY;
	wxWindow *_ParentPtr;

	bool AfterInit;
	void AddIconControls();
	
	void OnCloseButton(wxCommandEvent &event);
	//void OnSaveButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnMarkerList(wxCommandEvent &event);
	void OnMarkerDelete(wxCommandEvent &event);
	void OnTextChanged(wxCommandEvent &event);
	void OnLeftClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnLon(wxCommandEvent &event);
	void OnLat(wxCommandEvent &event);

					
public:

	void ShowIconChanger(bool show);
	void SetMarkerIcon(int id);
	void ShowWindow(bool show);		
	CMyFrame(void *Parent, wxWindow *ParentPtr);
	~CMyFrame();
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 5312,
		ID_NAME,
		ID_DESCRIPTION,
		ID_DELETE,
		ID_NEW_FIELD,
		ID_LON,
		ID_LAT,
	
	};

};

#endif