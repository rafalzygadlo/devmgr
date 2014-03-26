#include <wx/wx.h>
#include <wx/notebook.h>

#include "conf.h"
#include "tools.h"
#include "ais_options.h"
#include "ais.h"
#include "thread.h"

BEGIN_EVENT_TABLE(CAisOptions,wxPanel)
	
END_EVENT_TABLE()


CAisOptions::CAisOptions(wxWindow *parent, CMapPlugin *plugin, CDisplayPlugin *display) 
:wxPanel(parent)
{
	m_Broker = NULL;
	SetDoubleBuffered(true);
	m_Broker = plugin->GetBroker();
	m_Display = display;
	GetPanel();

}

CAisOptions::~CAisOptions()
{
	
}

void CAisOptions::GetPanel()
{

	wxBoxSizer *m_Sizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_Sizer->Add(Notebook,1,wxALL|wxEXPAND,0);
	wxPanel *Page1 = new wxPanel(Notebook);
	m_Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(m_Page1Sizer);
	Notebook->AddPage(Page1,GetMsg(MSG_AIS_OPTIONS));

			

	this->SetSizer(m_Sizer);

}