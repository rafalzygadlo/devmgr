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
#include "thread.h"
#include "GeometryTools.h"
#include "images/ship.img"
#include "options.h"
#include "signals.h"
#include "NaviDrawer.h"
#include "animpos.h"
#include <math.h>
#include "NaviDrawer.h"


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
	SetBroker(NaviBroker);
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
	m_AnimMarkerSize = 5.0f;
	
	//m_MilesPerDeg = nvDistance( 0.0f, 0.0f, 1.0f, 0.0f );
	m_ShipTick = 0;
	m_ShipInterval = 0;
	m_GlobalTick = m_OldGlobalTick = 0;
	m_OldPositionTick = m_OldHDTTick = 0;
	m_Factor = DEFAULT_FACTOR;
	m_FirstTime = true;

	m_AisBufferInterval = AIS_BUFFER_INTERVAL;
	m_CurrentShipVerticesBufferPtr = NULL;
	m_CurrentPointsBufferPtr = NULL;
	m_CurrentShipLineIndicesBufferPtr = NULL;
	m_CurrentTriangleVerticesBufferPtr = NULL;
	m_CurrentCOGVerticesBufferPtr = NULL;
	m_CurrentHDGVerticesBufferPtr = NULL;
	m_CurrentTrianglesColorBufferPtr = NULL;
	m_CurrentAtonVerticesBufferPtr = NULL;
	m_CurrentSmallShipVerticesBufferPtr = NULL;
	m_CurrentSmallShipColorBufferPtr = NULL;
	m_CurrentBSVerticesBufferPtr = NULL;
	m_CurrentShipNamesBufferPtr = NULL;
	m_CurrentTrackVerticesBufferPtr = NULL;
	m_CurrentROTVerticesBufferPtr = NULL;

	m_CurrentSARVerticesBufferPtr = NULL;
	m_CurrentSARTriangleIndicesBufferPtr = NULL;
	m_CurrentSARLineIndicesBufferPtr = NULL;

	m_CurrentCPAVerticesBufferPtr = NULL;
	m_CurrentShipCPAVerticesBufferPtr = NULL;
			
	//m_CurrentHDT = UNDEFINED_DOUBLE;
	m_LastHDT = UNDEFINED_DOUBLE;
	m_SignalID = -1;
	m_MaxFrequencyID = -1;
	memset(m_ShipValidFrequencyTable,0,MAX_SHIP_VALUES_LEN);
	m_ShipValidFrequency = true;
	m_Interpolation = false;
	m_SelectedVertexId = -1;
	m_ThreadCounter = 0;
	m_MouseLmb = m_MouseDLmb = m_MouseUp = false;
	m_ShipRender = false;
	m_AnimStarted = false;
	m_AnimTick = 0;

	m_TrianglesTriangleLength = m_TrianglesLineLength = 0;
	
	m_MyFrame = NULL;
	m_MyFrame = new CMyFrame(this,(wxWindow*)m_Broker->GetParentPtr());
	m_COGTime = DEFAULT_COG_TIME;
	m_HDTTime = DEFAULT_HDT_TIME;


	m_NameFont = new nvFastFont();
	m_NameFont->Assign( (nvFastFont*)NaviBroker->GetFont( 0 ) );	// 1 = nvAriali
	//m_NameFont->SetEffect(0);
	//m_NameFont->SetEffect( nvEFFECT_SMOOTH );
	m_NameFont->SetEffect( nvEFFECT_GLOW );
    
	m_NameFont->SetGlyphColor(0.0f, 0.0f, 0.0f);
	//m_NameFont->SetGlyphCenter(0.0001f);
    m_NameFont->SetGlyphOffset( 4.0f );
	m_NameFont->SetGlowColor(0.8f, 0.8f, 0.8f );
	//m_NameFont->SetGlowCenter( 4.0f );
	//m_NameFont->s
	
	m_MMSIFont = new nvFastFont();
	m_MMSIFont->Assign( (nvFastFont*)NaviBroker->GetFont( 0 ) );	// 1 = nvAriali
	//m_MMSIFont->SetEffect( nvEFFECT_SMOOTH );
	m_MMSIFont->SetEffect( nvEFFECT_GLOW );
    
	m_MMSIFont->SetGlyphColor(0.0f, 0.0f, 0.0f);
	//m_MMSIFont->SetGlyphCenter(1.0001f);
    m_MMSIFont->SetGlyphOffset( 4.0f );
	m_MMSIFont->SetGlowColor(0.8f, 0.8f, 0.8f );
	//m_MMSIFont->SetGlowCenter( 4.0f );
	
	
	m_Ready = true;
	m_Render = false;
	m_SearchTextChanged = m_FilterChanged = true;
	CreateSymbol(animpos, animpos_size);
	

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
	AddExecuteFunction("devmgr_OnSynchro",OnSynchro);

	nvRGBA color;	
	m_Light0 = new CObject();
	m_Light0->SetSize(LIGHT0_WIDTH,LIGHT0_HEIGHT);
	color.R = 255;color.G = 0;color.B = 0;color.A = 200;
	m_Light0->SetColor(color);
	m_Light0->SetOffset(-1.0,-1.0);
	
	color.R = 0;color.G = 255;color.B = 0;color.A = 200;
	m_Light1 = new CObject();
	m_Light1->SetSize(LIGHT1_WIDTH,LIGHT1_HEIGHT);
	m_Light1->SetColor(color);
	m_Light1->SetOffset(1.0,1.0);
	
	color.R = 0;color.G = 0;color.B = 255;color.A = 200;
	m_Light2 = new CObject();
	m_Light2->SetSize(LIGHT2_WIDTH,LIGHT2_HEIGHT);
	m_Light2->SetColor(color);
	m_Light2->SetOffset(1.0,2.0);
	
	//ship CPA
	//m_ShipCPA = new CObject();
	// CPA
	m_CPA = new CObject();
	m_CPA->SetRenderMode(GL_LINES);
	color.R = 255;color.G = 0;color.B = 0;color.A = 255;
	m_CPA->SetColor(color);

	InitMutex();
	InitSearchMutex();
	ais_load_file();

	m_Ticker1 = new CTicker(this,TICK_FREQUENCY);	//frequency
	m_Ticker1->Start(100);
	m_Ticker2 = new CTicker(this,TICK_AIS_BUFFER);	//ais buffer
	m_Ticker2->Start(AIS_BUFFER_INTERVAL);

	m_TickerAnim = new CTicker(this,TICK_ANIM);
	
	

	//m_SearchThread = new CNotifier();
	//m_SearchThread->Start();
	//CreateApiMenu();
	
}

CMapPlugin::~CMapPlugin()
{
	m_Devices->Clear();
	delete m_Devices;
	delete m_DisplaySignal;
	delete m_NameFont;
	m_NameFont = NULL;
	delete m_MMSIFont;
	m_MMSIFont = NULL;
	
	delete m_MyFrame;
		
	ClearBuffers();
	FreeMutex();
	FreeSearchMutex();
	//FreeSelectedPtr();

	delete m_Light0;
	delete m_Light1;
	delete m_Light2;
	
	//delete m_ShipCPA;
	m_CPA->ClearBuffers(); // bo robi siê poza buforem renderu statkow
	delete m_CPA;
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
	running = Reader->GetIsRunning();
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
	running = Reader->GetIsRunning();
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
	CreateTexture( m_TextureTGA_0,  &m_TextureID_0 );
}

void CMapPlugin::OnInitGL()
{
	if(m_NameFont)
		m_NameFont->InitGL();
	if(m_MMSIFont)
		m_MMSIFont->InitGL();
	if(m_CPA)
		m_CPA->InitGL();
}

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
		//if((time - m_ShipTimes[id]) < DEFAULT_MAX_FREQUENCY)
			//m_ShipTicks[id] = DEFAULT_MAX_FREQUENCY;
		//else
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
			if(m_ShipTicks[i] < m_MaxFrequency && m_ShipValidFrequencyTable[i])
			{	
				m_MaxFrequencyID = i;
				if(m_ShipTicks[i] > DEFAULT_MAX_FREQUENCY)
					m_MaxFrequency = m_ShipTicks[i];
				else
					m_MaxFrequency = DEFAULT_MAX_FREQUENCY;
			}
		}
	}

	for(size_t i = 0; i < MAX_SHIP_VALUES_LEN; i++)
	{
		if(!m_ShipValidFrequencyTable[i])
		{	
			//m_PositionExists = false;
			//m_Position_0_Exists = false;
			//m_Position_1_Exists = false;
			return;
		}
	}

	m_ShipValidFrequency = true;
}

void CMapPlugin::Prepare()
{
		
	if(!m_PositionExists)
	{
		if(!UNDEFINED_VAL(m_ShipGlobalState[SHIP_LON]))
		{
			m_ShipOldStaticState[SHIP_LON] = m_ShipStaticState[SHIP_LON];
			m_ShipState[SHIP_LON] = m_ShipGlobalState[SHIP_LON];
			m_ShipStaticState[SHIP_LON] = m_ShipGlobalState[SHIP_LON];
			SetFrequency(SHIP_LON);
			m_Position_0_Exists = true;
			m_SignalID = SHIP_LON;
		}
		
		if(!UNDEFINED_VAL(m_ShipGlobalState[SHIP_LAT]))
		{	
			m_ShipOldStaticState[SHIP_LAT] = m_ShipStaticState[SHIP_LAT];
			m_ShipState[SHIP_LAT] = m_ShipGlobalState[SHIP_LAT];
			m_ShipStaticState[SHIP_LAT] = m_ShipGlobalState[SHIP_LAT];
			SetFrequency(SHIP_LAT);
			m_Position_1_Exists = true;
			m_SignalID = SHIP_LAT;
		}
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[SHIP_ROT]))
	{
		m_ShipOldStaticState[SHIP_ROT] = m_ShipStaticState[SHIP_ROT];
		m_ShipState[2] = m_ShipGlobalState[SHIP_ROT];
		m_ShipStaticState[SHIP_ROT] = m_ShipGlobalState[SHIP_ROT];
		SetFrequency(SHIP_ROT);
		m_ROT_Exists = true;
		m_SignalID = SHIP_ROT;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[SHIP_SOG]))
	{
		m_ShipOldStaticState[SHIP_SOG] = m_ShipStaticState[SHIP_SOG];
		m_ShipState[SHIP_SOG] = m_ShipGlobalState[SHIP_SOG];
		m_ShipStaticState[SHIP_SOG] = m_ShipGlobalState[SHIP_SOG];
		SetFrequency(SHIP_SOG);
		m_SOG_Exists = true;
		m_SignalID = SHIP_SOG;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[SHIP_COG]))
	{
		m_ShipOldStaticState[SHIP_COG] = m_ShipStaticState[SHIP_COG];
		m_ShipState[SHIP_COG] = m_ShipGlobalState[SHIP_COG];
		m_ShipStaticState[SHIP_COG] = m_ShipGlobalState[SHIP_COG];
		SetFrequency(SHIP_COG);
		m_COG_Exists = true;
		m_SignalID = SHIP_COG;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[SHIP_HDT]))
	{
		m_ShipOldStaticState[SHIP_HDT] = m_ShipStaticState[SHIP_HDT];
		m_ShipState[SHIP_HDT] = m_ShipGlobalState[SHIP_HDT];
		m_ShipStaticState[SHIP_HDT] = m_ShipGlobalState[SHIP_HDT];
		SetFrequency(SHIP_HDT);
		m_HDT_Exists = true;
		m_SignalID = SHIP_HDT;
	}
	
	if(m_Position_0_Exists && m_Position_1_Exists)
		m_PositionExists = true;

}

void CMapPlugin::Interpolate()
{
		
	bool result = false;
	m_GlobalTick = GetTickCount();
	//Reset(m_ShipState);
	result = InterpolatePosition();
	result = InterpolateHDT();
	m_OldGlobalTick = m_GlobalTick;
		
}

bool CMapPlugin::InterpolatePosition()
{
	if(m_PositionExists)
	{
		double distance = nvDistance(m_ShipOldStaticState[SHIP_LON],m_ShipOldStaticState[SHIP_LON],m_ShipState[SHIP_LON],m_ShipState[SHIP_LAT],nvMeter);
		//fprintf(stdout,"\nLON LAT %4.10f %4.10f %4.4f\n",m_ShipState[0],m_ShipState[1],distance);
		m_OldPositionTick = 0;
		return false;
	}

	if(!m_ShipValidFrequency)
		return false;
	
	int time = 0;
	/*
	if(m_OldPositionTick == 0)
		time = m_GlobalTick - m_ShipTimes[1];
	else
		time = m_GlobalTick - m_OldPositionTick;
	*/

	if(m_OldPositionTick == 0)
		time = m_GlobalTick - m_ShipTimes[1];
	else
		time = m_GlobalTick - m_OldPositionTick;
	
	
	
	m_OldPositionTick = m_GlobalTick;
	//time = m_MaxFrequency;
	//fprintf(stdout,"Interpolowanie pozycji:[%d][%d] %d\n",m_ShipTicks[0],m_ShipTicks[1],time);
	NewPosition(time);
	
	//m_OldGlobalPositionTick = m_GlobalTick;
	
	
	return true;
}

bool CMapPlugin::InterpolateHDT()
{
	if(m_HDT_Exists)
	{
		//fprintf(stdout,"HDT %4.4f %4.4f\n",m_ShipStaticState[5], m_OldHDT - m_ShipStaticState[5]);
		m_OldHDTTick = 0;
		return false;
	}
	
	if(!m_ShipValidFrequency)
		return false;
	
	int time = 0;

	if(m_OldHDTTick == 0)
		time = m_GlobalTick - m_ShipTimes[SHIP_HDT];
	else
		time = m_GlobalTick - m_OldGlobalTick;
	
	m_OldHDTTick = m_GlobalTick;
	//fprintf(stdout,"HDT Time %d\n",time);
	NewHDT(time);
		
	return true;
}

bool CMapPlugin::NewPosition(int time)
{
	
	double v[4] = {m_ShipStaticState[SHIP_LON], m_ShipStaticState[SHIP_LAT], m_ShipStaticState[SHIP_SOG], m_ShipStaticState[SHIP_COG] };
	if(IsUndefined(v,4))
		return false;
		
	double lon = m_ShipStaticState[SHIP_LON];
	double lat = m_ShipStaticState[SHIP_LAT];
	double sog = m_ShipStaticState[SHIP_SOG];
	double cog = m_ShipStaticState[SHIP_COG];
	double sec = (double)time/1000.0;
		
	double rad360 = 2 * nvPI / 360.0;
	double sogm = (1852.0 /3600) * sog;
	double dlatm = (sogm * cos ( 2 * nvPI - cog * rad360 )) * sec;
	double dlonm = (sogm * sin ( 2 * nvPI - cog * rad360 )) * sec * -1;
	double lonDistance = nvDistance( lon, lat, lon + 1.0 , lat);
	double latDistance = nvDistance( lon, lat, lon , lat + 1.0);
		
	double nlon = lon + dlonm / (lonDistance * 1852.0);	// sta³a iloœæ km na 1 stopien
	double nlat = lat + dlatm / (latDistance * 1852.0);	// sta³a iloœæ km na 1 stopien
			
	// przypisz nowe wartosci 
	m_ShipState[SHIP_LON] = nlon;
	m_ShipState[SHIP_LAT] = nlat;
	
	m_ShipStaticState[SHIP_LON] = nlon; 
	m_ShipStaticState[SHIP_LAT] = nlat;
	
	//fprintf(stdout,"NEW LON LAT:%4.10f %4.10f\n",nlon,nlat);
	
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
	//fprintf(stdout,"HDT wyliczone %4.4f %4.4f\n",hdt, m_ShipStaticState[5] - hdt);
	m_ShipStaticState[5] = hdt;
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
	double v[1] = {m_ShipStaticState[3]}; // sog
	if(IsUndefined(v,1))
		return false;
		
	m_ShipState[3] = m_ShipStaticState[3];
	return true;
}

