#include <wx/wx.h>
#include "NaviDisplaySignals.h"
#include "conf.h"
#include "dll.h"
#include "serial.h"
#include "tools.h"
#include "info.h"
#include "markers.h"

unsigned char PluginInfoBlock[] = {
0x59,0x0,0x0,0x0,0x5a,0xa1,0xb1,0xfb,0xff,0x1c,0xbd,0xa7,0xc4,0xbf,0x99,0x83,0xaa,0xa9,0x33,0x3e,0xcd,0x2e,0x30,0x6e,0xc,0xa6,0x2a,0x51,0xef,0x72,0x80,0x38,0x39,0x2b,
0x23,0x64,0x4,0x6d,0x21,0xf1,0x8c,0x5c,0x2f,0x7,0xd4,0xb0,0x6c,0x5f,0x26,0x24,0xf2,0xb6,0xd3,0xd4,0xb2,0x8,0x90,0x67,0x3f,0xee,0x7,0xae,0x45,0x69,0xf8,0x1e,0xf3,0xd3,
0xcb,0x87,0x15,0x76,0x1a,0xbb,0x40,0x1e,0x16,0x95,0xa5,0xcf,0xe5,0x73,0xc,0x51,0x4f,0xf9,0x8b,0x8a,0xc2,0xd7,0xef,0x30,0xfc,0xb2,0xdb,0x9b,0xdf,0x86,0x67,0x77,0x83,0x87,
0x15,0x31,0x3f,0xb4,0x9e,0x80,0x5e,0xda,0x59,0x9c,0xe3,0x56,0x9a,0xeb,0xb2,0xd8,0x22,0x98,0x22,0x57,0x4b,0x76,0x38,0xf,0xcd,0xbd,0xe5,0x6f,0x16,0xe4,0x26,0xba,0x11,0x27,
0x1e,0xa7,0x9d,0xc9,0x23,0xe7,0xee,0x4e,0x70,0x14,0xc0,0x64,0x57,0x33,0xcd,0xda,0x1,0x7b,0x6e,0x61,0x3e,0x8,0x5e,0x70,0xc7,0x7f,0xdf,0x2d,0x41,0x3b,0xba,0x3e,0x89,0x95,
0x32,0x33,0x86,0x19,0x77,0xd0,0x96,0xb3,0xdf,0xc0,0x76,0x3e,0xe4,0x8e,0x5c,0xee,0x6,0x21,0x6f,0x8a,0x5b,0x6c,0x52,0x19,0xa,0x44,0x60,0x8f,0xfb,0xd6,0xe,0xc,0x80,0x1,
0xb6,0x79,0xaf,0x84,0x33,0x2d,0xd8,0x2f,0x35,0x37,0xf5,0x7a,0x2b,0x25,0xd,0xa4,0x89,0x63,0xac,0xd2,0x2c,0x18,0x56,0x83,0x0,0xdd,0xef,0x43,0xf2,0xe1,0x61,0xda,0x8f,0x52,
0x2c,0xbc,0xea,0x8b,0x3a,0x17,0x91,0x6d,0x21,0xea,0x55,0x33,0xae,0xb0,0x10,0x10,0x7e,0xee,0xc7,0x40,0x6d,0xe8,0xf8,0x47,0x1a,0x35,0xbd,0x6f,0x33,0x3a,0xb1,0x68,0xe7,0x9b,
0x1,0xa4,0xbc,0xc8,0xa8,0x89,0x4b,0xe5,0xa3,0x6c,0x11,0xbe,0xe8,0xb1,0x52,0xe9,0xe5,0xc2,0xc5,0x50,0x5,0x90,0x9d,0xdf,0x5c,0x5d,0x99,0xa4,0x31,0x78,0xf,0x1f,0x9c,0x6a,
0xb5,0xf6,0x66,0x62,0x1e,0xfb,0x91,0x42,0x3c,0xb3,0x3e,0xe0,0xb9,0x1e,0x8,0x7c,0x5d,0xe3,0xe9,0xd0,0xe5,0x19,0x7d,0x79,0x45,0x51,0x80,0xfd,0x98,0xf9,0xe2,0x7f,0xb7,0x87,
0xcb,0xbf,0xea,0x90,0x44,0xa6,0xb0,0x16,0x83,0x90,0xd,0x6e,0xc0,0x5e,0xa2,0x60,0xb7,0xff,0xac,0xb1,0x12,0xe8,0x3e,0x5e,0x8d,0x4b,0xac,0x5e,0x4a,0xc9,0xa8,0xa7,0xa7,0x21,
0x2f,0x2c,0x25,0xae,0x56,0x6,0x8c,0x4d,0xc3,0xac,0x93,0xb,0xed,0xfb,0x94,0xc3,0x1e,0x0,0x4e,0x5b,0x2e,0x6,0x2b,0x16,0x1e,0xbd,0x44,0xc9,0x95,0x27,0x1c,0x8a,0x86,0x5d,
0x90,0xb8,0x17,0xe5,0x92,0x64,0xd3,0x42,0x98,0x8a,0x5c,0x62,0x99,0x72,0x3d,0xf4,0xba,0xf6,0xc8,0xc,0x94,0x90,0x1b,0x1f,0xda,0xa6,0x7d,0x2e,0xc4,0x88,0x72,0x87,0x7f,0x35,
0x27,0x65,0x12,0xec,0x2d,0xb6,0xc1,0x3,0xa,0x2c,0x57,0x9e,0xe4,0x37,0x44,0x31,0xe2,0xdf,0xfa,0x1f,0xa3,0xf4,0xee,0x4e,0x1c,0x15,0xbe,0xeb,0xe3,0x8,0x60,0xae,0xec,0x4f,
0x8a,0x42,0xba,0xe7,0xfe,0x56,0x5e,0x42,0x97,0xec,0xe1,0xb1,0x1c,0x8e,0xbc,0x53,0x6b,0xd0,0xf0,0x35,0x7d,0xcf,0xc1,0x4e,0x3f,0x3d,0xf7,0x29,0x7,0xcd,0x0,0xcd,0x95,0xd5,
0xea,0xa8,0x95,0x14,0xfd,0x13};


