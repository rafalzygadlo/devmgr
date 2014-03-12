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

	//m_CurrentHDT = UNDEFINED_DOUBLE;
	m_LastHDT = UNDEFINED_DOUBLE;
	m_SignalID = -1;
	m_MaxFrequencyID = -1;
	memset(m_ShipValidFrequencyTable,0,MAX_SHIP_VALUES_LEN);
	m_ShipValidFrequency = false;
	m_Interpolation = false;
	m_SelectedShip = NULL;
	m_SelectedVertexId = -1;
	

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
	if(m_FirstTime)
	{
		CreateTextures();
		m_FirstTime = false;
	}
	
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
		
	double nlon = lon + dlonm / (lonDistance * 1852.0);	// sta�a ilo�� km na 1 stopien
	double nlat = lat + dlatm / (latDistance * 1852.0);	// sta�a ilo�� km na 1 stopien
			
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

void CMapPlugin::PrepareBuffer()
{
	GetMutex()->Lock();
	m_Font->Clear();
	
	CNaviArray <SAisData*> *buffer = ais_get_buffer();

	// przygotuj bufory do renderu
	m_CurrentPointsBufferPtr = &m_PointsBuffer1;
	//tr�jkaty
	m_CurrentTriangleVerticesBufferPtr = &m_TriangleVerticesBuffer1;				
	m_CurrentTrianglesTriangleIndicesBufferPtr = &m_TrianglesTriangleIndicesBuffer1;	//indexy
	m_CurrentTrianglesLineIndicesBufferPtr = &m_TrianglesLineIndicesBuffer1;			// indexy
	//ship
	m_CurrentShipVerticesBufferPtr = &m_ShipVerticesBuffer1; 
	m_CurrentShipTriangleIndicesBufferPtr = &m_ShipTriangleIndicesBuffer1;
	m_CurrentShipLineIndicesBufferPtr = &m_ShipLineIndicesBuffer1;
	
	m_CurrentShipNamesBufferPtr = &m_ShipNamesBuffer1;
	m_CurrentAtonTriangleBufferPtr = &m_AtonTriangleBuffer1;
		
	m_PointsBuffer0.Clear();
	m_TriangleVerticesBuffer0.Clear();
	m_TrianglesTriangleIndicesBuffer0.Clear();
	m_TrianglesLineIndicesBuffer0.Clear();

	m_ShipVerticesBuffer0.Clear();
	m_ShipTriangleIndicesBuffer0.Clear();
	m_ShipLineIndicesBuffer0.Clear();
	m_ShipNamesBuffer0.Clear();
	m_AtonTriangleBuffer0.Clear();
	
	for(size_t i = 0; i < buffer->Length(); i++)
	{
		SAisData *data = buffer->Get(i);
		double to_x,to_y;
		m_Broker->Unproject(data->lon,-data->lat,&to_x,&to_y);
		if(IsOnScreen(to_x,to_y))
		{
			PreparePointsBuffer(data);

			PrepareTriangleVerticesBuffer(data);		// bufor verteks�w trojkata
			PrepareTriangleTriangleIndicesBuffer(data);	// bufor index�w
			PrepareTriangleLineIndicesBuffer(data);		// bufor index�w

			PrepareShipVerticesBuffer(data);			// bufor verteks�w statku
			PrepareShipTriangleIndicesBuffer(data);		// indexy
			PrepareShipLineIndicesBuffer(data);			// indexy
			
			PrepareShipNamesBuffer(data);			
			PrepareAtonTriangleBuffer(data);
		}
	}
	
	m_CurrentPointsBufferPtr = &m_PointsBuffer0;
	
	m_CurrentShipVerticesBufferPtr = &m_ShipVerticesBuffer0;
	m_CurrentShipTriangleIndicesBufferPtr = &m_ShipTriangleIndicesBuffer0;
	m_CurrentShipLineIndicesBufferPtr = &m_ShipLineIndicesBuffer0;
	
	m_CurrentTriangleVerticesBufferPtr = &m_TriangleVerticesBuffer0;
	m_CurrentTrianglesTriangleIndicesBufferPtr = &m_TrianglesTriangleIndicesBuffer0;
	m_CurrentTrianglesLineIndicesBufferPtr = &m_TrianglesLineIndicesBuffer0;

	m_CurrentShipNamesBufferPtr = &m_ShipNamesBuffer0;
	m_CurrentAtonTriangleBufferPtr = &m_AtonTriangleBuffer0;
	
	//punkty
	CopyPointsBuffer();
	
	//tr�jkat
	CopyTriangleVerticesBuffer();
	CopyTriangleTriangleIndicesBuffer();
	CopyTriangleLineIndicesBuffer();
	
	//statek
	CopyShipVerticesBuffer();
	CopyShipTriangleIndicesBuffer();
	CopyShipLineIndicesBuffer();
	
	//czcionki
	CopyShipNamesBuffer();
	
	//atony
	CopyAtonTriangleBuffer();

	GetMutex()->Unlock();
	
}

