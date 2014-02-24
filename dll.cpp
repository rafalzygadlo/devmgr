#include <wx/wx.h>
#include "GLee.h"
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
#include "images/ship.img"



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
	m_PositionExists = false;
	m_Position_0_Exists = m_Position_1_Exists = false;
	m_OtherData = false;
	m_Ticker = new CTicker(this);
	m_Ticker->Start();
	m_MilesPerDeg = nvDistance( 0.0f, 0.0f, 1.0f, 0.0f );
	m_MaxFrequency = DEFAULT_FREQUENCY; // w milisekundach 10 sekund domyslnie
	m_ShipTick = 0;
	m_AisBufferTick = 0;
	m_ShipInterval = m_MaxFrequency/TICKER_SLEEP;
	m_ShipInterval = 200/TICKER_SLEEP;

	m_AisBufferInterval = AIS_BUFFER_INTERVAL;
	m_CurrentTriangleBufferPtr = NULL;
	//m_CurrentHDT = UNDEFINED_DOUBLE;
	m_LastHDT = UNDEFINED_DOUBLE;
	m_SignalID = -1;
	m_MaxFrequencyID = -1;
	memset(m_ShipValidFrequencyTable,0,MAX_SHIP_VALUES_LEN);
	m_ShipValidFrequency = false;
	m_Interpolation = false;

	m_Font = new nvFastFont();
	m_Font->Assign( (nvFastFont*)NaviBroker->GetFont( 2 ) );	// 1 = nvAriali 
	m_Font->SetEffect( nvEFFECT_SMOOTH );
	m_Font->SetEffect( nvEFFECT_GLOW );
    
	m_Font->SetGlyphColor(0.0f, 0.0f, 0.0f);
	//Font->SetGlyphCenter(0.0001f);
    //Font->SetGlyphOffset( 0.5f );

	m_Font->SetGlowColor(0.8f, 0.8f, 0.8f );
	m_Font->SetGlowCenter( 4.0f );

	memset(m_ShipTicks,0,sizeof(int) * MAX_SHIP_VALUES_LEN);
	memset(m_ShipTimes,0,sizeof(int) * MAX_SHIP_VALUES_LEN);

	Reset(m_ShipState);			//wysylany do statku
	Reset(m_ShipGlobalState);	
	Reset(m_ShipStaticState);	// statyczny state ktory nie jest resetowany przetrzymuje ostatnio otrzymane dane
	
	AddExecuteFunction("devmgr_OnDevData",OnDeviceData);
	AddExecuteFunction("devmgr_OnDevSignal",OnDeviceSignal);
	AddExecuteFunction("devmgr_GetParentPtr",GetParentPtr);
	AddExecuteFunction("devmgr_AddDevice",AddDevice);
	AddExecuteFunction("devmgr_OnFuncData",OnFunctionData);
	
	SetTickerTick();
	
	//m_SearchThread = new CNotifier();
	//m_SearchThread->Start();
	//CreateApiMenu();
	
}

