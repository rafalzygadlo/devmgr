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
	SAisData *SelectedPtr;
	CMapPlugin *m_DLL;	
	wxPanel *Panel;
	wxButton *ButtonClose;
	int ParentX, ParentY;
	wxWindow *_ParentPtr;
	wxHtmlWindow *Html;
	bool AfterInit;
	
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void SetHtml(wxString html);
	void ShowHtmlPanel();
	void ClearHtml();
					
public:
		
	void ShowWindow(bool show);		
	CMyFrame(void *Parent, wxWindow *ParentPtr);
	~CMyFrame();
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 5312,
	
	};

};

#endif