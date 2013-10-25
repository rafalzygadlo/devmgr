#ifndef __CONF
#define __CONF
#include <wx/wx.h>

#define COMMENT

#ifdef _WIN32
	#define DIR_SEPARATOR "\\"
#endif

#if defined(_LINUX32) || (_LINUX64)
	#define DIR_SEPARATOR "/"
#endif

#define nvPI 3.1415926535897932384626433832795

#define PRODUCT_NAME "Device Manager"
#define PRODUCT_VERSION "0.1"
#define PRODUCT_COPYRIGHT "Copyright 2010/2011 by NavSim. All rights reserved"
#define PLUGIN_CONFIG_FILE "devmgr.conf"

#define KEY_DEVICES "devices"
#define KEY_NAME "name"
#define KEY_PORT "port"
#define KEY_BAUD "baud"
#define KEY_RUNNING "running"
#define KEY_DATA "data"

#define DIR_WORKDIR "workdir"


// sygna³y do display
#define SERIAL_SIGNAL_RECONNECT 1	// sygna³ urzadzenia o ponownym polaczeniu
#define SERIAL_SIGNAL_ONDATA 2		// sygna³ z portu o danych
#define SERIAL_SIGNAL_NEW_SIGNAL 3	// linia nowego typu dostêpna
#define SERIAL_SIGNAL_NO_SIGNAL 4	// polaczony ale brak sygnalu
#define CLEAR_DISPLAY 5				// wyczyszczenie kontrolek nie u¿ywamy narazie
#define INIT_SIGNAL 6				// zainicjowanie kontrolek
#define ADD_DEVICE 7				// dodanie urz¹dzenia
#define REMOVE_DEVICE 8				// usuwanie urzadzenia

// jezyki id
#define MSG_DEVICE_NAME				0
#define MSG_PORT					1
#define MSG_BAUD					2
#define MSG_PORT_INFO				3
#define MSG_SCAN					4
#define MSG_OK						5
#define MSG_CANCEL					6
#define MSG_SCANNING_PORTS			7
#define MSG_DEVICES					8
#define MSG_NEW_DEVICE				9
#define MSG_START					10
#define MSG_STOP					11
#define MSG_CONFIGURE_DEVICE		12
#define MSG_CONFIGURE_DEVICE_DATA	13
#define MSG_STATUS					14
#define MSG_UNINSTALL				15
#define MSG_STOP_THE_DEVICE			16
#define MSG_STOPPING_DEVICE			17
#define MSG_IS_CONNECTED			18
#define MSG_IS_RUNNING				19





#define MAX_DATA_POSITIONS		10
typedef struct TDataDefinition_s {

	int	 DataID;							// id definicji danych pobrane ze zdalnego serwera
	char Name[32 + 1];						// nazwa definicji
	char Marker[5 + 1];						// nazwa markera NMEA do pobrania danych
	int  Position[MAX_DATA_POSITIONS];		// pozycje w lini NMEA (w formie indeksu), których wartoœci nale¿y wyci¹æ. Maksymalnie 10 pozycji
	bool Average;							// czy uœredniaæ dane

} TDataDefinition;

typedef struct TData_s {

	char	Marker[5 + 1];	// id definicji danych
	char	Value[16 + 1];
	bool	Average;							// czy uœredniaæ dane
	time_t	DateTime;

} TData;

typedef struct
{
	double x;
	double y;

} SPoint;



// globalne identyfikatory eventów
enum
{
    ID_SET_LOG = 5232,
	ID_SET_PORT,
	ID_SET_BAUD,

};
#endif
