#ifndef __DLL
#define __DLL

#include "NaviMapIOApi.h"
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "NaviDisplayApi.h"
#include <wx/fileconf.h>

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
	std::vector<CMySerial*> m_vDevices;
	CNaviBroker *m_Broker;
	bool m_NeedExit;
	wxFileConfig *m_FileConfig;
	wxString m_ConfigPath;
	int m_DisplaySignalType;
	int m_DeviceId;
	CDisplaySignal *m_DisplaySignal;
	bool m_Init;
	
	
	void CreateApiMenu(void);
	void WriteConfig();
	void ReadConfig();
	void SendSignal(int type, int id);
	void SetDisplaySignalType(int type);
	void SetDeviceId(int id);
	wxArrayString GetDevicesConfig(wxString path);
	void OnReconnect(CMySerial *Serial);
	bool IsInited();

					
public:

	CMapPlugin(CNaviBroker *NaviBroker);
	virtual ~CMapPlugin();

	bool GetNeedExit(void);
	CNaviBroker *GetBroker();
	size_t GetDevicesCount();
	CMySerial *GetDevice(size_t idx);
	void DeleteDevice(size_t idx);
	void AddDevice(CMySerial *serial);
	void AddDeviceFunc(CMySerial *serial); // pomocnicza funkcja kiedy urzadzenie dodawane z display plugina wysy³any jest sygna³ zwrotny
	void RemoveDevice(CMySerial *serial);
	void ReindexDevics();


	int GetDisplaySignalType();
	int GetDeviceId();
	
	virtual void Run(void *Params);
	virtual void Kill(void);
	//virtual void Render(void);
	virtual void Config();
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb );
	virtual void MouseDBLClick(int x, int y);
		
	// funkcje dostêpne dla innych pluginów
	static void *OnDeviceSignal(void *NaviMapIOApiPtr, void *Params);	// serial signal (recnnec, on data etc...)
	static void *OnDeviceData(void *NaviMapIOApiPtr, void *Params);		// dane które by³y w definicji s¹ dostêpne
	static void *GetParentPtr(void *NaviMapIOApiPtr, void *Params);
	static void *AddDevice(void *NaviMapIOApiPtr, void *Params);
	
};	

#ifdef __cplusplus
}
#endif

#endif