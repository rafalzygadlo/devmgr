#include "conf.h"
#include "tools.h"
#include <wx/stdpaths.h>
#include "protocol.h"
#include "GeometryTools.h"
#include <wx/zipstrm.h>
#include <wx/mstream.h>

wxMutex *mutex = NULL;
wxMutex *smutex = NULL;
int GlobalLanguageID;
bool m_HDT_Exists = false;
int m_HDT_Counter = 0;
SFrequency FrequencyTable;
int MaxFrequency  = 0;
CNaviBroker *Broker = NULL;
double m_SmoothScaleFactor = 0;
int m_SelectedSlot = 0;
int m_SelectedChannel = 0;
int m_SelectedMID = 0;
wxArrayPtrVoid *m_Devices = NULL;
//float m_FontSize;
//bool m_ShowNames;

//deqsdsad
const wchar_t *nvLanguage[][200] = 
{ 
		{L"Name",L"Nazwa"},
		{L"Port",L"Port"},
		{L"Baud",L"Baud"},
		{L"Port scanning on demand.",L"Skanowanie portu na żądanie"},
		{L"Scan for available ports",L"Skanuj w poszukiwaniu portów"},
		{L"Ok",L"OK"},
		{L"Cancel",L"Anuluj"},
		{L"Scaning ports. Please wait.",L"Skanuję porty. Proszę czekać"},
		{L"Devices",L"Urządzenia"},
		{L"New Device...",L"Nowe urządzenie"},
		{L"Start",L"Start"},
		{L"Stop",L"Stop"},
		{L"Configure Device",L"Konfiguruj urządzenie"},
		{L"Configure Data",L"Konfiguruje dane"},
		{L"Status",L"Status"},
		{L"Uninstall",L"Usuń"},
		{L"Stop The Device",L"Zatrzymaj"},
		{L"Stoping devices and freeing the resources.\nPlease wait this will take some time.",L"Zatrzumuję urządzenie i zwalniam zasoby.\nTo może potrwać kilka minut"},
		{L"Connected",L"Połączony"},
		{L"Running",L"Uruchomiony"},
		{L"New",L"Nowy"},
		{L"Delete",L"Usuń"},
		{L"Device Types...",L"Typy urządzeń..."},
		{L"Device Type",L"Typ urządzenia"},
		{L"Disconected",L"Odłączony"},
		{L"Device Wizard",L"Menadżer urządzeń"},
		{L"Monitor",L"Monitoruj"},
		{L"Close",L"Zamnkij"},
		{L"Next >",L"Następny >"},
		{L"< Prev",L"< Poprzedni"},
		{L"Finish",L"Zakończ"},
		{L"Scanning %s %d\n",L"skanuję %s %d\n"},
		{L"No devices found",L"Nie znaleziono urządzeń"},
		{L"Found %d device(s)",L"Znaleziono %d urządzeń"},
		{L"Selected device(s) %d",L"Wybrane urządzenia"},
		{L"Internet Connection",L"Połączenie Internetowe"},
		{L"Serial Connection",L"Połączenie szeregowe"},
		{L"Host",L"Host"},
		{L"Ais Objects (%d)",L"Obiekty AIS (%d)"},
		{L"MMSI",L"MMSI"},
		{L"Name",L"Nazwa"},
		{L"Position Report",L"Raport pozycji"},								//1
		{L"Position Report",L"Raport pozycji"},					//2
		{L"Position Report",L"Raport pozycji"},					//3
		{L"Base Station Report UTC/Date Response",L"Raport stacji bazowej UTC/Data odpowiedzi"},		//4
		{L"Ship static and voyage related data",L"Dane o statu i trasie"},			//5
		{L"Addressed Binary Message",L"Zadresowana Wiadomość Binarna (ABM)"},					//6
		{L"Binary acknowledge. Safety Related Acknowledge",L"Potwierdzenie binarne. Safety Related Message"}, //7
		{L"Binary Broadcast Message",L"BBM"},					//8
		{L"Standard SAR Aircraft Position Report",L"Standard SAR Aircraft Position Report"},			//9
		{L"UTC/Date inquiry",L"Czas UTC/Data zapytania"},							//10
		{L"Base Station Report UTC/Date Response",L"Czas UTC/Data odpowiedź stacji bazowej"},			//11
		{L"Safety Related Message",L"Safety Related Message"},					//12
		{L"Binary acknowledge. Safety Related Acknowledge",L"Binary acknowledge. Safety Related Acknowledge"},//13
		{L"Safety Related Broadcast Message",L"Safety Related Broadcast Message"},			//14
		{L"Interrogation",L"Przesłuchanie"},									//15
		{L"Assigned Mode Command",L"Assigned Mode Command"},						//16
		{L"GNSS Broadcast Binary Message",L"GNSS Broadcast Binary Message"},				//17
		{L"Standard Class B CS Position Report",L"Standard Class B CS Position Report"},			//18
		{L"Extended Class B CS Position Report",L"Extended Class B CS Position Report"},			//19
		{L"Data Link Management Message",L"Data Link Management Message"},					//20
		{L"Aid-to-Navigation Report",L"Aid-to-Navigation Report"},						//21
		{L"Channel Management",L"Channel Management"},							//22
		{L"Group Assignment Command",L"Group Assignment Command"},					//23
		{L"Class B CS Static Data Report",L"Class B CS Static Data Report"},					//24
		{L"Binary Message, Single Slot",L"Binary Message, Single Slot"},					//25
		{L"Binary Message, Multiple Slot",L"Binary Message, Multiple Slot"},					//26
		{L"Long Range AIS Broadcast message",L"Long Range AIS Broadcast message"},			//27
		{L"Position Accuracy",L"Dokładność pozycji"},
		{L"True",L"Prawda"},
		{L"False",L"Fałsz"},
		{L"N/A",L"N/A"},
		{L"COG",L"COG"},
		{L"HDT",L"HDT"},
		{L"Latitude",L"Szerokość"},
		{L"Longitude",L"Długość"},
		{L"Maneuver Indicator",L"Typ manewru"},
		{L"Radio status",L"Status radia"},
		{L"RAIM flag",L"Flaga RAIM"},
		{L"Second of UTC timestamp",L"Drugi znacznik czasu UTC"},
		{L"SOG",L"SOG"},
		{L"Navigation Status",L"Status nawigacyjny"},
		{L"Turn",L"W skręcie"},
		{L"Turning left at more than 5deg/30s (No TI available)",L"Turning left at more than 5deg/30s (No TI available)"},
		{L"Turning right at more than 5deg/30s (No TI available)",L"Turning right at more than 5deg/30s (No TI available)"},
		{L"Turning left at up to 708 degrees per minute or higher",L"Turning left at up to 708 degrees per minute or higher"},
		{L"Turning right at up to 708 degrees per minute or higher",L"Turning right at up to 708 degrees per minute or higher"},
		{L"Year (UTC)",L"Rok UTC"},
		{L"Month (UTC)",L"Miesiąc UTC"},
		{L"Day (UTC)",L"Dzień UTC"},
		{L"Hour (UTC)",L"Godzina UTC"},
		{L"Minute (UTC)",L"Minuta UTC"},
		{L"Second (UTC)",L"Sekunda UTC"},
		{L"EPFD Fix Types",L"EPFD Fix Types"},
		{L"Ais version",L"Wersja AIS"},
		{L"Callsign",L"Callsign"},
		{L"ETA Month (UTC)",L"ETA Miesiąc UTC"},
		{L"ETA Day (UTC)",L"ETA dzień UTC"},
		{L"ETA Hour (UTC)",L"ETA godzina UTC"},
		{L"ETA Minute (UTC)",L"ETA minuta UTC"},
		{L"Destination",L"Port docelowy"},
		{L"Ship type",L"Typ jednostki"},
		{L"IMO",L"IMO"},
		{L"Dimension to Bow",L"Odległość do dziobu"},
		{L"Dimension to Stern",L"Odległość do rufy"},
		{L"Dimension to Port",L"Odległość do lewej burty"},
		{L"Dimension to Starboard",L"Odległość do prawej burty"},
		{L"Draught",L"Zanużenie"},
		{L"DTE",L"DTE"},
		{L"Length/Width",L"Długość/Szerokość"},
		{L"Messages",L"Wiadomości"},
		{L"Top",L"Góra"},
		{L"Designated Area Code",L"Designated Area Code"},
		{L"Functional ID",L"Funkcjonalny ID"},
		{L"European Vessel ID",L"Europejski ID"},
		{L"Length of ship",L"Długość jednostki"},
		{L"Beam of ship",L"Szerokość jednostki"},
		{L"Ship/combination type",L"Typ jednostki"},
		{L"Hazardous cargo",L"Niebezpieczny ładunek"},
		{L"Loaded/Unloaded",L"Załadowany/Pusty"},
		{L"Speed inf. quality",L"Speed inf. quality"},
		{L"Course inf. quality",L"Course inf. quality"},
		{L"Heading inf. quality",L"Heading inf. quality"},
		{L"Average Wind Speed",L"Średnia prędkość wiatru"},
		{L"Gust Speed",L"Prędkość porywów"},
		{L"Wind Direction",L"Kierunek wiatru"},
		{L"Wind Gust Direction",L"Kierunke porywów"},
		{L"Air Temperature",L"Temperatura powietrza"},
		{L"Relative Humidity",L"Wilgotność względna"},
		{L"Dew Point",L"Punkt rosy"},
		{L"Air Pressure",L"Ciśnienie atmosferyczne"},
		{L"Pressure Tendency",L"Tendencja ciśnienia"},
		{L"Horizontal Visibility",L"Widzialność pozioma"},
		{L"Water Level",L"Poziom wody"},
		{L"Water Level Trend",L"Poziom wody - tendencja"},
		{L"Surface Current Speed",L"Prąd powierzchniowy - prędkość"},
		{L"Surface Current Direction",L"Prąd powierzchniowy - kierunek"},
		{L"Wave height",L"Wysokość fali"},
		{L"Wave period",L"Okres fali"},
		{L"Wave direction",L"Kierunek fali"},
		{L"AIS Options",L"Opcje AIS"},
		{L"Show names",L"Pokaż nazwy"},
		{L"Font size",L"Rozmiar czcionki"},
		{L"Show COG",L"Pokaż COG"},
		{L"Show HDT",L"Pokaż HDT"},
		{L"Ship color (moving)",L"Kolor ikony jednsotki (w ruchu)"},
		{L"Ship color (speed < 0.5kn)",L"Kolor ikony jednostki (w ruchu <0.5kts"},
		{L"Ship color (timeout)",L"Kolor ikony jednostki (timeout)"},
		{L"AtoN color",L"Kolor ikony AtoN"},
		{L"..",L".."},
		{L"Simple",L"Prosty"},
		{L"All",L"Wszystko"},
		{L"Options",L"Opcje"},
		{L"Frequency",L"Częstotliwość"},
		{L"View Names Scale",L"Skala czcionki"},
		{L"COG Color",L"Kolor COG"},
		{L"HDT Color",L"Kolor HDT"},
		{L"Show GPS",L"Pokaż GPS"},
		{L"GPS Color",L"Kolor GPS"},
		{L"Show Objects",L"Pokaż obiekty"},
		{L"Flag",L"Flaga"},
		{L"HDT Projection Time",L"Predykcja HDT"},
		{L"COG Projection Time",L"Predykcja COG"},
		{L"COG Line Width",L"Grubość linii COG"},
		{L"HDT Line Width",L"Grubość linii HDT"},
		{L"COG Line Style",L"Styl linii COG"},
		{L"HDT Line Style",L"Styl linii "},
		{L"Solid",L"Ciągła"},
		{L"Dash",L"Przerywana"},
		{L"Ship Border Color",L"Kolor obwiedni jednostki"},
		{L"Altitude",L"Wysokość"},
		{L"Assigned Mode",L"Przypisany tryb"},
		{L"Regional",L"Regionalny"},
		{L"Select All",L"Zaznacz wszystkie"},
		{L"Deselect All",L"Odznacz wszystki"},
		{L"Base Station Color",L"Kolor stacji bazowej"},
		{L"Class A",L"Klasa A"},
		{L"Class B",L"Klasa B"},
		{L"Water Temperature",L"Temperatura wody"},
		{L"Visibility",L"Widzialność"},
		{L"Yes",L"Tak"},
		{L"No",L"Nie"},
		{L"Is Running",L"Działa"},
		{L"Is Connected",L"Podłączony"},
		{L"Bad CRC",L"Nieprawidłowy CRC"},
		{L"Signal quality",L"Jakość sygnału"},
		{L"Show log",L"Pokaż log"},
		{L"VTS Options",L"Opcje VTS"},
		{L"Enable VTS Mode",L"Włącze tryb VTS"},
		{L"CPA [nm]",L"CPA [nm]"},
		{L"TCPA [min]",L"TCPA [min]"},
		{L"Clear",L"Wyczyść"},
		{L"Slot",L"Slot"},
		{L"Channel",L"Kanał"},
		{L"MID",L"MID"},
		{L"Age",L"Wiek"},
		{L"Target timeout",L"Target timout"},
		{L"Target timeout remove",L"Target timeout remove"},
		{L"HDT",L"HDT"},
		{L"ROT",L"ROT"},
		{L"Clear AIS buffer",L"Wyczyść bufor AIS"},
		{L"Target timeouts",L"Target timeouts"},
		{L"Target names",L"Nazwy obiektów"},
		{L"Object options",L"Opcje obiektu"},
		{L"COG Options",L"Opcje COG"},
		{L"HDT Options",L"Opcje HDT"},
		{L"GPS Options",L"Opcje GPS"},

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
	return nvLanguage[id][GlobalLanguageID];
}