CMapPlugin::CMapPlugin(CNaviBroker *NaviBroker):CNaviMapIOApi(NaviBroker)
{

	m_DisplaySignal = new CDisplaySignal(NDS_DEVICE_MANAGER);
	m_FileConfig = NULL;
    m_NeedExit = false;
    m_Broker = NaviBroker;
	m_ConfigPath = GetPluginConfigPath();
	m_EnableControls = false;
	//m_MyFrame = NULL;

	AddExecuteFunction("devmgr_OnDevData",OnDeviceData);
	AddExecuteFunction("devmgr_OnDevSignal",OnDeviceSignal);
	AddExecuteFunction("devmgr_GetParentPtr",GetParentPtr);
	AddExecuteFunction("devmgr_AddDevice",AddDevice);
	//CreateApiMenu();
	
}

CMapPlugin::~CMapPlugin()
{
	delete m_DisplaySignal;
}


void CMapPlugin::WriteConfig()
{
	m_FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	wxString name,port;
	int baud;
	bool running;
	
	m_FileConfig->DeleteGroup(_(KEY_DEVICES));
	
	for(size_t i = 0; i < m_vDevices.size(); i++)
	{
	
		CMySerial *Serial = m_vDevices[i];
		name = Serial->GetDeviceName();
		running = Serial->IsRunning();
		wxString port(Serial->GetPortName(),wxConvUTF8);
		baud = Serial->GetBaudRate();
		
		
		m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_NAME)),name);
		m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_PORT)),port);
		m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_BAUD)),baud);
		m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_RUNNING)),running);

		// dlugosc tablicy markerow
		for(size_t j = 0; j < Serial->GetMarkersLength(); j++)
		{
			TDataDefinition item = Serial->GetMarker(j);
			m_FileConfig->Write(wxString::Format(_("%s/%d/%d/%s"),_(KEY_DEVICES),i,j,_(KEY_MARKER_ID)),item.DataID);
		}
	
	}
	
	delete m_FileConfig;
	m_FileConfig = NULL;

}

void CMapPlugin::ReadConfig()
{
	m_FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	size_t len = m_FileConfig->GetNumberOfGroups();
	
	wxArrayString devices = GetConfigItems(_(KEY_DEVICES));
	wxString name, port;
	int baud, marker_id;
	bool running;
	
	for(size_t i = 0; i < devices.size(); i++)
	{
		m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_NAME)),&name);
		m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_PORT)),&port);
		m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_BAUD)),&baud);
		m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_RUNNING)),&running);

		CMySerial *serial = CreateNewDevice(name,port.char_str(),baud,running);
		
		wxArrayString markers = GetConfigItems(wxString::Format(_("%s/%d"),_(KEY_DEVICES),i));
		for(size_t j = 0; j < markers.size(); j++)
		{	
			m_FileConfig->Read(wxString::Format(_("%s/%d/%d/%s"),_(KEY_DEVICES),i,j,_(KEY_MARKER_ID)),&marker_id);
			
			TDataDefinition_s *item = GetMarker(marker_id);
			if(item != NULL)
				serial->AddMarker(*item);
		}
		
		AddDevice(serial);
	
	}
			
	delete m_FileConfig;
	m_FileConfig = NULL;


}

