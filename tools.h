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

char **ExplodeStr(const char *str, const char *separator, int *size);
void FreeStrList(char **list, int length);
time_t GetUTCTimeNow(void);
char *GetSentenceFromLine(const char *line, const char *identyfier);
int MemPos(const unsigned char *Memory, int MemorySize, const unsigned char *Search, int SearchSize, int StartAt = 0 );
wxString GetMsg(int id);

#endif