void CMapPlugin::SendShipData()
{
	//if(!m_ShipValidFrequency)
		//return;
	
	m_PositionExists = false;
	m_Position_0_Exists = false;
	m_Position_1_Exists = false;
	m_Interpolation = false;
	m_HDT_Exists = false;

	//m_ShipState[4] = UNDEFINED_DOUBLE;

	m_Broker->SetShip(m_Broker->GetParentPtr(),m_ShipState);
}

void CMapPlugin::OnTickerAnimTick()
{
	m_Broker->Refresh(m_Broker->GetParentPtr());
}

void CMapPlugin::OnTicker2Start(){}
void CMapPlugin::OnTicker2Stop(){}

void CMapPlugin::OnTicker2Tick()
{
	
	if(m_Render)
		return;
		
	PrepareAisBuffer();
	PrepareBuffer();
	PrepareSearchBuffer();
	CheckCollision();
	//CheckShipCollision();
	PrepareCPABuffer();
	//PrepareShipCPABuffer();
	
	if(GetStartAnimation() && !m_AnimStarted)
	{
		m_AnimTick = 0;
		m_AnimStarted = true;
		m_TickerAnim->Start(50);
	}
	
	if(m_AnimTick > 10)
	{
		m_AnimStarted = false;
		m_AnimTick = 0;
		SetStartAnimation(false);
		m_TickerAnim->Stop();
	}
	
	if(m_AnimStarted)
		m_AnimTick++;
	
	m_Broker->Refresh(m_Broker->GetParentPtr());
}

void CMapPlugin::OnTicker1Start(){}
void CMapPlugin::OnTicker1Stop(){}
void CMapPlugin::OnTicker1Tick()
{
	
	m_ShipTick++;
	//fprintf(stdout,"%d %d\n",m_ShipTick,m_ShipInterval);
	//if( m_ShipTick >= m_ShipInterval )
	//{
		m_ShipTick = 0;
		Interpolate();
		SendShipData();
		m_ShipInterval = GetFrequency();
		
	//}
	
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

	ReindexDevices();
}

void CMapPlugin::ReindexDevices()
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
	ReadOptionsConfig();
	m_Init = true;
	m_EnableControls = true;
	SendSignal(INIT_SIGNAL,NULL);
} 

void CMapPlugin::Kill(void)
{
	m_Ticker1->Stop();
	delete m_Ticker1;

	m_Ticker2->Stop();
	delete m_Ticker2;
	m_EnableControls = false;
	
	m_TickerAnim->Stop();
	delete m_TickerAnim;
	
	m_NeedExit = true;
	WriteConfig();
	WriteOptionsConfig();
		
	SendSignal(CLEAR_AIS_LIST,NULL);

	for(size_t i = 0; i < m_Devices->size(); i++)
	{
		CReader *ptr = (CReader*)m_Devices->Item(i);
		ptr->Stop();
		delete ptr;
	}
	
	if(m_FileConfig != NULL)
        delete m_FileConfig;

	ais_save_file();
	ais_free_list();
	ais_free_buffer();
	ais_free_track();
	ais_free_collision();
	ais_free_collision_CPA();
	ais_free_collision_TCPA();
	SignalsFree();
	SendSignal(CLEAR_DISPLAY,NULL);
	// before myserial delete

}

void CMapPlugin::SetSmoothScale(double _Scale) 
{
	if( _Scale > m_Factor )
		SetSmoothScaleFactor(_Scale);
	else
		SetSmoothScaleFactor( m_Factor);
}



bool CMapPlugin::IsOnScreen(double x, double y)
{
	if(nvIsPointInCircle(x,y,m_MapCircle.Center.x,m_MapCircle.Center.y,m_MapCircle.Radius))
		return true;
	
	return false;

}
/*
void CMapPlugin::FreeSelectedPtr()
{
	if(m_SelectedPtr)
		free(m_SelectedPtr);
	
	m_SelectedPtr = NULL;
}

void CMapPlugin::CopySelectedPtr(SAisData *ptr)
{
	if(m_SelectedPtr == NULL)
		m_SelectedPtr = (SAisData*)malloc(sizeof(SAisData));
	memcpy(m_SelectedPtr,ptr,sizeof(SAisData));
}
*/

void CMapPlugin::SetSelection()
{	
	SelectTriangle();
	SelectSmallShip();
	SelectShip();
	SelectAton();
	SelectBS();
}

void CMapPlugin::SelectTriangle()
{
	if(m_CurrentTriangleVerticesBufferPtr == NULL)
		return;

	nvPoint2d *RawPt  = m_CurrentTriangleVerticesBufferPtr->GetRawData();
	
	nvPoint2f pt;
	pt.x = m_MouseLmbX;
	pt.y = m_MouseLmbY;
	int selected = -1;
	
	for (size_t i = 0; i < m_CurrentTriangleVerticesBufferPtr->Length(); i+=3)
	{
			
		nvPoint2f pt0, pt1, pt2;
				
		pt0.x = RawPt[i].x;		pt0.y = RawPt[i].y;
		pt1.x = RawPt[i + 1].x;	pt1.y = RawPt[i + 1].y;
		pt2.x = RawPt[i + 2].x;	pt2.y = RawPt[i + 2].y;
		
		if(IsPointInTriangle(&pt,&pt0,&pt1,&pt2))
		{
			
			selected = i;
			for(size_t i = 0; i < m_IdToTriangleId.Length(); i++)
			{
				if(m_IdToTriangleId.Get(i).id1 == selected)
				{
					SetSelectedPtr( ais_get_buffer()->Get(m_IdToTriangleId.Get(i).id0));
					//CopySelectedPtr(ais_get_buffer()->Get(m_IdToTriangleId.Get(i).id0));
					return;
				}
			}
			
		}
		
	}
}

void CMapPlugin::SelectSmallShip()
{
	if(m_CurrentSmallShipVerticesBufferPtr == NULL)
		return;

	nvPoint2d *RawPt  = m_CurrentSmallShipVerticesBufferPtr->GetRawData();
	nvPoint2f pt;
	pt.x = m_MouseLmbX;
	pt.y = m_MouseLmbY;
	int selected = -1;
		

	for( size_t i = 0; i < m_CurrentSmallShipVerticesBufferPtr->Length(); i+=SMALL_SHIP_VERTICES_LENGTH )
	{
		nvPoint2d v[SMALL_SHIP_VERTICES_LENGTH];

		v[0].x = RawPt[i + 0].x; v[0].y = RawPt[i + 0].y;
		v[1].x = RawPt[i + 1].x; v[1].y = RawPt[i + 1].y;
		v[2].x = RawPt[i + 2].x; v[2].y = RawPt[i + 2].y;
		v[3].x = RawPt[i + 3].x; v[3].y = RawPt[i + 3].y;
		v[4].x = RawPt[i + 4].x; v[4].y = RawPt[i + 4].y;
		v[5].x = RawPt[i + 5].x; v[5].y = RawPt[i + 5].y;
		v[6].x = RawPt[i + 6].x; v[6].y = RawPt[i + 6].y;
				
		int in[SMALL_SHIP_INDICES_LENGTH];
		in[0] = 0;	in[1] = 1;	in[2] = 6;
		in[3] = 1;	in[4] = 2;	in[5] = 6;
		in[6] =	2;	in[7] =	3;	in[8] =	6;
		in[9] = 6;	in[10] = 5;	in[11] = 3;
		in[12] = 3;	in[13] = 4;	in[14] = 5;
		
		if(IsPointInsideMesh(&pt,v,SMALL_SHIP_VERTICES_LENGTH,in,SMALL_SHIP_INDICES_LENGTH))
		{
			
			selected = i;	
			for(size_t i = 0; i < m_IdToSmallShipId.Length(); i++)
			{
				if(m_IdToSmallShipId.Get(i).id1 == selected)
				{
					//CopySelectedPtr(ais_get_buffer()->Get(m_IdToSmallShipId.Get(i).id0));
					SetSelectedPtr( ais_get_buffer()->Get(m_IdToSmallShipId.Get(i).id0));
					return;
				}
			}	
		}
	}
	
}


void CMapPlugin::SelectShip()
{
	if(m_CurrentShipVerticesBufferPtr == NULL)
		return;

	nvPoint2d *RawPt  = m_CurrentShipVerticesBufferPtr->GetRawData();
	nvPoint2f pt;
	pt.x = m_MouseLmbX;
	pt.y = m_MouseLmbY;
	int selected = -1;
		

	for( size_t i = 0; i < m_CurrentShipVerticesBufferPtr->Length(); i+=SHIP_VERTICES_LENGTH )
	{
		nvPoint2d v[SHIP_VERTICES_LENGTH];

		v[0].x = RawPt[i + 0].x; v[0].y = RawPt[i + 0].y;
		v[1].x = RawPt[i + 1].x; v[1].y = RawPt[i + 1].y;
		v[2].x = RawPt[i + 2].x; v[2].y = RawPt[i + 2].y;
		v[3].x = RawPt[i + 3].x; v[3].y = RawPt[i + 3].y;
		v[4].x = RawPt[i + 4].x; v[4].y = RawPt[i + 4].y;
		v[5].x = RawPt[i + 5].x; v[5].y = RawPt[i + 5].y;
		v[6].x = RawPt[i + 6].x; v[6].y = RawPt[i + 6].y;
				
		int in[SHIP_INDICES_LENGTH];
		in[0] = 0;	in[1] = 1;	in[2] = 6;
		in[3] = 1;	in[4] = 2;	in[5] = 6;
		in[6] =	2;	in[7] =	3;	in[8] =	6;
		in[9] = 6;	in[10] = 5;	in[11] = 3;
		in[12] = 3;	in[13] = 4;	in[14] = 5;
		
		if(IsPointInsideMesh(&pt,v,SHIP_VERTICES_LENGTH,in,SHIP_INDICES_LENGTH))
		{
			
			selected = i;	
			for(size_t i = 0; i < m_IdToShipId.Length(); i++)
			{
				if(m_IdToShipId.Get(i).id1 == selected)
				{
					//CopySelectedPtr(ais_get_buffer()->Get(m_IdToShipId.Get(i).id0));
					SetSelectedPtr( ais_get_buffer()->Get(m_IdToShipId.Get(i).id0));
					return;
				}
			}	
		}
	}
	
}

void CMapPlugin::SelectAton()
{
	if(m_CurrentAtonVerticesBufferPtr == NULL)
		return;

	nvPoint2d *RawPt  = m_CurrentAtonVerticesBufferPtr->GetRawData();
	
	nvPoint2f pt;
	pt.x = m_MouseLmbX;
	pt.y = m_MouseLmbY;
	int selected = -1;
	
	for (size_t i = 0; i < m_CurrentAtonVerticesBufferPtr->Length(); i+=ATON_VERTICES_LENGTH)
	{
			
		nvPoint2f pt0, pt1, pt2 , pt4;
				
		nvPoint2d v[ATON_VERTICES_LENGTH/2]; // tylko skrajne punkty

		v[0].x = RawPt[i + 0].x; v[0].y = RawPt[i + 0].y;
		v[1].x = RawPt[i + 1].x; v[1].y = RawPt[i + 1].y;
		v[2].x = RawPt[i + 2].x; v[2].y = RawPt[i + 2].y;
		v[3].x = RawPt[i + 3].x; v[3].y = RawPt[i + 3].y;
		
		int in[ATON_INDICES_LENGTH];
		in[0] = 0;	in[1] = 1;	in[2] = 2;
		in[3] = 0;	in[4] = 2;	in[5] = 3;
		
		if(IsPointInsideMesh(&pt,v,ATON_VERTICES_LENGTH,in,ATON_INDICES_LENGTH))
		{
			
			selected = i;
			for(size_t i = 0; i < m_IdToAtonId.Length(); i++)
			{
				if(m_IdToAtonId.Get(i).id1 == selected)
				{
					//CopySelectedPtr(ais_get_buffer()->Get(m_IdToAtonId.Get(i).id0));
					SetSelectedPtr( ais_get_buffer()->Get(m_IdToAtonId.Get(i).id0));
					return;
				}
			}
			
		}
		
	}
}

void CMapPlugin::SelectBS()
{
	if(m_CurrentBSVerticesBufferPtr == NULL)
		return;

	nvPoint2d *RawPt  = m_CurrentBSVerticesBufferPtr->GetRawData();
	
	nvPoint2f pt;
	pt.x = m_MouseLmbX;
	pt.y = m_MouseLmbY;
	int selected = -1;
	
	for (size_t i = 0; i < m_CurrentBSVerticesBufferPtr->Length(); i+=BS_VERTICES_LENGTH)
	{
			
		//nvPoint2f pt0, pt1, pt2 , pt4;
				
		nvPoint2d v[BS_VERTICES_LENGTH];

		v[0].x = RawPt[i + 0].x; v[0].y = RawPt[i + 0].y;
		v[1].x = RawPt[i + 1].x; v[1].y = RawPt[i + 1].y;
		v[2].x = RawPt[i + 2].x; v[2].y = RawPt[i + 2].y;
		v[3].x = RawPt[i + 3].x; v[3].y = RawPt[i + 3].y;
		
		int in[BS_INDICES_LENGTH];
		in[0] = 0;	in[1] = 1;	in[2] = 2;
		in[3] = 0;	in[4] = 2;	in[5] = 3;
		
		if(IsPointInsideMesh(&pt,v,BS_VERTICES_LENGTH,in,BS_INDICES_LENGTH))
		{
			
			selected = i;
			for(size_t i = 0; i < m_IdToBSId.Length(); i++)
			{
				if(m_IdToBSId.Get(i).id1 == selected)
				{
					//CopySelectedPtr(ais_get_buffer()->Get(m_IdToBSId.Get(i).id0));
					SetSelectedPtr( ais_get_buffer()->Get(m_IdToBSId.Get(i).id0));
					return;
				}
			}
			
		}
		
	}
}

void CMapPlugin::SelectSAR()
{
	if(m_CurrentSARVerticesBufferPtr == NULL)
		return;

	nvPoint2d *RawPt  = m_CurrentSARVerticesBufferPtr->GetRawData();
	
	nvPoint2f pt;
	pt.x = m_MouseLmbX;
	pt.y = m_MouseLmbY;
	int selected = -1;
	
	for (size_t i = 0; i < m_CurrentSARVerticesBufferPtr->Length(); i+=SAR_VERTICES_LENGTH)
	{
			
		//nvPoint2f pt0, pt1, pt2 , pt4;
				
		nvPoint2d v[SAR_VERTICES_LENGTH];

		v[0].x = RawPt[i + 0].x; v[0].y = RawPt[i + 0].y;
		v[1].x = RawPt[i + 1].x; v[1].y = RawPt[i + 1].y;
		v[2].x = RawPt[i + 2].x; v[2].y = RawPt[i + 2].y;
		v[3].x = RawPt[i + 3].x; v[3].y = RawPt[i + 3].y;
		
		int in[SAR_INDICES_LENGTH];
		in[0] = 0;	in[1] = 1;	in[2] = 2;
		in[3] = 0;	in[4] = 2;	in[5] = 3;
		
		if(IsPointInsideMesh(&pt,v,SAR_VERTICES_LENGTH,in,SAR_INDICES_LENGTH))
		{
			
			selected = i;
			for(size_t i = 0; i < m_IdToSARId.Length(); i++)
			{
				if(m_IdToSARId.Get(i).id1 == selected)
				{
					//CopySelectedPtr(ais_get_buffer()->Get(m_IdToBSId.Get(i).id0));
					SetSelectedPtr( ais_get_buffer()->Get(m_IdToSARId.Get(i).id0));
					return;
				}
			}
			
		}
		
	}
}


