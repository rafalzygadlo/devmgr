#include <wx/wx.h>
#include "NaviDisplaySignals.h"
#include "conf.h"
#include "dll.h"
#include "reader.h"
#include "tools.h"
#include "info.h"
#include "devices.h"
#include "protocol.h"
#include "ais.h"
#include "GeometryTools.h"



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
	m_Data = NULL;
	m_Devices = new wxArrayPtrVoid();
	m_ShipStateExist = false;
	m_Position_0_Exists = m_Position_1_Exists = false;
	m_Ticker = new CTicker(this);
	m_Ticker->Start();
	m_MilesPerDeg = nvDistance( 0.0f, 0.0f, 1.0f, 0.0f );	
	
	m_Font = new nvFastFont();
	m_Font->Assign( (nvFastFont*)NaviBroker->GetFont( 2 ) );		// 1 = nvAriali 
	m_Font->SetEffect( nvEFFECT_SMOOTH );
	m_Font->SetEffect( nvEFFECT_GLOW );
    
	m_Font->SetGlyphColor(0.0f, 0.0f, 0.0f);
	//Font->SetGlyphCenter(0.0001f);
    //Font->SetGlyphOffset( 0.5f );

	m_Font->SetGlowColor(0.8f, 0.8f, 0.8f );
	m_Font->SetGlowCenter( 4.0f );

	Reset(m_ShipState);
	Reset(m_GlobalShipState);
	AddExecuteFunction("devmgr_OnDevData",OnDeviceData);
	AddExecuteFunction("devmgr_OnDevSignal",OnDeviceSignal);
	AddExecuteFunction("devmgr_GetParentPtr",GetParentPtr);
	AddExecuteFunction("devmgr_AddDevice",AddDevice);
	AddExecuteFunction("devmgr_OnFuncData",OnFunctionData);
		
	
	//m_SearchThread = new CNotifier();
	//m_SearchThread->Start();
	//CreateApiMenu();
	
}

CMapPlugin::~CMapPlugin()
{
	m_Devices->Clear();
	delete m_Devices;
	delete m_DisplaySignal;
	FreeMutex();
}

void CMapPlugin::WriteConfig()
{
	int type;
	m_FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	m_FileConfig->DeleteGroup(_(KEY_DEVICES));
	
	for(size_t i = 0; i < m_Devices->size(); i++)
	{
		CReader *ptr = (CReader*)m_Devices->Item(i);
		type = ptr->GetConnectionType();		
		
		switch(type)
		{
			case CONNECTION_TYPE_SERIAL:	WriteSerialConfig(i);	break;
			case CONNECTION_TYPE_SOCKET:	WriteSocketConfig(i);	break;
				
		}
			
	}
	
	delete m_FileConfig;
	m_FileConfig = NULL;

}

void CMapPlugin::WriteSerialConfig(int index)
{
	wxString name;
	int baud, type, ctype;
	bool running;
	
	CReader *Reader = (CReader*)m_Devices->Item(index);
	name = Reader->GetDeviceName();
	running = Reader->IsRunning();
	wxString port(Reader->GetSerialPort(),wxConvUTF8);
	baud = Reader->GetBaudRate();
	type = Reader->GetDeviceType();
	ctype = Reader->GetConnectionType();
			
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_NAME)),name);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_SERIAL_PORT)),port);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_BAUD)),baud);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_RUNNING)),running);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_DEVICE_TYPE)),type);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_CONNECTION_TYPE)),ctype);
}

void CMapPlugin::WriteSocketConfig(int index)
{
	wxString name, host;
	int  port, ctype, type;
	bool running;
	
	CReader *Reader = (CReader*)m_Devices->Item(index);
	name = Reader->GetDeviceName();
	running = Reader->IsRunning();
	port = Reader->GetPort();
	host = wxString(Reader->GetHost(),wxConvUTF8);
	ctype = Reader->GetConnectionType();
	type = Reader->GetDeviceType();
		
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_NAME)),name);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_HOST)),host);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_PORT)),port);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_RUNNING)),running);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_DEVICE_TYPE)),type);
	m_FileConfig->Write(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_CONNECTION_TYPE)),ctype);

}

