#include <wx/wx.h>
#include <wx/notebook.h>
#include "conf.h"
#include "tools.h"
#include "ais_messages.h"

BEGIN_EVENT_TABLE(CAisMessages,wxPanel)

END_EVENT_TABLE()


CAisMessages::CAisMessages(wxWindow *parent, CMapPlugin *plugin)
:wxPanel(parent)
{	
	GetPanel();
}

CAisMessages::~CAisMessages()
{
}

void CAisMessages::GetPanel()
{

	wxBoxSizer *m_Sizer = new wxBoxSizer(wxVERTICAL);
		
	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Sizer->Add(Notebook,1,wxALL|wxEXPAND,0);
	wxPanel *Page1 = new wxPanel(Notebook);
	wxBoxSizer *Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(Page1Sizer);
	Notebook->AddPage(Page1,GetMsg(MSG_AIS_MESSAGES));

	m_Html = new wxHtmlWindow(Page1,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Page1Sizer->Add(m_Html,1,wxALL|wxEXPAND,0);

	this->SetSizer(m_Sizer);

}
void CAisMessages::SetText(wxString text)
{
	m_Html->AppendToPage(text);

}