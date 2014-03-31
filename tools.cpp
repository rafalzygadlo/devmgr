#include "conf.h"
#include "tools.h"
#include <wx/stdpaths.h>
#include "protocol.h"
#include "GeometryTools.h"

wxMutex *mutex = NULL;
int GlobalLanguageID;
bool m_HDT_Exists = false;
int m_HDT_Counter = 0;
SFrequency FrequencyTable;
int MaxFrequency  = 0;
//float m_FontSize;
//bool m_ShowNames;


const wchar_t *nvLanguage[2][183] = 
{ 
	/*EN*/
	{
		_("Name"),
		_("Port"),
		_("Baud"),
		_("Port scanning on demand.\nWe do not check the available ports automatically because for some devices such as bluetooth,\nit takes a long time and it looks as if the program has crashed.\nThat's why we provide manual search for ports."),
		_("Scan for available ports"),
		_("Ok"),
		_("Cancel"),
		_("Scaning ports. Please wait."),
		_("Devices"),
		_("New Device..."),
		_("Start"),
		_("Stop"),
		_("Configure Device"),
		_("Configure Data"),
		_("Status"),
		_("Uninstall"),
		_("Stop The Device"),
		_("Stoping devices and freeing the resources.\nPlease wait this will take some time."),
		_("Connected"),
		_("Running"),
		_("New"),
		_("Delete"),
		_("Device Types..."),
		_("Device Type"),
		_("Disconected"),
		_("Device Wizard"),
		_("Monitor"),
		_("Close"),
		_("Next >"),
		_("< Prev"),
		_("Finish"),
		_("Scanning %s %d\n"),
		_("No devices found"),
		_("Found %d device(s)"),
		_("Selected device(s) %d"),
		_("Internet Connection"),
		_("Serial Connection"),
		_("Host"),
		_("Ais Objects"),
		_("MMSI"),
		_("Name"),

		_("Position Report"),								//1
		_("Position Report"),								//2
		_("Position Report"),								//3
		_("Base Station Report UTC/Date Response "),		//4
		_("Ship static and voyage related data"),			//5
		_("Addressed Binary Message"),						//6
		_("Binary acknowledge. Safety Related Acknowledge"),//7
		_("Binary Broadcast Message"),						//8
		_("Standard SAR Aircraft Position Report"),			//9
		_("UTC/Date inquiry"),								//10
		_("Base Station Report UTC/Date Response"),			//11
		_("Safety Related Message"),						//12
		_("Binary acknowledge. Safety Related Acknowledge"),//13
		_("Safety Related Broadcast Message"),				//14
		_("Interrogation"),									//15
		_("Assigned Mode Command"),							//16
		_("GNSS Broadcast Binary Message"),					//17
		_("Standard Class B CS Position Report"),			//18
		_("Extended Class B CS Position Report"),			//19
		_("Data Link Management Message"),					//20
		_("Aid-to-Navigation Report"),						//21
		_("Channel Management"),							//22
		_("Group Assignment Command"),						//23
		_("Class B CS Static Data Report"),					//24
		_("Binary Message, Single Slot"),					//25
		_("Binary Message, Multiple Slot"),					//26
		_("Long Range AIS Broadcast message"),				//27

		_("Position Accuracy"),					
		_("True"),						
		_("False"),						
		_("N/A"),							
		_("COG"),
		_("HDT"),
		_("Latitude"),
		_("Longitude"),
		_("Maneuver Indicator"),
		_("Radio status"),
		_("RAIM flag"),
		_("Second of UTC timestamp"),
		_("Speed"),
		_("Navigation Status"),
		_("ROT"),
		_("Turning left at more than 5deg/30s (No TI available)"),
		_("Turning right at more than 5deg/30s (No TI available)"),
		_("Turning left at up to 708 degrees per minute or higher"),
		_("Turning right at up to 708 degrees per minute or higher"),
		_("Year (UTC)"),
		_("Month (UTC)"),
		_("Day (UTC)"),
		_("Hour (UTC)"),
		_("Minute (UTC)"),        
		_("Second (UTC)"),
		_("EPFD Fix Types"),
		_("Ais version"),
		_("Callsign"),
		_("ETA Month (UTC)"),
		_("ETA Day (UTC)"),
		_("ETA Hour (UTC)"),
		_("ETA Minute (UTC)"),
		_("Destination"),
		_("Ship type"),
		_("IMO Number"),
		_("Dimension to Bow"),
		_("Dimension to Stern"),
		_("Dimension to Port"),
		_("Dimension to Starboard"),
		_("Draught"),
		_("DTE"),
		_("Length/Width"),
		_("Messages"),
		_("Top"),
		_("Designated Area Code"),
		_("Functional ID"),
		_("European Vessel ID"),
		_("Length of ship"),
		_("Beam of ship"),
		_("Ship/combination type"),
		_("Hazardous cargo"),
		_("Loaded/Unloaded"),
		_("Speed inf. quality"),
		_("Course inf. quality"),
		_("Heading inf. quality"),
		_("Average Wind Speed"),
		_("Gust Speed"),
		_("Wind Direction"),
		_("Wind Gust Direction"),
		_("Air Temperature"),
		_("Relative Humidity"),
		_("Dew Point"),
		_("Air Pressure"),
		_("Pressure Tendency"),
		_("Horizontal Visibility"),
		_("Water Level"),
		_("Water Level Trend"),
		_("Surface Current Speed"),
		_("Surface Current Direction"),
		_("Wave height"),
		_("Wave period"),
		_("Wave direction"),
		_("Options"),
		_("Show names"),
		_("Font size"),
		_("Show COG"),
		_("Show HDT"),
		_("Ship color 0"),
		_("Ship color 1"),
		_("Ship color 2"),
		_("Aton color"),
		_(".."),

	},
	
	/*PL*/
	{
		_("Abc"),

	}

};

