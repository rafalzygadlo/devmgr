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
	m_GlobalTick = m_OldGlobalTick = 0;	
	m_OldPositionTick = m_OldHDTTick = 0;
	m_Factor = DEFAULT_FONT_FACTOR;
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


	//m_CurrentHDT = UNDEFINED_DOUBLE;
	m_LastHDT = UNDEFINED_DOUBLE;
	m_SignalID = -1;
	m_MaxFrequencyID = -1;
	memset(m_ShipValidFrequencyTable,0,MAX_SHIP_VALUES_LEN);
	m_ShipValidFrequency = false;
	m_Interpolation = false;
	m_SelectedVertexId = -1;
	m_ThreadCounter = 0;
	m_MouseLmb = m_MouseDLmb = m_MouseUp = false;
	m_ShipRender = false;
	
	m_TrianglesTriangleLength = m_TrianglesLineLength = 0;
	m_SelectedPtr = m_OldSelectedPtr = NULL;
	m_MyFrame = NULL;
	m_MyFrame = new CMyFrame(this,(wxWindow*)m_Broker->GetParentPtr());

	m_Font = new nvFastFont();
	m_Font->Assign( (nvFastFont*)NaviBroker->GetFont( 2 ) );	// 1 = nvAriali 
	m_Font->SetEffect( nvEFFECT_SMOOTH );
	m_Font->SetEffect( nvEFFECT_GLOW );
    
	m_Font->SetGlyphColor(0.0f, 0.0f, 0.0f);
	//Font->SetGlyphCenter(0.0001f);
    //Font->SetGlyphOffset( 0.5f );

	m_Font->SetGlowColor(0.8f, 0.8f, 0.8f );
	m_Font->SetGlowCenter( 4.0f );

	//m_Ready = false;
	//m_Render = false;

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
	InitMutex();
	ais_load_file();
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
	delete m_MyFrame;
	
	ClearBuffers();
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
	
	
	m_Font->InitGL();
}
void CMapPlugin::SetShip(SFunctionData *data)
{
	//GetMutex()->Lock();
	memcpy(m_ShipGlobalState,data->values,sizeof(data->values));
	memcpy(m_GlobalFrequency,data->frequency,sizeof(data->frequency));
	Prepare();
	//GetMutex()->Unlock();
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
		if(!UNDEFINED_VAL(m_ShipGlobalState[0]))
		{
			m_ShipOldStaticState[0] = m_ShipStaticState[0];
			m_ShipState[0] = m_ShipGlobalState[0];
			m_ShipStaticState[0] = m_ShipGlobalState[0];
			SetFrequency(0);
			m_Position_0_Exists = true;
			m_SignalID = 0;
		}
		
		if(!UNDEFINED_VAL(m_ShipGlobalState[1]))
		{	
			m_ShipOldStaticState[1] = m_ShipStaticState[1];
			m_ShipState[1] = m_ShipGlobalState[1];
			m_ShipStaticState[1] = m_ShipGlobalState[1];
			SetFrequency(1);
			m_Position_1_Exists = true;
			m_SignalID = 1;
		}
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[2]))
	{
		m_ShipOldStaticState[2] = m_ShipStaticState[2];
		m_ShipState[2] = m_ShipGlobalState[2];
		m_ShipStaticState[2] = m_ShipGlobalState[2];
		SetFrequency(2);
		m_ROT_Exists = true;
		m_SignalID = 2;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[3]))
	{
		m_ShipOldStaticState[3] = m_ShipStaticState[3];
		m_ShipState[3] = m_ShipGlobalState[3];
		m_ShipStaticState[3] = m_ShipGlobalState[3];
		SetFrequency(3);
		m_SOG_Exists = true;
		m_SignalID = 3;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[4]))
	{
		m_ShipOldStaticState[4] = m_ShipStaticState[4];
		m_ShipState[4] = m_ShipGlobalState[4];
		m_ShipStaticState[4] = m_ShipGlobalState[4];
		SetFrequency(4);
		m_COG_Exists = true;
		m_SignalID = 4;
	}
	
	if(!UNDEFINED_VAL(m_ShipGlobalState[5]))
	{
		m_ShipOldStaticState[5] = m_ShipStaticState[5];
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
		double distance = nvDistance(m_ShipOldStaticState[0],m_ShipOldStaticState[1],m_ShipState[0],m_ShipState[1],nvMeter);
		fprintf(stdout,"\nLON LAT %4.10f %4.10f %4.4f\n",m_ShipState[0],m_ShipState[1],distance);
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
	fprintf(stdout,"Interpolowanie pozycji:[%d][%d] %d\n",m_ShipTicks[0],m_ShipTicks[1],time);
	NewPosition(time);
	
	//m_OldGlobalPositionTick = m_GlobalTick;
	
	
	return true;
}

