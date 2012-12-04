#ifndef __SERIAL
#define __SERIAL

#include "serial_port.h"
#include <wx/wx.h>
#include "conf.h"
#include "panel.h"
#include "NaviMapIOApi.h"

class CMySerial :public CSerial
{
	wxPanel *m_DisplayPanel;
	bool m_IsRunning;
	int m_DeviceId;
	wxString m_DeviceName;
	CNaviBroker *m_Broker;
	unsigned char m_LineBuffer[BUFFER_LENGTH];
	int m_LineBufLen;
	int m_SignalType;
		
		
public:
	CMySerial(CNaviBroker *_Broker);
	~CMySerial();
	
	bool IsRunning();
	void SetDeviceName(wxString name);
	wxString GetDeviceName();
	void SetDeviceId(size_t id);			
	size_t GetDeviceId();					
	int GetSignalType();

	
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

};




#endif