double _nvToRad( double angle ) 
{
	return angle * nvPI / 180.0f;
}

int GetLanguageId()
{
	return GlobalLanguageID;
}

wxString GetProductInfo()
{
	return wxString::Format(_("%s %s\n%s"),_(PRODUCT_NAME),_(PRODUCT_VERSION),_(PRODUCT_COPYRIGHT));
}

wxString GetProductName()
{
	return wxString::Format(_("%s %s"),_(PRODUCT_NAME),_(PRODUCT_VERSION));
}

const wchar_t *GetMsg(int id)
{
	return nvLanguage[GlobalLanguageID][id];
}

wxString GetPluginConfigPath()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir(),wxT(DIR_SEPARATOR),_(PLUGIN_CONFIG_FILE));
}

void PrintInfo(CNaviBroker *Broker,wchar_t *text)
{
	// 9 id chart_catalogu
//	if(Broker != NULL)
//		Broker->PrintInfoBlock(Broker->GetParentPtr(), 13 , text, 10);

}

wxString GetWorkDir(void)
{
	static wxString buffer;
	wxStandardPaths *Paths = new wxStandardPaths();
 	buffer.Printf(wxT("%s%s%s"), Paths->GetUserDataDir().wc_str(),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR) );
	delete Paths;
	return buffer;
}

/*
CReader *CreateNewDevice(wxString name, char *port, int baud, bool run, int type)
{
	CReader *Serial = new CReader();
	Serial->SetBaud(baud);
	Serial->SetPort(port);
	Serial->SetDeviceName(name);
	Serial->SetRunOnStart(run);
	Serial->SetDeviceType(type);
	Serial->SetDefinition();
	Serial->SetParseLine(true);
	
	return Serial;

}
*/

CReader *CreateSerialDevice(wxString name, char *port, int baud, int dtype, bool run)
{
	CReader *ptr = new CReader();
	ptr->SetConnectionType(CONNECTION_TYPE_SERIAL);
	ptr->SetDeviceType(dtype);
	ptr->SetBaud(baud);
	ptr->SetPort(port);
	ptr->SetDeviceName(name);
	ptr->SetRunOnStart(run);
	ptr->SetParseLine(true);
	ptr->SetDefinition();
	ptr->SetCheckCRC(true);
	return ptr;

}