CMapPlugin::~CMapPlugin()
{
	m_Devices->Clear();
	delete m_Devices;
	delete m_DisplaySignal;
	delete m_Font;
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

void CMapPlugin::CreateSymbol(void *MemoryBlock,long MemoryBlockSize)
{
	TMemoryBlock BlockTGA_0;
	BlockTGA_0.Ptr = MemoryBlock;
	BlockTGA_0.Size = MemoryBlockSize;
	m_TextureTGA_0 = LoadFromMemoryBlockTGA( &BlockTGA_0 );
}

void CMapPlugin::CreateTexture(TTexture *Texture, GLuint *TextureID)
{
	glGenTextures(1, TextureID );
	glBindTexture(GL_TEXTURE_2D, *TextureID );
	glTexImage2D(GL_TEXTURE_2D, 0, Texture->Bpp / 8, Texture->Width, Texture->Height, 0, Texture->Type, GL_UNSIGNED_BYTE, Texture->Data );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	FreeTexture( Texture );
}

void CMapPlugin::CreateTextures(void) 
{
	CreateSymbol(ship, ship_size);
	CreateTexture( m_TextureTGA_0,  &m_TextureID_0 );
}


void CMapPlugin::OnInitGL()
{
	CreateTextures();
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
	
	m_ShipTick++;
	m_AisBufferTick++;
		
	if( m_ShipTick >= m_ShipInterval ) 
	{
		m_ShipTick = 0;
		Interpolate();
		SendShipData();
	}
	
	if( m_AisBufferTick >= m_AisBufferInterval)	
	{	
		m_AisBufferTick = 0;
		PrepareBuffer();
	}
	
}


void CMapPlugin::PrepareBuffer()
{
	GetMutex()->Lock();
	CNaviArray <SAisData*> *buffer = ais_get_buffer();

	// przygotuj bufor punktow do renderu
	m_CurrentPointsBufferPtr = &m_PointsBuffer1;
	m_CurrentTriangleBufferPtr = &m_TriangleBuffer1; 
	m_CurrentTriangleIndicesBufferPtr = &m_TriangleIndicesBuffer1;
	
	m_PointsBuffer0.Clear();
	m_TriangleBuffer0.Clear();
	
	for(size_t i = 0; i < buffer->Length(); i++)
	{
		SAisData *data = buffer->Get(i);
		PreparePointsBuffer(data);
		PrepareTriangleBuffer(data);
		PrepareIndicesBuffer();
	}
	
	m_CurrentPointsBufferPtr = &m_PointsBuffer0;
	m_CurrentTriangleBufferPtr = &m_TriangleBuffer0;
	m_CurrentTriangleIndicesBufferPtr = &m_TriangleIndicesBuffer0;
	
	CopyPointsBuffer();
	CopyTriangleBuffer();
	CopyTriangleIndicesBuffer();

	GetMutex()->Unlock();
	
}

void CMapPlugin::CopyPointsBuffer()
{
	m_PointsBuffer1.Clear();
	m_PointsBuffer1.SetSize(m_PointsBuffer0.Length());
	
	for(size_t i = 0; i < m_PointsBuffer0.Length(); i++)
		m_PointsBuffer1.Set(i,m_PointsBuffer0.Get(i));
}

void CMapPlugin::CopyTriangleBuffer()
{
	m_TriangleBuffer1.Clear();
	m_TriangleBuffer1.SetSize(m_TriangleBuffer0.Length());
	
	for(size_t i = 0; i < m_TriangleBuffer0.Length(); i++)
		m_TriangleBuffer1.Set(i,m_TriangleBuffer0.Get(i));
}

void CMapPlugin::CopyTriangleIndicesBuffer()
{
	m_TriangleIndicesBuffer1.Clear();
	m_TriangleIndicesBuffer1.SetSize(m_TriangleIndicesBuffer0.Length());
	
	for(size_t i = 0; i < m_TriangleIndicesBuffer0.Length(); i++)
		m_TriangleIndicesBuffer1.Set(i,m_TriangleIndicesBuffer0.Get(i));
}


void CMapPlugin::PreparePointsBuffer(SAisData *ptr)
{
	nvPoint2d pt;
	
	m_Broker->Unproject(ptr->lon, -ptr->lat, &pt.x, &pt.y);							// pozycja y statku na mapie
	double Distance = nvDistance( ptr->lon, ptr->lat, ptr->lon + 1.0, ptr->lat );	// iloœæ mil na stopieñ w aktualnej pozycji y
		
	m_PointsBuffer0.Append(pt);

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
		
		to_bow = (double)ptr->to_bow/1852/yDistance; to_stern = (double)ptr->to_stern/1852/yDistance; to_port = (double)ptr->to_port/1852/yDistance; to_starboard = (double)ptr->to_starboard/1852/yDistance;
			
		double width = to_port + to_starboard;
		double height = to_bow + to_stern;

		double vx = (to_port - to_starboard)/2;
		double vy = (to_bow - to_stern)/2;

		//wymiary rzeczywiste
		p1.x = -0.5*width;	p1.y = 0.5*height;	p2.x = 0.5*width; p2.y =  0.5*height; p3.x = 0.5*width;	p3.y = -0.5*height;	p4.x = -0.5*width;	p4.y = -0.5*height;		
		//pozycja GPSa
		p1.x -= vx; p1.y -= vy;	p2.x -= vx; p2.y -= vy;	p3.x -= vx; p3.y -= vy;	p4.x -= vx; p4.y -= vy;

		if(ptr->valid_hdg)
		{
			double out_x,out_y;
			RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(ptr->cog));
			p1.x = out_x;	p1.y = out_y;
			RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(ptr->cog));
			p2.x = out_x;	p2.y = out_y;
			RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(ptr->cog));
			p3.x = out_x;	p3.y = out_y;
			RotateZ(p4.x,p4.y,out_x,out_y,nvToRad(ptr->cog));
			p4.x = out_x;	p4.y = out_y;
		}
		
		double to_x, to_y;
		m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
		pt.x = to_x;
		pt.y = to_y;
		
		// translate
		p1.x += pt.x; p1.y += pt.y;
		p2.x += pt.x; p2.y += pt.y;
		p3.x += pt.x; p3.y += pt.y;
		p4.x += pt.x; p4.y += pt.y;

		m_TriangleBuffer0.Append(p1);
		m_TriangleBuffer0.Append(p2);
		m_TriangleBuffer0.Append(p3);
		m_TriangleBuffer0.Append(p4);


		wchar_t str[128];
		float scale = (1 / m_Broker->GetMapScale()) / 4;
		wchar_t wc[128];
		mbstowcs(wc, ptr->shipname, 128);
		//m_Broker->Project(
		swprintf(str,L"mmsi:%d [%dx%d][bow:%d stern:%d port:%d %d] %ls",ptr->mmsi,ptr->to_bow+ptr->to_stern,ptr->to_port+ptr->to_starboard,ptr->to_bow,ptr->to_stern,ptr->to_port,ptr->to_starboard,wc);
				
		//m_Font->Print(p1.x,p1.y,scale,0,str);
		//glColor3f(1.0,0.0,0.0);
		
		//PointsBuffer0.Append(pt);
	}
	
	//double ShipScale = (ShipWidth / m_MilesPerDeg) * Percent;						// skalowanie rzeczywistego wymiaru statku w milach

}

