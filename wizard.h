#ifndef __WIZARD
#define __WIZARD

#include <wx/wx.h>
#include "conf.h"
#include "searcher.h"
#include "serial.h"

class CSearcher;
class CWizard: public wxDialog
{

	int m_Count;
	int m_BaudCount;
	wxListBox *m_ListBox,*m_NewListBox;
	wxButton *m_ButtonP1Next, *m_ButtonP2Next, *m_ButtonP2Prev , *m_ButtonP3Prev, *m_ButtonP3Next;
	wxTextCtrl *m_LogBox;
	CSearcher *m_Searcher;
	wxPanel *m_Page1, *m_Page2, *m_Page3;
	wxBoxSizer *m_MainSizer;
	std::vector <CMySerial*> vDevices;
	std::vector <CMySerial*> vNewDevices;

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
	CMySerial *GetDevice(int id);
		
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