bool CMapPlugin::InterpolateHDT()
{
	if(m_HDT_Exists)
	{
		fprintf(stdout,"HDT %4.4f %4.4f\n",m_ShipStaticState[5], m_OldHDT - m_ShipStaticState[5]);
		m_OldHDTTick = 0;
		return false;
	}
	
	if(!m_ShipValidFrequency)
		return false;
	
	int time = 0;

	if(m_OldHDTTick == 0)
		time = m_GlobalTick - m_ShipTimes[5];
	else
		time = m_GlobalTick - m_OldGlobalTick;
	
	m_OldHDTTick = m_GlobalTick;
	//fprintf(stdout,"HDT Time %d\n",time);
	NewHDT(time);
		
	return true;
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
	m_ShipState[0] = nlon;
	m_ShipState[1] = nlat;
	
	m_ShipStaticState[0] = nlon; 
	m_ShipStaticState[1] = nlat;
	
	fprintf(stdout,"NEW LON LAT:%4.10f %4.10f\n",nlon,nlat);
	
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
	double v[1] = {m_ShipStaticState[3]}; // cog
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
		//GetMutex()->Lock();
		m_ShipTick = 0;
		Interpolate();
		SendShipData();
		m_ShipInterval = m_MaxFrequency/TICKER_SLEEP;
		//GetMutex()->Unlock();
		
	}
	
	if( m_AisBufferTick >= m_AisBufferInterval)	
	{	
		m_AisBufferTick = 0;
		PrepareBuffer();
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
	SendSignal(CLEAR_DISPLAY,NULL);
	// before myserial delete

}

void CMapPlugin::SetSmoothScaleFactor(double _Scale) 
{
	if( _Scale > m_Factor )
		m_SmoothScaleFactor = _Scale;
	else
		m_SmoothScaleFactor = m_Factor;
}



bool CMapPlugin::IsOnScreen(double x, double y)
{
	if(IsPointInsideBox(x, y, m_ScreenX1 , m_ScreenY1, m_ScreenX2, m_ScreenY2))
		return true;
	
	return false;

}

void CMapPlugin::SetSelection()
{	
	SelectTriangle();
	SelectSmallShip();
	SelectShip();
	SelectAton();
}

void CMapPlugin::SelectTriangle()
{
	if(m_CurrentTriangleVerticesBufferPtr == NULL)
		return;

	nvPoint2d *RawPt  = m_CurrentTriangleVerticesBufferPtr->GetRawData();
	
	nvPoint2f pt;
	pt.x = m_MapX;
	pt.y = m_MapY;
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
					m_SelectedPtr = ais_get_buffer()->Get(m_IdToTriangleId.Get(i).id0);
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
	pt.x = m_MapX;
	pt.y = m_MapY;
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
					m_SelectedPtr = ais_get_buffer()->Get(m_IdToSmallShipId.Get(i).id0);
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
	pt.x = m_MapX;
	pt.y = m_MapY;
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
					m_SelectedPtr = ais_get_buffer()->Get(m_IdToShipId.Get(i).id0);
					return;
				}
			}	
		}
	}
	
}