void CMapPlugin::PrepareIndicesBuffer()
{
	int id = m_TriangleBuffer0.Length();

	m_TriangleIndicesBuffer0.Append(id);
	m_TriangleIndicesBuffer0.Append(id + 1);
	m_TriangleIndicesBuffer0.Append(id + 3);
	m_TriangleIndicesBuffer0.Append(id + 1);
	m_TriangleIndicesBuffer0.Append(id + 2);
	m_TriangleIndicesBuffer0.Append(id + 3);

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

void CMapPlugin::SetShip(SFunctionData *data)
{
	memcpy(m_ShipGlobalState,data->values,sizeof(data->values));
	memcpy(m_GlobalFrequency,data->frequency,sizeof(data->frequency));
	Prepare();
}

void CMapPlugin::SetFrequency(int id)
{
	int time = GetTickCount();
	
	bool valid = false;
	if(m_ShipTimes[id] != 0)
	{
		if(time - m_ShipTimes[id] == 0)
			m_ShipTicks[id] = 1;
		else
			m_ShipTicks[id] = time - m_ShipTimes[id];
		
		m_ShipValidFrequencyTable[id] = true;
		valid = true;
	}
	
	m_ShipTimes[id] = time;
	
	if(valid)
	{
		m_MaxFrequency = DEFAULT_FREQUENCY * 10; //10 sekund
		for(size_t i = 0; i < MAX_SHIP_VALUES_LEN; i++)
		{
			if(m_MaxFrequency > m_ShipTicks[i] && m_MaxFrequency != 0)
			{	
				m_MaxFrequencyID = i;
				m_MaxFrequency = m_ShipTicks[i];
			}
		}
	}

	for(size_t i = 0; i < MAX_SHIP_VALUES_LEN; i++)
	{
		if(!m_ShipValidFrequencyTable[i])
		{	
			m_PositionExists = false;
			m_Position_0_Exists = false;
			m_Position_1_Exists = false;
			return;
		}
	}

	m_ShipValidFrequency = true;
}

void CMapPlugin::Prepare()
{
		
	if(!m_PositionExists)
	{
		if(!UNDEFINED_VAL(m_ShipGlobalState[0]))
		{
			m_ShipState[0] = m_ShipGlobalState[0];
			m_ShipStaticState[0] = m_ShipGlobalState[0];
			SetFrequency(0);
			m_Position_0_Exists = true;
			m_SignalID = 0;
		}
		
		if(!UNDEFINED_VAL(m_ShipGlobalState[1]))
		{			
			m_ShipState[1] = m_ShipGlobalState[1];
			m_ShipStaticState[1] = m_ShipGlobalState[1];
			SetFrequency(1);
			m_Position_1_Exists = true;
			m_SignalID = 1;
		}
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[2]))
	{
		m_ShipState[2] = m_ShipGlobalState[2];
		m_ShipStaticState[2] = m_ShipGlobalState[2];
		SetFrequency(2);
		m_ROT_Exists = true;
		m_SignalID = 2;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[3]))
	{
		m_ShipState[3] = m_ShipGlobalState[3];
		m_ShipStaticState[3] = m_ShipGlobalState[3];
		SetFrequency(3);
		m_SOG_Exists = true;
		m_SignalID = 3;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[4]))
	{
		m_ShipState[4] = m_ShipGlobalState[4];
		m_ShipStaticState[4] = m_ShipGlobalState[4];
		SetFrequency(4);
		m_COG_Exists = true;
		m_SignalID = 4;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[5]))
	{
		m_ShipState[5] = m_ShipGlobalState[5];
		m_ShipStaticState[5] = m_ShipGlobalState[5];
		SetFrequency(5);
		m_HDT_Exists = true;
		m_SignalID = 5;
	}
	
	if(m_Position_0_Exists && m_Position_1_Exists)
		m_PositionExists = true;

}

