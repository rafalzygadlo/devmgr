#ifndef __WIZARD
#define __WIZARD

#include <wx/wx.h>
#include <wx/wizard.h>
#include "conf.h"
#include "dll.h"

class CFirstPage;
class CWizard: public wxWizard
{
	
	wxBoxSizer *MainSizer;
	CFirstPage *m_FirstPage;
			
public:

	CWizard();
	~CWizard();
	CFirstPage *GetFirstPage();
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 7384,
		
	};

};

class CFirstPage: public wxWizardPage
{

public:
	
	CFirstPage(CWizard *parent);
	~CFirstPage();

	wxWizardPage *GetNext() const;
	wxWizardPage *GetPrev() const;
};



#endif