void CMapPlugin::SetPtr0()
{
	// przygotuj bufory do renderu
	m_CurrentPointsBufferPtr = &m_PointsBuffer1;
	
	//statki
	m_CurrentShipVerticesBufferPtr = &m_ShipVerticesBuffer1; 
	m_CurrentShipTriangleIndicesBufferPtr = &m_ShipTriangleIndicesBuffer1;
	m_CurrentShipLineIndicesBufferPtr = &m_ShipLineIndicesBuffer1;
	m_CurrentShipColorBufferPtr = &m_ShipColorBuffer1;
	
	//ma³e statki
	m_CurrentSmallShipVerticesBufferPtr = &m_SmallShipVerticesBuffer1; 
	m_CurrentSmallShipTriangleIndicesBufferPtr = &m_SmallShipTriangleIndicesBuffer1;
	m_CurrentSmallShipLineIndicesBufferPtr = &m_SmallShipLineIndicesBuffer1;
	m_CurrentSmallShipColorBufferPtr = &m_SmallShipColorBuffer1;
	
	//trójkaty
	m_CurrentTriangleVerticesBufferPtr = &m_TriangleVerticesBuffer1;
	m_CurrentTrianglesTriangleIndicesBufferPtr = &m_TrianglesTriangleIndicesBuffer1;
	m_CurrentTrianglesLineIndicesBufferPtr = &m_TrianglesLineIndicesBuffer1;
	m_CurrentTrianglesColorBufferPtr = &m_TrianglesColorBuffer1;
		
	//ATON
	m_CurrentAtonVerticesBufferPtr = &m_AtonVerticesBuffer1;
	m_CurrentAtonTriangleIndicesBufferPtr = &m_AtonTriangleIndicesBuffer1;
	m_CurrentAtonLineIndicesBufferPtr = &m_AtonLineIndicesBuffer1;
	m_CurrentAtonColorBufferPtr = &m_AtonColorBuffer1;
	
	//BS
	m_CurrentBSVerticesBufferPtr = &m_BSVerticesBuffer1;
	m_CurrentBSTriangleIndicesBufferPtr = &m_BSTriangleIndicesBuffer1;
	m_CurrentBSLineIndicesBufferPtr = &m_BSLineIndicesBuffer1;
	m_CurrentBSColorBufferPtr = &m_BSColorBuffer1;

	//nazwy
	m_CurrentShipNamesBufferPtr = &m_ShipNamesBuffer1;
	
	//COG
	m_CurrentCOGVerticesBufferPtr = &m_COGVerticesBuffer1;
	//HDG
	m_CurrentHDGVerticesBufferPtr = &m_HDGVerticesBuffer1;
	
	//statek swiatla
	m_Light0->SetCurrentPtr(true);
	m_Light1->SetCurrentPtr(true);
	//m_CurrentShipLightsVerticesBufferPtr = &m_ShipLightsVerticesBuffer1;
	//m_CurrentShipLightsTriangleIndicesBufferPtr = &m_ShipLightsTriangleIndicesBuffer1;
	
	//track
	m_CurrentTrackVerticesBufferPtr = &m_TrackVerticesBuffer1;

	//SAR
	m_CurrentSARVerticesBufferPtr = &m_SARVerticesBuffer1;
	m_CurrentSARTriangleIndicesBufferPtr = &m_SARTriangleIndicesBuffer1;
	m_CurrentSARLineIndicesBufferPtr = &m_SARLineIndicesBuffer1;

	//ROT
	m_CurrentROTVerticesBufferPtr = &m_ROTVerticesBuffer1;
		
}

void CMapPlugin::SetPtr1()
{
	//punkty
	m_CurrentPointsBufferPtr = &m_PointsBuffer0;
	
	//statki
	m_CurrentShipVerticesBufferPtr = &m_ShipVerticesBuffer0;
	m_CurrentShipTriangleIndicesBufferPtr = &m_ShipTriangleIndicesBuffer0;
	m_CurrentShipLineIndicesBufferPtr = &m_ShipLineIndicesBuffer0;
	m_CurrentShipColorBufferPtr = &m_ShipColorBuffer0;
	
	//ma³e statki
	m_CurrentSmallShipVerticesBufferPtr = &m_SmallShipVerticesBuffer0;
	m_CurrentSmallShipTriangleIndicesBufferPtr = &m_SmallShipTriangleIndicesBuffer0;
	m_CurrentSmallShipLineIndicesBufferPtr = &m_SmallShipLineIndicesBuffer0;
	m_CurrentSmallShipColorBufferPtr = &m_SmallShipColorBuffer0;

	//trojkaty
	m_CurrentTriangleVerticesBufferPtr = &m_TriangleVerticesBuffer0;
	m_CurrentTrianglesTriangleIndicesBufferPtr = &m_TrianglesTriangleIndicesBuffer0;
	m_CurrentTrianglesLineIndicesBufferPtr = &m_TrianglesLineIndicesBuffer0;
	m_CurrentTrianglesColorBufferPtr = &m_TrianglesColorBuffer0;

	//atony
	m_CurrentAtonVerticesBufferPtr = &m_AtonVerticesBuffer0;
	m_CurrentAtonTriangleIndicesBufferPtr = &m_AtonTriangleIndicesBuffer0;
	m_CurrentAtonLineIndicesBufferPtr = &m_AtonLineIndicesBuffer0;
	m_CurrentAtonColorBufferPtr = &m_AtonColorBuffer0;

	//BS
	m_CurrentBSVerticesBufferPtr = &m_BSVerticesBuffer0;
	m_CurrentBSTriangleIndicesBufferPtr = &m_BSTriangleIndicesBuffer0;
	m_CurrentBSLineIndicesBufferPtr = &m_BSLineIndicesBuffer0;
	m_CurrentBSColorBufferPtr = &m_BSColorBuffer0;

	m_CurrentShipNamesBufferPtr = &m_ShipNamesBuffer0;
	
	//COG
	m_CurrentCOGVerticesBufferPtr = &m_COGVerticesBuffer0;

	//HDG
	m_CurrentHDGVerticesBufferPtr = &m_HDGVerticesBuffer0;

	//statek swiatla
	m_Light0->SetCurrentPtr(false);
	m_Light1->SetCurrentPtr(false);

	//track
	m_CurrentTrackVerticesBufferPtr = &m_TrackVerticesBuffer0;

	//SAR
	m_CurrentSARVerticesBufferPtr = &m_SARVerticesBuffer0;
	m_CurrentSARTriangleIndicesBufferPtr = &m_SARTriangleIndicesBuffer0;
	m_CurrentSARLineIndicesBufferPtr = &m_SARLineIndicesBuffer0;

	//ROT
	m_CurrentROTVerticesBufferPtr = &m_ROTVerticesBuffer0; 
		
}


void CMapPlugin::ClearBuffers()
{
	//punkty	
	m_PointsBuffer0.Clear();
	
	//trojkaty
	m_TriangleVerticesBuffer0.Clear();			//
	m_TrianglesTriangleIndicesBuffer0.Clear();	//indexy trojkatow
	m_TrianglesLineIndicesBuffer0.Clear();		//indexy lini
	m_TrianglesColorBuffer0.Clear();			//kolory

	//ma³e statki
	m_SmallShipVerticesBuffer0.Clear();
	m_SmallShipTriangleIndicesBuffer0.Clear();
	m_SmallShipLineIndicesBuffer0.Clear();
	m_SmallShipColorBuffer0.Clear();

	//statki
	m_ShipVerticesBuffer0.Clear();
	m_ShipTriangleIndicesBuffer0.Clear();
	m_ShipLineIndicesBuffer0.Clear();
	m_ShipColorBuffer0.Clear();
	
	// statki swiatla
	m_Light0->ClearBuffers();
	m_Light1->ClearBuffers();
	//m_ShipLightsVerticesBuffer0.Clear();
	//m_ShipLightsTriangleIndicesBuffer0.Clear();

	//ATON
	m_AtonVerticesBuffer0.Clear();
	m_AtonLineIndicesBuffer0.Clear();
	m_AtonTriangleIndicesBuffer0.Clear();
	m_AtonColorBuffer0.Clear();
		
	//BS
	m_BSVerticesBuffer0.Clear();
	m_BSLineIndicesBuffer0.Clear();
	m_BSTriangleIndicesBuffer0.Clear();
	m_BSColorBuffer0.Clear();
		
	//nazwy
	for(size_t i = 0; i < m_ShipNamesBuffer0.Length(); i++)
	{	
		free(m_ShipNamesBuffer0.Get(i));
	}	

	m_ShipNamesBuffer0.Clear();
		
	//COG
	m_COGVerticesBuffer0.Clear();

	//HDG
	m_HDGVerticesBuffer0.Clear();

	//track
	m_TrackVerticesBuffer0.Clear();
	
	//SAR
	m_SARVerticesBuffer0.Clear();
	m_SARTriangleIndicesBuffer0.Clear();
	m_SARLineIndicesBuffer0.Clear();

	//ROT
	m_ROTVerticesBuffer0.Clear();
	
	//indeksy
	m_IdToTriangleId.Clear();
	m_IdToShipId.Clear();
	m_IdToAtonId.Clear();
	m_IdToSmallShipId.Clear();
	m_IdToBSId.Clear();
	m_IdToSARId.Clear();
}

void CMapPlugin::CopyBuffers()
{

	//Kopiowanie
	//punkty
	CopyNvPoint2d(&m_PointsBuffer0,&m_PointsBuffer1);
		
	//trójkat
	CopyNvPoint2d(&m_TriangleVerticesBuffer0,&m_TriangleVerticesBuffer1);
	CopyInt(&m_TrianglesTriangleIndicesBuffer0,&m_TrianglesTriangleIndicesBuffer1);
	CopyInt(&m_TrianglesLineIndicesBuffer0,&m_TrianglesLineIndicesBuffer1);
	CopyNvRGBA(&m_TrianglesColorBuffer0, &m_TrianglesColorBuffer1);
	
	//ma³y statek
	CopyNvPoint2d(&m_SmallShipVerticesBuffer0,&m_SmallShipVerticesBuffer1);
	CopyInt(&m_SmallShipTriangleIndicesBuffer0,&m_SmallShipTriangleIndicesBuffer1);
	CopyInt(&m_SmallShipLineIndicesBuffer0,&m_SmallShipLineIndicesBuffer1);
	CopyNvRGBA(&m_SmallShipColorBuffer0, &m_SmallShipColorBuffer1);

	//statek
	CopyNvPoint2d(&m_ShipVerticesBuffer0,&m_ShipVerticesBuffer1);
	CopyInt(&m_ShipTriangleIndicesBuffer0,&m_ShipTriangleIndicesBuffer1);
	CopyInt(&m_ShipLineIndicesBuffer0,&m_ShipLineIndicesBuffer1);
	CopyNvRGBA(&m_ShipColorBuffer0, &m_ShipColorBuffer1);

	//ATON
	CopyNvPoint2d(&m_AtonVerticesBuffer0,&m_AtonVerticesBuffer1);
	CopyInt(&m_AtonTriangleIndicesBuffer0,&m_AtonTriangleIndicesBuffer1);
	CopyInt(&m_AtonLineIndicesBuffer0,&m_AtonLineIndicesBuffer1);
	CopyNvRGBA(&m_AtonColorBuffer0, &m_AtonColorBuffer1);
			
	//BS
	CopyNvPoint2d(&m_BSVerticesBuffer0,&m_BSVerticesBuffer1);
	CopyInt(&m_BSTriangleIndicesBuffer0,&m_BSTriangleIndicesBuffer1);
	CopyInt(&m_BSLineIndicesBuffer0,&m_BSLineIndicesBuffer1);
	CopyNvRGBA(&m_BSColorBuffer0, &m_BSColorBuffer1);

	//COG
	CopyNvPoint2d(&m_COGVerticesBuffer0,&m_COGVerticesBuffer1);

	//HDG
	CopyNvPoint2d(&m_HDGVerticesBuffer0,&m_HDGVerticesBuffer1);

	//nazwy
	CopySAisNames(&m_ShipNamesBuffer0,&m_ShipNamesBuffer1);

	//track
	CopyNvPoint2d(&m_TrackVerticesBuffer0,&m_TrackVerticesBuffer1);

	//SAR
	CopyNvPoint2d(&m_SARVerticesBuffer0,&m_SARVerticesBuffer1);

	//ROT
	CopyNvPoint2d(&m_ROTVerticesBuffer0,&m_ROTVerticesBuffer1);
		
	
	//statek swiatla
	m_Light0->CopyBuffers();
	m_Light1->CopyBuffers();

}

void CMapPlugin::SetBuffers()
{
	CNaviArray <SAisData*> *buffer = ais_get_buffer();
	//CNaviArray <SAisData*> *buffer = ais_get_se
	//SetValues();

	for(size_t i = 0; i < buffer->Length(); i++)
	{
		m_CurrentId = i;
		SAisData *ptr = buffer->Get(i);
		double to_x,to_y;
		m_Broker->Unproject(ptr->lon,-ptr->lat,&to_x,&to_y);
		
		if(IsOnScreen(to_x,to_y))
		{
			SetAngle(ptr);
			PreparePointsBuffer(ptr);
			
			bool ship = false;
			if(GetShipWidth(ptr) > (GetTriangleWidth(GetSmoothScaleFactor()) * TRIANGLE_WIDTH_FACTOR))
				ship = true;
			
			if(GetShipHeight(ptr) > (GetTriangleHeight(GetSmoothScaleFactor()) * TRIANGLE_HEIGHT_FACTOR))
				ship = true;
			
			if(ship)
				PrepareShipBuffer(ptr);
			else
				PrepareTriangleBuffer(ptr);
			
			PrepareShipLightsBuffer(ptr);
			PrepareAtonBuffer(ptr);
			PrepareBSBuffer(ptr);

			PrepareCOGVerticesBuffer(ptr);				// linia cog
			PrepareHDGVerticesBuffer(ptr);
			PrepareShipNamesBuffer(ptr);
			PrepareTrackVerticesBuffer(ptr);
			PrepareSARBuffer(ptr);
			PrepareROTBuffer(ptr);
		
		}
	}

}
/*
void CMapPlugin::PrepareListBuffer()
{
	if(GetMutex()->TryLock() != wxMUTEX_NO_ERROR)
		return;

	wxString str;
	wxString name;

	ais_t *ais = NULL;
	int count = ais_get
	for(size_t i = 0 i < 
	
	ais = ais_get_search_item(item);
		
	wxString mes;
	for(size_t i = 1; i < AIS_MESSAGES_LENGTH;i++)
	{
		if(ais->valid[i])
			mes.Append(wxString::Format(_("[%d]"),i));
	}
	
	if(ais->valid[AIS_MSG_5])
	{
		wxString name5(ais->type5.shipname,wxConvUTF8);
		name = name5;
	}
	
	if(ais->valid[AIS_MSG_19])
	{
		wxString name19(ais->type5.shipname,wxConvUTF8);
		name = name19;
	}
	
	if(ais->valid[AIS_MSG_21])
	{
		wxString name21(ais->type21.name,wxConvUTF8);
		name = name21;
	}
	
	if(ais->valid[AIS_MSG_24])
	{
		wxString name24(ais->type24.shipname,wxConvUTF8);
		name = name24;
	}
	
	wxString lon(_("N/A"));
	wxString lat(_("N/A"));
	
	double _lon,_lat;
	
	switch (column)
	{
		case 0:	str = mes;										break;
		case 1:	str = wxString::Format(_("%d"),ais->mmsi);		break;
		case 2:	str = wxString::Format(_("%s"),name.wc_str());	break;

	}	
	
	GetMutex()->Unlock();

}
*/
void CMapPlugin::SetAngle(SAisData *ptr)
{
	double angle = 0;
	if(ptr->valid_cog)
		angle = ptr->cog;
	if(ptr->valid_hdg)
		angle = ptr->hdg;
	
	m_Angle = angle;
}