void CMapPlugin::Interpolate()
{
	if(!m_ShipValidFrequency)
		return;
	
	m_GlobalTick = GetTickCount();
	InterpolatePosition();
	InterpolateHDT();

		
}

bool CMapPlugin::InterpolatePosition()
{
	if(m_PositionExists)
	{
		//fprintf(stdout,"LON LAT %4.6f %4.6f\n",m_ShipState[0],m_ShipState[1]);
		return false;
	}

	bool result = false;
	int time = 0;
	//int tick = GetTickCount();
	time = abs(m_ShipTimes[1] - m_GlobalTick);
	//fprintf(stdout,"Interpolowanie pozycji:[%d]%d\n",m_MaxFrequencyID,time);
	result = NewPosition(time);
	
	return result;
}

bool CMapPlugin::InterpolateHDT()
{
	if(m_HDT_Exists)
	{
		fprintf(stdout,"HDT %4.4f %4.4f\n",m_ShipStaticState[5], m_OldHDT - m_ShipStaticState[5]);
		return false;
	}
	
	bool result = false;
	//int tick = GetTickCount();
	int time = abs(m_ShipTimes[5] - m_GlobalTick);
	fprintf(stdout,"Time %d\n",time);
	result = NewHDT(time);
		
	//m_ShipTimes[5] = m_GlobalTick;
	return result;
}


void CMapPlugin::SendShipData()
{
	if(!m_ShipValidFrequency)
		return;
	
	m_PositionExists = false;
	m_Position_0_Exists = false;
	m_Position_1_Exists = false;
	m_Interpolation = false;
	m_HDT_Exists = false;

	m_ShipState[4] = UNDEFINED_DOUBLE;

	m_Broker->SetShip(m_Broker->GetParentPtr(),m_ShipState);
}

void CMapPlugin::SetTickerTick()
{
	m_Ticker->SetTick(TICKER_SLEEP);
}

bool CMapPlugin::NewPosition(int time)
{
	
	double v[4] = {m_ShipStaticState[0], m_ShipStaticState[1], m_ShipStaticState[3], m_ShipStaticState[4] };
	if(IsUndefined(v,4))
		return false;
		
	double lon = m_ShipStaticState[0];
	double lat = m_ShipStaticState[1];
	double sog = m_ShipStaticState[3];
	double cog = m_ShipStaticState[4];
	double sec = (double)time / 1000;

	//sec = 1;
	//fprintf(stdout,"%f sog:%f cog:%f\n",sec,sog,cog);

	double rad360 = 2 * nvPI / 360.0;
	double sogm = (1852.0 / 3600.0) * sog;
	double dlatm = (sogm * cos ( 2 * nvPI - cog * rad360 )) * sec;
	double dlonm = (sogm * sin ( 2 * nvPI - cog * rad360 )) * sec * -1;
	double lonDistance = nvDistance( lon, lat, lon + 1.0 , lat);
	double latDistance = nvDistance( lon, lat, lon , lat + 1.0);
		
	double nlon = lon + dlonm / (lonDistance * 1852.0);	// sta³a iloœæ km na 1 stopien
	double nlat = lat + dlatm / (latDistance * 1852.0);	// sta³a iloœæ km na 1 stopien
			
	// przypisz nowe wartosci 
	m_ShipState[0] = nlon;
	m_ShipState[1] = nlat;

	//m_ShipStaticState[0] = nlon;
	//m_ShipStaticState[1] = nlat;
	
	//fprintf(stdout,"%4.10f %4.10f\n",nlon,nlat);
	
	return true;
}

