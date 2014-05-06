#include "ais.h"
#include "tools.h"
#include "filter.h"
#include "options.h"


BEGIN_EVENT_TABLE(CFilter,wxDialog)
	EVT_CHECKBOX(wxID_ANY,OnCheck)
END_EVENT_TABLE()


CFilter::CFilter()
	:wxDialog(NULL,wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{
	MainSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->SetMinSize(300,-1);
						
	this->SetSizer(MainSizer);
	
	for(size_t i = 0; i < AIS_MESSAGES_LENGTH; i++)
	{
		wxCheckBox *CheckBox = new wxCheckBox(this,ID_FILTER_BEGIN	+ i,wxString::Format(_("[%d] %s"),i + 1, GetMsg(MSG_AIS_1_NAME + i)));

		if(IS_BIT_SET(GetFilter(),i))
			CheckBox->SetValue(true);

		MainSizer->Add(CheckBox,0,wxALL,5);
	}
	
	wxButton *ButtonClose = new wxButton(this,wxID_OK,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);

	MainSizer->SetSizeHints(this);
	Center();
		
}	

CFilter::~CFilter(void)
{

}

void CFilter::OnCheck(wxCommandEvent &event)
{
	int exponent = event.GetId() - ID_FILTER_BEGIN;

	int a = pow(2.0,exponent);

	if(event.IsChecked())
		a |= GetFilter();
	
	else
		a ^= GetFilter();

	SetFilter(a);
	SetFilterChanged(true);
}