void CMapPlugin::CheckCollision()
{
	if(GetMutex()->TryLock() != wxMUTEX_NO_ERROR)
		return;

	ais_check_collision();
	
	GetMutex()->Unlock();
}

void CMapPlugin::CheckShipCollision()
{
	if(GetMutex()->TryLock() != wxMUTEX_NO_ERROR)
		return;

	ais_check_ship_collision(m_ShipState[SHIP_LON],m_ShipState[SHIP_LAT],m_ShipState[SHIP_COG],m_ShipState[SHIP_SOG]);
	
	GetMutex()->Unlock();
}

void CMapPlugin::PrepareAisBuffer()
{
	if(GetMutex()->TryLock() != wxMUTEX_NO_ERROR)
		return;
	ais_prepare_buffer(false);

	GetMutex()->Unlock();
}

void CMapPlugin::PrepareSearchBuffer()
{
	int counter = 0;
	if(GetMutex()->TryLock() != wxMUTEX_NO_ERROR)
		return;
		
	ais_set_search_buffer(GetSearchText());
		
	GetMutex()->Unlock();
	
	SendSignal(SIGNAL_UPDATE_LIST,0);
}

void CMapPlugin::PrepareBuffer()
{
	if(m_Render)
		return;
	
	m_Ready = false;
		
	if(GetMutex()->TryLock() != wxMUTEX_NO_ERROR)
		return;
	
	SetPtr0();
	ClearBuffers();
	SetBuffers();
	CopyBuffers();
	SetPtr1();
		
	GetMutex()->Unlock();

	m_Ready = true;
		
}


void CMapPlugin::CopyNvRGBA(CNaviArray <nvRGBA> *src, CNaviArray <nvRGBA> *dst)
{
	dst->Clear();
	dst->SetSize(src->Length());
	
	for(size_t i = 0; i < src->Length(); i++)
		dst->Set(i,src->Get(i));
}

void CMapPlugin::CopyNvPoint2d(CNaviArray <nvPoint2d> *src, CNaviArray <nvPoint2d> *dst)
{
	dst->Clear();
	dst->SetSize(src->Length());
	
	for(size_t i = 0; i < src->Length(); i++)
		dst->Set(i,src->Get(i));
}

void CMapPlugin::CopyInt(CNaviArray <int> *src, CNaviArray <int> *dst)
{
	dst->Clear();
	dst->SetSize(src->Length());
	
	for(size_t i = 0; i < src->Length(); i++)
		dst->Set(i,src->Get(i));
}

void CMapPlugin::CopySAisNames(CNaviArray <SAisNames*> *src, CNaviArray <SAisNames*> *dst)
{
	dst->Clear();
	dst->SetSize(src->Length());
	
	for(size_t i = 0; i < src->Length(); i++)
		dst->Set(i,src->Get(i));
}


void CMapPlugin::PreparePointsBuffer(SAisData *ptr)
{
	nvPoint2d pt;
	
	m_Broker->Unproject(ptr->lon, -ptr->lat, &pt.x, &pt.y);							// pozycja y statku na mapie
	double Distance = nvDistance( ptr->lon, ptr->lat, ptr->lon + 1.0, ptr->lat );	// iloœæ mil na stopieñ w aktualnej pozycji y
		
	m_PointsBuffer0.Append(pt);
	
}

void CMapPlugin::PrepareBSBuffer(SAisData *ptr)
{
	if(!ptr->valid_pos)
		return;

	if(ptr->valid[AIS_MSG_4])
	{
		PrepareBSVerticesBuffer(ptr);
		PrepareBSTriangleIndicesBuffer(ptr);
		PrepareBSLineIndicesBuffer(ptr);
		PrepareBSColorBuffer(ptr);

		SIdToId id;
		id.id0 = m_CurrentId;
		id.id1 = m_BSVerticesBuffer0.Length() - BS_VERTICES_LENGTH;
		m_IdToBSId.Append(id);
	}

}

void CMapPlugin::PrepareShipLightsBuffer(SAisData *ptr)
{
	if(!ptr->valid_pos)
		return;

	ais_t *ais = (ais_t*)ptr->ais_ptr;
	switch(ais->type1.status)
	{
		case SHIP_STATUS_RESTRICTED_MANOEUVER:		PrepareShipLightsBuffer0(ptr);	break;
		case SHIP_STATUS_CONSTRAINED_BY_DRAUGHT:	PrepareShipLightsBuffer1(ptr);	break;
		case SHIP_STATUS_FISHING:					PrepareShipLightsBuffer2(ptr);	break;
		
	}
}

void CMapPlugin::PrepareShipLightsBuffer0(SAisData *ptr)
{	
	double to_x, to_y;
	nvPoint2d pt;
				
	m_Broker->Unproject(ptr->lon, -ptr->lat,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;
			
	m_Light0->Add(pt,GetSmoothScaleFactor());

}

void CMapPlugin::PrepareShipLightsBuffer1(SAisData *ptr)
{	
	double to_x, to_y;
	nvPoint2d pt;
				
	m_Broker->Unproject(ptr->lon, -ptr->lat,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;
			
	m_Light1->Add(pt,GetSmoothScaleFactor());

}

void CMapPlugin::PrepareShipLightsBuffer2(SAisData *ptr)
{	
	double to_x, to_y;
	nvPoint2d pt;
				
	m_Broker->Unproject(ptr->lon, -ptr->lat,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;
			
	m_Light2->Add(pt,GetSmoothScaleFactor());

}

void CMapPlugin::PrepareAtonBuffer(SAisData *ptr)
{
	if(!ptr->valid_pos)
		return;

	if(ptr->valid[AIS_MSG_21])
	{
		PrepareAtonVerticesBuffer(ptr);
		PrepareAtonTriangleIndicesBuffer(ptr);
		PrepareAtonLineIndicesBuffer(ptr);
		PrepareAtonColorBuffer(ptr);

		SIdToId id;
		id.id0 = m_CurrentId;
		id.id1 = m_AtonVerticesBuffer0.Length() - ATON_VERTICES_LENGTH;
		m_IdToAtonId.Append(id);
	}

}

void CMapPlugin::PrepareShipBuffer(SAisData *ptr)
{
	if(!ptr->valid_dim || !ptr->valid_pos)
		return;
	if(GetShipWidth(ptr) == 0)
		return;
	if(GetShipHeight(ptr) == 0)
		return;

	PrepareShipVerticesBuffer(ptr);
	PrepareShipTriangleIndicesBuffer(ptr);
	PrepareShipLineIndicesBuffer(ptr);
	PrepareShipColorBuffer(ptr);

	SIdToId id;
	id.id0 = m_CurrentId;
	id.id1 = m_ShipVerticesBuffer0.Length() - SHIP_VERTICES_LENGTH;
	m_IdToShipId.Append(id);
	
}

void CMapPlugin::PrepareTriangleBuffer(SAisData *ptr)
{
	if(ptr->valid[AIS_MSG_5] || ptr->valid[AIS_MSG_24])
	{
		// jako male statki
		if(ptr->valid[AIS_MSG_1] || ptr->valid[AIS_MSG_2] || ptr->valid[AIS_MSG_3] || ptr->valid[AIS_MSG_18] || ptr->valid[AIS_MSG_19])
		{
			PrepareSmallShipVerticesBuffer(ptr);
			PrepareSmallShipTriangleIndicesBuffer(ptr);
			PrepareSmallShipLineIndicesBuffer(ptr);
			PrepareSmallShipColorBuffer(ptr);

			SIdToId id;
			id.id0 = m_CurrentId;
			id.id1 = m_SmallShipVerticesBuffer0.Length() - SMALL_SHIP_VERTICES_LENGTH;
			m_IdToSmallShipId.Append(id);
		}
	

	}else{
	
		// jako trojkaty 
		if(ptr->valid[AIS_MSG_1] || ptr->valid[AIS_MSG_2] || ptr->valid[AIS_MSG_3] || ptr->valid[AIS_MSG_18] || ptr->valid[AIS_MSG_19])
		{
			PrepareTriangleVerticesBuffer(ptr);
			PrepareTriangleTriangleIndicesBuffer(ptr);
			PrepareTriangleLineIndicesBuffer(ptr);
			PrepareTriangleColorBuffer(ptr);

			SIdToId id;
			id.id0 = m_CurrentId;
			id.id1 = m_TriangleVerticesBuffer0.Length() - TRIANGLE_VERTICES_LENGTH;
			m_IdToTriangleId.Append(id);
		}
	
	
	}
}

void CMapPlugin::PrepareSARBuffer(SAisData *ptr)
{
	if(!ptr->valid_pos)
		return;

	if(ptr->valid[AIS_MSG_9])
	{
		PrepareSARVerticesBuffer(ptr);
		PrepareSARTriangleIndicesBuffer(ptr);
		PrepareSARLineIndicesBuffer(ptr);
		//PrepareAtonColorBuffer(ptr);

		SIdToId id;
		id.id0 = m_CurrentId;
		id.id1 = m_SARVerticesBuffer0.Length() - SAR_VERTICES_LENGTH;
		m_IdToSARId.Append(id);
	}

}

//ROT
void CMapPlugin::PrepareROTBuffer(SAisData *ptr)
{
	int a = 0;
	if(!ptr->valid_pos)
		return;

	if(ptr->valid[AIS_MSG_1] || ptr->valid[AIS_MSG_2] || ptr->valid[AIS_MSG_3])
	{
		if (ptr->turn == AIS_TURN_HARD_RIGHT || ptr->turn == AIS_TURN_RIGHT)
		{
			PrepareROTVerticesBuffer(ptr,true);	
			//PrepareROTLineIndicesBuffer(ptr,true);
		}	

		if (ptr->turn == AIS_TURN_HARD_LEFT || ptr->turn == AIS_TURN_LEFT)
		{
			PrepareROTVerticesBuffer(ptr,false);
			//PrepareROTLineIndicesBuffer(ptr,false);
		}
	}

}

//rot
void CMapPlugin::PrepareROTVerticesBuffer(SAisData *ptr, bool right)
{
	nvPoint2d p1,p2;	
	double width = ROT_WIDTH/GetSmoothScaleFactor();
	double out_x,out_y;
	double to_x,to_y;
	
	m_ROTVerticesBuffer0.Append(m_HdtLastPoint);
	p1.x = m_HdtLastPoint.x;
	p1.y = m_HdtLastPoint.y;
	double ship_angle = m_Angle - 90; // opengl -90
	double angle = 0;
	
	if(right)
		angle = 90;
	else
		angle = -90;
		
	double x = (width) * cos((ship_angle + angle) * nvPI/180) + p1.x;
	double y = (width) * sin((ship_angle + angle) * nvPI/180) + p1.y;

	p1.x = x;
	p1.y = y;
				
	m_ROTVerticesBuffer0.Append(p1);
	
		
}

//CPA
void CMapPlugin::PrepareCPABuffer()
{
	if(GetMutex()->TryLock() != wxMUTEX_NO_ERROR)
		return;
	
	m_CPA->SetCurrentPtr(true);
	m_CPA->ClearBuffers();
	
	int counter = 0;
	for(size_t i = 0; i < ais_get_collision_item_count();i+=2)
	{
		SAisData *ptr1 = ais_get_collision_item(i);
		SAisData *ptr2 = ais_get_collision_item(i+1);

		nvPoint2d p1,p2;
		double to_x,to_y;
		GetBroker()->Unproject(ptr1->lon,-ptr1->lat,&to_x,&to_y);
		p1.x = to_x; p1.y = to_y;
		
		GetBroker()->Unproject(ptr2->lon,-ptr2->lat,&to_x,&to_y);
		p2.x = to_x; p2.y = to_y;

		PrepareCPAVerticesBuffer(p1,p2);
		double cpa = ais_get_CPA_item(counter);
		double tcpa = ais_get_TCPA_item(counter);
		double d1 = ais_get_D1_item(counter);
		double d2 = ais_get_D2_item(counter);
		PrepareCPAFontBuffer(ptr1,ptr2,cpa,tcpa,d1,d2);
		counter++;
	}
	
	m_CPA->CopyBuffers();
	m_CPA->SetCurrentPtr(false);

	GetMutex()->Unlock();

}

//CPA
void CMapPlugin::PrepareCPAVerticesBuffer(nvPoint2d pt1,nvPoint2d pt2)
{
	
	m_CPA->AddPoint(pt1);
	m_CPA->AddPoint(pt2);
			
	int id = m_CPA->GetVertexLength();
		
	m_CPA->AddIndice(id - 2);	//0
	m_CPA->AddIndice(id - 1);	//0
		
}

void CMapPlugin::PrepareCPAFontBuffer(SAisData *ptr1, SAisData *ptr2, double cpa, double tcpa, double d1, double d2)
{
	
	wchar_t str[128];
	double to_x,to_y;

	swprintf(str,L"CPA:%4.4f TCPA:%4.4f %4.10f %4.10f",cpa*1852,tcpa*60,d1,d2);
	double m1,m2;
	nvMidPoint(ptr1->lon, ptr1->lat,ptr2->lon, ptr2->lat, &m1, &m2);
		
	m_Broker->Unproject(m1,-m2,&to_x,&to_y);
	m_CPA->AddText(to_x,to_y,str);

}


//Ship CPA
void CMapPlugin::PrepareShipCPABuffer()
{
	if(GetMutex()->TryLock() != wxMUTEX_NO_ERROR)
		return;
	
	for(size_t i = 0; i < ais_get_collision_item_count();i++)
	{
		PrepareShipCPAVerticesBuffer(ais_get_collision_item(i));
	}

	GetMutex()->Unlock();
}


//Ship CPA
void CMapPlugin::PrepareShipCPAVerticesBuffer(SAisData *ptr)
{
	nvPoint2d p1,p2,p3;	
	double to_x,to_y;

	m_Broker->Unproject(ptr->lon,-ptr->lat,&to_x,&to_y);
	p1.x = to_x;
	p1.y = to_y;
	
	m_ShipCPAVerticesBuffer0.Append(p1);
	
}

//base station
void CMapPlugin::PrepareBSVerticesBuffer(SAisData *ptr)
{
	
	double to_x, to_y;
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	nvPoint2d p1, p2, p3, p4;
		
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;
		
	double width = BS_WIDTH/GetSmoothScaleFactor();
	double height = BS_HEIGHT/GetSmoothScaleFactor();
			
	p1.x = -1.0 * width;	p1.y =  1.0 * height;
	p2.x =  1.0 * width;	p2.y =  1.0 * height;
	p3.x =  1.0 * width;	p3.y = -1.0 * height;
	p4.x = -1.0 * width;	p4.y = -1.0 * height;
		
	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;
	p4.x += pt.x; p4.y += pt.y;
			
	m_BSVerticesBuffer0.Append(p1);
	m_BSVerticesBuffer0.Append(p2);
	m_BSVerticesBuffer0.Append(p3);
	m_BSVerticesBuffer0.Append(p4);
	
}

void CMapPlugin::PrepareBSTriangleIndicesBuffer(SAisData *ptr)
{
	int id = m_BSVerticesBuffer0.Length();

	//m_BSTriangleIndicesBuffer0.Append(id - 8);	//0
	//m_BSTriangleIndicesBuffer0.Append(id - 7);	//1
	//m_BSTriangleIndicesBuffer0.Append(id - 6);	//2
	//m_BSTriangleIndicesBuffer0.Append(id - 8);	//0
	//m_BSTriangleIndicesBuffer0.Append(id - 6);	//2
	//m_BSTriangleIndicesBuffer0.Append(id - 5);	//3
	
	m_BSTriangleIndicesBuffer0.Append(id - 4);	//0
	m_BSTriangleIndicesBuffer0.Append(id - 3);	//1
	m_BSTriangleIndicesBuffer0.Append(id - 2);	//2
	m_BSTriangleIndicesBuffer0.Append(id - 4);	//0
	m_BSTriangleIndicesBuffer0.Append(id - 2);	//2
	m_BSTriangleIndicesBuffer0.Append(id - 1);	//3

}

void CMapPlugin::PrepareBSLineIndicesBuffer(SAisData *ptr)
{
	int id = m_BSVerticesBuffer0.Length();

	m_BSLineIndicesBuffer0.Append(id - 4);	//0
	m_BSLineIndicesBuffer0.Append(id - 3);	//1
	m_BSLineIndicesBuffer0.Append(id - 3);	//1
	m_BSLineIndicesBuffer0.Append(id - 2);	//2
	m_BSLineIndicesBuffer0.Append(id - 2);	//2
	m_BSLineIndicesBuffer0.Append(id - 1);	//3
	m_BSLineIndicesBuffer0.Append(id - 1);	//3
	m_BSLineIndicesBuffer0.Append(id - 4);	//0

}


void CMapPlugin::PrepareBSColorBuffer(SAisData *ptr)
{
		
	m_BSColorBuffer0.Append(GetColor(BASE_STATION_COLOR));
	m_BSColorBuffer0.Append(GetColor(BASE_STATION_COLOR));
	m_BSColorBuffer0.Append(GetColor(BASE_STATION_COLOR));
	m_BSColorBuffer0.Append(GetColor(BASE_STATION_COLOR));
	
}

 
void CMapPlugin::PrepareAtonVerticesBuffer(SAisData *ptr)
{
	
	double to_x, to_y;
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	nvPoint2d p1, p2, p3, p4, p5, p6, p7, p8;
		
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;
		
	double width = ATON_WIDTH/GetSmoothScaleFactor();
	double height = ATON_HEIGHT/GetSmoothScaleFactor();
			
	p1.x = -1.0 * width;	p1.y =  1.0 * height;
	p2.x =  1.0 * width;	p2.y =  1.0 * height;
	p3.x =  1.0 * width;	p3.y = -1.0 * height;
	p4.x = -1.0 * width;	p4.y = -1.0 * height;
	p5.x = -0.7 * width;	p5.y =  0.7 * height;
	p6.x =  0.7 * width;	p6.y =  0.7 * height;
	p7.x =  0.7 * width;	p7.y = -0.7 * height;
	p8.x = -0.7 * width;	p8.y = -0.7 * height;

	double out_x,out_y;
	double angle = ATON_ANGLE; 

#ifdef ROTATE
	RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(angle));	p1.x = out_x;	p1.y = out_y;
	RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(angle));	p2.x = out_x;	p2.y = out_y;
	RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(angle));	p3.x = out_x;	p3.y = out_y;
	RotateZ(p4.x,p4.y,out_x,out_y,nvToRad(angle));	p4.x = out_x;	p4.y = out_y;
	RotateZ(p5.x,p5.y,out_x,out_y,nvToRad(angle));	p5.x = out_x;	p5.y = out_y;
	RotateZ(p6.x,p6.y,out_x,out_y,nvToRad(angle));	p6.x = out_x;	p6.y = out_y;
	RotateZ(p7.x,p7.y,out_x,out_y,nvToRad(angle));	p7.x = out_x;	p7.y = out_y;
	RotateZ(p8.x,p8.y,out_x,out_y,nvToRad(angle));	p8.x = out_x;	p8.y = out_y;
#endif	


	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;
	p4.x += pt.x; p4.y += pt.y;
	p5.x += pt.x; p5.y += pt.y;
	p6.x += pt.x; p6.y += pt.y;
	p7.x += pt.x; p7.y += pt.y;
	p8.x += pt.x; p8.y += pt.y;
		
	m_AtonVerticesBuffer0.Append(p1);
	m_AtonVerticesBuffer0.Append(p2);
	m_AtonVerticesBuffer0.Append(p3);
	m_AtonVerticesBuffer0.Append(p4);
	m_AtonVerticesBuffer0.Append(p5);
	m_AtonVerticesBuffer0.Append(p6);
	m_AtonVerticesBuffer0.Append(p7);
	m_AtonVerticesBuffer0.Append(p8);


}