bool CMapPlugin::NewHDT(int time)
{
	double v[2] = {m_ShipStaticState[2],m_ShipStaticState[5]}; // rot
	if(IsUndefined(v,2))
		return false;

	double rot = m_ShipStaticState[2];
	double min = (double)time/1000.0/60.0;
	double a = rot * min;
	double hdt = m_ShipStaticState[5] + a;
	
	m_OldHDT = hdt;
	fprintf(stdout,"HDT wyliczone %4.4f %4.2f\n",hdt, m_ShipStaticState[5] - hdt);
	//m_ShipStaticState[5] = hdt;
	m_ShipState[5] = hdt;
	
	return true;
}


bool CMapPlugin::NewCOG()
{
	double v[1] = {m_ShipStaticState[4]}; // cog
	if(IsUndefined(v,1))
		return false;
	
	m_ShipState[4] = m_ShipStaticState[4];
	return true;
}

bool CMapPlugin::NewSOG()
{
	double v[1] = {m_ShipStaticState[3]}; // cog
	if(IsUndefined(v,1))
		return false;
		
	m_ShipState[3] = m_ShipStaticState[3];
	return true;
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

void CMapPlugin::CreateVBO()
{
	
	glGenBuffers(1, &m_ShipsArrayBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, m_ShipsArrayBuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentTriangleBufferPtr->Length(),NULL, GL_STATIC_DRAW );
		
	
		
	GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
       // fprintf(stderr, "ERROR: Could not create a VBO: %s \n", gluErrorString(ErrorCheckValue));
 
        exit(-1);
    }
 
			
}

void CMapPlugin::RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_DOUBLE, 0, RawData);
    glDrawArrays(Mode, 0, DataLength);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void CMapPlugin::RenderVBO()
{

	CreateVBO();
	GLenum  err = 0;
	//glPushMatrix();
	      
    
	//glEnable(GL_TEXTURE_2D);
	glPointSize(10);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glColor3f(1.0,0.0,0.0);
	
	//glBindTexture( GL_TEXTURE_2D, m_TextureID_0);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_ShipsArrayBuffer);	
	glVertexPointer(3, GL_FLOAT,  0, 0);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,m_CurrentTriangleIndicesBufferPtr->GetRawData());
				
	
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER,0);


	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_POINT_SPRITE);

	//glPopMatrix();

}



void CMapPlugin::Render()
{

	if(m_CurrentTriangleBufferPtr == NULL)
		return;
	if(m_CurrentPointsBufferPtr == NULL)
		return;
	
	//RenderVBO();

	/*
	glEnable(GL_BLEND);
	glColor4f(0.0,0.0,0.0,0.6);
	glPointSize(5);
	
	RenderGeometry(GL_POINTS,m_CurrentTriangleBufferPtr->GetRawData(),m_CurrentTriangleBufferPtr->Length());
	RenderGeometry(GL_QUADS,m_CurrentTriangleBufferPtr->GetRawData(),m_CurrentTriangleBufferPtr->Length());
			
	glColor3f(1.0,0.0,0.0);
	RenderGeometry(GL_POINTS,m_CurrentPointsBufferPtr->GetRawData(),m_CurrentPointsBufferPtr->Length());
	
	glPointSize(1);
	glDisable(GL_BLEND);

	m_Font->ClearBuffers();
	m_Font->CreateBuffers();
	m_Font->Render();
	*/
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
		case 0: SetShip(data);	break;
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
