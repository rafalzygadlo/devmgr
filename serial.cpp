#include "serial.h"
#include "frame.h"
#include "dll.h"
#include "tools.h"

CMySerial::CMySerial(CNaviBroker *Broker):CSerial()
{
    _IsRunning = false;
	_Broker = Broker;
    //_Exit = false;
    _LineBufLen = 0;
    _ValidData = false; // valid parsed data
	 
}

CMySerial::~CMySerial()
{
	bool flag = true;
	_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetExit",&flag);
}
void CMySerial::SetDeviceName(wxString name)
{
	DeviceName = name;
}

wxString CMySerial::GetDeviceName()
{
	return DeviceName;
}

bool CMySerial::IsRunning()
{
	return _IsRunning;
}

void CMySerial::OnConnect()
{
    wxString port_name(GetPortName(),wxConvUTF8);
    _ValidGPS = false;
	
}

void CMySerial::OnDisconnect()
{
    
}

void CMySerial::OnData(unsigned char *buffer, int length)
{
    //_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetLog",(void*)buffer);
    
}

bool CMySerial::IsValidGPS()
{
    return _ValidGPS;
}

void CMySerial::OnExit()
{
    //_Exit = true;
}

void CMySerial::OnStart()
{
	_IsRunning = true;
}

void CMySerial::OnStop()
{
	_IsRunning = false;
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",NULL);

}

void CMySerial::OnReconnect()
{
	//char str[32];
	//sprintf(str,"%s %d\n",GetPortName(),GetBaudRate());
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",NULL);
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetLog",&str);
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetPort",GetPortName());
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetBaud",(void*)GetBaudRate());

	
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetExit",&flag);

}

void CMySerial::OnAfterMainLoop()
{
	bool flag = true;
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetExit",&flag);
		
}

void CMySerial::OnBeforeMainLoop()
{
}


void CMySerial::OnLine(unsigned char *line)
{
	fprintf(stderr,"%s %d\n",GetPortName(),GetBaudRate());
	fprintf(stderr,"%s",line);
	//_Broker->ExecuteFunction(_Broker->GetParentPtr(),"gps_SetNMEAInfo",NULL);
}

void CMySerial::OnNewSignal()
{
	for(size_t i = 0; i < GetSignalCount(); i++)
	{
		fprintf(stderr,"%s %d\n",GetSignal(i)->name,GetSignal(i)->count);	
	}

}