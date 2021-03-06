#include <wx/wx.h>
#include <wx/statline.h>
#include "reader.h"
#include "dll.h"
#include "tools.h"
#include "protocol.h"


CReader::CReader()
{
	m_DeviceId = -1;
	m_DeviceType = -1;
    m_RunOnStart = false;
	m_IsRunning = false;
	m_LineBufLen = 0;
	m_SignalType = -1;
	m_Broker = NULL;
	m_Parser = new CParser();
	m_Parser->SetDevice(this);
	TreeCtrl = NULL;
	m_DeviceType = -1;
	SerialPtr = (CSerial*)this;
	SocketPtr = (CClient*)this;
	m_LineEvent = false;
	m_ConnectionType = CONNECTION_TYPE_SERIAL;
	m_AisState = NULL;
	
}

CReader::~CReader()
{
	delete m_Parser;	
}

void CReader::SetRunOnStart(bool val)
{
	m_RunOnStart = val;
}

bool CReader::RunOnStart()
{
	return m_RunOnStart;
}

void CReader::SetBroker(CNaviBroker *broker)
{
	m_Broker = broker;
	m_Parser->SetBroker(broker);
}

void CReader::SetDeviceId(size_t id)
{
	m_DeviceId = id;
	
}

size_t CReader::GetDeviceId()
{
	return m_DeviceId;
}

void CReader::SetDeviceName(wxString name)
{
	m_DeviceName = name;
}

wxString CReader::GetDeviceName()
{
	return m_DeviceName;
}

void CReader::SetDeviceType(int type)
{
	m_DeviceType = type;
}

int CReader::GetDeviceType()
{
	return m_DeviceType;
}

bool CReader::GetIsRunning()
{
	return m_IsRunning;
}

//void CReader::SetTreeCtrl(wxTreeCtrl *tree)
//{
//	TreeCtrl = tree;
//}

//void CReader::SetTreeItemId(wxTreeItemId id)
//{
	//TreeItemId = id;
//}

//wxTreeItemId CReader::GetTreeItemId()
//{
	//return TreeItemId;
//}

int CReader::GetSignalType()
{
	return m_SignalType;
}

void CReader::SetDefinition()
{
	m_Parser->SetDefinition(m_DeviceType);
}

void CReader::SetPort(const char *port)
{
	SerialPtr->_SetPort(port);
}

void CReader::SetPort(int port)
{
	SocketPtr->_SetPort(port);
}

int CReader::GetSocketPort()
{
	return SocketPtr->GetPort();
}

const char *CReader::GetSerialPort()
{
	return SerialPtr->GetPortName();
}

void CReader::Parse( char *line)
{
	 m_Parser->Parse(line);
}

void CReader::Stop()
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET: SocketPtr->Stop(); break;
		case CONNECTION_TYPE_SERIAL: SerialPtr->Stop(); break;
	}
}

void CReader::Start()
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET: SocketPtr->Start(); break;
		case CONNECTION_TYPE_SERIAL: SerialPtr->Start(); break;
	}
}

void CReader::SetParseLine(bool val)
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET: SocketPtr->SetParseLine(val);	break;
		case CONNECTION_TYPE_SERIAL: SerialPtr->SetParseLine(val);	break;
	}
}

bool CReader::IsConnected()
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET:	return SocketPtr->IsConnected();
		case CONNECTION_TYPE_SERIAL:	return SerialPtr->IsConnected();
	}

	return false;
}

size_t CReader::GetBadCRC()
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET: return SocketPtr->GetBadCRC();
		case CONNECTION_TYPE_SERIAL: return SerialPtr->GetBadCRC();
	}
	
	return 0;
}

size_t CReader::GetSignalQuality()
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET: return SocketPtr->GetSignalQuality();
		case CONNECTION_TYPE_SERIAL: return SerialPtr->GetSignalQuality();
	}
	return 0;
}


void CReader::SetHost(char *host)
{
	SocketPtr->_SetHost(host);
}

void CReader::SetConnectionType(int type)
{
	m_ConnectionType = type;
}

int CReader::GetConnectionType()
{
	return m_ConnectionType;
}

char *CReader::GetBuffer()
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET:	return SocketPtr->GetBuffer();
		case CONNECTION_TYPE_SERIAL:	return SerialPtr->GetBuffer();
	}

	return NULL;

}

char *CReader::GetLineBuffer()
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET:	return SocketPtr->GetLineBuffer();
		case CONNECTION_TYPE_SERIAL:	return SerialPtr->GetLineBuffer();
	}

	return NULL;

}

void CReader::SetCheckCRC(bool val)
{
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET:	return SocketPtr->SetCheckCRC(val);
		case CONNECTION_TYPE_SERIAL:	return SerialPtr->SetCheckCRC(val);
	}

}

void CReader::SetLineEvent(bool val)
{
	m_LineEvent = val;
}

// zdarzenia seriala
void CReader::OnConnect()
{
}

void CReader::OnConnected()
{
	m_SignalType = SIGNAL_CONNECTED;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
}

void CReader::OnDisconnect()
{
}

void CReader::OnExit()
{
}

void CReader::OnStart()
{
	m_IsRunning = true;
}

void CReader::OnStop()
{
	m_IsRunning = false;
}

void CReader::OnAfterMainLoop()
{
	bool flag = true;
}

void CReader::OnBeforeMainLoop()
{
}

void CReader::OnLine( char *buffer, int length)
{
	//if(m_LineEvent)
	//{
		//m_SignalType = SIGNAL_NMEA_LINE;
		//m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this); // zaburza przeplyw sygnalow
	//}
	
	//Parse(buffer);	
}

void CReader::OnNMEALine( char *buffer, int length)
{
	//fprintf(stdout,"%d\n",m_LineEvent);
	if(m_LineEvent)
	{
		m_SignalType = SIGNAL_NMEA_LINE;
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this); // zaburza przeplyw sygnalow
	}
	Parse(buffer);
	// narazie przeniesiono do OnLine
}

void CReader::OnReconnect()
{
	m_SignalType = SIGNAL_RECONNECT;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
}

void CReader::OnNewSignal()
{
	
}

void CReader::OnNoSignal()
{
	m_SignalType = SIGNAL_NO_SIGNAL;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
	switch(m_ConnectionType)
	{
		case CONNECTION_TYPE_SOCKET:	return SocketPtr->Disconnect();
		case CONNECTION_TYPE_SERIAL:	return SerialPtr->Disconnect();
	}

}

void CReader::OnData( char *buffer, int length)
{
	//fprintf(stdout,"%s",buffer);
}

SAisState *CReader::GetAisStatePtr()
{
	return m_AisState;
}

void CReader::SetAisStatePtr(SAisState * ptr)
{
	m_AisState = ptr;
}