void CMapPlugin::PrepareAtonTriangleIndicesBuffer(SAisData *ptr)
{
	int id = m_AtonVerticesBuffer0.Length();

	//1
	m_AtonTriangleIndicesBuffer0.Append(id - 8);	//0
	m_AtonTriangleIndicesBuffer0.Append(id - 7);	//1
	m_AtonTriangleIndicesBuffer0.Append(id - 6);	//2

	m_AtonTriangleIndicesBuffer0.Append(id - 8);	//0
	m_AtonTriangleIndicesBuffer0.Append(id - 6);	//2
	m_AtonTriangleIndicesBuffer0.Append(id - 5);	//3


	m_AtonTriangleIndicesBuffer0.Append(id - 4);	//4
	m_AtonTriangleIndicesBuffer0.Append(id - 3);	//5
	m_AtonTriangleIndicesBuffer0.Append(id - 2);	//6

	m_AtonTriangleIndicesBuffer0.Append(id - 4);	//4
	m_AtonTriangleIndicesBuffer0.Append(id - 2);	//6
	m_AtonTriangleIndicesBuffer0.Append(id - 1);	//7

}

void CMapPlugin::PrepareAtonLineIndicesBuffer(SAisData *ptr)
{
	int id = m_AtonVerticesBuffer0.Length();

	//
	m_AtonLineIndicesBuffer0.Append(id - 4);	//4
	m_AtonLineIndicesBuffer0.Append(id - 2);	//6
	m_AtonLineIndicesBuffer0.Append(id - 3);	//5
	m_AtonLineIndicesBuffer0.Append(id - 1);	//7

	//obrys
	m_AtonLineIndicesBuffer0.Append(id - 8);	//0
	m_AtonLineIndicesBuffer0.Append(id - 7);	//1
	m_AtonLineIndicesBuffer0.Append(id - 7);	//1
	m_AtonLineIndicesBuffer0.Append(id - 6);	//2
	m_AtonLineIndicesBuffer0.Append(id - 6);	//2
	m_AtonLineIndicesBuffer0.Append(id - 5);	//3
	m_AtonLineIndicesBuffer0.Append(id - 5);	//3
	m_AtonLineIndicesBuffer0.Append(id - 8);	//0

}


void CMapPlugin::PrepareAtonColorBuffer(SAisData *ptr)
{
		
	m_AtonColorBuffer0.Append(GetColor(ATON_COLOR));
	m_AtonColorBuffer0.Append(GetColor(ATON_COLOR));
	m_AtonColorBuffer0.Append(GetColor(ATON_COLOR));
	m_AtonColorBuffer0.Append(GetColor(ATON_COLOR));
	m_AtonColorBuffer0.Append(GetColor(ATON_COLOR));
	m_AtonColorBuffer0.Append(GetColor(ATON_COLOR));
	m_AtonColorBuffer0.Append(GetColor(ATON_COLOR));
	m_AtonColorBuffer0.Append(GetColor(ATON_COLOR));

}

void CMapPlugin::PrepareTriangleVerticesBuffer(SAisData *ptr)
{
	
	double to_x, to_y;
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	nvPoint2d p1, p2, p3;
		
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;
		
	double width =  SHIP_TRIANGLE_WIDTH/GetSmoothScaleFactor();
	double height = SHIP_TRIANGLE_HEIGHT/GetSmoothScaleFactor();
			
	p1.x = -0.5 * width;	p1.y =  0.8 * height;
	p2.x =  0.0 * width;	p2.y = -0.8 * height;
	p3.x =  0.5 * width;	p3.y =  0.8 * height;
	
	m_ShipPoint	= p2;			
	
	double out_x,out_y;

#ifdef ROTATE
	RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(m_Angle));	p1.x = out_x;	p1.y = out_y;
	RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(m_Angle));	p2.x = out_x;	p2.y = out_y;
	RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(m_Angle));	p3.x = out_x;	p3.y = out_y;
#endif	
	
	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;

	m_HdtPoint = p2;
	
	m_TriangleVerticesBuffer0.Append(p1);
	m_TriangleVerticesBuffer0.Append(p2);
	m_TriangleVerticesBuffer0.Append(p3);

}
// indexy verteksów dla ma³ych trójkacików
void CMapPlugin::PrepareTriangleTriangleIndicesBuffer(SAisData *ptr)
{
	
	int id = m_TriangleVerticesBuffer0.Length();

	//1
	m_TrianglesTriangleIndicesBuffer0.Append(id - 3);	//0
	m_TrianglesTriangleIndicesBuffer0.Append(id - 2);	//1
	m_TrianglesTriangleIndicesBuffer0.Append(id - 1);	//2

	
}

void CMapPlugin::PrepareTriangleLineIndicesBuffer(SAisData *ptr)
{	
	int id = m_TriangleVerticesBuffer0.Length();

	//1
	m_TrianglesLineIndicesBuffer0.Append(id - 3);	//0
	m_TrianglesLineIndicesBuffer0.Append(id - 2);	//1
	
	m_TrianglesLineIndicesBuffer0.Append(id - 2);	//1
	m_TrianglesLineIndicesBuffer0.Append(id - 1);	//2

	m_TrianglesLineIndicesBuffer0.Append(id - 1);	//2
	m_TrianglesLineIndicesBuffer0.Append(id - 3);	//0
	
}
void CMapPlugin::PrepareTriangleColorBuffer(SAisData *ptr)
{

	ais_t *ais = (ais_t*)ptr->ais_ptr;
	int timeout = GetTickCount() - ais->timeout;

	if(ptr->_class == AIS_CLASS_A)
	{

		if(timeout >= AIS_TIMEOUT)
		{
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			return;
		}
	
		if(ptr->sog > MIN_SHIP_SPEED)
		{
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
	
		}else{
	
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
		}
	}

	if(ptr->_class == AIS_CLASS_B)
	{

		if(timeout >= AIS_TIMEOUT)
		{
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			return;
		}
	
		if(ptr->sog > MIN_SHIP_SPEED)
		{
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
	
		}else{
	
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_TrianglesColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
		}
	}


}


void CMapPlugin::PrepareSmallShipVerticesBuffer(SAisData *ptr)
{
	
	double to_x, to_y;
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	nvPoint2d p1, p2, p3, p4, p5, p6, p7;
		
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;
		
	double width =  SMALL_SHIP_WIDTH/GetSmoothScaleFactor();
	double height = SMALL_SHIP_HEIGHT/GetSmoothScaleFactor();
		
	p1.x = -0.5 * width;	p1.y =  0.5    * height;	
	p2.x =  0.5 * width;	p2.y =  0.5    * height; 
	p3.x =  0.5 * width;	p3.y = -0.3    * height;	
	p4.x =  0.3 * width;	p4.y = -0.425  * height;
	p5.x =  0.0;			p5.y = -0.5    * height;
	p6.x = -0.3 * width;	p6.y = -0.425  * height;
	p7.x = -0.5 * width;	p7.y = -0.3    * height;
	
	m_ShipPoint = p5;		
		
	double out_x,out_y;

#ifdef ROTATE
	RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(m_Angle));	p1.x = out_x;	p1.y = out_y;
	RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(m_Angle));	p2.x = out_x;	p2.y = out_y;
	RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(m_Angle));	p3.x = out_x;	p3.y = out_y;
	RotateZ(p4.x,p4.y,out_x,out_y,nvToRad(m_Angle));	p4.x = out_x;	p4.y = out_y;
	RotateZ(p5.x,p5.y,out_x,out_y,nvToRad(m_Angle));	p5.x = out_x;	p5.y = out_y;
	RotateZ(p6.x,p6.y,out_x,out_y,nvToRad(m_Angle));	p6.x = out_x;	p6.y = out_y;
	RotateZ(p7.x,p7.y,out_x,out_y,nvToRad(m_Angle));	p7.x = out_x;	p7.y = out_y;
#endif	
	
	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;
	p4.x += pt.x; p4.y += pt.y;
	p5.x += pt.x; p5.y += pt.y;
	p6.x += pt.x; p6.y += pt.y;
	p7.x += pt.x; p7.y += pt.y;

	m_HdtPoint = p5;

	m_SmallShipVerticesBuffer0.Append(p1);
	m_SmallShipVerticesBuffer0.Append(p2);
	m_SmallShipVerticesBuffer0.Append(p3);
	m_SmallShipVerticesBuffer0.Append(p4);
	m_SmallShipVerticesBuffer0.Append(p5);
	m_SmallShipVerticesBuffer0.Append(p6);
	m_SmallShipVerticesBuffer0.Append(p7);

}
// indexy verteksów dla ma³ych statkow
void CMapPlugin::PrepareSmallShipTriangleIndicesBuffer(SAisData *ptr)
{
	int id = m_SmallShipVerticesBuffer0.Length();
	
	m_SmallShipTriangleIndicesBuffer0.Append(id - 7);	//0
	m_SmallShipTriangleIndicesBuffer0.Append(id - 6);	//1
	m_SmallShipTriangleIndicesBuffer0.Append(id - 1);	//6
	m_SmallShipTriangleIndicesBuffer0.Append(id - 6);	//1
	m_SmallShipTriangleIndicesBuffer0.Append(id - 5);	//2
	m_SmallShipTriangleIndicesBuffer0.Append(id - 1);	//6
	m_SmallShipTriangleIndicesBuffer0.Append(id - 5);	//2
	m_SmallShipTriangleIndicesBuffer0.Append(id - 4);	//3
	m_SmallShipTriangleIndicesBuffer0.Append(id - 1);	//6
	m_SmallShipTriangleIndicesBuffer0.Append(id - 1);	//6
	m_SmallShipTriangleIndicesBuffer0.Append(id - 2);	//5
	m_SmallShipTriangleIndicesBuffer0.Append(id - 4);	//3
	m_SmallShipTriangleIndicesBuffer0.Append(id - 4);	//3
	m_SmallShipTriangleIndicesBuffer0.Append(id - 3);	//4
	m_SmallShipTriangleIndicesBuffer0.Append(id - 2);	//5
	
}