wxString GetPluginConfigPath()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir(),wxT(DIR_SEPARATOR),_(PLUGIN_CONFIG_FILE));
}

wxString GetPluginDataFilePath()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir(),wxT(DIR_SEPARATOR),_(PLUGIN_DATA_FILE));
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
	//wxStandardPaths *Paths = new wxStandardPaths();
	wxStandardPaths Paths = wxStandardPaths::Get();
 	buffer.Printf(wxT("%s%s%s"), Paths.GetDataDir().wc_str(),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR) );
	//delete Paths;
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

	size_t seplen = strlen(separator);	// długość separatora
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

	int IdentSuplement = 5 - (int)strlen(identyfier);	// uzupełnienie wycinania w przypadku gdy nie podano identyfikatora w całości (5 znaków)
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

void InitDevices()
{
	m_Devices = new wxArrayPtrVoid();
}

wxArrayPtrVoid *GetDevices()
{
	return m_Devices;
}

void FreeDevices()
{
	m_Devices->Clear();
	delete m_Devices;
}


void FreeSearchMutex()
{
	if(smutex)
		delete smutex;
	smutex = NULL;
}

void InitSearchMutex()
{
	smutex = new wxMutex();
}

wxMutex *GetSearchMutex()
{
	return smutex;
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
	tab[SHIP_LON] = UNDEFINED_DOUBLE;
	tab[SHIP_LAT] = UNDEFINED_DOUBLE;
	tab[SHIP_ROT] = UNDEFINED_DOUBLE;
	tab[SHIP_SOG] = UNDEFINED_DOUBLE;
	tab[SHIP_COG] = UNDEFINED_DOUBLE;
	tab[SHIP_HDT] = UNDEFINED_DOUBLE;
}

