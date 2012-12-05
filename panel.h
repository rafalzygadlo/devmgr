#ifndef __PANEL
#define __PANEL

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "serial.h"

class CMySerial;
class CPanel: public wxPanel
{
	int PortSelection;
	wxString ConfigPath;
	wxTextCtrl *m_LogText;
	wxStaticText *m_ConfigPathText;
	wxComboBox *m_PortComboBox,*m_BaudComboBox;
	wxButton *m_StartButton;
	wxButton *m_StopButton;
	wxCheckBox *m_CheckLogBox,*m_CheckBoxHint;
	CMySerial *m_Serial;

	void OnStartButton(wxCommandEvent &event);			// start button click
	void OnStopButton(wxCommandEvent &event);			// stop button click
	void OnCloseButton(wxCommandEvent &event);			// close click
	void OnPortComboChange(wxCommandEvent &event);		// combo box changed
	void OnCheckLog(wxCommandEvent &event);				// check box log
	
	void OnComboBox(wxCommandEvent &event);
	// custom events to send text from thread
	void OnSetLog(wxCommandEvent &event);
	void OnSetPort(wxCommandEvent &event);
	void OnSetBaud(wxCommandEvent &event);

	
public:
	CPanel(wxWindow *Parent, CMySerial *Serial);
	~CPanel();
	void _SetInfoText(wxString text);
	void _SetStatusText(wxString text);
	void _SetConfigPathText(wxString text);
	void _SetPort();
	void SetLogEvent(wxString str);	
	void SetPortEvent(wxString str);
	void SetBaudEvent(wxString str);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_START = 12345,
		ID_STOP,
		ID_CLOSE,
		ID_PORTS,
		ID_TRANSPARENT,
		ID_CHECK_LOG,
		ID_CHECK_HINT,
		ID_REFRESH,
		ID_SPIN,
	};

};

#endif