void CMapPlugin::PrepareSmallShipLineIndicesBuffer(SAisData *ptr)
{	
	int id = m_SmallShipVerticesBuffer0.Length();
		
	m_SmallShipLineIndicesBuffer0.Append(id - 7); //0
	m_SmallShipLineIndicesBuffer0.Append(id - 6); //1
	m_SmallShipLineIndicesBuffer0.Append(id - 6); //1
	m_SmallShipLineIndicesBuffer0.Append(id - 5); //2
	m_SmallShipLineIndicesBuffer0.Append(id - 5); //2
	m_SmallShipLineIndicesBuffer0.Append(id - 4); //3
	m_SmallShipLineIndicesBuffer0.Append(id - 4); //3
	m_SmallShipLineIndicesBuffer0.Append(id - 3); //4
	m_SmallShipLineIndicesBuffer0.Append(id - 3); //4
	m_SmallShipLineIndicesBuffer0.Append(id - 2); //5
	m_SmallShipLineIndicesBuffer0.Append(id - 2); //5
	m_SmallShipLineIndicesBuffer0.Append(id - 1); //6
	m_SmallShipLineIndicesBuffer0.Append(id - 1); //6
	m_SmallShipLineIndicesBuffer0.Append(id - 7); //0
	
}

void CMapPlugin::PrepareSmallShipColorBuffer(SAisData *ptr)
{
		
	ais_t *ais = (ais_t*)ptr->ais_ptr;
	int timeout = GetTickCount() - ais->timeout;
	
	if(ptr->_class == AIS_CLASS_A)
	{

		if(timeout >= AIS_TIMEOUT)
		{
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			return;
		}
	
		if(ptr->sog > MIN_SHIP_SPEED)
		{
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
	
		}else{
	
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
		}
	}

	if(ptr->_class == AIS_CLASS_B)
	{

		if(timeout >= AIS_TIMEOUT)
		{
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			return;
		}
	
		if(ptr->sog > MIN_SHIP_SPEED)
		{
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
	
		}else{
	
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_SmallShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
		}
	}

}

void CMapPlugin::PrepareShipVerticesBuffer(SAisData *ptr)
{
	
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	nvPoint2d p1, p2, p3, p4, p5, p6, p7;
	double width = GetShipWidth(ptr);
	double height = GetShipHeight(ptr);
		
	//wymiary rzeczywiste
	p1.x = -0.5 * width;	p1.y =  0.5    * height;	
	p2.x =  0.5 * width;	p2.y =  0.5    * height; 
	p3.x =  0.5 * width;	p3.y = -0.3    * height;	
	p4.x =  0.3 * width;	p4.y = -0.425  * height;
	p5.x =  0.0;			p5.y = -0.5    * height;
	p6.x = -0.3 * width;	p6.y = -0.425  * height;
	p7.x = -0.5 * width;	p7.y = -0.3    * height;
	
	
	//pozycja GPSa
	double vx = (ToPort(ptr) - ToStarboard(ptr))/2;
	double vy = (ToBow(ptr) - ToStern(ptr))/2;
		
	m_ShipPoint = p5;
	
	p1.x -= vx; p1.y -= vy;
	p2.x -= vx; p2.y -= vy;
	p3.x -= vx; p3.y -= vy;
	p4.x -= vx; p4.y -= vy;
	p5.x -= vx; p5.y -= vy;
	p6.x -= vx; p6.y -= vy;
	p7.x -= vx; p7.y -= vy;
	

	
#ifdef ROTATE
	double out_x,out_y;
	RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(m_Angle));	p1.x = out_x;	p1.y = out_y;
	RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(m_Angle));	p2.x = out_x;	p2.y = out_y;
	RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(m_Angle));	p3.x = out_x;	p3.y = out_y;
	RotateZ(p4.x,p4.y,out_x,out_y,nvToRad(m_Angle));	p4.x = out_x;	p4.y = out_y;
	RotateZ(p5.x,p5.y,out_x,out_y,nvToRad(m_Angle));	p5.x = out_x;	p5.y = out_y;
	RotateZ(p6.x,p6.y,out_x,out_y,nvToRad(m_Angle));	p6.x = out_x;	p6.y = out_y;
	RotateZ(p7.x,p7.y,out_x,out_y,nvToRad(m_Angle));	p7.x = out_x;	p7.y = out_y;
#endif

	double to_x, to_y;
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;

	// translate
	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;
	p4.x += pt.x; p4.y += pt.y;
	p5.x += pt.x; p5.y += pt.y;
	p6.x += pt.x; p6.y += pt.y;
	p7.x += pt.x; p7.y += pt.y;
	
	m_HdtPoint = p5;

	m_ShipVerticesBuffer0.Append(p1);
	m_ShipVerticesBuffer0.Append(p2);
	m_ShipVerticesBuffer0.Append(p3);
	m_ShipVerticesBuffer0.Append(p4);
	m_ShipVerticesBuffer0.Append(p5);
	m_ShipVerticesBuffer0.Append(p6);
	m_ShipVerticesBuffer0.Append(p7);

}

void CMapPlugin::PrepareShipTriangleIndicesBuffer(SAisData *ptr)
{
	
	int id = m_ShipVerticesBuffer0.Length();
	//1
	m_ShipTriangleIndicesBuffer0.Append(id - 7);	//0
	m_ShipTriangleIndicesBuffer0.Append(id - 6);	//1
	m_ShipTriangleIndicesBuffer0.Append(id - 1);	//6
		
	//2
	m_ShipTriangleIndicesBuffer0.Append(id - 6);	//1
	m_ShipTriangleIndicesBuffer0.Append(id - 5);	//2
	m_ShipTriangleIndicesBuffer0.Append(id - 1);	//6
		
	//3
	m_ShipTriangleIndicesBuffer0.Append(id - 5);	//2
	m_ShipTriangleIndicesBuffer0.Append(id - 4);	//3
	m_ShipTriangleIndicesBuffer0.Append(id - 1);	//6
		
	//4
	m_ShipTriangleIndicesBuffer0.Append(id - 1);	//6
	m_ShipTriangleIndicesBuffer0.Append(id - 2);	//5
	m_ShipTriangleIndicesBuffer0.Append(id - 4);	//3
		
	//5
	m_ShipTriangleIndicesBuffer0.Append(id - 4);	//3
	m_ShipTriangleIndicesBuffer0.Append(id - 3);	//4
	m_ShipTriangleIndicesBuffer0.Append(id - 2);	//5

}

void CMapPlugin::PrepareShipLineIndicesBuffer(SAisData *ptr)
{
	int id = m_ShipVerticesBuffer0.Length();
		
	m_ShipLineIndicesBuffer0.Append(id - 7); //0
	m_ShipLineIndicesBuffer0.Append(id - 6); //1

	m_ShipLineIndicesBuffer0.Append(id - 6); //1
	m_ShipLineIndicesBuffer0.Append(id - 5); //2

	m_ShipLineIndicesBuffer0.Append(id - 5); //2
	m_ShipLineIndicesBuffer0.Append(id - 4); //3

	m_ShipLineIndicesBuffer0.Append(id - 4); //3
	m_ShipLineIndicesBuffer0.Append(id - 3); //4

	m_ShipLineIndicesBuffer0.Append(id - 3); //4
	m_ShipLineIndicesBuffer0.Append(id - 2); //5

	m_ShipLineIndicesBuffer0.Append(id - 2); //5
	m_ShipLineIndicesBuffer0.Append(id - 1); //6
		
	m_ShipLineIndicesBuffer0.Append(id - 1); //6
	m_ShipLineIndicesBuffer0.Append(id - 7); //0
	
}

void CMapPlugin::PrepareShipColorBuffer(SAisData *ptr)
{
	
	ais_t *ais = (ais_t*)ptr->ais_ptr;
	int timeout = GetTickCount() - ais->timeout;
	
	if(ptr->_class == AIS_CLASS_A)
	{	
		if(timeout >= AIS_TIMEOUT)
		{
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2A));
			return;
		}
	
		if(ptr->sog > MIN_SHIP_SPEED)
		{
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0A));
	
		}else{
	
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1A));
		}
	}
	
	if(ptr->_class == AIS_CLASS_B)
	{

		if(timeout >= AIS_TIMEOUT)
		{
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_2B));
			return;
		}
	
		if(ptr->sog > MIN_SHIP_SPEED)
		{
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_0B));
	
		}else{
	
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
			m_ShipColorBuffer0.Append(GetColor(SHIP_COLOR_1B));
		}
	}

}


void CMapPlugin::PrepareShipNamesBuffer(SAisData *ptr) 
{
	wchar_t str[64];
	wchar_t wc[64];
	
	if(ptr->valid_name)
	{
		SAisNames *a = (SAisNames*)malloc(sizeof(SAisNames));
		
		mbstowcs(wc, ptr->name, 64);
		if(ptr->_class == AIS_CLASS_B)
			swprintf(str,L"%ls (B)",wc);
		else
			swprintf(str,L"%ls",wc);

		a->lat = ptr->lat;
		a->lon = ptr->lon;
		memcpy(a->name,str,64);
				
		m_ShipNamesBuffer0.Append(a);
	}
}

void CMapPlugin::PrepareCOGVerticesBuffer(SAisData *ptr)
{
	if(!ptr->valid_cog || !ptr->valid_sog)
		return;
		
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	
	nvPoint2d p1, p2;
		
	//obrót
	double cog = ptr->cog;
	double sog = ptr->sog;
	
	double to_x, to_y;
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	p1.x = to_x;p1.y = to_y;
	
	double new_lon, new_lat;
	NewLonLat(GetCOGTime(),pt.x,pt.y,sog,cog,&new_lon,&new_lat);
	p2.x = new_lon; p2.y = new_lat;
	m_Broker->Unproject(p2.x, p2.y,&to_x,&to_y);
	p2.x = to_x; p2.y = to_y;
		
	m_COGVerticesBuffer0.Append(p1);
	m_COGVerticesBuffer0.Append(p2);
	
}

void CMapPlugin::PrepareHDGVerticesBuffer(SAisData *ptr)
{
	if(!ptr->valid_hdg || !ptr->valid_sog)
		return;
		
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	
	nvPoint2d p1, p2, pn;
		
	//obrót
	double hdg = ptr->hdg;
	double sog = ptr->sog;
	
	double to_x, to_y;
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	p1.x = to_x;p1.y = to_y;
	
	p1 = m_HdtPoint;
	m_Broker->Project(p1.x, p1.y,&to_x,&to_y);
	
	pn.x = to_x;
	pn.y = to_y;
	
	double new_lon, new_lat;
	NewLonLat(GetHDTTime(),pn.x,pn.y,sog,hdg,&new_lon,&new_lat);
	p2.x = new_lon; p2.y = new_lat;
	
	
	
	m_Broker->Unproject(p2.x, p2.y,&to_x,&to_y);
	p2.x = to_x; p2.y = to_y;
	m_HdtLastPoint = p2;
	
	//nvPoint2d npt;

	//npt.x = p1.x - p2.x;
	//npt.y = p1.y - p2.y;
	
	
	//p2.x = p2.x + npt.x;
	//p2.y = p2.y + npt.x;

	m_HDGVerticesBuffer0.Append(p1);
	m_HDGVerticesBuffer0.Append(p2);
	
	
}

void CMapPlugin::PrepareTrackVerticesBuffer(SAisData *ptr)
{
		
	CNaviArray <SAisData> *ar =  ais_track_exists(ptr->mmsi);

	for(size_t i = 0; i < ar->Length(); i++)
	{
		SAisData data = ar->Get(i);
		nvPoint2d pt;
		double to_x,to_y;
		m_Broker->Unproject(data.lon,data.lat,&to_x,&to_y);
		to_y = -to_y;

		pt.x = to_x;
		pt.y = to_y;
		m_TrackVerticesBuffer0.Append(pt);
	}
}

void CMapPlugin::PrepareSARVerticesBuffer(SAisData *ptr)
{
	double to_x, to_y;
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	nvPoint2d p1, p2, p3, p4;
		
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	pt.x = to_x;
	pt.y = to_y;
		
	double width =  SAR_WIDTH/GetSmoothScaleFactor();
	double height = SAR_HEIGHT/GetSmoothScaleFactor();
			
	p1.x = -1.0 * width;	p1.y =  1.0 * height;
	p2.x =  1.0 * width;	p2.y =	1.0 * height;
	p3.x =  1.0 * width;	p3.y = -1.0 * height;
	p4.x = -1.0 * width;	p4.y = -1.0 * height;
		
	//obrót
	double out_x,out_y;

#ifdef ROTATE
	RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(m_Angle));	p1.x = out_x;	p1.y = out_y;
	RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(m_Angle));	p2.x = out_x;	p2.y = out_y;
	RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(m_Angle));	p3.x = out_x;	p3.y = out_y;
	RotateZ(p4.x,p4.y,out_x,out_y,nvToRad(m_Angle));	p4.x = out_x;	p4.y = out_y;
#endif	
	
	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;
	p4.x += pt.x; p4.y += pt.y;
	
	m_HdtPoint = p2;
	
	m_SARVerticesBuffer0.Append(p1);
	m_SARVerticesBuffer0.Append(p2);
	m_SARVerticesBuffer0.Append(p3);
	m_SARVerticesBuffer0.Append(p4);
	

}

void CMapPlugin::PrepareSARTriangleIndicesBuffer(SAisData *ptr)
{
	
	int id = m_SARVerticesBuffer0.Length();
	
	m_SARTriangleIndicesBuffer0.Append(id - 4);	//0
	m_SARTriangleIndicesBuffer0.Append(id - 3);	//1
	m_SARTriangleIndicesBuffer0.Append(id - 2);	//2

	m_SARTriangleIndicesBuffer0.Append(id - 4);	//0
	m_SARTriangleIndicesBuffer0.Append(id - 2);	//2
	m_SARTriangleIndicesBuffer0.Append(id - 1);	//3

}


void CMapPlugin::PrepareSARLineIndicesBuffer(SAisData *ptr)
{
	int id = m_SARVerticesBuffer0.Length();

	m_SARLineIndicesBuffer0.Append(id - 4);	//0
	m_SARLineIndicesBuffer0.Append(id - 3);	//1
	m_SARLineIndicesBuffer0.Append(id - 3);	//1
	m_SARLineIndicesBuffer0.Append(id - 2);	//2
	m_SARLineIndicesBuffer0.Append(id - 2);	//2
	m_SARLineIndicesBuffer0.Append(id - 1);	//3
	m_SARLineIndicesBuffer0.Append(id - 1);	//3
	m_SARLineIndicesBuffer0.Append(id - 4);	//0
	
}

void CMapPlugin::DeleteShipsVBO()
{
	//glDeleteBuffers(1, &m_ShipsArrayBuffer);
	//glDeleteBuffers(1, &m_ShipsTriangleIndicesBuffer);
	//glDeleteBuffers(1, &m_ShipsLineIndicesBuffer);
	
}

void CMapPlugin::DeleteTrianglesVBO()
{
	//glDeleteBuffers(1, &m_TrianglesArrayBuffer);
	//glDeleteBuffers(1, &m_TrianglesTriangleIndicesBuffer);
	//glDeleteBuffers(1, &m_TrianglesLineIndicesBuffer);
}