CReader *CreateSocketDevice(wxString name, wxString host, int port, int dtype, bool run)
{
	CReader *ptr = new CReader();
	ptr->SetConnectionType(CONNECTION_TYPE_SOCKET);
	ptr->SetDeviceType(dtype);
	ptr->SetHost(host.char_str());
	ptr->SetPort(port);
	ptr->SetDeviceName(name);
	ptr->SetRunOnStart(run);
	ptr->SetParseLine(true);
	ptr->SetDefinition();
	ptr->SetCheckCRC(true);
	return ptr;

}


char **ExplodeStr(const char *str, const char *separator, int *size) 
{

	size_t seplen = strlen(separator);	// d³ugoœæ separatora
	size_t start = 0;
	char **List = NULL;
	char *Element;

	*size = 0;
	for(size_t i=0; i < strlen(str); i++ ) {

		if( memcmp(str + i, separator, seplen) == 0 ) {

			*size = *size + 1;
			List = (char**)realloc(List, *size * (sizeof(*List)) );
			size_t ElementLen = strlen(str) - start;
			Element = (char*)malloc( ElementLen * sizeof( char ) );
			memset(Element, 0, ElementLen * sizeof( char ) );
			int id = 0;
			for(size_t j = start; j < i; j++ ) {

				Element[id] = str[j];
				id++;
			};
			start = i + seplen;
			List[ *size - 1] = Element;
		};
	};

	// ostatni element ,xxx
	if( strlen(str) > 0 ) {
		*size = *size + 1;
		List = (char**)realloc(List, *size * (sizeof(*List)) );
		size_t ElementLen = strlen(str) - start + 1;
		Element = (char*)malloc( ElementLen * sizeof( char ) );
		memset(Element, 0, ElementLen * sizeof( char ) );
		int id = 0;
		for(size_t j = start; j < strlen(str); j++ ) {

			Element[id] = str[j];
			id++;
		};
		List[ *size - 1] = Element;
	};

	return List;

};

void FreeStrList(char **list, int length) 
{

	for( int i = 0; i < length; i++ )
		free( list[i] );

	free(list);
};

char *GetSentenceFromLine(const char *line, const char *identyfier) 
{

	int IdentSuplement = 5 - (int)strlen(identyfier);	// uzupe³nienie wycinania w przypadku gdy nie podano identyfikatora w ca³oœci (5 znaków)
	int ValidSentenceLen = (int)strlen(line) - ((int)strlen(identyfier) + 2) - 3 - IdentSuplement;
	if(ValidSentenceLen < 0)
		return NULL;
	
	char *ValidSentence = (char*)malloc( ValidSentenceLen + 1 );

	memcpy( ValidSentence, line + strlen(identyfier) + 2 + IdentSuplement, ValidSentenceLen );
	ValidSentence[ ValidSentenceLen ] = 0; 

	return ValidSentence;

};

int MemPos(const unsigned char *Memory, int MemorySize, const unsigned char *Search, int SearchSize, int StartAt ) 
{

	int Len = MemorySize - SearchSize;
	for( int i = StartAt; i < Len + 1; i++ ) {

		if( memcmp( Memory + i, Search, SearchSize ) == 0 )
			return i;

	};

	return -1;
};

void FreeMutex()
{
	if(mutex)
		delete mutex;
	mutex = NULL;
}
void InitMutex()
{
	mutex = new wxMutex();
}

wxMutex *GetMutex()
{
	return mutex;
}

bool SetGlobalPrioryty(int fid)
{
	switch(fid)
	{
		case SIGNAL_HDT:
			m_HDT_Exists = true; 
			m_HDT_Counter = 30;
			return true;
		break;
		
		case SIGNAL_RMC_COG:
			return Set_RMC_COG();
		break;
		
		case SIGNAL_VTG_COG:
			return Set_VTG_COG();
		break;
	}
	
	// dla innych zawsze true
	return true;
}