void CMapPlugin::ReadConfig()
{
	m_FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	size_t len = m_FileConfig->GetNumberOfGroups();
	
	wxArrayString devices = GetConfigItems(_(KEY_DEVICES));
	int type;
	
	for(size_t i = 0; i < devices.size(); i++)
	{
		m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),i,_(KEY_CONNECTION_TYPE)),&type);
		
		switch(type)
		{
			case CONNECTION_TYPE_SERIAL:	ReadSerialConfig(i);	break;
			case CONNECTION_TYPE_SOCKET:	ReadSocketConfig(i);	break;
		}
	}
			
	delete m_FileConfig;
	m_FileConfig = NULL;


}

void CMapPlugin::ReadSerialConfig(int index)
{
	wxString port, name;
	int baud,dtype;
	bool running;

	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_NAME)),&name);
	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_SERIAL_PORT)),&port);
	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_BAUD)),&baud);
	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_RUNNING)),&running);
	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_DEVICE_TYPE)),&dtype);
	
	CReader *reader = CreateSerialDevice(name,port.char_str(),baud,dtype,running);
	AddDevice(reader);

}

void CMapPlugin::ReadSocketConfig(int index)
{
	wxString name, host;
	bool running;
	int port,dtype;

	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_NAME)),&name);
	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_HOST)),&host);
	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_PORT)),&port);
	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_RUNNING)),&running);
	m_FileConfig->Read(wxString::Format(_("%s/%d/%s"),_(KEY_DEVICES),index,_(KEY_DEVICE_TYPE)),&dtype);
	
	CReader *socket = CreateSocketDevice(name,host,port,dtype,running);
	AddDevice(socket);

}

void CMapPlugin::OnInitGL()
{
	m_Font->InitGL();
}

void CMapPlugin::OnTickerStart()
{

}

void CMapPlugin::OnTickerStop()
{

}

void CMapPlugin::OnTickerTick()
{
	SendShipData();
	PrepareBuffer();
}		

void CMapPlugin::PrepareBuffer()
{
	GetMutex()->Lock();
	CNaviArray <SAisData*> *buffer = ais_get_buffer();
	m_Font->Clear();	
	// przygotuj bufor punktow do renderu
	CurrentBufferPtr = &PointsBuffer1;
	PointsBuffer0.Clear();
	TriangleBuffer0.Clear();
	
	for(size_t i = 0; i < buffer->Length(); i++)
	{
		SAisData *data = buffer->Get(i);
		PreparePointsBuffer(data);
		PrepareTriangleBuffer(data);
			
		//PrepareIndicesBuffer();
	}
	CurrentBufferPtr = &PointsBuffer0;
	CopyPointsBuffer();

	GetMutex()->Unlock();
	
}

void CMapPlugin::CopyPointsBuffer()
{
	PointsBuffer1.Clear();
	PointsBuffer1.SetSize(PointsBuffer0.Length());
	
	for(size_t i = 0; i < PointsBuffer0.Length(); i++)
		PointsBuffer1.Set(i,PointsBuffer0.Get(i));
}

void CMapPlugin::PreparePointsBuffer(SAisData *ptr)
{
	nvPoint2d pt;
	
	m_Broker->Unproject(ptr->lon, -ptr->lat, &pt.x, &pt.y);							// pozycja y statku na mapie
	double Distance = nvDistance( ptr->lon, ptr->lat, ptr->lon + 1.0, ptr->lat );	// iloœæ mil na stopieñ w aktualnej pozycji y
		
	PointsBuffer0.Append(pt);

}

