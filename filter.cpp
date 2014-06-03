#include "ais.h"
#include "tools.h"
#include "filter.h"
#include "options.h"
#include <wx/wx.h>
#include <wx/checkbox.h>
#include <wx/event.h>


BEGIN_EVENT_TABLE(CFilter,wxDialog)
	EVT_CHECKBOX(wxID_ANY,OnCheck)
	EVT_BUTTON(ID_SELECT_ALL,OnSelectAll)
	EVT_BUTTON(ID_DESELECT_ALL,OnDeSelectAll)
END_EVENT_TABLE()


CFilter::CFilter()
	:wxDialog(NULL,wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{
	m_MainSizer = new wxBoxSizer(wxVERTICAL);
	m_MainSizer->SetMinSize(300,-1);
						
	this->SetSizer(m_MainSizer);
	
	for(size_t i = 0; i < AIS_MESSAGES_LENGTH; i++)
	{
		wxCheckBox *CheckBox = new wxCheckBox(this,ID_FILTER_BEGIN	+ i,wxString::Format(_("[%d] %s"),i + 1, GetMsg(MSG_AIS_1_NAME + i)));
		m_CheckList.Add(CheckBox);
		if(IS_BIT_SET(GetFilter(),i))
			CheckBox->SetValue(true);

		m_MainSizer->Add(CheckBox,0,wxALL,5);
	}
	
	m_ButtonSelect = new wxButton(this,ID_SELECT_ALL,GetMsg(MSG_SELECT_ALL),wxDefaultPosition,wxDefaultSize);
	m_MainSizer->Add(m_ButtonSelect,0,wxALL,5);

	wxButton *ButtonClose = new wxButton(this,wxID_OK,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	m_MainSizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);



	m_MainSizer->SetSizeHints(this);
	Center();
		
}	

CFilter::~CFilter(void)
{
	m_CheckList.Clear();
}

void CFilter::Set(int id, bool checked)
{
	int exponent = id - ID_FILTER_BEGIN;
	int a = pow(2.0,exponent);

	if(checked)
		a |= GetFilter();
	
	else
		a ^= GetFilter();

	SetFilter(a);
	SetFilterChanged(true);

}

void CFilter::OnCheck(wxCommandEvent &event)
{
	Set( event.GetId(),event.IsChecked());
}

void CFilter::OnSelectAll(wxCommandEvent &event)
{

	for(size_t i = 0; i < m_CheckList.size(); i++)
	{
		wxCheckBox *item =  (wxCheckBox*)m_CheckList.Item(i);
		item->SetValue(true);
		Set( item->GetId(),true);
	}
	m_ButtonSelect->SetId(ID_DESELECT_ALL);
	m_ButtonSelect->SetLabel(GetMsg(MSG_DESELECT_ALL));
	

}
void CFilter::OnDeSelectAll(wxCommandEvent &event)
{

	for(size_t i = 0; i < m_CheckList.size(); i++)
	{
		wxCheckBox *item =  (wxCheckBox*)m_CheckList.Item(i);
		item->SetValue(false);
		Set( item->GetId(),false);
	}
	m_ButtonSelect->SetId(ID_SELECT_ALL);
	m_ButtonSelect->SetLabel(GetMsg(MSG_SELECT_ALL));
}