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
#include "frame.h"

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
	float m_MapScale,m_OldMapScale;
	double m_MapX,m_MapY;
	int m_SelectedVertexId;
	nvPoint2f ptt0,ptt1;
	bool m_FirstTime;
	double m_ScreenX1,m_ScreenY1,m_ScreenX2,m_ScreenY2;
	int m_CurrentId;
	SAisData *m_SelectedPtr,*m_OldSelectedPtr;
	bool m_MouseLmb, m_MouseDLmb,m_MouseUp;
	CMyFrame *m_MyFrame;

	TTexture *m_TextureTGA_0;
	GLuint m_TextureID_0;
	GLuint m_ShipsArrayBuffer, m_ShipsLineIndicesBuffer, m_ShipsTriangleIndicesBuffer,m_ShipsColorBuffer;
	GLuint m_TrianglesArrayBuffer, m_TrianglesTriangleIndicesBuffer,m_TrianglesLineIndicesBuffer, m_TrianglesColorBuffer;
	GLuint m_AtonArrayBuffer, m_AtonTriangleIndicesBuffer, m_AtonLineIndicesBuffer, m_AtonColorBuffer;

	int m_TrianglesTriangleLength, m_TrianglesLineLength, m_TrianglesColorLength;
	int m_ShipTriangleLength, m_ShipLineLength, m_ShipColorLength;
	int m_AtonTriangleLength, m_AtonLineLength;
	bool m_Ready;
	int m_ThreadCounter;
	bool m_ShipRender;
	
	// bufory punktów
	// SHIP
	CNaviArray <nvPoint2d> m_PointsBuffer0;				CNaviArray <nvPoint2d> m_PointsBuffer1;					CNaviArray <nvPoint2d> *m_CurrentPointsBufferPtr;				// bufor punktów trójk¹tów SHIP
	CNaviArray <nvPoint2d> m_ShipVerticesBuffer0;		CNaviArray <nvPoint2d> m_ShipVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentShipVerticesBufferPtr;			// bufor indexów trójk¹tów SHIP
	CNaviArray <int> m_ShipTriangleIndicesBuffer0;		CNaviArray <int>  m_ShipTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentShipTriangleIndicesBufferPtr;
	CNaviArray <int> m_ShipLineIndicesBuffer0;			CNaviArray <int>  m_ShipLineIndicesBuffer1;				CNaviArray <int> *m_CurrentShipLineIndicesBufferPtr;			// bufor indexów lini SHIP
	CNaviArray <nvRGBAf> m_ShipColorBuffer0;			CNaviArray <nvRGBAf> m_ShipColorBuffer1;				CNaviArray <nvRGBAf> *m_CurrentShipColorBufferPtr;
	
	// SHIP trójkat
	CNaviArray <nvPoint2d> m_TriangleVerticesBuffer0;	CNaviArray <nvPoint2d> m_TriangleVerticesBuffer1;		CNaviArray <nvPoint2d> *m_CurrentTriangleVerticesBufferPtr;
	CNaviArray <int> m_TrianglesTriangleIndicesBuffer0;	CNaviArray <int>  m_TrianglesTriangleIndicesBuffer1;	CNaviArray <int> *m_CurrentTrianglesTriangleIndicesBufferPtr;	// bufor indexów trójk¹tów SHIP
	CNaviArray <int> m_TrianglesLineIndicesBuffer0;		CNaviArray <int>  m_TrianglesLineIndicesBuffer1;		CNaviArray <int> *m_CurrentTrianglesLineIndicesBufferPtr;		// bufor indexów lini SHIP
	CNaviArray <nvRGBAf> m_TrianglesColorBuffer0;		CNaviArray <nvRGBAf> m_TrianglesColorBuffer1;			CNaviArray <nvRGBAf> *m_CurrentTrianglesColorBufferPtr;
	
	//SHIP linie
	CNaviArray <nvPoint2d> m_COGVerticesBuffer0;		CNaviArray <nvPoint2d> m_COGVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentCOGVerticesBufferPtr;			// SHIP linie COG
	CNaviArray <nvPoint2d> m_HDGVerticesBuffer0;		CNaviArray <nvPoint2d> m_HDGVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentHDGVerticesBufferPtr;			// SHIP linie HDG
	
	// bufor punktów trójk¹tów ATON
	CNaviArray <nvPoint2d> m_AtonVerticesBuffer0;		CNaviArray <nvPoint2d> m_AtonVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentAtonVerticesBufferPtr;
	CNaviArray <int> m_AtonTriangleIndicesBuffer0;		CNaviArray <int> m_AtonTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentAtonTriangleIndicesBufferPtr;
	CNaviArray <int> m_AtonLineIndicesBuffer0;			CNaviArray <int> m_AtonLineIndicesBuffer1;				CNaviArray <int> *m_CurrentAtonLineIndicesBufferPtr;
	CNaviArray <nvRGBAf> m_AtonColorBuffer0;			CNaviArray <nvRGBAf> m_AtonColorBuffer1;				CNaviArray <nvRGBAf> *m_CurrentAtonColorBufferPtr;

	CNaviArray <SIdToId> m_IdToTriangleId;
	CNaviArray <SIdToId> m_IdToShipId;
	CNaviArray <SIdToId> m_IdToAtonId;
	// bufor koordynat tekstur
	//CNaviArray <nvPoint2float> m_TriangleTexCoordsBuffer0;
	//CNaviArray <nvPoint2float>  m_TriangleTexCoordsBuffer1;
	// pointer na aktualny bufor
	//CNaviArray <nvPoint2float> *m_CurrentTriangleTexCoordsBufferPtr;
	
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
		
	// bufor trójkatów
	void PrepareTriangleVerticesBuffer(SAisData *ptr);			//vertexy
	void PrepareTriangleTriangleIndicesBuffer(SAisData *ptr);   //indexy
	void PrepareTriangleLineIndicesBuffer(SAisData *ptr);		//indexy lini
	void PrepareTriangleColorBuffer(SAisData *ptr);				//kolory

	// bufor statku
	void PrepareShipVerticesBuffer(SAisData *ptr);				//vertexy
	void PrepareShipTriangleIndicesBuffer(SAisData *ptr);		//indexy trojkatow
	void PrepareShipLineIndicesBuffer(SAisData *ptr);			//indexy lini
	void PrepareShipColorBuffer(SAisData *ptr);					//kolory

	// bufor aton
	void PrepareAtonVerticesBuffer(SAisData *ptr);
	void PrepareAtonTriangleIndicesBuffer(SAisData *ptr);
	void PrepareAtonLineIndicesBuffer(SAisData *ptr);
	void PrepareAtonColorBuffer(SAisData *ptr);
	
	// bufor lini COG
	void PrepareCOGVerticesBuffer(SAisData *ptr);
	// bufor linii HDG
	void PrepareHDGVerticesBuffer(SAisData *ptr);
	
	bool IsOnScreen(double x , double y);
	bool VisibleStateChanged();
	void RunThread();
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
	bool CreateShipsVBO();
	bool CreateTrianglesVBO();
	bool CreateAtonsVBO();

	void DeleteShipsVBO();
	void DeleteTrianglesVBO();
	void RenderShipNames();
	void RenderSelection();
	void SetInvalid();
	void SetFrequency(int id);
	void SetShip(SFunctionData *data);
	void SetSmoothScaleFactor(double _Scale);
	void SetValues();
	bool IsTriangleBuffer();
	bool IsShipBuffer();
	bool IsAtonBuffer();
	void SetSelection();
	void CopyInt(CNaviArray <int> *a, CNaviArray <int> *b);
	void CopyNvPoint2d(CNaviArray <nvPoint2d> *src, CNaviArray <nvPoint2d> *dst);
	void CopyNvRGBAf(CNaviArray <nvRGBAf> *src, CNaviArray <nvRGBAf> *dst);
	void SetPtr0();
	void SetPtr1();
	void CopyBuffers();
	void SetBuffers();
	void ClearBuffers();
	void SelectShip();
	void SelectTriangle();
	void SelectAton();
	void ShowFrameWindow(bool show);
	
	void PrepareShipBuffer(SAisData *ptr);
	void PrepareAtonBuffer(SAisData *ptr);
	void PrepareTriangleBuffer(SAisData *ptr);
	void CheckTriangleBuffer(SAisData *ptr);
		
	void Generate();
	void RenderGPS();
	void RenderCOG();
	void RenderHDG();
	void RenderRealShips();
	void RenderShipTriangles();
	void RenderPosition();
	void RenderShips();
	void RenderTriangles();
	void RenderPoints();
	void RenderAtons();
	void RenderRealAtons();

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
	SAisData *GetSelectedPtr();
	
	SData *GetData();
	wxArrayPtrVoid *GetDevicesList();
	
	int GetDisplaySignalType();
	int GetDeviceId();
	bool GetEnableControlsFlag();

	void OnTickerStart();
	void OnTickerStop();
	void OnTickerTick();

	void ThreadBegin();
	void ThreadEnd();
	
	virtual void Run(void *Params);
	virtual void Kill(void);
	virtual void Render(void);
	virtual void Config();
	virtual void Mouse(int x, int y, bool lmb, bool mmb, bool rmb );
	virtual void MouseDBLClick(int x, int y);
	virtual void OnInitGL();
	virtual void OnZoom(double Scale);
		
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