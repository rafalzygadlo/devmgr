#ifndef __INFO_H
#define __INFO_H

#include <wx/wx.h>
#include <vector>

class CMyInfo: public wxDialog
{
	wxStaticText *Text;
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
					
public:

	CMyInfo(wxWindow *Parent,wxString text);
	~CMyInfo();
	void SetText(wxString text);	
	
	
	
};

#endif