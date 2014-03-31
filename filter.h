#ifndef __FILTER_H
#define __FILTER_H

#include "conf.h"

class CFilter: public wxDialog
{
		
	wxBoxSizer *MainSizer;
	void OnCheck(wxCommandEvent &event);

public:

	CFilter();
	~CFilter();
	
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_FILTER_BEGIN = 5213,
	};
	

};


#endif