#include <wx/wx.h>
#include <wx/notebook.h>
#include "conf.h"
#include "tools.h"
#include "ais_dialog.h"

BEGIN_EVENT_TABLE(CAisDialog,wxDialog)

END_EVENT_TABLE()


CAisDialog::CAisDialog() 
:wxDialog(NULL,wxID_ANY,wxEmptyString, wxDefaultPosition,wxDefaultSize)
{	
	GetPanel();
}

CAisDialog::~CAisDialog()
{
}

void CAisDialog::GetPanel()
{

	wxBoxSizer *m_Sizer = new wxBoxSizer(wxVERTICAL);
		
	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Sizer->Add(Notebook,1,wxALL|wxEXPAND,0);
	wxPanel *Page1 = new wxPanel(Notebook);
	wxBoxSizer *Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(Page1Sizer);
	Notebook->AddPage(Page1,GetMsg(MSG_AIS_TARGETS));

	m_Html = new wxHtmlWindow(Page1,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Page1Sizer->Add(m_Html,1,wxALL|wxEXPAND,0);

	this->SetSizer(m_Sizer);

}
void CAisDialog::SetText(wxString text)
{
	m_Html->AppendToPage(text);

}