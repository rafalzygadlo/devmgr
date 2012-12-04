#include "conf.h"
#include "tools.h"

#include <wx/stdpaths.h>

wxMutex *mutex = new wxMutex;

wxMutex *GetMutex()
{
	return mutex;
}

wxString GetPluginConfigPath()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir(),wxT(DIR_SEPARATOR),_(PLUGIN_CONFIG_FILE));
}

void PrintInfo(CNaviBroker *Broker,wchar_t *text)
{
	// 9 id chart_catalogu
	if(Broker != NULL)
		Broker->PrintInfoBlock(Broker->GetParentPtr(), 13 , text, 10);

}

wxString GetWorkDir(void)
{
	static wxString buffer;
	wxStandardPaths *Paths = new wxStandardPaths();
 	buffer.Printf(wxT("%s%s%s"), Paths->GetUserDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR) );
	delete Paths;
	return buffer;
}

CMySerial *CreateNewDevice(wxString name, char *port, int baud, bool run)
{
	CMySerial *Serial = new CMySerial();
	Serial->SetBaud(baud);
	Serial->SetPort(port);
	Serial->SetDeviceName(name);
	Serial->SetRunOnStart(run);
	
	return Serial;

}