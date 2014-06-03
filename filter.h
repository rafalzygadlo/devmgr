#ifndef __FILTER_H
#define __FILTER_H

#include "conf.h"

class CFilter: public wxDialog
{
		
	wxBoxSizer *m_MainSizer;
	wxButton *m_ButtonSelect;
	wxArrayPtrVoid m_CheckList;
	void OnCheck(wxCommandEvent &event);
	void OnSelectAll(wxCommandEvent &event);
	void OnDeSelectAll(wxCommandEvent &event);
	void Set(int id, bool checked);

public:

	CFilter();
	~CFilter();
	
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_FILTER_BEGIN = 5213,
		ID_SELECT_ALL,
		ID_DESELECT_ALL,
	};
	

};


#endif