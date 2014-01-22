#include "conf.h"
#include "tools.h"
#include <wx/stdpaths.h>
#include "protocol.h"

wxMutex *a_mutex = NULL;
wxMutex *s_mutex = NULL;
int GlobalLanguageID;
bool m_HDT_Exists = false;
int m_HDT_Counter = 0;

const wxChar *nvLanguage[2][38] = 
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

	},
	
	/*PL*/
	{
		_("Abc"),

	}

};

wxString GetProductInfo()
{
	return wxString::Format(_("%s %s\n%s"),_(PRODUCT_NAME),_(PRODUCT_VERSION),_(PRODUCT_COPYRIGHT));
}

wxString GetProductName()
{
	return wxString::Format(_("%s %s"),_(PRODUCT_NAME),_(PRODUCT_VERSION));
}

wxString GetMsg(int id)
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
 	buffer.Printf(wxT("%s%s%s"), Paths->GetUserDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR) );
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

void FreeAisMutex()
{
	if(a_mutex)
		delete a_mutex;
	a_mutex = NULL;
}

wxMutex *GetAisMutex()
{
	if(a_mutex == NULL)
		a_mutex = new wxMutex();
	return a_mutex;

}

void FreeSignalMutex()
{
	if(s_mutex)
		delete s_mutex;
	s_mutex = NULL;
}

wxMutex *GetSignalMutex()
{
	if(s_mutex == NULL)
		s_mutex = new wxMutex();
	return s_mutex;

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
		//fprintf(stdout,"FORM HDT\n");
		return true;
	}
}

bool Set_VTG_COG()
{
	Check_HDT();
	
	if(m_HDT_Exists)
		return false;
	else{
		//fprintf(stdout,"FORM VTG\n");
		return true;
	}
}

bool Set_RMC_COG()
{
	Check_HDT();

	if(m_HDT_Exists)
		return false;
	else{
		//fprintf(stdout,"FORM COG\n");
		return true;
	}
}