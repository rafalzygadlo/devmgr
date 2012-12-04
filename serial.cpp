#include "serial.h"
#include "frame.h"
#include "dll.h"
#include "tools.h"

CMySerial::CMySerial(CNaviBroker *Broker):CSerial()
{
    m_IsRunning = false;
	m_Broker = Broker;
    m_LineBufLen = 0;
	m_DisplayPanel = NULL;
}

CMySerial::~CMySerial()
{
	
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
	for(size_t i = 0; i < GetSignalCount(); i++)
	{
		fprintf(stderr,"%s %d\n",GetSignal(i)->name,GetSignal(i)->count);	
	}

}
int CMySerial::GetSignalType()
{
	return m_SignalType;
}