CNaviBroker *CMapPlugin::GetBroker()
{
    return m_Broker;
}

size_t CMapPlugin::GetDevicesCount()
{
	return m_vDevices.size();
}

CMySerial *CMapPlugin::GetDevice(size_t idx)
{
	if(idx > m_vDevices.size())
		return NULL;
	else
		return m_vDevices[idx];
}


void *CMapPlugin::AddDevice(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->AddDeviceFunc((CMySerial*)Params);

	return NULL;
}

void CMapPlugin::AddDeviceFunc(CMySerial *serial)
{
	AddDevice(serial);
	SendSignal(ADD_DEVICE,0);
}

void CMapPlugin::RemoveDevice(CMySerial *serial)
{
	for(size_t i = 0; i < m_vDevices.size(); i++)
	{
		if(m_vDevices[i] == serial)
		{
			m_vDevices[i]->Stop();
			CMyInfo Info(NULL,wxString::Format(GetMsg(MSG_STOPPING_DEVICE),m_vDevices[i]->GetDeviceName()));
			while(m_vDevices[i]->GetWorkingFlag())
				wxMilliSleep(10);

			delete m_vDevices[i];
			m_vDevices.erase(m_vDevices.begin() + i);
			SendSignal(REMOVE_DEVICE,0);
		}
	}

	ReindexDevics();
}

void CMapPlugin::ReindexDevics()
{
	for(size_t i = 0; i < m_vDevices.size(); i++)
	{
		m_vDevices[i]->SetDeviceId(i);
	}
}

void CMapPlugin::AddDevice(CMySerial *serial)
{
	m_vDevices.push_back(serial);

	serial->SetBroker(m_Broker);
	serial->SetDeviceId(m_vDevices.size() - 1);
			
	if(serial->RunOnStart())
		serial->Start();

}

void CMapPlugin::DeleteDevice(size_t idx)
{
	m_vDevices[idx]->Stop();
	m_vDevices.erase(m_vDevices.begin() + idx);
}

wxArrayString CMapPlugin::GetConfigItems(wxString path)
{
    
    wxArrayString Names;
    long dummy;

    wxString old_path = m_FileConfig->GetPath();
    m_FileConfig->SetPath(path);

    bool bCont = m_FileConfig->GetFirstGroup(path, dummy);

    while ( bCont )
    {
        Names.Add(path);
        bCont = m_FileConfig->GetNextGroup(path, dummy);
    }

    m_FileConfig->SetPath(old_path);
    
	return Names;
}


bool CMapPlugin::IsInited()
{
	return m_Init;
}

void CMapPlugin::SetDisplaySignal(int type)
{
	m_DisplaySignalType = type;
}

bool CMapPlugin::GetEnableControlsFlag()
{
	return m_EnableControls;
}


void CMapPlugin::Run(void *Params)
{
	m_Init = false;
	ReadConfig();
	m_Init = true;
	m_EnableControls = true;
	//SendSignal(CLEAR_DISPLAY,0);
	SendSignal(INIT_SIGNAL,0);
} 

void CMapPlugin::Kill(void)
{
	m_EnableControls = false;
		
	m_NeedExit = true;
	WriteConfig();
	
	for(size_t i = 0; i < m_vDevices.size(); i++)
	{
		m_vDevices[i]->Stop();
		CMyInfo Info(NULL,wxString::Format(GetMsg(MSG_STOPPING_DEVICE),m_vDevices[i]->GetDeviceName()));
		while(m_vDevices[i]->GetWorkingFlag())
			wxMilliSleep(50);
				
		delete m_vDevices[i];
	}
    
    if(m_FileConfig != NULL)
        delete m_FileConfig;
	
	SendSignal(CLEAR_DISPLAY,0);
	
	// before myserial delete
	

}

