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

#define PRODUCT_NAME "Device Manager"
#define PRODUCT_VERSION "0.1"
#define PRODUCT_COPYRIGHT "Copyright 2010/2011 by NavSim. All rights reserved"
#define PLUGIN_CONFIG_FILE "devmgr.conf"

#define KEY_DEVICES "devices"
#define KEY_PORT "port"
#define KEY_BAUD "baud"
#define KEY_RUNNING "running"
#define DIR_WORKDIR "workdir"

// sygna³y do display
#define SERIAL_SIGNAL_RECONNECT 1 // sygna³ urzadzenia o ponownym polaczeniu
#define SERIAL_SIGNAL_ONDATA 2	// sygna³ z portu o danych
#define SERIAL_SIGNAL_NEW_SIGNAL 3 // linia nowego typu dostêpna
#define SERIAL_SIGNAL_NO_SIGNAL 4 // polaczony ale brak sygnalu
#define CLEAR_DISPLAY 5	// wyczyszczenie kontrolek nie u¿ywamy narazie
#define INIT_SIGNAL 6	// zainicjowanie kontrolek
#define ADD_DEVICE 7	// dodanie urz¹dzenia

// globalne identyfikatory eventów
enum
{
    ID_SET_LOG = 5232,
	ID_SET_PORT,
	ID_SET_BAUD,

};
#endif
