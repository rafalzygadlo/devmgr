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
	bool m_Position_0_Exists,m_Position_1_Exists,m_HDT_Exists,m_COG_Exists,m_ROT_Exists,m_SOG_Exists;
	bool m_OtherData;
	double m_ShipState[MAX_SHIP_VALUES_LEN];
	double m_ShipStaticState[MAX_SHIP_VALUES_LEN];
	double m_ShipOldStaticState[MAX_SHIP_VALUES_LEN]; // dane starsze o jeden tick
	double m_ShipGlobalState[MAX_SHIP_VALUES_LEN];
	int m_ShipTicks[MAX_SHIP_VALUES_LEN];
	int m_ShipTimes[MAX_SHIP_VALUES_LEN];
	bool m_ShipValidFrequencyTable[MAX_SHIP_VALUES_LEN];
	bool m_ShipValidFrequency;
	double m_LastHDT;
	int m_OldPositionTick, m_OldHDTTick;
	int m_SignalID, m_MaxFrequencyID;
	int m_GlobalFrequency[MAX_SHIP_VALUES_LEN];
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
	CTicker *m_Ticker;
	double m_MilesPerDeg;
	nvFastFont *m_Font;
	bool m_Prepare;
	int m_MaxFrequency;
	int m_ShipTick,m_AisBufferTick;
	int m_ShipInterval,m_AisBufferInterval;
	bool m_PositionExists;
	bool m_Interpolation;
	double m_OldHDT;
	int m_GlobalTick, m_OldGlobalTick;
	double m_SmoothScaleFactor, m_Factor;
	float m_MapScale;
	double m_MapX,m_MapY;
	nvPoint2d *m_SelectedShip;
	int m_SelectedVertexId;
	nvPoint2f ptt0,ptt1;

	TTexture *m_TextureTGA_0;
	GLuint m_TextureID_0;
	GLuint m_ShipsArrayBuffer, m_ShipsIndicesBuffer, m_ShipsTexCoordsBuffer;

	// bufory punktów
	CNaviArray <nvPoint2d> m_PointsBuffer0;
	CNaviArray <nvPoint2d> m_PointsBuffer1;
	// pointer na aktualny bufor
	CNaviArray <nvPoint2d> *m_CurrentPointsBufferPtr;

	// bufor punktów trójk¹tów
	CNaviArray <nvPoint2d> m_TriangleBuffer0;
	CNaviArray <nvPoint2d> m_TriangleBuffer1;
	// pointer na aktualny bufor
	CNaviArray <nvPoint2d> *m_CurrentTriangleBufferPtr;

	// bufor indexów trójk¹tów
	CNaviArray <int> m_TriangleIndicesBuffer0;
	CNaviArray <int>  m_TriangleIndicesBuffer1;
	// pointer na aktualny bufor
	CNaviArray <int> *m_CurrentTriangleIndicesBufferPtr;
	
	// bufor koordynat tekstur
	CNaviArray <nvPoint2float> m_TriangleTexCoordsBuffer0;
	CNaviArray <nvPoint2float>  m_TriangleTexCoordsBuffer1;
	// pointer na aktualny bufor
	CNaviArray <nvPoint2float> *m_CurrentTriangleTexCoordsBufferPtr;
	
	// bufor nazw obiektów mmsi, shipname
	CNaviArray <wchar_t[128]> m_ShipNamesBuffer0;
	CNaviArray <wchar_t[128]> m_ShipNamesBuffer1;
	// pointer na aktualny bufor
	CNaviArray <wchar_t[128]> *m_CurrentShipNamesBufferPtr;
	
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
	void PrepareIndicesBuffer(SAisData *ptr);
	void PrepareShipNamesBuffer(SAisData *ptr);
	void PrepareTexCoordsBuffer(SAisData *ptr);

	void CopyPointsBuffer();
	void CopyTriangleBuffer();
	void CopyTriangleIndicesBuffer();
	void CopyTriangleTexCoordsBuffer();
	void CopyShipNamesBuffer();
	void SendShipData();
	bool NewPosition(int time);
	bool NewHDT(int time);
	bool NewCOG();
	bool NewSOG();
	void SetTickerTick();
	void Interpolate();
	bool InterpolatePosition();
	bool InterpolateHDT();
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateTextures(void);
	bool CreateVBO();
	void DeleteVBO();
	void RenderVBO();
	void RenderShipNames();
	void SetInvalid();
	void SetFrequency(int id);
	void SetShip(SFunctionData *data);
	void SetSmoothScaleFactor(double _Scale);
	void SetValues();

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