void CMapPlugin::CopyPointsBuffer()
{
	m_PointsBuffer1.Clear();
	m_PointsBuffer1.SetSize(m_PointsBuffer0.Length());
	
	for(size_t i = 0; i < m_PointsBuffer0.Length(); i++)
		m_PointsBuffer1.Set(i,m_PointsBuffer0.Get(i));
}

void CMapPlugin::CopyShipVerticesBuffer()
{
	m_ShipVerticesBuffer1.Clear();
	m_ShipVerticesBuffer1.SetSize(m_ShipVerticesBuffer0.Length());
	
	for(size_t i = 0; i < m_ShipVerticesBuffer0.Length(); i++)
		m_ShipVerticesBuffer1.Set(i,m_ShipVerticesBuffer0.Get(i));
}

void CMapPlugin::CopyTriangleTriangleIndicesBuffer()
{
	m_TrianglesTriangleIndicesBuffer1.Clear();
	m_TrianglesTriangleIndicesBuffer1.SetSize(m_TrianglesTriangleIndicesBuffer0.Length());
	
	for(size_t i = 0; i < m_TrianglesTriangleIndicesBuffer0.Length(); i++)
		m_TrianglesTriangleIndicesBuffer1.Set(i,m_TrianglesTriangleIndicesBuffer0.Get(i));
}

void CMapPlugin::CopyTriangleLineIndicesBuffer()
{
	m_TrianglesLineIndicesBuffer1.Clear();
	m_TrianglesLineIndicesBuffer1.SetSize(m_TrianglesLineIndicesBuffer0.Length());
	
	for(size_t i = 0; i < m_TrianglesLineIndicesBuffer0.Length(); i++)
		m_TrianglesLineIndicesBuffer1.Set(i,m_TrianglesLineIndicesBuffer0.Get(i));
}


void CMapPlugin::CopyTriangleVerticesBuffer()
{
	m_TriangleVerticesBuffer1.Clear();
	m_TriangleVerticesBuffer1.SetSize(m_TriangleVerticesBuffer0.Length());
	
	for(size_t i = 0; i < m_TriangleVerticesBuffer0.Length(); i++)
		m_TriangleVerticesBuffer1.Set(i,m_TriangleVerticesBuffer0.Get(i));
}

void CMapPlugin::CopyShipTriangleIndicesBuffer()
{
	m_ShipTriangleIndicesBuffer1.Clear();
	m_ShipTriangleIndicesBuffer1.SetSize(m_ShipTriangleIndicesBuffer0.Length());
	
	for(size_t i = 0; i < m_ShipTriangleIndicesBuffer0.Length(); i++)
		m_ShipTriangleIndicesBuffer1.Set(i,m_ShipTriangleIndicesBuffer0.Get(i));
}

void CMapPlugin::CopyShipLineIndicesBuffer()
{
	m_ShipLineIndicesBuffer1.Clear();
	m_ShipLineIndicesBuffer1.SetSize(m_ShipLineIndicesBuffer0.Length());
	
	for(size_t i = 0; i < m_ShipLineIndicesBuffer0.Length(); i++)
		m_ShipLineIndicesBuffer1.Set(i,m_ShipLineIndicesBuffer0.Get(i));
}

