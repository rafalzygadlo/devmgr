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

#define PRODUCT_NAME		"Device Manager"
#define PRODUCT_VERSION		"0.1"
#define PRODUCT_COPYRIGHT	"Copyright 2010/2011 by NavSim. All rights reserved"
#define PLUGIN_CONFIG_FILE	"devmgr.conf"

#define KEY_PORT			"port"
#define KEY_BAUD			"baud"
#define KEY_PORT_INDEX		"pindex"
#define KEY_BAUD_INDEX		"bindex"
#define KEY_CHECK_LOG		"log"

#define DIR_WORKDIR "workdir"

// sygna³y do display
#define SERIAL_SIGNAL_RECONNECT 0
#define SERIAL_SIGNAL_ONDATA 1

// globalne identyfikatory eventów
enum
{
    ID_SET_LOG = 5232,
	ID_SET_PORT,
	ID_SET_BAUD,

};
#endif
