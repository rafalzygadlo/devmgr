#ifndef __WIZARD
#define __WIZARD

#include <wx/wx.h>
#include "conf.h"
#include "searcher.h"

class CSearcher;
class CWizard: public wxDialog
{

	int m_Count;
	int m_BaudCount;
	wxListBox *m_ListBox;
	wxButton *m_ButtonStart;
	wxTextCtrl *m_LogBox;
	CSearcher *m_Searcher;

	void Start();
	void SetGui();
	void SetDeviceType();
	void OnButtonStart(wxCommandEvent &event);

public:

	CWizard();
	~CWizard();
	void ThreadBegin(int work_id);
	void ThreadEnd(int work_id);
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 7384,
		ID_START
		
	};

};


#endif