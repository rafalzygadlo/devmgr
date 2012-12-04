#ifndef __SERIAL
#define __SERIAL

#include "serial_port.h"
#include <wx/wx.h>
#include "conf.h"
#include "panel.h"
#include "NaviMapIOApi.h"

class CMySerial :public CSerial
{
	bool m_IsRunning;
	int m_DeviceId;
	wxString m_DeviceName;
	CNaviBroker *m_Broker;
	unsigned char m_LineBuffer[BUFFER_LENGTH];
	int m_LineBufLen;
	int m_SignalType;
	bool m_RunOnStart;
		
		
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
	virtual void OnNoSignal();

};




#endif
