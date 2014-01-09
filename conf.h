#ifndef __CONF
#define __CONF
#include <wx/wx.h>

#define COMMENT

#define DEBUG

#ifdef _WIN32
	#define DIR_SEPARATOR "\\"
#endif

#if defined(_LINUX32) || (_LINUX64)
	#define DIR_SEPARATOR "/"
#endif

#define nvPI 3.1415926535897932384626433832795

#define PRODUCT_NAME "Device Manager"
#define PRODUCT_VERSION "0.1"
#define PRODUCT_COPYRIGHT "Copyright 2010/2013 by NavSim. All rights reserved"
#define PLUGIN_CONFIG_FILE "devmgr.conf"

#define KEY_DEVICES "devices"
#define KEY_NAME "name"
#define KEY_PORT "port"
#define KEY_BAUD "baud"
#define KEY_RUNNING "running"
#define KEY_DEVICE_TYPE "device_type"

#define DIR_WORKDIR "workdir"

#define ICON_STOP 0
#define ICON_START 1

#define MAX_BAD_CRC					2
#define MAX_INVALID_NMEA			2

// sygna�y do display
#define SERIAL_SIGNAL_RECONNECT		1	// sygna� urzadzenia o ponownym polaczeniu
#define SERIAL_SIGNAL_ONDATA		2	// sygna� z portu o danych
#define SERIAL_SIGNAL_NEW_SIGNAL	3	// linia nowego typu dost�pna
#define SERIAL_SIGNAL_NO_SIGNAL		4	// polaczony ale brak sygnalu
#define SERIAL_SIGNAL_NMEA_LINE		5	// nmea line
#define SERIAL_SIGNAL_CONNECTED		6
#define CLEAR_DISPLAY				7	// wyczyszczenie kontrolek nie u�ywamy narazie
#define INIT_SIGNAL					8	// zainicjowanie kontrolek
#define ADD_DEVICE					9	// dodanie urz�dzenia
#define REMOVE_DEVICE				10	// usuwanie urzadzenia
#define START_DEVICE				11  // sygnal startu urzadzenia
#define STOP_DEVICE					12	// sygnal zatrzymania urzadzenia
#define DATA_SIGNAL					13	// sygna� danych

#define TEXT_OK		0 // kolory tekstow w kontrolce
#define TEXT_ERROR	1 // kolory tekstow w kontrolce

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
#define MSG_CONNECTED				18
#define MSG_RUNNING					19
#define MSG_NEW						20
#define MSG_DELETE					21
#define	MSG_DEVICE_TYPES			22
#define MSG_DEVICE_TYPE				23
#define MSG_DISCONNECTED			24
#define MSG_DEVICE_WIZARD			25
#define MSG_MONITOR					26
#define MSG_CLOSE					27
#define MSG_NEXT					28
#define MSG_PREV					29
#define MSG_FINISH					30
#define MSG_SCANNING				31
#define MSG_NO_DEVICE_FOUND			32
#define MSG_DEVICE_FOUND			33
#define MSG_SELECTED_DEVICES		34
#define MSG_DEVICE_TYPE_SOCKET		35
#define MSG_DEVICE_TYPE_SERIAL		36
#define MSG_HOST					37

#define MAX_DATA_POSITIONS		10
#define WORK_WIZARD 0


#define DEVICE_TYPE_SOCKET	0
#define DEVICE_TYPE_SERIAL	1

typedef struct SData 
{
	int		id;
	char	marker[5 + 1];	// id definicji danych
	char	value[64 + 1];

} SData;

typedef struct SFunctionData 
{
	int		id_function;
	double	values[6];

} SFunctionData;



// globalne identyfikatory event�w
enum
{
	ID_SET_LOG = 5232,
	ID_SET_PORT,
	ID_SET_BAUD,
};


#endif