bool Check_HDT()
{
	m_HDT_Counter--;

	if(m_HDT_Counter < 0)
	{
		m_HDT_Exists = false;
		return false;
	}else{
		return true;
	}
}

bool Set_VTG_COG()
{
	Check_HDT();
	
	if(m_HDT_Exists)
		return false;
	else
		return true;
}

bool Set_RMC_COG()
{
	Check_HDT();

	if(m_HDT_Exists)
		return false;
	else
		return true;
}

void Reset(double *tab)
{
	tab[0] = UNDEFINED_DOUBLE;
	tab[1] = UNDEFINED_DOUBLE;
	tab[2] = UNDEFINED_DOUBLE;
	tab[3] = UNDEFINED_DOUBLE;
	tab[4] = UNDEFINED_DOUBLE;
	tab[5] = UNDEFINED_DOUBLE;
}

bool IsUndefined(double *idx, size_t size)
{
	
	for(size_t i = 0; i < size; i++)
	{
		if(UNDEFINED_VAL(idx[i]))
			return true;
	}
	
	return false;

}

void RotateZ( double x, double y, double &out_x, double &out_y, double radangle) 
{
	out_x = (x * cos( radangle )) - (y * sin( radangle ) );
	out_y = (x * sin( radangle )) + (y * cos( radangle ) );
}

double nvDistance(double lon1, double lat1, double lon2, double lat2, int distanceunit) 
{

	double dLat = nvToRad( lat2 - lat1 );
	double dLon = nvToRad( lon2 - lon1 );
	double R = 6371.0;

	double a = ( sin(dLat/2) * sin(dLat/2) )  +  ( cos( nvToRad(lat1) ) * cos( nvToRad(lat2) ) * sin(dLon/2) * sin(dLon/2) );
	double c = 2 * atan2( sqrt(a), sqrt( 1 - a ) );

	switch( distanceunit ) 
	{
		case nvKilometer: return R * c;
		case nvNauticMiles: return (R *c) / 1.852;
		case nvMeter : return R * c * 1000;
		default:
			return (R *c) / 1.852;
	}
}

// index w tablicy SetShip
void SetFrequencyTable(int id)
{
	int time = GetTickCount();
	int tick = time - FrequencyTable.time[id];
		
	FrequencyTable.frequency[id] = tick;
	FrequencyTable.time[id] = time;
	
	MaxFrequency = DEFAULT_FREQUENCY * 10; //10 sekund
	for(size_t i = 0; i < MAX_SHIP_VALUES_LEN; i++)
	{
		if(MaxFrequency > FrequencyTable.frequency[i])
			MaxFrequency = FrequencyTable.frequency[i];
	}
	
}

int GetFrequency(int id)
{
	return FrequencyTable.frequency[id];
}

int GetMaxFrequency()
{
	return MaxFrequency;
}

void NewLonLat(int seconds, double lon, double lat, double sog, double cog, double *new_lon, double *new_lat)
{
	
	double _sec = (double)seconds;
		
	//sog = 1000.0;
	cog = cog - 180;

	double rad360 = 2 * nvPI / 360.0;
	double sogm = (1852.0 /3600) * sog;
	double dlatm = (sogm * cos ( 2 * nvPI - cog * rad360 )) * _sec;
	double dlonm = (sogm * sin ( 2 * nvPI - cog * rad360 )) * _sec;
	double lonDistance = nvDistance( lon, lat, lon + 1.0 , lat);
	double latDistance = nvDistance( lon, lat, lon , lat + 1.0);
		
	double nlon = lon + dlonm / (lonDistance * 1852.0);	// sta³a iloœæ km na 1 stopien
	double nlat = lat + dlatm / (latDistance * 1852.0);	// sta³a iloœæ km na 1 stopien
			
	// przypisz nowe wartosci 
	*new_lon = nlon;
	*new_lat = nlat;
	
}