/*
void CMapPlugin::CopyTriangleTexCoordsBuffer()
{
	m_TriangleTexCoordsBuffer1.Clear();
	m_TriangleTexCoordsBuffer1.SetSize(m_TriangleTexCoordsBuffer0.Length());
	
	for(size_t i = 0; i < m_TriangleTexCoordsBuffer0.Length(); i++)
		m_TriangleTexCoordsBuffer1.Set(i,m_TriangleTexCoordsBuffer0.Get(i));
}
*/

void CMapPlugin::CopyAtonTriangleBuffer()
{
	m_AtonTriangleBuffer1.Clear();
	m_AtonTriangleBuffer1.SetSize(m_AtonTriangleBuffer0.Length());
	
	for(size_t i = 0; i < m_AtonTriangleBuffer0.Length(); i++)
		m_AtonTriangleBuffer1.Set(i,m_AtonTriangleBuffer0.Get(i));
}

void CMapPlugin::CopyShipNamesBuffer()
{
	m_ShipNamesBuffer1.Clear();
	m_ShipNamesBuffer1.SetSize(m_ShipNamesBuffer0.Length());
	
	for(size_t i = 0; i < m_ShipNamesBuffer0.Length(); i++)
		m_ShipNamesBuffer1.Set(i,m_ShipNamesBuffer0.Get(i));
}


void CMapPlugin::PreparePointsBuffer(SAisData *ptr)
{
	nvPoint2d pt;
	
	m_Broker->Unproject(ptr->lon, -ptr->lat, &pt.x, &pt.y);							// pozycja y statku na mapie
	double Distance = nvDistance( ptr->lon, ptr->lat, ptr->lon + 1.0, ptr->lat );	// ilo�� mil na stopie� w aktualnej pozycji y
		
	m_PointsBuffer0.Append(pt);
	
}

void CMapPlugin::PrepareAtonTriangleBuffer(SAisData *ptr)
{
	if(!ptr->valid_pos)
		return;

	if(ptr->valid[AIS_MSG_21])
	{
		double to_x, to_y;
		nvPoint2d pt;
		pt.x = ptr->lon;
		pt.y = -ptr->lat;
		nvPoint2d p1, p2, p3, p4;
		
		m_Broker->Unproject(pt.x, pt.y,&to_x,&to_y);
		pt.x = to_x;
		pt.y = to_y;
		
		double width = ATON_WIDTH/m_SmoothScaleFactor;
		double height = ATON_HEIGHT/m_SmoothScaleFactor;
			
		p1.x = -0.5 * width;	p1.y =  0.5 * height;
		p2.x =  0.5 * width;	p2.y =  0.5 * height;
		p3.x =  0.5 * width;	p3.y = -0.5 * height;
		p4.x = -0.5 * width;	p4.y = -0.5 * height;

		p1.x += pt.x; p1.y += pt.y;
		p2.x += pt.x; p2.y += pt.y;
		p3.x += pt.x; p3.y += pt.y;
		p4.x += pt.x; p4.y += pt.y;
	
		m_AtonTriangleBuffer0.Append(p1);
		m_AtonTriangleBuffer0.Append(p2);
		m_AtonTriangleBuffer0.Append(p3);
		m_AtonTriangleBuffer0.Append(p4);

	}
}

