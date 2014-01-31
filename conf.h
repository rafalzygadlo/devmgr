#ifndef __CONF_H
#define __CONF_H
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
#define PRODUCT_VERSION "1.1"
#define PRODUCT_COPYRIGHT "Copyright 2010/2013 by NavSim. All rights reserved"
#define PLUGIN_CONFIG_FILE "devmgr.conf"

#define KEY_DEVICES "devices"
#define KEY_NAME "name"
#define KEY_PORT "port"
#define KEY_BAUD "baud"
#define KEY_RUNNING "running"
#define KEY_DEVICE_TYPE "device_type"
#define KEY_CONNECTION_TYPE "connection_type"
#define KEY_SERIAL_PORT "serial_port"
#define KEY_HOST "host"

#define DIR_WORKDIR "workdir"

#define ICON_STOP 0
#define ICON_START 1

#define MAX_BAD_CRC					2
#define MAX_INVALID_NMEA			2

// sygna³y do display
#define SIGNAL_RECONNECT			1	// sygna³ urzadzenia o ponownym polaczeniu
#define SIGNAL_ONDATA				2	// sygna³ z portu o danych
#define SIGNAL_NEW_SIGNAL			3	// linia nowego typu dostêpna
#define SIGNAL_NO_SIGNAL			4	// polaczony ale brak sygnalu
#define SIGNAL_NMEA_LINE			5	// nmea line
#define SIGNAL_NEW_AIS_OBJECT		6
#define	SIGNAL_CONNECTED			7
#define CLEAR_DISPLAY				8	// wyczyszczenie kontrolek nie u¿ywamy narazie
#define INIT_SIGNAL					9	// zainicjowanie kontrolek
#define ADD_DEVICE					10	// dodanie urz¹dzenia
#define REMOVE_DEVICE				11	// usuwanie urzadzenia
#define START_DEVICE				12  // sygnal startu urzadzenia
#define STOP_DEVICE					13	// sygnal zatrzymania urzadzenia
#define DATA_SIGNAL					14	// sygna³ danych
#define CLEAR_AIS_LIST				15	// set item count na 0

#define TEXT_OK		0 // kolory tekstow w kontrolce
#define TEXT_ERROR	1 // kolory tekstow w kontrolce

#define ID_MENU_BEGIN 1000
#define ID_MENU_END 1100
#define DEFAULT_CONTROL_TYPE 1000

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
#define MSG_AIS_TARGETS				38
#define MSG_MMSI					39
#define MSG_SHIPNAME				40

#define MSG_AIS_1_NAME				41
#define MSG_AIS_2_NAME				42
#define MSG_AIS_3_NAME				43
#define MSG_AIS_4_NAME				44
#define MSG_AIS_5_NAME				45
#define MSG_AIS_6_NAME				46
#define MSG_AIS_7_NAME				47
#define MSG_AIS_8_NAME				48
#define MSG_AIS_9_NAME				49
#define MSG_AIS_10_NAME				50
#define MSG_AIS_11_NAME				51
#define MSG_AIS_12_NAME				52
#define MSG_AIS_13_NAME				53
#define MSG_AIS_14_NAME				54
#define MSG_AIS_15_NAME				55
#define MSG_AIS_16_NAME				56
#define MSG_AIS_17_NAME				57
#define MSG_AIS_18_NAME				58
#define MSG_AIS_19_NAME				59
#define MSG_AIS_20_NAME				60
#define MSG_AIS_21_NAME				61
#define MSG_AIS_22_NAME				62
#define MSG_AIS_23_NAME				63
#define MSG_AIS_24_NAME				64
#define MSG_AIS_25_NAME				65
#define MSG_AIS_26_NAME				66
#define MSG_AIS_27_NAME				67
#define MSG_ACCURACY				68
#define MSG_TRUE					69
#define MSG_FALSE					70
#define MSG_NA						71
#define MSG_COG						72
#define MSG_HEADING					73
#define MSG_LAT						74
#define MSG_LON						75
#define MSG_MANEUVER				76
#define MSG_RADIO					77
#define MSG_RAIM					78
#define MSG_SECOND					79
#define MSG_SPEED					80
#define MSG_NAVIGATION_STATUS		81
#define MSG_TURN					82
#define MSG_TURN_HARD_LEFT			83
#define MSG_TURN_HARD_RIGHT			84
#define MSG_TURN_LEFT				85
#define MSG_TURN_RIGHT				86
#define MSG_YEAR					87
#define MSG_MONTH					88
#define MSG_DAY						89
#define MSG_HOUR					90
#define MSG_MINUTE					91
#define MSG_SECONDS					92
#define MSG_EPFD					93
#define MSG_AIS_VERSION				94
#define MSG_CALLSIGN				95
#define MSG_ETA_MONTH				96
#define MSG_ETA_DAY					97
#define MSG_ETA_HOUR				98
#define MSG_ETA_MINUTE				99
#define MSG_DESTINATION				100
#define MSG_SHIP_TYPE				101
#define MSG_IMO_NUMBER				102
#define MSG_TO_BOW					103
#define MSG_TO_STERN				104
#define MSG_TO_PORT					105
#define MSG_TO_STARBOARD			106
#define MSG_DRAUGHT					107
#define MSG_DTE						108
#define MSG_LENGTH_WIDTH			109
#define MSG_AIS_MESSAGES			110
#define MSG_GO_TOP					111
#define MSG_DAC						112
#define MSG_FID						113


#define MAX_DATA_POSITIONS	10
#define WORK_WIZARD 0

#define CONNECTION_TYPE_SOCKET	0
#define CONNECTION_TYPE_SERIAL	1

#define DEFAULT_SOCKET_HOST "195.116.95.12"
#define DEFAULT_SOCKET_PORT	"3557"

// w bibliotece protocols definicja w tablicach parsera
#define AIS_MESSAGE					25

#define AIS_CHECKSUM			6
#define AIS_MESSAGE_ID			3			
#define AIS_FRAGMENT_NUMBER		2
#define AIS_FRAGMENT_COUNTER	1
#define AIS_DATA				5

#define AIS_PARTS 7 // czesci wiadomosci

#define MARKER_LENGTH 5
#define MAX_VALUE_LENGTH 82 //NMEA 0183’s 82 dla AIS

#define TICKER_SLEEP	1000

typedef struct SData 
{
	int		id;
	char	marker[MARKER_LENGTH + 1];	// id definicji danych
	char	value[MAX_VALUE_LENGTH + 1];  //NMEA 0183’s 82
	float	interval;

} SData;

typedef struct SFunctionData 
{
	int		id_function;
	double	values[6];

} SFunctionData;


// globalne identyfikatory eventów
enum
{
	ID_SET_LOG = 5232,
	ID_SET_PORT,
	ID_SET_BAUD,
};


#endif



