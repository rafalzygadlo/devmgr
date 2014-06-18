#ifndef __READER_H
#define __READER_H

#include <wx/wx.h>
#include "serial_port.h"
#include "conf.h"
#include "NaviMapIOApi.h"
#include "protocol.h"
#include "parser.h"
#include "sclient.h"
#include <Windows.h>
#include <wx/treectrl.h>

class CReader :public CSerial, public CClient
{
	CParser *m_Parser;
	bool m_IsRunning;
	int m_DeviceId;
	int m_DeviceType;
	wxString m_DeviceName;
	CNaviBroker *m_Broker;
	char *m_LineBuffer;
	int m_LineBufLen;
	int m_SignalType;
	bool m_RunOnStart;
	wxTreeItemId TreeItemId;
	wxTreeCtrl *TreeCtrl;
	CSerial *SerialPtr;
	CClient *SocketPtr;
	int m_ConnectionType;
	bool m_LineEvent;

public:
	CReader();
	~CReader();
	
	bool GetIsRunning();
	bool RunOnStart();
	void SetDeviceName(wxString name);
	void SetDeviceId(size_t id);			
	void SetBroker(CNaviBroker *broker);
	void SetRunOnStart(bool val);
	wxString GetDeviceName();
	size_t GetDeviceId();					
	void SetDefinition();
	void Parse( char *line);
	void SetDeviceType(int type);
	int GetSignalType();
	int GetDeviceType();
	//void SetTreeItemId(wxTreeItemId id);
	//void SetTreeCtrl(wxTreeCtrl *tree);
	//wxTreeItemId GetTreeItemId();
	void SetPort(const char *port);
	void SetPort(int port);
	void Stop();
	void Start();
	void SetParseLine(bool val);
	bool IsConnected();
	void SetHost(char *host);
	int GetSocketPort();
	const char *GetSerialPort();
	void SetConnectionType(int type);
	int GetConnectionType();
	char *GetBuffer();
	char *GetLineBuffer();
	void SetLineEvent(bool val);
	void SetCheckCRC(bool val);
	size_t GetBadCRC();
	size_t GetSignalQuality();
	
	
	virtual void OnConnect();
	virtual void OnConnected();
	virtual void OnDisconnect();
	virtual void OnData( char *buffer, int length);
	virtual void OnLine( char *buffer, int length);
	virtual void OnNMEALine( char *buffer, int length);
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