void CMapPlugin::PrepareTriangleVerticesBuffer(SAisData *ptr)
{
	if(!ptr->valid_pos)
		return;
	if(ptr->valid[AIS_MSG_21])
		return;

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
			
	p1.x = -0.5 * width;	p1.y =  1.0 * height;
	p2.x =  0.0 * width;	p2.y =	-1.0 * height;
	p3.x =  0.5 * width;	p3.y =  1.0 * height;
				
	//obr�t
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
// indexy verteks�w dla ma�ych tr�jkacik�w
void CMapPlugin::PrepareTriangleTriangleIndicesBuffer(SAisData *ptr)
{
	if(!ptr->valid_pos)
		return;
	if(ptr->valid[AIS_MSG_21])
		return;
	
	int id = m_TriangleVerticesBuffer0.Length();

	//1
	m_TrianglesTriangleIndicesBuffer0.Append(id - 3);	//0
	m_TrianglesTriangleIndicesBuffer0.Append(id - 2);	//1
	m_TrianglesTriangleIndicesBuffer0.Append(id - 1);	//2

	
}

void CMapPlugin::PrepareTriangleLineIndicesBuffer(SAisData *ptr)
{
	if(!ptr->valid_pos)
		return;
	if(ptr->valid[AIS_MSG_21])
		return;
	
	int id = m_TriangleVerticesBuffer0.Length();

	//1
	m_TrianglesLineIndicesBuffer0.Append(id - 3);	//0
	m_TrianglesLineIndicesBuffer0.Append(id - 2);	//1
	
	m_TrianglesLineIndicesBuffer0.Append(id - 2);	//1
	m_TrianglesLineIndicesBuffer0.Append(id - 1);	//2

	m_TrianglesLineIndicesBuffer0.Append(id - 1);	//2
	m_TrianglesLineIndicesBuffer0.Append(id - 3);	//0
	
}


void CMapPlugin::PrepareShipVerticesBuffer(SAisData *ptr)
{

	if(!ptr->valid_dim || !ptr->valid_pos)
		return;
	
	nvPoint2d pt;
	pt.x = ptr->lon;
	pt.y = -ptr->lat;
	
	double yDistance = nvDistance( pt.x, pt.y, pt.x + 1.0, pt.y );	// ilo�� mil na stopie� w aktualnej pozycji y
	double to_bow, to_stern, to_port, to_starboard;
	nvPoint2d p1, p2, p3, p4, p5, p6, p7;
		
	to_bow = (double)ptr->to_bow/1852/yDistance; to_stern = (double)ptr->to_stern/1852/yDistance; to_port = (double)ptr->to_port/1852/yDistance; to_starboard = (double)ptr->to_starboard/1852/yDistance;
			
	double width = to_port + to_starboard;
	double height = to_bow + to_stern;
			
	//wymiary rzeczywiste
	p1.x = -0.5 * width;	p1.y =  0.5    * height;	
	p2.x =  0.5 * width;	p2.y =  0.5    * height; 
	p3.x =  0.5 * width;	p3.y = -0.3    * height;	
	p4.x =  0.3 * width;	p4.y = -0.425  * height;
	p5.x =  0.0;			p5.y = -0.5    * height;
	p6.x = -0.3 * width;	p6.y = -0.425  * height;
	p7.x = -0.5 * width;	p7.y = -0.3    * height;
		
	double vx = (to_port - to_starboard)/2;
	double vy = (to_bow - to_stern)/2;
	
	//pozycja GPSa
	p1.x -= vx; p1.y -= vy;
	p2.x -= vx; p2.y -= vy;
	p3.x -= vx; p3.y -= vy;
	p4.x -= vx; p4.y -= vy;
	p5.x -= vx; p5.y -= vy;
	p6.x -= vx; p6.y -= vy;
	p7.x -= vx; p7.y -= vy;

	//obr�t
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
	if(ptr->valid_dim && ptr->valid_pos)
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
}

void CMapPlugin::PrepareShipLineIndicesBuffer(SAisData *ptr)
{
	if(ptr->valid_dim && ptr->valid_pos)
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
}

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




void CMapPlugin::DeleteShipsVBO()
{
	glDeleteBuffers(1, &m_ShipsArrayBuffer);
	glDeleteBuffers(1, &m_ShipsTriangleIndicesBuffer);
	glDeleteBuffers(1, &m_ShipsLineIndicesBuffer);
	
}

void CMapPlugin::DeleteTrianglesVBO()
{
	glDeleteBuffers(1, &m_TrianglesArrayBuffer);
	glDeleteBuffers(1, &m_TrianglesTriangleIndicesBuffer);
	glDeleteBuffers(1, &m_TrianglesLineIndicesBuffer);
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
    vect2 *Positions = (vect2*)malloc( CaptionsSize *sizeof( vect2 ) );    // cz�� ca�kowita jednostki sondowania
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
		CaptionsStr[i] = m_CurrentShipNamesBufferPtr->Get(i);   // bez kopiowania �a�cucha!!! 
		Angle[i] = m_Broker->GetAngle();
    }

	m_Font->Clear();
    m_Font->PrintList( Positions, Scale, Angle, CaptionsStr, CaptionsSize, vx, vy );
	m_Font->ClearBuffers();
	m_Font->CreateBuffers();
	m_Font->Render();

	free( CaptionsStr );    // �a�cuchy nie zosta�y skopiowane, nie ma konieczno�ci zwalniania ca�ej listy
    free( Positions );
    free( Scale );
    free( Angle );
    free( vx );
    free( vy );
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

bool CMapPlugin::CreateTrianglesVBO()
{
					
	//tr�jkaty
	glGenBuffers(1, &m_TrianglesArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentTriangleVerticesBufferPtr->Length(), m_CurrentTriangleVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glGenBuffers(1, &m_TrianglesTriangleIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesTriangleIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentTrianglesTriangleIndicesBufferPtr->Length(), m_CurrentTrianglesTriangleIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glGenBuffers(1, &m_TrianglesLineIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesLineIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentTrianglesLineIndicesBufferPtr->Length(), m_CurrentTrianglesLineIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	return true;
			
}


bool CMapPlugin::CreateShipsVBO()
{
		
	//statki
	glGenBuffers(1, &m_ShipsArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_ShipsArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentShipVerticesBufferPtr->Length(), m_CurrentShipVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glGenBuffers(1, &m_ShipsTriangleIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsTriangleIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentShipTriangleIndicesBufferPtr->Length(), m_CurrentShipTriangleIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_ShipsLineIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsLineIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentShipLineIndicesBufferPtr->Length(), m_CurrentShipLineIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
		
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	return true;
			
}


void CMapPlugin::RenderPoints()
{

}

void CMapPlugin::RenderTriangles()
{
	glEnableClientState(GL_VERTEX_ARRAY);
				
	glBindBuffer(GL_ARRAY_BUFFER, m_TrianglesArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);

	//wypelnienie
	glColor4f(0.0,1.0,0.0,0.4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_CurrentTrianglesTriangleIndicesBufferPtr->Length(), GL_UNSIGNED_INT,0);

	// obrys (linie)
	glColor4f(0.0,0.0,0.0,0.9);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TrianglesLineIndicesBuffer);
	glDrawElements(GL_LINES, m_CurrentTrianglesLineIndicesBufferPtr->Length(), GL_UNSIGNED_INT,0);

	glDisableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}


void CMapPlugin::RenderShips()
{
	glEnableClientState(GL_VERTEX_ARRAY);
		
	//statki
	glBindBuffer(GL_ARRAY_BUFFER, m_ShipsArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);
	
	// wype�nienie (tr�jk�ty)
	glColor4f(0.0,0.0,0.0,0.6);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsTriangleIndicesBuffer);
	glDrawElements(GL_TRIANGLES, m_CurrentShipTriangleIndicesBufferPtr->Length(), GL_UNSIGNED_INT,0);

	// obrys (linie)
	glColor4f(0.0,0.0,0.0,0.9);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ShipsLineIndicesBuffer);
	glDrawElements(GL_LINES, m_CurrentShipLineIndicesBufferPtr->Length(), GL_UNSIGNED_INT,0);

	
	glDisableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

void  CMapPlugin::RenderSelection()
{
	if(m_SelectedVertexId == -1)
		return;
	
	if(m_CurrentTriangleVerticesBufferPtr->Length() > 0)
	{
		nvPoint2d pt0 = m_CurrentTriangleVerticesBufferPtr->Get(m_SelectedVertexId);
 		nvPoint2d pt1 = m_CurrentTriangleVerticesBufferPtr->Get(m_SelectedVertexId + 1);
		nvPoint2d pt2 = m_CurrentTriangleVerticesBufferPtr->Get(m_SelectedVertexId + 2);
				
		double size = 10.0/m_SmoothScaleFactor;
		//glBegin(GL_);
			//glVertex2d(pt0.x, pt0.y);
			//glVertex2d(pt0.x + size,pt0.y);
			//glVertex2d(pt0.x, pt0.y);
			//glVertex2d(pt0.x ,pt0.y + size);

			//glVertex2d(pt1.x, pt1.y);
			//glVertex2d(pt1.x - size,pt1.y);
			//glVertex2d(pt1.x, pt1.y);
			//glVertex2d(pt1.x ,pt1.y + size);

			//glVertex2d(pt2.x,pt2.y);
			//glVertex2d(pt2.x + size,pt2.y);
			//glVertex2d(pt2.x,pt2.y);
			//glVertex2d(pt2.x ,pt2.y - size);
		//glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
			
			glColor3f(1.0,0.0,0.0);
			glVertex2d(pt0.x,pt0.y);
			
			glColor3f(0.0,1.0,0.0);
			glVertex2d(pt1.x,pt1.y);
			
			glColor3f(0.0,0.0,1.0);
			glVertex2d(pt2.x,pt2.y);
		
			glEnd();
		glPointSize(1);

	}
	
}

void CMapPlugin::Render()
{
		
	SetValues();
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	//glLineWidth(2);

	
	//wxMutexLocker locker(*GetMutex());
	
	if(IsShipBuffer())
	{
		CreateShipsVBO();
		RenderShips();
		DeleteShipsVBO();
	}
	
	if(IsTriangleBuffer())
	{
		CreateTrianglesVBO();
		RenderTriangles();
		DeleteTrianglesVBO();
	}

	glColor4f(1.0,0.0,0.0,0.8);
	glPointSize(4);
			
	RenderGeometry(GL_POINTS,m_CurrentPointsBufferPtr->GetRawData(),m_CurrentPointsBufferPtr->Length()); //miejsce przyczepienia GPS
		
	//if(m_MapScale > 20000.0)
		//RenderShipNames();
	
	//RenderSelection();
	//glPointSize(1);
	//glLineWidth(1);

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	
	m_OldMapScale = m_MapScale;
	
		
}

void CMapPlugin::SetValues()
{
	double mom[2];
	double _x,_y;
	
	// kolejnosc wa�na
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

//	NaviApiMenu = new CNaviApiMenu( L"Settings" );	// nie u�uwa� delete - klasa zwalnia obiejt automatycznie
//	NaviApiMenu->AddItem( L"Device Manager",this, MenuConfig );
	
}

void CMapPlugin::Config()
{

}

void CMapPlugin::OnZoom(double Scale)
{
	SetValues();
	RunThread();
	//fprintf(stdout
}

void CMapPlugin::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
		
	if(!lmb)
		return;

	RunThread();

	SetValues();
						
	if(m_CurrentTriangleVerticesBufferPtr == NULL)
		return;
	
	/*
	nvPoint2d *RawPt  = m_CurrentTriangleVerticesBufferPtr->GetRawData();
	
	for (size_t i = 0; i < m_CurrentTriangleVerticesBufferPtr->Length(); i+=3)
	{

		nvPoint2f pt;
		pt.x = m_MapX;
		pt.y = m_MapY;
		
		nvPoint2f pt0,pt1,pt2,pt3;
				
		pt0.x = RawPt[i].x;	pt0.y = RawPt[i].y;
		pt1.x = RawPt[i + 1].x;	pt1.y = RawPt[i + 1].y;
		pt2.x = RawPt[i + 2].x;	pt2.y = RawPt[i + 2].y;
				
		
		fprintf(stdout,"%f %f\n",m_MapX,m_MapY);
		
		if(IsPointInTriangle(&pt,&pt0,&pt1,&pt2))
		{
			m_SelectedVertexId = i;
			return;
		}
		
	}

	m_SelectedVertexId = -1;
	*/
	
	
	
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
	PrepareBuffer();
}

void CMapPlugin::ThreadEnd()
{
	//m_Broker->Refresh(m_Broker->GetParentPtr());
}

//bool CMapPlugin::VisibleStateChanged()
//{
	//if(m_MapScale != m_OldMapScale)
		//return true;
	
	//return false;

//}

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
