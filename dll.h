#ifndef __DLL_H
#define __DLL_H

#include "NaviMapIOApi.h"
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "NaviDisplayApi.h"
#include <wx/fileconf.h>
#include "GeometryConfig.h"
#include "nvFastFont.h"

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif
#include "reader.h"
#include "conf.h"
#include "ticker.h"

#ifdef __cplusplus
extern "C" {
#endif


class CMyFrame;
class CNotifier;
class CMapPlugin :public CNaviMapIOApi
{
	bool m_Position_0_Exists,m_Position_1_Exists;
	bool m_OtherData;
	double m_ShipState[6];
	wxArrayPtrVoid *m_Devices;
	CNaviBroker *m_Broker;
	bool m_ShipStateExist;
	bool m_NeedExit;
	wxFileConfig *m_FileConfig;
	wxString m_ConfigPath;
	int m_DisplaySignalType;
	int m_DeviceId;
	CDisplaySignal *m_DisplaySignal;
	bool m_Init;
	float m_Scale;
	bool m_EnableControls;
	CNotifier *m_SearchThread;
	SData *m_Data;
	double m_GlobalShipState[6];
	CTicker *m_Ticker;
	double m_MilesPerDeg;
	nvFastFont *m_Font;
	
	// bufory punktow
	CNaviArray <nvPoint2d> PointsBuffer0;
	CNaviArray <nvPoint2d> PointsBuffer1;
	CNaviArray <nvPoint2d> TriangleBuffer0;

	CNaviArray <nvPoint2d> *CurrentBufferPtr;

	void Prepare();
	void CreateApiMenu(void);
	void WriteConfig();
	void ReadConfig();
	void SendSignal(int type, void *ptr);
	void SendDataSignal(SData *data);
	void SetDisplaySignalType(int type);
	void SetDeviceId(int id);
	wxArrayString GetConfigItems(wxString path);
	void OnReconnect(CReader *ptr);
	bool IsInited();
	void RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength);
	void SetData(SData *value);
	void SetDisplaySignal(int type);
	void SetFunctionData(SFunctionData *data);
	void WriteSerialConfig(int index);
	void WriteSocketConfig(int index);
	void ReadSocketConfig(int index);
	void ReadSerialConfig(int index);
	void PrepareBuffer();
	void PreparePointsBuffer(SAisData *ptr);
	void PrepareTriangleBuffer(SAisData *ptr);
	void CopyPointsBuffer();
	void SendShipData();
					
public:

	CMapPlugin(CNaviBroker *NaviBroker);
	virtual ~CMapPlugin();

	bool GetNeedExit(void);
	CNaviBroker *GetBroker();
	size_t GetDevicesCount();
	CReader *GetReader(size_t idx);
	void DeleteDevice(size_t idx);
	void AddDevice(CReader *ptr);
	void AddDeviceFunc(CReader *ptr); // pomocnicza funkcja kiedy urzadzenie dodawane z display plugina wysy³any jest sygna³ zwrotny
	void RemoveDevice(CReader *ptr);
	void StartDevice(CReader *ptr);
	void StopDevice(CReader *ptr);
	void ReindexDevics();
	void RenderPosition();
	SData *GetData();
	wxArrayPtrVoid *GetDevicesList();
	
	int GetDisplaySignalType();
	int GetDeviceId();
	bool GetEnableControlsFlag();

	void OnTickerStart();
	void OnTickerStop();
	void OnTickerTick();
	
	virtual void Run(void *Params);
	virtual void Kill(void);
	virtual void Render(void);
	virtual void Config();
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb );
	virtual void MouseDBLClick(int x, int y);
	virtual void OnInitGL();
		
	// funkcje dostêpne dla innych pluginów
	static void *OnDeviceSignal(void *NaviMapIOApiPtr, void *Params);	// serial signal (recnnec, on data etc...)
	static void *OnDeviceData(void *NaviMapIOApiPtr, void *Params);		// dane które by³y w definicji s¹ dostêpne
	static void *GetParentPtr(void *NaviMapIOApiPtr, void *Params);
	static void *AddDevice(void *NaviMapIOApiPtr, void *Params);
	static void *OnFunctionData(void *NaviMapIOApiPtr, void *Params);
	static void *OnNewAisObject(void *NaviMapIOApiPtr, void *Params);	// nowe dane do tablicy ais
	static void *OnData(void *NaviMapIOApiPtr, void *Params); // dane
	static void *GetAisBuffer(void *NaviMapIOApiPtr, void *Params); // ais buffer
	
};	

#ifdef __cplusplus
}
#endif

#endif