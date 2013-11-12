#ifndef __SERIAL
#define __SERIAL

#include <wx/wx.h>
#include "serial_port.h"
#include "conf.h"
#include "NaviMapIOApi.h"
#include "protocol.h"
#include "parser.h"

class CMySerial :public CSerial
{
	CParser *m_Parser;
	bool m_IsRunning;
	int m_DeviceId;
	int m_DeviceType;
	wxString m_DeviceName;
	CNaviBroker *m_Broker;
	unsigned char *m_LineBuffer;
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
	void Parse(unsigned char *line);
	void SetDeviceType(int type);
	int GetDeviceType();
	void SetDefinition();
	int GetMarkersLength();
	
	virtual void OnConnect();
	virtual void OnDisconnect();
	virtual void OnData(unsigned char *buffer, int length);
	virtual void OnLine(unsigned char *buffer, int length, int valid_nmea);
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