void CMapPlugin::RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_DOUBLE, 0, RawData);
    glDrawArrays(Mode, 0, DataLength);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void CMapPlugin::RenderShipNames()
{
	if(!GetShowNames())
	{
		m_NameFont->Clear();
		return;
	}

	if(m_CurrentShipNamesBufferPtr == NULL)
		return;

	size_t size = m_CurrentShipNamesBufferPtr->Length();
	if(size == 0)
	{
		m_NameFont->Clear();
		return;
	}

	if(!m_Ready)
		return;
	
	size_t CaptionsSize = size;
    vect2 *Positions = (vect2*)malloc( CaptionsSize *sizeof( vect2 ) );
    float *Scale = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *Angle = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *vx = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *vy = (float*)malloc( CaptionsSize * sizeof( float ) );
    wchar_t **CaptionsStr = (wchar_t**)malloc(  CaptionsSize * sizeof( wchar_t** ) );
	double to_x,to_y;
    
	for(size_t i = 0 ; i < m_CurrentShipNamesBufferPtr->Length(); i++ ) 
	{
		
		SAisNames *a = m_CurrentShipNamesBufferPtr->Get(i);
		m_Broker->Unproject(a->lon,-a->lat,&to_x,&to_y);
		Positions[i][0] = to_x;
        Positions[i][1] = to_y + (10.0/GetSmoothScaleFactor());
		Scale[i] = GetFontSize()/GetSmoothScaleFactor()/DEFAULT_FONT_FACTOR;
        vx[i] = 0.5f;
        vy[i] = -3.0f;
		CaptionsStr[i] = a->name;   // bez kopiowania ³añcucha!!! 
		Angle[i] = m_Broker->GetAngle();
    }

	m_NameFont->Clear();
    m_NameFont->PrintList( Positions, Scale, Angle, CaptionsStr, CaptionsSize, vx, vy );
	
	free( CaptionsStr );    // ³añcuchy nie zosta³y skopiowane, nie ma koniecznoœci zwalniania ca³ej listy
    free( Positions );
    free( Scale );
    free( Angle );
    free( vx );
    free( vy );
}

bool CMapPlugin::IsBSBuffer()
{
	if(m_CurrentBSVerticesBufferPtr == NULL)
		return false;

	if(m_CurrentBSVerticesBufferPtr->Length() == 0)
		return false;
	
	return true;
}

bool CMapPlugin::IsAtonBuffer()
{
	if(m_CurrentAtonVerticesBufferPtr == NULL)
		return false;

	if(m_CurrentAtonVerticesBufferPtr->Length() == 0)
		return false;
	
	return true;
}

bool CMapPlugin::IsShipBuffer()
{
	if(m_CurrentShipVerticesBufferPtr == NULL)
		return false;
	
	if(m_CurrentShipVerticesBufferPtr->Length() == 0)
		return false;
		
	return true;
}

bool CMapPlugin::IsSARBuffer()
{
	if(m_CurrentSARVerticesBufferPtr == NULL)
		return false;
	
	if(m_CurrentSARVerticesBufferPtr->Length() == 0)
		return false;
		
	return true;
}

bool CMapPlugin::IsTriangleBuffer()
{
	if(m_CurrentTriangleVerticesBufferPtr == NULL)
		return false;

	if(m_CurrentTriangleVerticesBufferPtr->Length() == 0)
		return false;
	
	return true;
}

bool CMapPlugin::IsSmallShipBuffer()
{
	if(m_CurrentSmallShipVerticesBufferPtr == NULL)
		return false;

	if(m_CurrentSmallShipVerticesBufferPtr->Length() == 0)
		return false;
	
	return true;
}


bool CMapPlugin::CreateBSVBO()
{
	if(!m_Ready)
		return false;
	
	//trójkaty
	glBindBuffer(GL_ARRAY_BUFFER, m_BSArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentBSVerticesBufferPtr->Length(), m_CurrentBSVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BSTriangleIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentBSTriangleIndicesBufferPtr->Length(), m_CurrentBSTriangleIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BSLineIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentBSLineIndicesBufferPtr->Length(), m_CurrentBSLineIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_BSColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBA) * m_CurrentBSColorBufferPtr->Length(), m_CurrentBSColorBufferPtr->GetRawData(), GL_STATIC_DRAW);
	
	m_BSTriangleLength = m_CurrentBSTriangleIndicesBufferPtr->Length();
	m_BSLineLength = m_CurrentBSLineIndicesBufferPtr->Length();

	return true;
}

bool CMapPlugin::CreateAtonsVBO()
{
	if(!m_Ready)
		return false;
	
	//trójkaty
	glBindBuffer(GL_ARRAY_BUFFER, m_AtonArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentAtonVerticesBufferPtr->Length(), m_CurrentAtonVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_AtonTriangleIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentAtonTriangleIndicesBufferPtr->Length(), m_CurrentAtonTriangleIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_AtonLineIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentAtonLineIndicesBufferPtr->Length(), m_CurrentAtonLineIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_AtonColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBA) * m_CurrentAtonColorBufferPtr->Length(), m_CurrentAtonColorBufferPtr->GetRawData(), GL_STATIC_DRAW);
	
	m_AtonTriangleLength = m_CurrentAtonTriangleIndicesBufferPtr->Length();
	m_AtonLineLength = m_CurrentAtonLineIndicesBufferPtr->Length();

	return true;
}


bool CMapPlugin::CreateTrianglesVBO()
{
	if(!m_Ready)
		return false;
					
	//trójkaty
	glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentTriangleVerticesBufferPtr->Length(), m_CurrentTriangleVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesTriangleIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentTrianglesTriangleIndicesBufferPtr->Length(), m_CurrentTrianglesTriangleIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesLineIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentTrianglesLineIndicesBufferPtr->Length(), m_CurrentTrianglesLineIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBA) * m_CurrentTrianglesColorBufferPtr->Length(), m_CurrentTrianglesColorBufferPtr->GetRawData(), GL_STATIC_DRAW);

	m_TrianglesTriangleLength = m_CurrentTrianglesTriangleIndicesBufferPtr->Length();
	m_TrianglesLineLength = m_CurrentTrianglesLineIndicesBufferPtr->Length();


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if(glGetError() == GL_NO_ERROR)
		return true;
	else
		return false;
			
}

bool CMapPlugin::CreateSmallShipsVBO()
{
	if(!m_Ready)
		return false;
					
	//trójkaty
	glBindBuffer(GL_ARRAY_BUFFER, m_SmallShipArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentSmallShipVerticesBufferPtr->Length(), m_CurrentSmallShipVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SmallShipTriangleIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentSmallShipTriangleIndicesBufferPtr->Length(), m_CurrentSmallShipTriangleIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SmallShipLineIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentSmallShipLineIndicesBufferPtr->Length(), m_CurrentSmallShipLineIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_SmallShipColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBA) * m_CurrentSmallShipColorBufferPtr->Length(), m_CurrentSmallShipColorBufferPtr->GetRawData(), GL_STATIC_DRAW);

	m_SmallShipTriangleLength = m_CurrentSmallShipTriangleIndicesBufferPtr->Length();
	m_SmallShipLineLength = m_CurrentSmallShipLineIndicesBufferPtr->Length();


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if(glGetError() == GL_NO_ERROR)
		return true;
	else
		return false;
			
}


bool CMapPlugin::CreateShipsVBO()
{
	if(!m_Ready)
		return false;

	//statki
	glBindBuffer(GL_ARRAY_BUFFER, m_ShipsArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentShipVerticesBufferPtr->Length(), m_CurrentShipVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsTriangleIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentShipTriangleIndicesBufferPtr->Length(), m_CurrentShipTriangleIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsLineIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentShipLineIndicesBufferPtr->Length(), m_CurrentShipLineIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_ShipsColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBA) * m_CurrentShipColorBufferPtr->Length(), m_CurrentShipColorBufferPtr->GetRawData(), GL_STATIC_DRAW);

	m_ShipTriangleLength = m_CurrentShipTriangleIndicesBufferPtr->Length();
	m_ShipLineLength = m_CurrentShipLineIndicesBufferPtr->Length();


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	if(glGetError() == GL_NO_ERROR)
		return true;
	else
		return false;
				
}

bool CMapPlugin::CreateSARVBO()
{
	if(!m_Ready)
		return false;

	//SAR
	glBindBuffer(GL_ARRAY_BUFFER, m_SARArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentSARVerticesBufferPtr->Length(), m_CurrentSARVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SARTriangleIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentSARTriangleIndicesBufferPtr->Length(), m_CurrentSARTriangleIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SARLineIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentSARLineIndicesBufferPtr->Length(), m_CurrentSARLineIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
	
	//glBindBuffer(GL_ARRAY_BUFFER, m_ShipsColorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBA) * m_CurrentShipColorBufferPtr->Length(), m_CurrentShipColorBufferPtr->GetRawData(), GL_STATIC_DRAW);

	m_SARTriangleLength = m_CurrentSARTriangleIndicesBufferPtr->Length();
	m_SARLineLength = m_CurrentSARLineIndicesBufferPtr->Length();


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	if(glGetError() == GL_NO_ERROR)
		return true;
	else
		return false;
				
}

void CMapPlugin::RenderBS()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_BSArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);
		
	glBindBuffer(GL_ARRAY_BUFFER, m_BSColorBuffer);
	glColorPointer(4, GL_UNSIGNED_BYTE,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BSTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_BSTriangleLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_COLOR_ARRAY);
	
	glColor4f(0.0,0.0,0.0,0.8);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BSLineIndicesBuffer);
	glDrawElements(GL_LINES, m_BSLineLength, GL_UNSIGNED_INT,0);
		
	glDisableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void CMapPlugin::RenderAtons()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_AtonArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);
		
	glBindBuffer(GL_ARRAY_BUFFER, m_AtonColorBuffer);
	glColorPointer(4, GL_UNSIGNED_BYTE,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_AtonTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_AtonTriangleLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_COLOR_ARRAY);
	
	glColor4f(0.0,0.0,0.0,0.8);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_AtonLineIndicesBuffer);
	glDrawElements(GL_LINES, m_AtonLineLength, GL_UNSIGNED_INT,0);
		
	glDisableClientState(GL_VERTEX_ARRAY);
	
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void CMapPlugin::RenderTriangles()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesColorBuffer);
	glColorPointer(4, GL_UNSIGNED_BYTE,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_TrianglesTriangleLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_COLOR_ARRAY);

	// obrys (linie)
	glColor4ub(GetColor(SHIP_BORDER_COLORA).R ,GetColor(SHIP_BORDER_COLORA).G,GetColor(SHIP_BORDER_COLORA).B,GetColor(SHIP_BORDER_COLORA).A);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesLineIndicesBuffer);
	glDrawElements(GL_LINES, m_TrianglesLineLength , GL_UNSIGNED_INT,0);

	glDisableClientState(GL_VERTEX_ARRAY);
	
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

void CMapPlugin::RenderSmallShips()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_SmallShipArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_SmallShipColorBuffer);
	glColorPointer(4, GL_UNSIGNED_BYTE,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SmallShipTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_SmallShipTriangleLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_COLOR_ARRAY);

	// obrys (linie)
	glColor4ub(GetColor(SHIP_BORDER_COLORA).R ,GetColor(SHIP_BORDER_COLORA).G,GetColor(SHIP_BORDER_COLORA).B,GetColor(SHIP_BORDER_COLORA).A);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SmallShipLineIndicesBuffer);
	glDrawElements(GL_LINES, m_SmallShipLineLength , GL_UNSIGNED_INT,0);

	glDisableClientState(GL_VERTEX_ARRAY);
	
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

void CMapPlugin::RenderShips()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
		
	//statki
	glBindBuffer(GL_ARRAY_BUFFER, m_ShipsArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_ShipsColorBuffer);
	glColorPointer(4, GL_UNSIGNED_BYTE,  0, 0);

		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_ShipTriangleLength, GL_UNSIGNED_INT,0);
		
	glDisableClientState(GL_COLOR_ARRAY);
	
	// obrys (linie)
	glColor4ub(GetColor(SHIP_BORDER_COLORA).R ,GetColor(SHIP_BORDER_COLORA).G,GetColor(SHIP_BORDER_COLORA).B,GetColor(SHIP_BORDER_COLORA).A);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsLineIndicesBuffer);
	glDrawElements(GL_LINES, m_ShipLineLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

void CMapPlugin::RenderSAR()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_SARArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_SARColorBuffer);
	glColorPointer(4, GL_UNSIGNED_BYTE,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SARTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_SARTriangleLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_COLOR_ARRAY);

	// obrys (linie)
	glColor4ub(GetColor(SHIP_BORDER_COLORA).R ,GetColor(SHIP_BORDER_COLORA).G,GetColor(SHIP_BORDER_COLORA).B,GetColor(SHIP_BORDER_COLORA).A);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SARLineIndicesBuffer);
	glDrawElements(GL_LINES, m_SARLineLength , GL_UNSIGNED_INT,0);

	glDisableClientState(GL_VERTEX_ARRAY);
	
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}


void  CMapPlugin::RenderSelection()
{
	m_MMSIFont->Clear();

	SAisData *ptr = GetSelectedPtr();
	if(ptr == NULL)
		return;
		
	double to_x,to_y;
	m_Broker->Unproject(ptr->lon,ptr->lat,&to_x,&to_y);
	to_y = -to_y;

	wchar_t str[64];
	
	//wchar_t wc[64];
	
	if(ptr->valid_pos)
	{
		wchar_t mmsi[16];
		swprintf(mmsi,L"%d",ptr->mmsi);
		m_MMSIFont->Print(to_x,to_y,GetFontSize()/GetSmoothScaleFactor()/DEFAULT_FONT_FACTOR,0.0,mmsi,0.5,3.2);
	}	

	if(ptr->valid_cog)
	{
		wchar_t cog[16];
		swprintf(cog,L"%4.2f", ptr->cog);
		m_MMSIFont->Print(to_x,to_y,GetFontSize()/GetSmoothScaleFactor()/DEFAULT_FONT_FACTOR,0.0,cog,0.5,4.3);
	}
	
	if(ptr->valid_sog)
	{
		wchar_t sog[16];
		swprintf(sog,L"%4.2f", ptr->sog);
		m_MMSIFont->Print(to_x,to_y,GetFontSize()/GetSmoothScaleFactor()/DEFAULT_FONT_FACTOR,0.0,sog,0.5,5.4);
	}


	// quad selection
	double width =  SHIP_QUAD_WIDTH/GetSmoothScaleFactor();
	double height = SHIP_QUAD_HEIGHT/GetSmoothScaleFactor();
	nvPoint2d p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16;		
	
	p1.x = -1.0 * width;	p1.y =  1.0 * height;
	p2.x = -0.7 * width;	p2.y =  1.0 * height;
	
	p3.x =  0.7 * width;	p3.y =  1.0 * height;
	p4.x =  1.0 * width;	p4.y =  1.0 * height;
	
	p5.x =  1.0 * width;	p5.y =  1.0 * height;
	p6.x =  1.0 * width;	p6.y =  0.7 * height;
		
	p7.x =	1.0 * width;	p7.y = -0.7 * height;
	p8.x =  1.0 * width;	p8.y = -1.0 * height;
	
	p9.x =  1.0 * width;	p9.y = -1.0 * height;
	p10.x =  0.7 * width;	p10.y = -1.0 * height;
	
	p11.x = -0.7 * width;	p11.y = -1.0 * height;
	p12.x = -1.0 * width;	p12.y = -1.0 * height;
		
	p13.x = -1.0 * width;	p13.y = -1.0 * height;
	p14.x = -1.0 * width;	p14.y = -0.7 * height;

	p15.x = -1.0 * width;	p15.y =  0.7 * height;
	p16.x = -1.0 * width;	p16.y =  1.0 * height;
	
	
	p1.x += to_x; p1.y += to_y;
	p2.x += to_x; p2.y += to_y;
	p3.x += to_x; p3.y += to_y;
	p4.x += to_x; p4.y += to_y;
	p5.x += to_x; p5.y += to_y;
	p6.x += to_x; p6.y += to_y;
	p7.x += to_x; p7.y += to_y;
	p8.x += to_x; p8.y += to_y;
	p9.x += to_x; p9.y += to_y;
	p10.x += to_x; p10.y += to_y;
	p11.x += to_x; p11.y += to_y;
	p12.x += to_x; p12.y += to_y;
	p13.x += to_x; p13.y += to_y;
	p14.x += to_x; p14.y += to_y;
	p15.x += to_x; p15.y += to_y;
	p16.x += to_x; p16.y += to_y;

	glLineWidth(3);
	glColor4f(0.0,0.0,1.0,0.8);
	glBegin(GL_LINES);
		glVertex2d(p1.x ,p1.y);
		glVertex2d(p2.x ,p2.y);
		glVertex2d(p3.x ,p3.y);
		glVertex2d(p4.x ,p4.y);
		glVertex2d(p5.x ,p5.y);
		glVertex2d(p6.x ,p6.y);
		glVertex2d(p7.x ,p7.y);
		glVertex2d(p8.x ,p8.y);
		glVertex2d(p9.x ,p9.y);
		glVertex2d(p10.x,p10.y);
		glVertex2d(p11.x,p11.y);
		glVertex2d(p12.x,p12.y);
		glVertex2d(p13.x,p13.y);
		glVertex2d(p14.x,p14.y);
		glVertex2d(p15.x,p15.y);
		glVertex2d(p16.x,p16.y);
	glEnd();
	glLineWidth(1);


	nvCircle c;
	c.Center.x = to_x;
	c.Center.y = to_y;
	GetMilesPerDegree(ptr->lon,-ptr->lat);
	double h = GetShipHeight(ptr);

	if(h > 0.0)
		c.Radius = h;
	else
		c.Radius = (double)100/1852/GetMilesPerDegree(ptr->lon,-ptr->lat);
	
	nvDrawCircle(&c);
	
	
}

