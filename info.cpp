#include "conf.h"
#include "info.h"
//#include "waitanim.h"
#include <wx/mstream.h>
#include <wx/animate.h>

CMyInfo::CMyInfo(wxWindow *Parent, wxString text)
	:wxDialog(Parent, wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize)
{
	
	//wxMemoryInputStream in((const unsigned char*)waitanim, waitanim_size);
	
	wxBoxSizer *MainSizer = new wxBoxSizer(wxHORIZONTAL);
	//wxAnimation data;
	//data.Load(in);
	//wxAnimationCtrl *Animation = new wxAnimationCtrl(this,wxID_ANY,data);
	//Animation->SetAnimation(data);
	//Animation->Play();
	//MainSizer->Add(Animation,1,wxALL|wxCENTER|wxALIGN_CENTER ,5);
	
	Text = new wxStaticText(this,wxID_ANY,text,wxDefaultPosition,wxDefaultSize);
	MainSizer->Add(Text,1,wxALL|wxALIGN_CENTER_VERTICAL ,10);
	
	this->SetBackgroundColour(*wxWHITE);
	//this->SetForegroundColour(*wxWHITE);
	//this->SetTransparent(200);
	this->SetSizer(MainSizer);
	this->Fit();
	this->Layout();
	this->Center();		
	this->Show();
	this->Refresh();
    this->Update();
	
	
}

CMyInfo::~CMyInfo(void)
{
	this->Show(false);
	this->Close();
}

void CMyInfo::SetText(wxString str)
{
	Text->SetLabel(str);
}