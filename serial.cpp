#include <wx/wx.h>
#include <wx/statline.h>
#include "serial.h"
#include "frame.h"
#include "dll.h"
#include "tools.h"
#include "protocol.h"


CMySerial::CMySerial()
	:CSerial()
{
	m_DeviceId = -1;
	m_DeviceType = -1;
    m_RunOnStart = false;
	m_IsRunning = false;
	m_LineBufLen = 0;
	m_SignalType = -1;
	m_Broker = NULL;
	m_Parser = new CParser();
}

CMySerial::~CMySerial()
{
	delete m_Parser;	
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

void CMySerial::SetDeviceType(int type)
{
	m_DeviceType = type;
}

int CMySerial::GetDeviceType()
{
	return m_DeviceType;
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

void CMySerial::OnAfterMainLoop()
{
	bool flag = true;
}

void CMySerial::OnBeforeMainLoop()
{
}

void CMySerial::OnLine(unsigned char *buffer, int length, int valid_nmea)
{
	if(valid_nmea == 0)
		Parse(buffer);
	else
		int a = valid_nmea;
}
void CMySerial::OnReconnect()
{
	m_SignalType = SERIAL_SIGNAL_RECONNECT;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevSignal",this);
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

void CMySerial::SetDefinition()
{
	m_Parser->SetDefinition(m_DeviceType);
}

void CMySerial::Parse(unsigned char *line)
{

	SData *data = m_Parser->Parse(line);
	if(data)
	{
		wchar_t str[1024] = {0}; 
		swprintf(str,L"[%d][%d][%hs]",m_DeviceId, data->id, data->value);
		m_Broker->consolef(m_Broker->GetParentPtr(),str);
	}
}

