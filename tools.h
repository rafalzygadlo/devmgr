#ifndef __TOOLS
#define __TOOLS

#include <wx/wx.h>
#include "NaviBroker.h"

wxMutex *GetMutex();
char *gen_random(const int len) ;
wxString GenerateRandomFileName(wxString dir, wxString ext, int len);
wxString GetWorkDir(void);
void PrintInfo(CNaviBroker *Broker,wchar_t *text);	// drukuj info na mapie
wxString ConvertDegree(float degree);
double ConvertDegreeDouble(float degree);
wxString FormatLongitude(float x);
wxString FormatLatitude(float y);
double DD(float DM);

#endif