void CMapPlugin::SelectAton()
{
	if(m_CurrentTriangleVerticesBufferPtr == NULL)
		return;

	nvPoint2d *RawPt  = m_CurrentAtonVerticesBufferPtr->GetRawData();
	
	nvPoint2f pt;
	pt.x = m_MapX;
	pt.y = m_MapY;
	int selected = -1;
	
	for (size_t i = 0; i < m_CurrentAtonVerticesBufferPtr->Length(); i+=8)
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
					m_SelectedPtr = ais_get_buffer()->Get(m_IdToAtonId.Get(i).id0);
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
	m_CurrentTrianglesTriangleIndicesBufferPtr = &m_TrianglesTriangleIndicesBuffer1;	// indexy
	m_CurrentTrianglesLineIndicesBufferPtr = &m_TrianglesLineIndicesBuffer1;			// indexy
	m_CurrentTrianglesColorBufferPtr = &m_TrianglesColorBuffer1;						// kolory
		
	//ATON
	m_CurrentAtonVerticesBufferPtr = &m_AtonVerticesBuffer1;
	m_CurrentAtonTriangleIndicesBufferPtr = &m_AtonTriangleIndicesBuffer1;
	m_CurrentAtonLineIndicesBufferPtr = &m_AtonLineIndicesBuffer1;
	m_CurrentAtonColorBufferPtr = &m_AtonColorBuffer1;
	
	//nazwy
	m_CurrentShipNamesBufferPtr = &m_ShipNamesBuffer1;
	
	//COG
	m_CurrentCOGVerticesBufferPtr = &m_COGVerticesBuffer1;
	//HDG
	m_CurrentHDGVerticesBufferPtr = &m_HDGVerticesBuffer1;

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

	
	m_CurrentShipNamesBufferPtr = &m_ShipNamesBuffer0;
	
	//COG
	m_CurrentCOGVerticesBufferPtr = &m_COGVerticesBuffer0;

	//HDG
	m_CurrentHDGVerticesBufferPtr = &m_HDGVerticesBuffer0;

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
	m_SmallShipColorBuffer0.Clear();					//kolory

	//statki
	m_ShipVerticesBuffer0.Clear();				
	m_ShipTriangleIndicesBuffer0.Clear();
	m_ShipLineIndicesBuffer0.Clear();
	m_ShipColorBuffer0.Clear();					//kolory
	
	//ATON
	m_AtonVerticesBuffer0.Clear();
	m_AtonLineIndicesBuffer0.Clear();
	m_AtonTriangleIndicesBuffer0.Clear();
	m_AtonColorBuffer0.Clear();
		
	//nazwy
	m_ShipNamesBuffer0.Clear();
		
	
	//COG
	m_COGVerticesBuffer0.Clear();

	//HDG
	m_HDGVerticesBuffer0.Clear();

	//indeksy
	m_IdToTriangleId.Clear();
	m_IdToShipId.Clear();
	m_IdToAtonId.Clear();
	m_IdToSmallShipId.Clear();
	
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
	CopyNvRGBAf(&m_TrianglesColorBuffer0, &m_TrianglesColorBuffer1);
	
	//ma³y statek
	CopyNvPoint2d(&m_SmallShipVerticesBuffer0,&m_SmallShipVerticesBuffer1);
	CopyInt(&m_SmallShipTriangleIndicesBuffer0,&m_SmallShipTriangleIndicesBuffer1);
	CopyInt(&m_SmallShipLineIndicesBuffer0,&m_SmallShipLineIndicesBuffer1);
	CopyNvRGBAf(&m_SmallShipColorBuffer0, &m_SmallShipColorBuffer1);

	//statek
	CopyNvPoint2d(&m_ShipVerticesBuffer0,&m_ShipVerticesBuffer1);
	CopyInt(&m_ShipTriangleIndicesBuffer0,&m_ShipTriangleIndicesBuffer1);
	CopyInt(&m_ShipLineIndicesBuffer0,&m_ShipLineIndicesBuffer1);
	CopyNvRGBAf(&m_ShipColorBuffer0, &m_ShipColorBuffer1);

	//aton
	CopyNvPoint2d(&m_AtonVerticesBuffer0,&m_AtonVerticesBuffer1);
	CopyInt(&m_AtonTriangleIndicesBuffer0,&m_AtonTriangleIndicesBuffer1);
	CopyInt(&m_AtonLineIndicesBuffer0,&m_AtonLineIndicesBuffer1);
			
	//COG
	CopyNvPoint2d(&m_COGVerticesBuffer0,&m_COGVerticesBuffer1);

	//HDG
	CopyNvPoint2d(&m_HDGVerticesBuffer0,&m_HDGVerticesBuffer1);

}

void CMapPlugin::SetBuffers()
{
	CNaviArray <SAisData*> *buffer = ais_get_buffer();

	for(size_t i = 0; i < buffer->Length(); i++)
	{
		m_CurrentId = i;
		SAisData *ptr = buffer->Get(i);
		double to_x,to_y;
		m_Broker->Unproject(ptr->lon,-ptr->lat,&to_x,&to_y);
		
		if(IsOnScreen(to_x,to_y))
		{
			PreparePointsBuffer(ptr);
			
			bool ship = false;
			if(GetShipWidth(ptr) > (GetTriangleWidth(m_SmoothScaleFactor) * TRIANGLE_WIDTH_FACTOR))
				ship = true;
			
			if(GetShipHeight(ptr) > (GetTriangleHeight(m_SmoothScaleFactor) * TRIANGLE_HEIGHT_FACTOR))
				ship = true;
			
			if(ship)
				PrepareShipBuffer(ptr);				
			else
				PrepareTriangleBuffer(ptr);
			
									
			PrepareAtonBuffer(ptr);

			PrepareCOGVerticesBuffer(ptr);				// linia cog
			PrepareHDGVerticesBuffer(ptr);
		}
	}

}