void CMapPlugin::PrepareTriangleBuffer(SAisData *ptr)
{
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	
	double yDistance = nvDistance( pt.x, pt.y, pt.x + 1.0, pt.y );	// iloœæ mil na stopieñ w aktualnej pozycji y
	
	// na mile morskie
	if(ptr->valid_dim && ptr->valid_pos)
	{
		double to_bow, to_stern, to_port, to_starboard;	
		nvPoint2d p1, p2, p3, p4;
		
		to_bow		 = (double)ptr->to_bow/1852/yDistance; 			
		to_stern	 = (double)ptr->to_stern/1852/yDistance;		
		to_port		 = (double)ptr->to_port/1852/yDistance ;			
		to_starboard = (double)ptr->to_starboard/1852/yDistance;
			
		double width = to_port + to_starboard;
		double height = to_bow + to_stern;

		p1.x = -0.5*width;	p1.y =  0.5*height;
		p2.x =  0.5*width;	p2.y =  0.5*height;
		p3.x =  0.5*width;	p3.y = -0.5*height;
		p4.x = -0.5*width;	p4.y = -0.5*height;
				
		if(ptr->valid_cog)
		{
			double out_x,out_y;
			RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(ptr->cog));	p1.x = out_x;	p1.y = out_y;
			RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(ptr->cog));	p2.x = out_x;	p2.y = out_y;
			RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(ptr->cog));	p3.x = out_x;	p3.y = out_y;
			RotateZ(p4.x,p4.y,out_x,out_y,nvToRad(ptr->cog));	p4.x = out_x;	p4.y = out_y;
		}
		
		double to_x, to_y;
		m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
		pt.x = to_x;
		pt.y = to_y;
		
		double vx = to_port - to_starboard;
		double vy = to_bow - to_stern;
		m_Broker->Unproject(vx, vy,&to_x,&to_y);
		vx = to_x;
		vy = to_y;
		
		p1.x += vy; p1.y += vx;
		p2.x += vy; p2.y += vx;
		p3.x += vy; p3.y += vx;
		p4.x += vy; p4.y += vx;

		// translate
		p1.x += pt.x; p1.y += pt.y;
		p2.x += pt.x; p2.y += pt.y;
		p3.x += pt.x; p3.y += pt.y;
		p4.x += pt.x; p4.y += pt.y;

				
		TriangleBuffer0.Append(p1);
		TriangleBuffer0.Append(p2);
		TriangleBuffer0.Append(p3);
		TriangleBuffer0.Append(p4);


		wchar_t str[128];
		float scale = (1 / m_Broker->GetMapScale()) / 8;
		wchar_t wc[128];
		mbstowcs(wc, ptr->shipname, 128);
		//m_Broker->Project(
		swprintf(str,L"mmsi:%d [%dx%d] %ls",ptr->mmsi,ptr->to_bow+ptr->to_stern,ptr->to_port+ptr->to_starboard,wc);
				
		m_Font->Print(p1.x,p1.y,scale,0,str);
		glColor3f(1.0,0.0,0.0);
		
		//PointsBuffer0.Append(pt);
	}
	
	//double ShipScale = (ShipWidth / m_MilesPerDeg) * Percent;						// skalowanie rzeczywistego wymiaru statku w milach
			
	

}
/*
void CMapPlugin::BuildFontData(SAisData *ptr)
{
	Font
	
	Font->Clear();
	if(size == 0)
		return;

	size_t CaptionsSize = size;
    vect2 *Positions = (vect2*)malloc( CaptionsSize *sizeof( vect2 ) );    // czêœæ ca³kowita jednostki sondowania
    float *Scale = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *Angle = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *vx = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *vy = (float*)malloc( CaptionsSize * sizeof( float ) );
    wchar_t **CaptionsStr = (wchar_t**)malloc(  CaptionsSize * sizeof( wchar_t** ) );
	
	

    for(size_t i = 0 ; i < Towns.Length(); i++ ) 
	{
		//STown Town = Towns.Get(i);
		Positions[i][0] = TownsList[i].p1; 
        Positions[i][1] = TownsList[i].p2  + (20.0/SmoothScaleFactor);
		Scale[i] = TownsList[i].scale / SmoothScaleFactor / DEFAULT_FONT_FACTOR;
        vx[i] = 0.5f;
        vy[i] = 0.5f;
		CaptionsStr[i] = TownsList[i].name;   // bez kopiowania ³añcucha!!! 
		Angle[i] = Broker->GetAngle();
    }

	Font->Clear();
    Font->PrintList( Positions, Scale, Angle, CaptionsStr, CaptionsSize, vx, vy );

	free( CaptionsStr );    // ³añcuchy nie zosta³y skopiowane, nie ma koniecznoœci zwalniania ca³ej listy
    free( Positions );
    free( Scale );
    free( Angle );
    free( vx );
    free( vy );

}
*/

