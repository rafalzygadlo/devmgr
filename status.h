#ifndef __STATUS
#define __STATUS

#include <wx/wx.h>
#include "conf.h"
#include "dll.h"
#include "tools.h"
#include <vector>

class CStatus: public wxDialog
{
	
	wxBoxSizer *MainSizer;
	wxTextCtrl *DataDefinition;
	CReader *Reader;
	wxTextCtrl *m_Status;
	wxTextCtrl *m_NMEA;
	wxCheckBox *m_ShowLog;

	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnShowLog(wxCommandEvent &event);
	
	
public:

	CStatus();
	~CStatus();
	void ShowWindow(bool show);	
	int GetBaud();
	void AppendText(wxString text);
	void SetReader(CReader *ptr);
	void SetShowLog(bool val);
	
	DECLARE_EVENT_TABLE();


	enum
	{
		ID_CLOSE,
		ID_SHOW_LOG,
	};

};


#endif