void CMapPlugin::PrepareBuffer()
{
	m_Ready = false;
	GetMutex()->Lock();
	SetPtr0();
	ClearBuffers();
	SetBuffers();	
	CopyBuffers();
	SetPtr1();
	
	GetMutex()->Unlock();
	m_Ready = true;
		
}

void CMapPlugin::CopyNvRGBAf(CNaviArray <nvRGBAf> *src, CNaviArray <nvRGBAf> *dst)
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

void CMapPlugin::PreparePointsBuffer(SAisData *ptr)
{
	nvPoint2d pt;
	
	m_Broker->Unproject(ptr->lon, -ptr->lat, &pt.x, &pt.y);							// pozycja y statku na mapie
	double Distance = nvDistance( ptr->lon, ptr->lat, ptr->lon + 1.0, ptr->lat );	// iloœæ mil na stopieñ w aktualnej pozycji y
		
	m_PointsBuffer0.Append(pt);
	
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
	if(ptr->valid[AIS_MSG_5])
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
		
	double width = ATON_WIDTH/m_SmoothScaleFactor;
	double height = ATON_HEIGHT/m_SmoothScaleFactor;
			
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
	nvRGBAf green;	green.R = 0.0f;	green.G = 1.0f;	green.B = 0.0f; green.A = 0.0f;	
	
	m_AtonColorBuffer0.Append(green);
	m_AtonColorBuffer0.Append(green);
	m_AtonColorBuffer0.Append(green);
	m_AtonColorBuffer0.Append(green);
	m_AtonColorBuffer0.Append(green);
	m_AtonColorBuffer0.Append(green);
	m_AtonColorBuffer0.Append(green);
	m_AtonColorBuffer0.Append(green);

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
		
	double width =  SHIP_TRIANGLE_WIDTH/m_SmoothScaleFactor;
	double height = SHIP_TRIANGLE_HEIGHT/m_SmoothScaleFactor;
			
	p1.x = -0.5 * width;	p1.y =  0.8 * height;
	p2.x =  0.0 * width;	p2.y = -0.8 * height;
	p3.x =  0.5 * width;	p3.y =  0.8 * height;
				
	//obrót
	double angle = 0;
	if(ptr->valid_cog)
		angle = ptr->cog;
	if(ptr->valid_hdg)
		angle = ptr->hdg;
		
	double out_x,out_y;

#ifdef ROTATE
	RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(angle));	p1.x = out_x;	p1.y = out_y;
	RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(angle));	p2.x = out_x;	p2.y = out_y;
	RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(angle));	p3.x = out_x;	p3.y = out_y;
#endif	
	
	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;

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

	nvRGBAf green;	green.R = 0.0f;	green.G = 1.0f;	green.B = 0.0f; green.A = 0.6f;	
	nvRGBAf yellow; yellow.R = 0.98f; yellow.G = 0.91f; yellow.B = 0.0f; yellow.A = 0.6f; 
	nvRGBAf red; red.R = 1.0f; red.G = 0.0f; red.B = 0.0f; red.A = 0.6f; 

	int timeout = GetTickCount() - ptr->time;

	if(timeout >= AIS_TIMEOUT)
	{
		m_TrianglesColorBuffer0.Append(red);
		m_TrianglesColorBuffer0.Append(red);
		m_TrianglesColorBuffer0.Append(red);
		return;
	}
	
	if(ptr->sog > MIN_SHIP_SPEED)
	{
		m_TrianglesColorBuffer0.Append(green);
		m_TrianglesColorBuffer0.Append(green);
		m_TrianglesColorBuffer0.Append(green);
	
	}else{
	
		m_TrianglesColorBuffer0.Append(yellow);
		m_TrianglesColorBuffer0.Append(yellow);
		m_TrianglesColorBuffer0.Append(yellow);
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
		
	double width =  SMALL_SHIP_WIDTH/m_SmoothScaleFactor;
	double height = SMALL_SHIP_HEIGHT/m_SmoothScaleFactor;
		
	p1.x = -0.5 * width;	p1.y =  0.5    * height;	
	p2.x =  0.5 * width;	p2.y =  0.5    * height; 
	p3.x =  0.5 * width;	p3.y = -0.3    * height;	
	p4.x =  0.3 * width;	p4.y = -0.425  * height;
	p5.x =  0.0;			p5.y = -0.5    * height;
	p6.x = -0.3 * width;	p6.y = -0.425  * height;
	p7.x = -0.5 * width;	p7.y = -0.3    * height;
					
	//obrót
	double angle = 0;
	if(ptr->valid_cog)
		angle = ptr->cog;
	if(ptr->valid_hdg)
		angle = ptr->hdg;
		
	double out_x,out_y;

#ifdef ROTATE
	RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(angle));	p1.x = out_x;	p1.y = out_y;
	RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(angle));	p2.x = out_x;	p2.y = out_y;
	RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(angle));	p3.x = out_x;	p3.y = out_y;
	RotateZ(p4.x,p4.y,out_x,out_y,nvToRad(angle));	p4.x = out_x;	p4.y = out_y;
	RotateZ(p5.x,p5.y,out_x,out_y,nvToRad(angle));	p5.x = out_x;	p5.y = out_y;
	RotateZ(p6.x,p6.y,out_x,out_y,nvToRad(angle));	p6.x = out_x;	p6.y = out_y;
	RotateZ(p7.x,p7.y,out_x,out_y,nvToRad(angle));	p7.x = out_x;	p7.y = out_y;