void CMapPlugin::SendShipData()
{

	if(m_ShipStateExist)
	{
		m_Broker->SetShip(m_Broker->GetParentPtr(),m_ShipState);	
		m_Position_0_Exists = false;
		m_Position_1_Exists = false;
		m_ShipStateExist = false;
		Reset(m_ShipState);
	
	}else{
	
		if(m_OtherData)
		{
			m_Broker->SetShip(m_Broker->GetParentPtr(),m_GlobalShipState);
			Reset(m_GlobalShipState);
		}
	
	}
}

CNaviBroker *CMapPlugin::GetBroker()
{
    return m_Broker;
}

size_t CMapPlugin::GetDevicesCount()
{
	return m_Devices->size();
}

CReader *CMapPlugin::GetReader(size_t idx)
{
	if(idx > m_Devices->size())
		return NULL;
	else
		return (CReader*)m_Devices->Item(idx);
}


void *CMapPlugin::AddDevice(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	ThisPtr->AddDeviceFunc((CReader*)Params);

	return NULL;
}

void CMapPlugin::AddDeviceFunc(CReader *ptr)
{
	AddDevice(ptr);
	SendSignal(ADD_DEVICE,0);
}

void CMapPlugin::StartDevice(CReader *ptr)
{
	SendSignal(START_DEVICE,ptr);
}

void CMapPlugin::StopDevice(CReader *ptr)
{
	SendSignal(STOP_DEVICE,ptr);
}

void CMapPlugin::RemoveDevice(CReader *ptr)
{
	for(size_t i = 0; i < m_Devices->size(); i++)
	{
		CReader *_ptr = (CReader*)m_Devices->Item(i);
		if(_ptr == ptr)
		{
			_ptr->Stop();
			CMyInfo Info(NULL,wxString::Format(GetMsg(MSG_STOPPING_DEVICE),_ptr->GetDeviceName()));
			while(_ptr->GetWorkingFlag())
				wxMilliSleep(10);

			delete _ptr;
			m_Devices->Remove(_ptr);
			SendSignal(REMOVE_DEVICE,_ptr);
		}
	}

	ReindexDevics();
}

void CMapPlugin::ReindexDevics()
{
	for(size_t i = 0; i < m_Devices->size(); i++)
	{
		CReader *ptr = (CReader*)m_Devices->Item(i);
		ptr->SetDeviceId(i);
	}
}

void CMapPlugin::AddDevice(CReader *ptr)
{
	m_Devices->Add(ptr);

	ptr->SetBroker(m_Broker);
	ptr->SetDeviceId(m_Devices->size() - 1);
			
	if(ptr->RunOnStart())
		ptr->Start();

}

void CMapPlugin::DeleteDevice(size_t idx)
{
	CReader *ptr = (CReader*)m_Devices->Item(idx);
	ptr->Stop();
	m_Devices->Remove(ptr);
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

wxArrayPtrVoid *CMapPlugin::GetDevicesList()
{
	return m_Devices;
}

void CMapPlugin::Run(void *Params)
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	ReadConfig();
	m_Init = true;
	m_EnableControls = true;
	SendSignal(INIT_SIGNAL,NULL);
} 

void CMapPlugin::Kill(void)
{
	m_Ticker->Stop();
	delete m_Ticker;
	m_EnableControls = false;
		
	m_NeedExit = true;
	WriteConfig();
	//CMyInfo Info(NULL,wxString::Format(GetMsg(MSG_STOPPING_DEVICE)));
	
	//m_SearchThread->Stop();
	//delete m_SearchThread;
	SendSignal(CLEAR_AIS_LIST,NULL);

	for(size_t i = 0; i < m_Devices->size(); i++)
	{
		CReader *ptr = (CReader*)m_Devices->Item(i);
		ptr->Stop();
		delete ptr;
	}
	
	if(m_FileConfig != NULL)
        delete m_FileConfig;

	ais_free_list();
	ais_free_buffer();
	SendSignal(CLEAR_DISPLAY,NULL);
	// before myserial delete

}

