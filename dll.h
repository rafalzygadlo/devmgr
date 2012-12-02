#ifndef __DLL
#define __DLL

#include "NaviMapIOApi.h"
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "NaviDisplayApi.h"
#include <wx/fileconf.h>
#include "frame.h"

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif
#include "serial.h"
#include "conf.h"

#ifdef __cplusplus
extern "C" {
#endif


class CMyFrame;

class CMapPlugin :public CNaviMapIOApi
{

	std::vector<CMySerial*> vDevices;
	CMyFrame *MyFrame;
	CDisplaySignal *DisplaySignal;
	CNaviBroker *Broker;
	bool NeedExit;
	//bool _Exit;
#if defined(_WIN32) || defined(_WIN64)
		HANDLE threadFrame;
#endif
	wxFileConfig *FileConfig;
	wxString ConfigPath;

	static void *MenuConfig(void *NaviMapIOApiPtr, void *Input);
	void CreateApiMenu(void);
	void WriteConfig();
	void ReadConfig();

					
public:

	CMapPlugin(CNaviBroker *NaviBroker);
	virtual ~CMapPlugin();

	bool GetNeedExit(void);
	CNaviBroker *GetBroker();
	size_t GetDevicesCount();
	CMySerial *GetDevice(size_t idx);
	void DeleteDevice(size_t idx);
	void NewDevice(char *port, int baud);


	virtual void Run(void *Params);
	virtual void Kill(void);
	//virtual void Render(void);
	virtual void Config();
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb );
	virtual void MouseDBLClick(int x, int y);
		
	// funkcje dostêpne dla innych pluginów
	///static void *SetExit(void *NaviMapIOApiPtr, void *Params);			// serial port ustawia flagê zakoñczenia dzia³ania
	//static void *SetNMEAInfo(void *NaviMapIOApiPtr, void *Params);
	//static void *SetLog(void *NaviMapIOApiPtr, void *Params);			// ustawia log w okienku konfiguracyjnym
	//static void *SetPort(void *NaviMapIOApiPtr, void *Params);			// ustawia port w okienku konfiguracyjnym
	//static void *SetBaud(void *NaviMapIOApiPtr, void *Params);			// ustawia port w okienku konfiguracyjnym
};	

#ifdef __cplusplus
}
#endif

#endif