#endif	
	
	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;
	p4.x += pt.x; p4.y += pt.y;
	p5.x += pt.x; p5.y += pt.y;
	p6.x += pt.x; p6.y += pt.y;
	p7.x += pt.x; p7.y += pt.y;

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

	nvRGBAf green;	green.R = 0.0f;	green.G = 1.0f;	green.B = 0.0f; green.A = 0.6f;	
	nvRGBAf yellow; yellow.R = 0.98f; yellow.G = 0.91f; yellow.B = 0.0f; yellow.A = 0.6f; 
	nvRGBAf red; red.R = 1.0f; red.G = 0.0f; red.B = 0.0f; red.A = 0.6f; 

	int timeout = GetTickCount() - ptr->time;

	if(timeout >= AIS_TIMEOUT)
	{
		m_SmallShipColorBuffer0.Append(red);
		m_SmallShipColorBuffer0.Append(red);
		m_SmallShipColorBuffer0.Append(red);
		m_SmallShipColorBuffer0.Append(red);
		m_SmallShipColorBuffer0.Append(red);
		m_SmallShipColorBuffer0.Append(red);
		m_SmallShipColorBuffer0.Append(red);
		return;
	}
	
	if(ptr->sog > MIN_SHIP_SPEED)
	{
		m_SmallShipColorBuffer0.Append(green);
		m_SmallShipColorBuffer0.Append(green);
		m_SmallShipColorBuffer0.Append(green);
		m_SmallShipColorBuffer0.Append(green);
		m_SmallShipColorBuffer0.Append(green);
		m_SmallShipColorBuffer0.Append(green);
		m_SmallShipColorBuffer0.Append(green);
	
	}else{
	
		m_SmallShipColorBuffer0.Append(yellow);
		m_SmallShipColorBuffer0.Append(yellow);
		m_SmallShipColorBuffer0.Append(yellow);
		m_SmallShipColorBuffer0.Append(yellow);
		m_SmallShipColorBuffer0.Append(yellow);
		m_SmallShipColorBuffer0.Append(yellow);
		m_SmallShipColorBuffer0.Append(yellow);
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
		
	p1.x -= vx; p1.y -= vy;
	p2.x -= vx; p2.y -= vy;
	p3.x -= vx; p3.y -= vy;
	p4.x -= vx; p4.y -= vy;
	p5.x -= vx; p5.y -= vy;
	p6.x -= vx; p6.y -= vy;
	p7.x -= vx; p7.y -= vy;

	//obrót
	double angle = 0;
	if(ptr->valid_cog)
		angle = ptr->cog;
	if(ptr->valid_hdg)
		angle = ptr->hdg;

#ifdef ROTATE
	double out_x,out_y;
	RotateZ(p1.x,p1.y,out_x,out_y,nvToRad(angle));	p1.x = out_x;	p1.y = out_y;
	RotateZ(p2.x,p2.y,out_x,out_y,nvToRad(angle));	p2.x = out_x;	p2.y = out_y;
	RotateZ(p3.x,p3.y,out_x,out_y,nvToRad(angle));	p3.x = out_x;	p3.y = out_y;
	RotateZ(p4.x,p4.y,out_x,out_y,nvToRad(angle));	p4.x = out_x;	p4.y = out_y;
	RotateZ(p5.x,p5.y,out_x,out_y,nvToRad(angle));	p5.x = out_x;	p5.y = out_y;
	RotateZ(p6.x,p6.y,out_x,out_y,nvToRad(angle));	p6.x = out_x;	p6.y = out_y;
	RotateZ(p7.x,p7.y,out_x,out_y,nvToRad(angle));	p7.x = out_x;	p7.y = out_y;
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
	nvRGBAf green;	green.R = 0.0f;	green.G = 1.0f;	green.B = 0.0f; green.A = 0.6f;	
	nvRGBAf yellow; yellow.R = 0.98f; yellow.G = 0.91f; yellow.B = 0.0f; yellow.A = 0.6f; 
	nvRGBAf red; red.R = 1.0f; red.G = 0.0f; red.B = 0.0f; red.A = 0.6f; 

	int timeout = GetTickCount() - ptr->time;

	if(timeout >= AIS_TIMEOUT)
	{
		m_ShipColorBuffer0.Append(red);
		m_ShipColorBuffer0.Append(red);
		m_ShipColorBuffer0.Append(red);
		m_ShipColorBuffer0.Append(red);
		m_ShipColorBuffer0.Append(red);
		m_ShipColorBuffer0.Append(red);
		m_ShipColorBuffer0.Append(red);
		return;
	}
	
	if(ptr->sog > MIN_SHIP_SPEED)
	{
		m_ShipColorBuffer0.Append(green);
		m_ShipColorBuffer0.Append(green);
		m_ShipColorBuffer0.Append(green);
		m_ShipColorBuffer0.Append(green);
		m_ShipColorBuffer0.Append(green);
		m_ShipColorBuffer0.Append(green);
		m_ShipColorBuffer0.Append(green);
	
	}else{
	
		m_ShipColorBuffer0.Append(yellow);
		m_ShipColorBuffer0.Append(yellow);
		m_ShipColorBuffer0.Append(yellow);
		m_ShipColorBuffer0.Append(yellow);
		m_ShipColorBuffer0.Append(yellow);
		m_ShipColorBuffer0.Append(yellow);
		m_ShipColorBuffer0.Append(yellow);
	}

}

