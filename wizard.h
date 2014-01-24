#ifndef __WIZARD_H
#define __WIZARD_H

#include <wx/wx.h>
#include "conf.h"
#include "searcher.h"
#include "reader.h"

class CSearcher;
class CWizard: public wxDialog
{

	int m_Count, m_Counter;
	int m_BaudCount;
	bool m_Found;
	wxListBox *m_ListBox,*m_NewListBox;
	wxButton *m_ButtonP1Next, *m_ButtonP2Next, *m_ButtonP2Prev , *m_ButtonP3Prev, *m_ButtonP3Next;
	wxButton *m_ButtonClose;
	wxTextCtrl *m_LogBox;
	CSearcher *m_Searcher;
	wxPanel *m_Page1, *m_Page2, *m_Page3;
	wxBoxSizer *m_MainSizer;
	std::vector <CReader*> vDevices;
	std::vector <CReader*> vNewDevices;
	wxStaticText *m_Page1Text,*m_Page2Text,*m_Page3Text;


	void Start();
	void SetGui();
	void SetDeviceType();
	void OnButton1Next(wxCommandEvent &event);
	void OnButton2Next(wxCommandEvent &event);
	void OnButton2Prev(wxCommandEvent &event);
	void OnButton3Prev(wxCommandEvent &event);
	
	wxPanel *Page1();
	wxPanel *Page2();
	wxPanel *Page3();

public:

	CWizard();
	~CWizard();
	void ThreadBegin(int work_id);
	void ThreadEnd(int work_id);
	size_t GetCount();
	CReader *GetDevice(int id);
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 7384,
		ID_1_NEXT,
		ID_2_NEXT,
		ID_2_PREV,
		ID_3_NEXT,
		ID_3_PREV,
		ID_FINISH,
		
	};

};


#endif