bool IsPointInsideMesh(nvPoint2f *point, nvPoint2d *points, int points_length, int *indices, int indices_length )
{
	for(size_t i = 0; i < indices_length; i+=3)
	{
		nvPoint2d p0 = points[indices[i]];
		nvPoint2d p1 = points[indices[i + 1]];
		nvPoint2d p2 = points[indices[i + 2]];
		
		if(IsPointInTriangle(point,(nvPoint2f*)&p0,(nvPoint2f*)&p1,(nvPoint2f*)&p2))
			return true;
	}
	
	return false;

}
wxString ConvertDegree(float degree) 
{
	int decimal = (int)degree;
    double minutes = (float)(degree - decimal) * 60;
    double second = (float)(minutes - (int)(minutes)) * 60;
	return wxString::Format(_("%02d° %02d' %02.2f''"),decimal, (int)minutes, second);
      
}

wxString FormatLongitude(float x) 
{
      wxString str;

      if(x == 0)
		  return str = wxString::Format(_("%s"), ConvertDegree(0).wc_str());
	  
	  if (x > 0.0f) 
	  {
        if (x <= 180.0f)
			str = wxString::Format(_("%s E"), ConvertDegree(x).wc_str());
        else
			str = wxString::Format(_("%s W"), ConvertDegree(360 - x).wc_str());
      } else {
        if (x >= -180.0f)
			str = wxString::Format(_("%s W"), ConvertDegree(-x).wc_str());
        else
			str = wxString::Format(_("%s E"), ConvertDegree(x+360).wc_str());
            
      }
      return str;
}

wxString FormatLatitude(float y) 
{
	
	wxString str;
	 if(y == 0)
		  return str = wxString::Format(_("%s"), ConvertDegree(0).wc_str());

    if (y > 0)
		str = wxString::Format(_("%s N"), ConvertDegree(y).wc_str());
    else
		str = wxString::Format(_("%s S"), ConvertDegree(-y).wc_str());

    return str;

}

double GetMilesPerDegree(double x, double y)
{
	return nvDistance( x, y, x + 1.0, y );	// iloœæ mil na stopieñ w aktualnej pozycji y
}

double ToBow(SAisData *ptr)
{
	return  (double)ptr->to_bow/1852/GetMilesPerDegree(ptr->lon,-ptr->lat); 
}

double ToStern(SAisData *ptr)
{
	return (double)ptr->to_stern/1852/GetMilesPerDegree(ptr->lon,-ptr->lat); 
}

double ToPort(SAisData *ptr)
{
	return (double)ptr->to_port/1852/GetMilesPerDegree(ptr->lon,-ptr->lat); 
}

double ToStarboard(SAisData *ptr)
{
	return (double)ptr->to_starboard/1852/GetMilesPerDegree(ptr->lon,-ptr->lat); 
}

double GetShipHeight(SAisData *ptr)
{
	return ToBow(ptr) + ToStern(ptr);
}

double GetShipWidth(SAisData *ptr)
{
	return ToPort(ptr) + ToStarboard(ptr);
}

double GetTriangleHeight(double smooth_scale)
{
	return SHIP_TRIANGLE_HEIGHT/smooth_scale;
}

double GetTriangleWidth(double smooth_scale)
{
	return SHIP_TRIANGLE_WIDTH/smooth_scale;
}

wxString GetAisFile()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir().wc_str(),wxT(DIR_SEPARATOR),wxT(AIS_FILE));
}

wxString RGBAToStr(nvRGBA *RGB) 
{
	return wxString::Format(_("%03d%03d%03d%03d"), RGB->R, RGB->G, RGB->B,RGB->A);
}

nvRGBA StrToRGBA(wxString str) {

	nvRGBA RGB;
	
	wxString str1; 
	
	str1 = str.substr(0,3);	RGB.R = atoi(str1.char_str());
	str1 = str.substr(3,3);	RGB.G = atoi(str1.char_str());
	str1 = str.substr(6,3);	RGB.B = atoi(str1.char_str());
	str1 = str.substr(9,3);	RGB.A = atoi(str1.char_str());

	return RGB;
};