/*
void CMapPlugin::PrepareShipNamesBuffer(SAisData *ptr) 
{
	wchar_t str[128];
	wchar_t wc[64];
	
	if(ptr->valid_dim && ptr->valid_pos)
	{
		mbstowcs(wc, ptr->shipname, 128);
		swprintf(str,L"%d %ls",ptr->mmsi,wc);
		m_ShipNamesBuffer0.Append(str);
	
	}else{
	
		if(ptr->valid[AIS_MSG_21])
			swprintf(str,L"ATON %d",ptr->mmsi);
		else
			swprintf(str,L"%d",ptr->mmsi);
		
		m_ShipNamesBuffer0.Append(str);
	}
}
*/
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
	NewLonLat(60,pt.x,pt.y,sog,cog,&new_lon,&new_lat);
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
	
	nvPoint2d p1, p2;
		
	//obrót
	double hdg = ptr->hdg;
	double sog = ptr->sog;
	
	double to_x, to_y;
	m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
	p1.x = to_x;p1.y = to_y;
	
	double new_lon, new_lat;
	NewLonLat(60,pt.x,pt.y,sog,hdg,&new_lon,&new_lat);
	p2.x = new_lon; p2.y = new_lat;
	m_Broker->Unproject(p2.x, p2.y,&to_x,&to_y);
	p2.x = to_x; p2.y = to_y;
		
	m_HDGVerticesBuffer0.Append(p1);
	m_HDGVerticesBuffer0.Append(p2);
	
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

	size_t size = m_CurrentShipNamesBufferPtr->Length();
	m_Font->Clear();
	if(size == 0)
		return;

	size_t CaptionsSize = size;
    vect2 *Positions = (vect2*)malloc( CaptionsSize *sizeof( vect2 ) );    // czêœæ ca³kowita jednostki sondowania
    float *Scale = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *Angle = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *vx = (float*)malloc( CaptionsSize * sizeof( float ) );
    float *vy = (float*)malloc( CaptionsSize * sizeof( float ) );
    wchar_t **CaptionsStr = (wchar_t**)malloc(  CaptionsSize * sizeof( wchar_t** ) );
	
    for(size_t i = 0 ; i < m_CurrentShipNamesBufferPtr->Length(); i++ ) 
	{
		Positions[i][0] = m_CurrentPointsBufferPtr->Get(i).x;
        Positions[i][1] = m_CurrentPointsBufferPtr->Get(i).y + (10.0/m_SmoothScaleFactor);
		Scale[i] = 6.0 / m_SmoothScaleFactor / DEFAULT_FONT_FACTOR;
        vx[i] = 0.5f;
        vy[i] = 0.5f;
		CaptionsStr[i] = m_CurrentShipNamesBufferPtr->Get(i);   // bez kopiowania ³añcucha!!! 
		Angle[i] = m_Broker->GetAngle();
    }

	m_Font->Clear();
    m_Font->PrintList( Positions, Scale, Angle, CaptionsStr, CaptionsSize, vx, vy );
	m_Font->ClearBuffers();
	m_Font->CreateBuffers();
	m_Font->Render();

	free( CaptionsStr );    // ³añcuchy nie zosta³y skopiowane, nie ma koniecznoœci zwalniania ca³ej listy
    free( Positions );
    free( Scale );
    free( Angle );
    free( vx );
    free( vy );
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBAf) * m_CurrentAtonColorBufferPtr->Length(), m_CurrentAtonColorBufferPtr->GetRawData(), GL_STATIC_DRAW);
	
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBAf) * m_CurrentTrianglesColorBufferPtr->Length(), m_CurrentTrianglesColorBufferPtr->GetRawData(), GL_STATIC_DRAW);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBAf) * m_CurrentSmallShipColorBufferPtr->Length(), m_CurrentSmallShipColorBufferPtr->GetRawData(), GL_STATIC_DRAW);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBAf) * m_CurrentShipColorBufferPtr->Length(), m_CurrentShipColorBufferPtr->GetRawData(), GL_STATIC_DRAW);

	m_ShipColorLength = m_CurrentShipColorBufferPtr->Length();
	m_ShipTriangleLength = m_CurrentShipTriangleIndicesBufferPtr->Length();
	m_ShipLineLength = m_CurrentShipLineIndicesBufferPtr->Length();


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	if(glGetError() == GL_NO_ERROR)
		return true;
	else
		return false;
				
}