void CMapPlugin::RenderCPA()
{
	glLineWidth(1);
	m_CPA->Render();
	glLineWidth(1);
}


void CMapPlugin::RenderHDT()
{
	if(!GetShowHDT())
		return;
	
	if(GetHDTLineStyle() == 1)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple( 5, 0xAAAA );
	}

	glLineWidth(GetHDTLineWidth());
	glColor4ub(GetColor(HDT_COLOR).R ,GetColor(HDT_COLOR).G,GetColor(HDT_COLOR).B,GetColor(HDT_COLOR).A);
			
	if(m_CurrentHDGVerticesBufferPtr != NULL && m_CurrentHDGVerticesBufferPtr->Length() > 0)
		RenderGeometry(GL_LINES,m_CurrentHDGVerticesBufferPtr->GetRawData(),m_CurrentHDGVerticesBufferPtr->Length());	// HDG linia
	glLineWidth(1);

	glDisable(GL_LINE_STIPPLE);

}

void CMapPlugin::RenderROT()
{
	glLineWidth(GetHDTLineWidth());
	glColor4ub(GetColor(HDT_COLOR).R ,GetColor(HDT_COLOR).G,GetColor(HDT_COLOR).B,GetColor(HDT_COLOR).A);
			
	if(m_CurrentROTVerticesBufferPtr != NULL && m_CurrentROTVerticesBufferPtr->Length() > 0)
		RenderGeometry(GL_LINES,m_CurrentROTVerticesBufferPtr->GetRawData(),m_CurrentROTVerticesBufferPtr->Length());
	glLineWidth(1);

}


void CMapPlugin::RenderCOG()
{
	if(!GetShowCOG())
		return;
	
	if(GetCOGLineStyle() == 1)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple( 5, 0xAAAA );
	}
	
	glLineWidth(GetCOGLineWidth());
	glColor4ub(GetColor(COG_COLOR).R ,GetColor(COG_COLOR).G,GetColor(COG_COLOR).B,GetColor(COG_COLOR).A);
			
	if(m_CurrentCOGVerticesBufferPtr != NULL && m_CurrentCOGVerticesBufferPtr->Length() > 0)
		RenderGeometry(GL_LINES,m_CurrentCOGVerticesBufferPtr->GetRawData(),m_CurrentCOGVerticesBufferPtr->Length());	// COG linia
	glLineWidth(1);

	glDisable(GL_LINE_STIPPLE);
}

void CMapPlugin::RenderGPS()
{
	
	if(!GetShowGPS())
		return;
	
	glColor4ub(GetColor(GPS_COLOR).R ,GetColor(GPS_COLOR).G,GetColor(GPS_COLOR).B,GetColor(GPS_COLOR).A);

	glPointSize(6);
	
	if(m_CurrentPointsBufferPtr != NULL && m_CurrentPointsBufferPtr->Length() > 0)
		RenderGeometry(GL_POINTS,m_CurrentPointsBufferPtr->GetRawData(),m_CurrentPointsBufferPtr->Length());			//miejsce przyczepienia GPS
		
	glPointSize(1);

}
void CMapPlugin::RenderTracks()
{
	glPointSize(3);	
	if(m_CurrentTrackVerticesBufferPtr != NULL && m_CurrentTrackVerticesBufferPtr->Length() > 0)
	{
		RenderGeometry(GL_POINTS,m_CurrentTrackVerticesBufferPtr->GetRawData(),m_CurrentTrackVerticesBufferPtr->Length());
		
	}
	glLineWidth(1);

}

void CMapPlugin::RenderAnimation()
{
	if(!m_AnimStarted)
		return;

	SAisData * ptr = GetSelectedAnimPtr();

	if(ptr == NULL)
		return;
	
	double to_x,to_y;	
	m_Broker->Unproject(ptr->lon,-ptr->lat,&to_x,&to_y);
	double Factor = 10.0;
		
	float MarkerSize = m_AnimMarkerSize / GetBroker()->GetMapScale();;
	
	// animation
	//if(NmeaInfo.sig == 0)         
		//glColor4ub( 255, 0, 0, 255 - ((AnimMarkerSize / 1000.0f) * 255) );
	//else
		//glColor4ub( 0, 0, 255, 255 - ((AnimMarkerSize / 1000.0f) * 255) );
	
	//glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
		glBindTexture( GL_TEXTURE_2D, m_TextureID_0 );		
		//glTranslated(to_x,to_y,0.0);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex2f( -(MarkerSize)+to_x, -(MarkerSize)+to_y );
			glTexCoord2f(0.0f, 0.0f); glVertex2f( MarkerSize+to_x, -(MarkerSize)+to_y);
			glTexCoord2f(0.0f, 1.0f); glVertex2f( MarkerSize+to_x, MarkerSize+to_y );
			glTexCoord2f(1.0f, 1.0f); glVertex2f( -(MarkerSize)+to_x, MarkerSize+to_y );
		glEnd();
		
	glDisable(GL_TEXTURE_2D);	
	glDisable(GL_BLEND);	
	//glPopMatrix();

	m_AnimMarkerSize += 2.0f;
	if( m_AnimMarkerSize > 30.0f)
		m_AnimMarkerSize = 1.0f;

}


void CMapPlugin::_RenderShipLights()
{
	m_Light0->Render();
	m_Light1->Render();
	m_Light2->Render();
	
}

void CMapPlugin::_RenderBS()
{
	if(!IsBSBuffer())
		return;
	
	CreateBSVBO();
	RenderBS();
	
}

void CMapPlugin::_RenderAtons()
{
	if(!IsAtonBuffer())
		return;
	
	CreateAtonsVBO();
	RenderAtons();

}

void CMapPlugin::_RenderTriangles()
{
	if(!IsTriangleBuffer())
		return;
		
	CreateTrianglesVBO();
	RenderTriangles();

}

void CMapPlugin::_RenderSmallShips()
{
	if(!IsSmallShipBuffer())
		return;
		
	CreateSmallShipsVBO();
	RenderSmallShips();

}

void CMapPlugin::_RenderShips()
{
	if(!IsShipBuffer())
		return;
	
	CreateShipsVBO();
	RenderShips();
	
}

void CMapPlugin::_RenderSAR()
{
	if(!IsSARBuffer())
		return;
	
	CreateSARVBO();
	RenderSAR();
	
}

void CMapPlugin::RenderNormalScale()
{
	//return;
	
	_RenderShips();
	_RenderSmallShips();
	_RenderTriangles();
	_RenderAtons();
	_RenderBS();
	//_RenderSAR();				//moze niestabilne
	//_RenderShipLights();
	RenderROT();
	RenderCOG();
	RenderHDT();
	RenderCPA();
	RenderGPS();
	RenderShipNames();
	RenderSelection();
	RenderTracks();
	

	if(m_MapScale > GetViewFontScale())
	{
		m_NameFont->ClearBuffers();
		m_NameFont->CreateBuffers();
		m_NameFont->Render();
		
		m_MMSIFont->ClearBuffers();
		m_MMSIFont->CreateBuffers();
		m_MMSIFont->Render();

	}

	// napisy

}

void CMapPlugin::RenderSmallScale()
{
	RenderGPS();
}

void CMapPlugin::Render()
{
	if(!GetShowOBJECTS())
		return;

	m_Render = true;
	Generate();
	SetValues(false);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1);
		
	//wxMutexLocker lock(*GetMutex());
	if(m_MapScale < m_Factor/5)
		RenderSmallScale();
	else
		RenderNormalScale();
		
	RenderAnimation();
	
	glLineWidth(1);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	
	m_Render = false;
		
}
void CMapPlugin::Generate()
{
	if(m_FirstTime)
	{
		CreateTextures();
		m_FirstTime = false;
		
		glGenBuffers(1, &m_SmallShipArrayBuffer);
		glGenBuffers(1, &m_SmallShipTriangleIndicesBuffer);
		glGenBuffers(1, &m_SmallShipLineIndicesBuffer);
		glGenBuffers(1, &m_SmallShipColorBuffer);

		glGenBuffers(1, &m_TrianglesArrayBuffer);
		glGenBuffers(1, &m_TrianglesTriangleIndicesBuffer);
		glGenBuffers(1, &m_TrianglesLineIndicesBuffer);
		glGenBuffers(1, &m_TrianglesColorBuffer);

		glGenBuffers(1, &m_ShipsArrayBuffer);
		glGenBuffers(1, &m_ShipsTriangleIndicesBuffer);
		glGenBuffers(1, &m_ShipsLineIndicesBuffer);
		glGenBuffers(1, &m_ShipsColorBuffer);

		glGenBuffers(1, &m_AtonArrayBuffer);
		glGenBuffers(1, &m_AtonTriangleIndicesBuffer);
		glGenBuffers(1, &m_AtonLineIndicesBuffer);
		glGenBuffers(1, &m_AtonColorBuffer);

		glGenBuffers(1, &m_BSArrayBuffer);
		glGenBuffers(1, &m_BSTriangleIndicesBuffer);
		glGenBuffers(1, &m_BSLineIndicesBuffer);
		glGenBuffers(1, &m_BSColorBuffer);

		glGenBuffers(1, &m_SARArrayBuffer);
		glGenBuffers(1, &m_SARTriangleIndicesBuffer);
		glGenBuffers(1, &m_SARLineIndicesBuffer);
		glGenBuffers(1, &m_SARColorBuffer);
	
	}
	
}
void CMapPlugin::SetValues(bool lmb)
{
	double mom[2];
	double _x,_y;
	
	// kolejnosc wa¿na
	m_MapScale = m_Broker->GetMapScale();
	SetSmoothScaleFactor( m_MapScale );
		
	double cr[3];

	m_Broker->GetMapCircle(m_Broker->GetParentPtr(),cr);

	m_MapCircle.Center.x = cr[0];
	m_MapCircle.Center.y = cr[1];
	m_MapCircle.Radius = cr[2] * 2;
	
	m_Broker->GetMouseOM(mom);
	m_Broker->Unproject(mom[0],mom[1],&_x,&_y);
	_y = _y *-1;
	
	m_MapX = _x;
	m_MapY = _y;

	if(lmb)
	{
		m_MouseLmbX = _x;
		m_MouseLmbY = _y;
		
	}

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

void CMapPlugin::OnZoom(double Scale)
{
	//m_MouseUp = false;
	SetValues(false);
	RunThread();
	//fprintf(stdout
}

void CMapPlugin::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
	if(!lmb && m_MouseLmb)
	{
		SetSelectedPtr(NULL);
		SetValues(false);
		RunThread();
		m_MouseUp = true;
	}
	
	if(rmb)
		ShowMenu();

	if(lmb)
	{
		SetValues(true);
		m_MouseLmb = true;
		
	}else{
		m_MouseLmb = false;
	}
	
	
	if(!lmb)
		return;
		
	ShowFrameWindow(false);
	
		
}

void CMapPlugin::MouseDBLClick(int x, int y)
{
	m_MouseDLmb = true;
}

void CMapPlugin::ShowMenu()
{
	wxMenu *Menu = new wxMenu();
	Menu->Append(0,_("test"));
}

void CMapPlugin::RunThread()
{
	CThread *Thread = new CThread(this);
	Thread->SetWorkId(WORK_RENDER_BUFFER);
	Thread->Start();
}

void CMapPlugin::ThreadBegin()
{
	m_ThreadCounter++;
	PrepareBuffer();
	//PrepareCPABuffer();
		
	if(m_MouseUp)
	{
		//FreeSelectedPtr();
		//SetSelectedPtr( NULL);
		SetSelection();
	}
}

void CMapPlugin::ThreadEnd()
{
	m_ThreadCounter--;

	if(m_ThreadCounter == 0)
	{
		if(GetSelectedPtr() != NULL && m_MouseDLmb)
			ShowFrameWindow(true);
		//else
			//ShowFrameWindow(false);
			//m_ShowFrameWindow = false;
		m_Broker->Refresh(m_Broker->GetParentPtr());
	}
	
	m_MouseUp = false;
	m_MouseDLmb = false;
	
				
}

void CMapPlugin::ShowFrameWindow(bool show)
{
	
	m_MyFrame->ShowWindowEvent(show);			
		
}

//bool CMapPlugin::VisibleStateChanged()
//{
	//if(m_MapScale != m_OldMapScale)
		//return true;
	
	//return false;

//}


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

void *CMapPlugin::OnSynchro(void *NaviMapIOApiPtr, void *Params)
{
	CMapPlugin *ThisPtr = (CMapPlugin*)NaviMapIOApiPtr;
	SFunctionData *Data = (SFunctionData*)Params;
	
	ThisPtr->Synchro();
	
	return NULL;
}

void CMapPlugin::Synchro()
{ 
	//m_Ticker1->Stop();
	//m_Ticker1->Start(1000/GetFrequency());
	
	SendSynchroSignal();
	m_Broker->Refresh(m_Broker->GetParentPtr());
}

void CMapPlugin::SendSynchroSignal()
{
	SendSignal(SIGNAL_SYNCHRO_OPTIONS,0);
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
	return MAP_PLUGIN_RUN_ON_DEMAND | RENDER_PRIORITY_8;
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