void CMapPlugin::RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_DOUBLE, 0, RawData);
    glDrawArrays(Mode, 0, DataLength);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void CMapPlugin::Render()
{
	glColor3f(0.0,0.0,0.0);
	glPointSize(5);
	RenderGeometry(GL_POINTS,TriangleBuffer0.GetRawData(),TriangleBuffer0.Length());
	RenderGeometry(GL_QUADS,TriangleBuffer0.GetRawData(),TriangleBuffer0.Length());
			
	glColor3f(1.0,0.0,0.0);
	//RenderGeometry(GL_POINTS,CurrentBufferPtr->GetRawData(),CurrentBufferPtr->Length());
	RenderGeometry(GL_POINTS,PointsBuffer0.GetRawData(),PointsBuffer0.Length());

	glPointSize(1);


	m_Font->ClearBuffers();
	m_Font->CreateBuffers();
	m_Font->Render();

}

bool CMapPlugin::GetNeedExit(void)
{    
	return m_NeedExit;
}

void CMapPlugin::CreateApiMenu(void) 
{

//	NaviApiMenu = new CNaviApiMenu( L"Settings" );	// nie u¿uwaæ delete - klasa zwalnia obiejt automatycznie
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
	}
	
	return ThisPtr;
}

void *CMapPlugin::OnDeviceSignal(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	CReader *ptr = (CReader*)Params;
	ThisPtr->SendSignal(ptr->GetSignalType(),ptr);
		
	return NULL;
}


void *CMapPlugin::OnFunctionData(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	SFunctionData *Data = (SFunctionData*)Params;
	
	ThisPtr->SetFunctionData(Data);
	
	return NULL;
}

void *CMapPlugin::OnDeviceData(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	SData *Data = (SData*)Params;
	
	ThisPtr->SetData(Data);
	
	return NULL;
}

void *CMapPlugin::OnNewAisObject(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	//SFunctionData *Data = (SFunctionData*)Params;
	
	//ThisPtr->SendSignal(SIGNAL_NEW_AIS_OBJECT,NULL);
		
	return NULL;
}

void *CMapPlugin::GetAisBuffer(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	//Params = ais_get_buffer();
	return NULL;
}


SData *CMapPlugin::GetData()
{
	return m_Data;
}

void CMapPlugin::SetData(SData *value)
{	
	SendSignal(DATA_SIGNAL,value);
}

void CMapPlugin::SetFunctionData(SFunctionData *data)
{
	switch(data->id_function)
	{
		case 0: 
			memcpy(m_GlobalShipState,data->values,sizeof(data->values));
			Prepare();
		break;
	}
	
}

void CMapPlugin::Prepare()
{
	m_OtherData = true;
	
	if(!m_ShipStateExist)
	{
		if(!UNDEFINED_VAL(m_GlobalShipState[0]))
		{
			m_ShipState[0] = m_GlobalShipState[0];
			m_Position_0_Exists = true;
			m_OtherData = false;
		}
		
		if(!UNDEFINED_VAL(m_GlobalShipState[1]))
		{			
			m_ShipState[1] = m_GlobalShipState[1];
			m_Position_1_Exists = true;
			m_OtherData = false;
		}
	}
	
	if(!UNDEFINED_VAL(m_GlobalShipState[2]))
		m_ShipState[2] = m_GlobalShipState[2];
	
	if(!UNDEFINED_VAL(m_GlobalShipState[3]))
		m_ShipState[3] = m_GlobalShipState[3];
	
	if(!UNDEFINED_VAL(m_GlobalShipState[4]))
		m_ShipState[4] = m_GlobalShipState[4];

	if(!UNDEFINED_VAL(m_GlobalShipState[5]))
		m_ShipState[5] = m_GlobalShipState[5];

	if(m_Position_0_Exists && m_Position_1_Exists)
	{
		m_ShipStateExist = true;
		m_Position_0_Exists = false;
		m_Position_1_Exists = false;
	}
	
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

void CMapPlugin::SendSignal(int type, void *ptr)
{
	m_DisplaySignal->SetData((void*)ptr,sizeof(ptr));
	m_DisplaySignal->SetTag(type);
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
    return TEXT(PRODUCT_NAME);
#endif
#if defined(_LINUX32) || defined(_LINUX64)
    return LPRODUCT_NAME;
#endif
}

const NAVIMAPAPI wchar_t *NaviPluginIntroduce(int LangID)
{
#if defined(_WIN32) || defined(_WIN64)
    return TEXT(PRODUCT_NAME);
#endif
#if defined(_LINUX32) || defined(_LINUX64)
    return LPRODUCT_NAME;
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