void CMapPlugin::RenderAtons()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, m_AtonArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);
		
	glBindBuffer(GL_ARRAY_BUFFER, m_AtonColorBuffer);
	glColorPointer(4, GL_FLOAT,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_AtonTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_AtonTriangleLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_COLOR_ARRAY);
	
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
	glColorPointer(4, GL_FLOAT,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_TrianglesTriangleLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_COLOR_ARRAY);

	// obrys (linie)
	glColor4f(0.0,0.0,0.0,0.9);
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
	glColorPointer(4, GL_FLOAT,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SmallShipTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_SmallShipTriangleLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_COLOR_ARRAY);

	// obrys (linie)
	glColor4f(0.0,0.0,0.0,0.9);
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
	glColorPointer(4, GL_FLOAT,  0, 0);

	// wype³nienie (trójk¹ty)
	glColor4f(0.0,0.0,0.0,0.6);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_ShipTriangleLength, GL_UNSIGNED_INT,0);
		
	
	glDisableClientState(GL_COLOR_ARRAY);
	
	// obrys (linie)
	glColor4f(0.0,0.0,0.0,0.9);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsLineIndicesBuffer);
	glDrawElements(GL_LINES, m_ShipLineLength, GL_UNSIGNED_INT,0);

	glDisableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

void  CMapPlugin::RenderSelection()
{
	if(m_SelectedPtr == NULL)
		return;
	
	double to_x,to_y;
	m_Broker->Unproject(m_SelectedPtr->lon,m_SelectedPtr->lat,&to_x,&to_y);
	to_y = -to_y;

	wchar_t str[64];
	wchar_t mmsi[16];
	wchar_t wc[64];
	
	m_Font->Clear();
	
	if(m_SelectedPtr->valid_pos)
	{
		swprintf(mmsi,L"%d",m_SelectedPtr->mmsi);	
		m_Font->Print(to_x,to_y,0.12/m_MapScale,0.0,mmsi,0.5,3.2);
	}	
	
	if(m_SelectedPtr->valid_dim)
	{
		mbstowcs(wc, m_SelectedPtr->shipname, 128);
		swprintf(str,L"%ls",wc);
		m_Font->Print(to_x,to_y,0.12/m_MapScale,0.0,str,0.5,4.4);
	}
	
	if(m_SelectedPtr->valid_aton)
	{
		mbstowcs(wc, m_SelectedPtr->aton_name, 128);
		swprintf(str,L"%ls",wc);
		m_Font->Print(to_x,to_y,0.12/m_MapScale,0.0,str,0.5,4.4);
	}

	m_Font->ClearBuffers();
	m_Font->CreateBuffers();
	m_Font->Render();

	// quad selection
	double width =  SHIP_QUAD_WIDTH/m_SmoothScaleFactor;
	double height = SHIP_QUAD_HEIGHT/m_SmoothScaleFactor;
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

	glLineWidth(2);
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
	
}

