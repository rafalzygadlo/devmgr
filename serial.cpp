#include "serial.h"
#include "frame.h"
#include "dll.h"
#include "tools.h"

CMySerial::CMySerial()
	:CSerial()
{
	m_DeviceId = -1;
    m_RunOnStart = false;
	m_IsRunning = false;
	m_LineBufLen = 0;
	m_SignalType = -1;
	m_Broker = NULL;
}

CMySerial::~CMySerial()
{
	
}

void CMySerial::SetRunOnStart(bool val)
{
	m_RunOnStart = val;
}

bool CMySerial::RunOnStart()
{
	return m_RunOnStart;
}

void CMySerial::SetBroker(CNaviBroker *broker)
{
	m_Broker = broker;
}

void CMySerial::SetDeviceId(size_t id)
{
	m_DeviceId = id;
}

size_t CMySerial::GetDeviceId()
{
	return m_DeviceId;
}

void CMySerial::SetDeviceName(wxString name)
{
	m_DeviceName = name;
}

wxString CMySerial::GetDeviceName()
{
	return m_DeviceName;
}

bool CMySerial::IsRunning()
{
	return m_IsRunning;
}

void CMySerial::OnConnect()
{

}

void CMySerial::OnDisconnect()
{
   
}

void CMySerial::OnData(unsigned char *buffer, int length)
{
	m_SignalType = SERIAL_SIGNAL_ONDATA;
    m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
}

void CMySerial::OnExit()
{
}

void CMySerial::OnStart()
{
	m_IsRunning = true;
}

void CMySerial::OnStop()
{
	m_IsRunning = false;
}

void CMySerial::OnReconnect()
{
	m_SignalType = SERIAL_SIGNAL_RECONNECT;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
}

void CMySerial::OnAfterMainLoop()
{
	bool flag = true;
}

void CMySerial::OnBeforeMainLoop()
{
}

void CMySerial::OnLine(unsigned char *line)
{
	
}

void CMySerial::OnNewSignal()
{
	m_SignalType = SERIAL_SIGNAL_NEW_SIGNAL;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
	
}

void CMySerial::OnNoSignal()
{
	m_SignalType = SERIAL_SIGNAL_NO_SIGNAL;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
	
}


int CMySerial::GetSignalType()
{
	return m_SignalType;
}