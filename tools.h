#ifndef __TOOLS
#define __TOOLS

#include <wx/wx.h>
#include "NaviBroker.h"
#include "serial.h"

wxString GetProductInfo();
wxString GetProductName();
wxMutex *GetMutex();
void FreeMutex();
wxString GetPluginConfigPath();								
wxString GetWorkDir(void);
void PrintInfo(CNaviBroker *Broker,wchar_t *text);	// drukuj info na mapie
CMySerial *CreateNewDevice(wxString name, char *port, int baud, bool run, int type);

char **ExplodeStr(const char *str, const char *separator, int *size);
void FreeStrList(char **list, int length);
time_t GetUTCTimeNow(void);
char *GetSentenceFromLine(const char *line, const char *identyfier);
int MemPos(const unsigned char *Memory, int MemorySize, const unsigned char *Search, int SearchSize, int StartAt = 0 );
wxString GetMsg(int id);
bool SetGlobalPrioryty(int fid);
bool Set_RMC_COG();
bool Set_VTG_COG();
bool Check_HDT();

// funkcje protokolu

#endif