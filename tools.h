#ifndef __TOOLS
#define __TOOLS

#include <wx/wx.h>
#include "NaviBroker.h"
#include "serial.h"

wxMutex *GetMutex();
wxString GetPluginConfigPath();								
wxString GetWorkDir(void);
void PrintInfo(CNaviBroker *Broker,wchar_t *text);	// drukuj info na mapie
CMySerial *CreateNewDevice(wxString name, char *port, int baud, bool run);

#endif