void Reset(int id,double *tab)
{
	tab[id] = UNDEFINED_DOUBLE;
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

double nvBearing(double lon1, double lat1, double lon2, double lat2)
{
	double bearing = atan2 (cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(lon2 - lon1), sin(lon2 - lon1) * cos(lat2)) * 180/nvPI;
	/*
	if(bearing  > 0)
		return	bearing += 90;
	if(bearing < -90)
		return 	bearing = 360 + bearing + 90;
	if(bearing < 0)
		return bearing = 90 + bearing;
	*/
	//bearing = bearing + 90;
	return bearing;
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
	return wxString::Format(_("%02d%c %02d' %02.2f''"),decimal, 176, (int)minutes, second);
      
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
/*
double GetMilesPerDegree(double x, double y)
{
	return nvDistance( x, y, x + 1.0, y );	// ilość mil na stopień w aktualnej pozycji y
}
*/
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

nvRGBA StrToRGBA(wxString str)
{
	nvRGBA RGB;
	
	wxString str1; 
	
	str1 = str.substr(0,3);	RGB.R = atoi(str1.char_str());
	str1 = str.substr(3,3);	RGB.G = atoi(str1.char_str());
	str1 = str.substr(6,3);	RGB.B = atoi(str1.char_str());
	str1 = str.substr(9,3);	RGB.A = atoi(str1.char_str());

	return RGB;
}




bool GetShipImage(int mmsi, char *&buffer, int *size)
{
	
	FILE *f;
	
	wxString str = GetPluginDataFilePath();
	wxCharBuffer file = str.ToUTF8(); 
	const char *fname = file.data();
		
	f = fopen(fname , "rb" );
	
	if( f == NULL )
		return false;

	int data_size = nvFileSize(fname);
	
	rewind(f);
	
	char *data = (char*)malloc(data_size);
		
	size_t a = fread(data,data_size,1,f);
	fclose(f);
	wxMemoryInputStream memory(data,data_size);
	
	wxZipInputStream zip(memory);
	wxZipEntry *entry;
	int i = 0;
	
	bool exists = false;
	while((entry = zip.GetNextEntry()) != NULL)
	{
		wxString str = entry->GetName();
		wxString _mmsi = wxString::Format(_("%d.jpg"),(mmsi));
		if(str.CmpNoCase(_mmsi) == 0)
		{
			buffer = (char*)malloc(zip.GetLength());
			*size = zip.GetLength();
			zip.Read( buffer,*size );
			exists = true;
			delete entry;
			break;
		}
		
		delete entry;
		
	}
	
	free(data);
	return exists;
	
}
 
 void SetBroker(CNaviBroker *ptr)
 {
	Broker = ptr;
 }

 CNaviBroker *GetBroker()
 {
	return Broker;
 }

 double GetSmoothScaleFactor()
 {
	return m_SmoothScaleFactor;
 }
 
 void SetSmoothScaleFactor(double val)
 {
	m_SmoothScaleFactor = val;
 }

void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2)
{
	*v1 = (lon1 + lon2) / 2;
	*v2 = (lat1 + lat2) / 2;
}

void SetSelectedSlot(int id)
{
	m_SelectedSlot = id;
}

int GetSelectedSlot()
{
	return m_SelectedSlot;
}

void SetSelectedChannel(int id)
{
	m_SelectedChannel = id;
}

int GetSelectedChannel()
{
	return m_SelectedChannel;
}

void SetSelectedMID(int id)
{
	m_SelectedMID = id;
}

int GetSelectedMID()
{
	return m_SelectedMID;
}

void SetLanguageId(int id)
{
	GlobalLanguageID = id;
}
