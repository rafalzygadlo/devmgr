#include "conf.h"
#include "wizard.h"


BEGIN_EVENT_TABLE(CWizard,wxWizard)
END_EVENT_TABLE()


CWizard::CWizard()
	:wxWizard(NULL)
{

	m_FirstPage = new CFirstPage(this);
	wxStaticText *Text = new wxStaticText(this,wxID_ANY,_("This Wizard"));
		
}	

CWizard::~CWizard()
{

}

CFirstPage *CWizard::GetFirstPage()
{
	return m_FirstPage;
}

// Page1
CFirstPage::CFirstPage(CWizard *parent)
	:wxWizardPage(parent)
{

}

CFirstPage::~CFirstPage()
{

}

wxWizardPage *CFirstPage::GetPrev() const
{

	return NULL;
}

wxWizardPage *CFirstPage::GetNext() const
{
	return NULL;
}
