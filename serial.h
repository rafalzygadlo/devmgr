#ifndef __SERIAL
#define __SERIAL

#include "serial_port.h"
#include <wx/wx.h>
#include "conf.h"
#include "NaviMapIOApi.h"

class CPanel;
class CMySerial :public CSerial
{
	bool m_IsRunning;
	int m_DeviceId;
	wxString m_DeviceName;
	CNaviBroker *m_Broker;
	unsigned char *m_LineBuffer;
	int m_LineBufLen;
	int m_SignalType;
	bool m_RunOnStart;
	CPanel *m_ConfigPanel;
	std::vector<TDataDefinition> m_DataDefinitionTable;
	wxString m_DataDefinitionString;
		
		
public:
	CMySerial();
	~CMySerial();
	
	bool IsRunning();
	bool RunOnStart();
	void SetDeviceName(wxString name);
	void SetDeviceId(size_t id);			
	void SetBroker(CNaviBroker *broker);
	void SetRunOnStart(bool val);
	wxString GetDeviceName();
	void SetDataDefinition();
	size_t GetDeviceId();					
	int GetSignalType();
	void CreateDataDefinitionTable(char *data);
	void Parse(unsigned char *line);
	//TDataDefinition *GetDataDefinition(const char *NMEALine);
	wxString GetDataDefinitionAsString();

	virtual void OnConnect();
	virtual void OnDisconnect();
	virtual void OnData(unsigned char *buffer, int length);
	virtual void OnLine(unsigned char* line);
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnAfterMainLoop();
	virtual void OnBeforeMainLoop();
	virtual void OnExit();					// no gps found plugin ends working
	virtual void OnReconnect();
	virtual void OnNewSignal();
	virtual void OnNoSignal();

};

// config panel
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
	CPanel(wxWindow *Parent,CMySerial *Serial);
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