void CMapPlugin::RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_DOUBLE, 0, RawData);
    glDrawArrays(Mode, 0, DataLength);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void CMapPlugin::RenderPosition()
{
		
	//glColor4f(0.0f,0.0f,1.0f,0.5f);
	//glPushMatrix();
		//glLineWidth(2);
		//glTranslated(0.0,0.0,0.0);
		//glScalef(50.0/Scale,50.0/Scale,0.0f);
		//glRotatef(Hdg,0.0f,0.0f,1.0f);
		//RenderGeometry(GL_LINE_LOOP,&vCircle1[0],vCircle1.size());	// circle 0
		//RenderGeometry(GL_LINE_LOOP,&vCircle2[0],vCircle2.size());  // circle 1
		//RenderGeometry(GL_LINE_LOOP,&vCircle3[0],vCircle3.size());  // circle 1
		//RenderGeometry(GL_LINES,&vLineH[0],vLineH.size());			// line H
		//glLineWidth(1);
    //glPopMatrix();

}

void CMapPlugin::Render()
{
	//Scale = m_Broker->GetMapScale();
	//RenderPosition();
}


bool CMapPlugin::GetNeedExit(void)
{
    return m_NeedExit;
}

void CMapPlugin::CreateApiMenu(void) 
{

//	NaviApiMenu = new CNaviApiMenu( L"Settings" );	// nie u�uwa� delete - klasa zwalnia obiejt automatycznie
//	NaviApiMenu->AddItem( L"Device Manager",this, MenuConfig );
	
}

void CMapPlugin::Config()
{

}

void CMapPlugin::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{

}

void CMapPlugin::MouseDBLClick(int x, int y)
{

}

void *CMapPlugin::GetParentPtr(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	
	while(!ThisPtr->IsInited())
	{
		wxMilliSleep(200);
		fprintf(stderr,"waiting for event\n");
	}
	
	
//	ThisPtr->SendAllInsertSignal();
//	ThisPtr->SendQueueInsertSignal();
//	ThisPtr->SendInstalledInsertSignal();
	return ThisPtr;
}

void *CMapPlugin::OnDeviceSignal(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	CMySerial *Serial = (CMySerial*)Params;
	ThisPtr->SendSignal(Serial->GetSignalType(),Serial->GetDeviceId());
		
	return NULL;
}

void *CMapPlugin::OnDeviceData(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	TData *Data = (TData*)Params;

	
	ThisPtr->SetData(Data);
	
	return NULL;

}

void CMapPlugin::SetData(TData *val)
{
//	Hdg = val;
//	m_Broker->SetMapAngle(m_Broker->GetParentPtr(), val);
	wchar_t str[1024] = {0}; 

	swprintf(str,L"%d %hs %hs",val->DataID,val->Marker,val->Value);
	m_Broker->consolef(m_Broker->GetParentPtr(),str);
	m_Broker->Refresh(m_Broker->GetParentPtr());
}

int CMapPlugin::GetDisplaySignalType()
{
	return m_DisplaySignalType;
}

void CMapPlugin::SetDeviceId(int id)
{
	m_DeviceId = id;
}

int CMapPlugin::GetDeviceId()
{
	return 	m_DeviceId;
}

void CMapPlugin::SetDisplaySignalType(int type)
{
	m_DisplaySignalType = type;
}

void CMapPlugin::SendSignal(int type, int id)
{
	SetDeviceId(id);
	SetDisplaySignalType(type);
	m_DisplaySignal->SetData((void*)this,sizeof(this));
	GetBroker()->SendDisplaySignal((void*)m_DisplaySignal);
}

//	 API dla DLL
void NAVIMAPAPI *CreateNaviClassInstance(CNaviBroker *NaviBroker)
{
   CMapPlugin *DLL = new CMapPlugin(NaviBroker);
    return (void*) ( DLL );
}

const NAVIMAPAPI wchar_t *NaviPluginDescription(int LangID)
{
#if defined(_WIN32) || defined(_WIN64)
    return TEXT("Device Manager.");
#endif
#if defined(_LINUX32) || defined(_LINUX64)
    return L"Device Manager.";
#endif
}

const NAVIMAPAPI wchar_t *NaviPluginIntroduce(int LangID)
{
#if defined(_WIN32) || defined(_WIN64)
    return TEXT("Device Manager");
#endif
#if defined(_LINUX32) || defined(_LINUX64)
    return L"Device Manager";
#endif
}

int NAVIMAPAPI GetNaviPluginType(void)
{
    return MAP_PLUGIN_RUN_ON_DEMAND;
}
#if defined(_WIN32) || defined(_WIN64)
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
#endif

unsigned char *GetNaviPluginInfoBlock()
{
	return PluginInfoBlock;
}

void NAVIMAPAPI FreeNaviClassInstance(void *ptr)
{
	delete (CMapPlugin*)ptr;
}