void CMapPlugin::RenderHDG()
{
	glPointSize(4);
	
	if(m_CurrentHDGVerticesBufferPtr != NULL && m_CurrentHDGVerticesBufferPtr->Length() > 0)
	{
		RenderGeometry(GL_LINES,m_CurrentHDGVerticesBufferPtr->GetRawData(),m_CurrentHDGVerticesBufferPtr->Length());	// HDG linia
		RenderGeometry(GL_POINTS,m_CurrentHDGVerticesBufferPtr->GetRawData(),m_CurrentHDGVerticesBufferPtr->Length());	// HDG punkty
	}
	
	glPointSize(1);
}

void CMapPlugin::RenderCOG()
{
	glPointSize(4);
	
	if(m_CurrentCOGVerticesBufferPtr != NULL && m_CurrentCOGVerticesBufferPtr->Length() > 0)
	{
		RenderGeometry(GL_LINES,m_CurrentCOGVerticesBufferPtr->GetRawData(),m_CurrentCOGVerticesBufferPtr->Length());	// COG linia
		RenderGeometry(GL_POINTS,m_CurrentCOGVerticesBufferPtr->GetRawData(),m_CurrentCOGVerticesBufferPtr->Length());	// COG punkty
	}
	
	glPointSize(1);
}

void CMapPlugin::RenderGPS()
{
	glColor4f(0.0,0.0,1.0,0.7);
	glPointSize(5);
	
	if(m_CurrentPointsBufferPtr != NULL && m_CurrentPointsBufferPtr->Length() > 0)
	{
		RenderGeometry(GL_POINTS,m_CurrentPointsBufferPtr->GetRawData(),m_CurrentPointsBufferPtr->Length());			//miejsce przyczepienia GPS
	}
	
	glPointSize(1);

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



void CMapPlugin::Render()
{
		
	Generate();
	SetValues();
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1);	
	
	wxMutexLocker locker(*GetMutex());
	
	_RenderShips();
	_RenderSmallShips();
	_RenderTriangles();
	_RenderAtons();
	RenderCOG();
	RenderHDG();
	RenderGPS();
	RenderSelection();
	
	glLineWidth(1);		
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	
		
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



	
	}
	
}
void CMapPlugin::SetValues()
{
	double mom[2];
	double _x,_y;
	
	// kolejnosc wa¿na
	m_MapScale = m_Broker->GetMapScale();
	SetSmoothScaleFactor( m_MapScale );
	
	double vmap[4];
	m_Broker->GetVisibleMap(vmap);

	m_ScreenX1 = vmap[0];
	m_ScreenY1 = vmap[1];
	m_ScreenX2 = vmap[2];
	m_ScreenY2 = vmap[3];
	
	m_Broker->GetMouseOM(mom);
	m_Broker->Unproject(mom[0],mom[1],&_x,&_y);
	_y = _y *-1;
	
	m_MapX = _x;
	m_MapY = _y;

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
	SetValues();
	RunThread();
	//fprintf(stdout
}

void CMapPlugin::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
	if(!lmb && m_MouseLmb)
	{
		m_SelectedPtr = NULL;
		SetValues();
		RunThread();
		m_MouseUp = true;	
	}
	
	if(lmb)
	{
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

void CMapPlugin::RunThread()
{
	//m_AisBufferInterval
	CThread *Thread = new CThread(this);
	Thread->SetWorkId(WORK_RENDER_BUFFER);
	Thread->Start();

}

void CMapPlugin::ThreadBegin()
{
	m_ThreadCounter++;
	PrepareBuffer();
	if(m_MouseUp)
	{
		m_SelectedPtr = NULL;
		SetSelection();
	}
}

void CMapPlugin::ThreadEnd()
{
	m_ThreadCounter--;

	if(m_ThreadCounter == 0)
	{
		if(m_SelectedPtr != NULL && m_MouseDLmb)
			ShowFrameWindow(true);
		//else
			//ShowFrameWindow(false);
	}
	
	m_MouseUp = false;
	m_MouseDLmb = false;
	m_Broker->Refresh(m_Broker->GetParentPtr());
				
}

void CMapPlugin::ShowFrameWindow(bool show)
{
	m_MyFrame->ShowWindow(show);
}

SAisData *CMapPlugin::GetSelectedPtr()
{
	return m_SelectedPtr;
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
