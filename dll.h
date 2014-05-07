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
	CTicker *m_Ticker1, *m_Ticker2;
	//double m_MilesPerDeg;
	nvFastFont *m_NameFont, *m_MMSIFont;
	bool m_Prepare;
	int m_MaxFrequency;
	int m_ShipTick;
	int m_ShipInterval,m_AisBufferInterval;
	bool m_PositionExists;
	bool m_Interpolation;
	double m_OldHDT;
	int m_GlobalTick, m_OldGlobalTick;
	double m_SmoothScaleFactor, m_Factor;
	float m_MapScale,m_OldMapScale;
	double m_MapX,m_MapY,m_MouseLmbX,m_MouseLmbY;
	int m_SelectedVertexId;
	nvPoint2f ptt0,ptt1;
	bool m_FirstTime;
	double m_ScreenX1,m_ScreenY1,m_ScreenX2,m_ScreenY2;
	int m_CurrentId;
	SAisData *m_SelectedPtr,*m_BufferedSelectedPtr;
	bool m_MouseLmb, m_MouseDLmb,m_MouseUp;
	CMyFrame *m_MyFrame;
	nvCircle m_MapCircle;
	bool m_Render;
	int m_COGTime,m_HDTTime;
	bool m_SearchTextChanged,m_FilterChanged;


	TTexture *m_TextureTGA_0;
	GLuint m_TextureID_0;
	GLuint m_SmallShipArrayBuffer, m_SmallShipTriangleIndicesBuffer, m_SmallShipLineIndicesBuffer, m_SmallShipColorBuffer;
	GLuint m_ShipsArrayBuffer, m_ShipsLineIndicesBuffer, m_ShipsTriangleIndicesBuffer,m_ShipsColorBuffer;
	GLuint m_TrianglesArrayBuffer, m_TrianglesTriangleIndicesBuffer,m_TrianglesLineIndicesBuffer, m_TrianglesColorBuffer;
	GLuint m_AtonArrayBuffer, m_AtonTriangleIndicesBuffer, m_AtonLineIndicesBuffer, m_AtonColorBuffer;
	GLuint m_BSArrayBuffer, m_BSTriangleIndicesBuffer, m_BSLineIndicesBuffer, m_BSColorBuffer;
	GLuint m_ShipLightsArrayBuffer,m_ShipLightsTriangleIndicesBuffer;

	int m_SmallShipTriangleLength, m_SmallShipLineLength;
	int m_TrianglesTriangleLength, m_TrianglesLineLength ;
	int m_ShipTriangleLength, m_ShipLineLength;
	int m_AtonTriangleLength, m_AtonLineLength;
	int m_BSTriangleLength, m_BSLineLength;
	int m_ShipLightsTriangleLength;

	bool m_Ready;
	int m_ThreadCounter;
	bool m_ShipRender;
	bool m_ShowFrameWindow;


	// bufory punktów
	// SHIP
	CNaviArray <nvPoint2d> m_PointsBuffer0;					CNaviArray <nvPoint2d> m_PointsBuffer1;					CNaviArray <nvPoint2d> *m_CurrentPointsBufferPtr;				// bufor punktów trójk¹tów SHIP
	CNaviArray <nvPoint2d> m_ShipVerticesBuffer0;			CNaviArray <nvPoint2d> m_ShipVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentShipVerticesBufferPtr;			// bufor indexów trójk¹tów SHIP
	CNaviArray <int> m_ShipTriangleIndicesBuffer0;			CNaviArray <int>  m_ShipTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentShipTriangleIndicesBufferPtr;
	CNaviArray <int> m_ShipLineIndicesBuffer0;				CNaviArray <int>  m_ShipLineIndicesBuffer1;				CNaviArray <int> *m_CurrentShipLineIndicesBufferPtr;			// bufor indexów lini SHIP
	CNaviArray <nvRGBA> m_ShipColorBuffer0;					CNaviArray <nvRGBA> m_ShipColorBuffer1;					CNaviArray <nvRGBA> *m_CurrentShipColorBufferPtr;
	
	// SHIP trójkat
	CNaviArray <nvPoint2d> m_TriangleVerticesBuffer0;		CNaviArray <nvPoint2d> m_TriangleVerticesBuffer1;		CNaviArray <nvPoint2d> *m_CurrentTriangleVerticesBufferPtr;
	CNaviArray <int> m_TrianglesTriangleIndicesBuffer0;		CNaviArray <int>  m_TrianglesTriangleIndicesBuffer1;	CNaviArray <int> *m_CurrentTrianglesTriangleIndicesBufferPtr;	// bufor indexów trójk¹tów SHIP
	CNaviArray <int> m_TrianglesLineIndicesBuffer0;			CNaviArray <int>  m_TrianglesLineIndicesBuffer1;		CNaviArray <int> *m_CurrentTrianglesLineIndicesBufferPtr;		// bufor indexów lini SHIP
	CNaviArray <nvRGBA> m_TrianglesColorBuffer0;			CNaviArray <nvRGBA> m_TrianglesColorBuffer1;			CNaviArray <nvRGBA> *m_CurrentTrianglesColorBufferPtr;
	
	// SHIP small ship
	CNaviArray <nvPoint2d> m_SmallShipVerticesBuffer0;		CNaviArray <nvPoint2d> m_SmallShipVerticesBuffer1;		CNaviArray <nvPoint2d> *m_CurrentSmallShipVerticesBufferPtr;
	CNaviArray <int> m_SmallShipTriangleIndicesBuffer0;		CNaviArray <int>  m_SmallShipTriangleIndicesBuffer1;	CNaviArray <int> *m_CurrentSmallShipTriangleIndicesBufferPtr;	// bufor indexów trójk¹tów SHIP
	CNaviArray <int> m_SmallShipLineIndicesBuffer0;			CNaviArray <int>  m_SmallShipLineIndicesBuffer1;		CNaviArray <int> *m_CurrentSmallShipLineIndicesBufferPtr;		// bufor indexów lini SHIP
	CNaviArray <nvRGBA> m_SmallShipColorBuffer0;			CNaviArray <nvRGBA> m_SmallShipColorBuffer1;			CNaviArray <nvRGBA> *m_CurrentSmallShipColorBufferPtr;

	//SHIP linie HDG,COG
	CNaviArray <nvPoint2d> m_COGVerticesBuffer0;			CNaviArray <nvPoint2d> m_COGVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentCOGVerticesBufferPtr;			// SHIP linie COG
	CNaviArray <nvPoint2d> m_HDGVerticesBuffer0;			CNaviArray <nvPoint2d> m_HDGVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentHDGVerticesBufferPtr;			// SHIP linie HDG
	
	// bufor punktów trójk¹tów ATON
	CNaviArray <nvPoint2d> m_AtonVerticesBuffer0;			CNaviArray <nvPoint2d> m_AtonVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentAtonVerticesBufferPtr;
	CNaviArray <int> m_AtonTriangleIndicesBuffer0;			CNaviArray <int> m_AtonTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentAtonTriangleIndicesBufferPtr;
	CNaviArray <int> m_AtonLineIndicesBuffer0;				CNaviArray <int> m_AtonLineIndicesBuffer1;				CNaviArray <int> *m_CurrentAtonLineIndicesBufferPtr;
	CNaviArray <nvRGBA> m_AtonColorBuffer0;					CNaviArray <nvRGBA> m_AtonColorBuffer1;					CNaviArray <nvRGBA> *m_CurrentAtonColorBufferPtr;

	// bufor punktów trójk¹tów BS
	CNaviArray <nvPoint2d> m_BSVerticesBuffer0;				CNaviArray <nvPoint2d> m_BSVerticesBuffer1;				CNaviArray <nvPoint2d> *m_CurrentBSVerticesBufferPtr;
	CNaviArray <int> m_BSTriangleIndicesBuffer0;			CNaviArray <int> m_BSTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentBSTriangleIndicesBufferPtr;
	CNaviArray <int> m_BSLineIndicesBuffer0;				CNaviArray <int> m_BSLineIndicesBuffer1;				CNaviArray <int> *m_CurrentBSLineIndicesBufferPtr;
	CNaviArray <nvRGBA> m_BSColorBuffer0;					CNaviArray <nvRGBA> m_BSColorBuffer1;					CNaviArray <nvRGBA> *m_CurrentBSColorBufferPtr;

	// bufor œwiate³
	CNaviArray <nvPoint2d> m_ShipLightsVerticesBuffer0;		CNaviArray <nvPoint2d> m_ShipLightsVerticesBuffer1;		CNaviArray <nvPoint2d> *m_CurrentShipLightsVerticesBufferPtr;
	CNaviArray <int> m_ShipLightsTriangleIndicesBuffer0;	CNaviArray <int> m_ShipLightsTriangleIndicesBuffer1;	CNaviArray <int> *m_CurrentShipLightsTriangleIndicesBufferPtr;

	CNaviArray <SIdToId> m_IdToTriangleId;
	CNaviArray <SIdToId> m_IdToShipId;
	CNaviArray <SIdToId> m_IdToAtonId;
	CNaviArray <SIdToId> m_IdToSmallShipId;
	CNaviArray <SIdToId> m_IdToBSId;
	// bufor koordynat tekstur
	//CNaviArray <nvPoint2float> m_TriangleTexCoordsBuffer0;
	//CNaviArray <nvPoint2float>  m_TriangleTexCoordsBuffer1;
	// pointer na aktualny bufor
	//CNaviArray <nvPoint2float> *m_CurrentTriangleTexCoordsBufferPtr;
	
	// bufor nazw obiektów mmsi, shipname
	CNaviArray <SAisNames*> m_ShipNamesBuffer0;
	CNaviArray <SAisNames*> m_ShipNamesBuffer1;
	// pointer na aktualny bufor
	CNaviArray <SAisNames*> *m_CurrentShipNamesBufferPtr;
	
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
	void PrepareAisBuffer();
	void PrepareSearchBuffer();
	void PrepareTimeoutBuffer();
	void PreparePointsBuffer(SAisData *ptr);
	void PrepareShipNamesBuffer(SAisData *ptr);
	void PrepareShipLightsBuffer(SAisData *ptr);
	void PrepareShipLightsBuffer0(SAisData *ptr);
	//void PrepareShipLightsBuffer1(SAisData *ptr);
	//void PrepareShipLightsBuffer2(SAisData *ptr);
	void PrepareShipLightsVerticesBuffer(SAisData *ptr);
	void PrepareShipLightsTriangleIndicesBuffer(SAisData *ptr);
	
	// bufor trójkatów
	void PrepareTriangleVerticesBuffer(SAisData *ptr);			//vertexy
	void PrepareTriangleTriangleIndicesBuffer(SAisData *ptr);   //indexy
	void PrepareTriangleLineIndicesBuffer(SAisData *ptr);		//indexy lini
	void PrepareTriangleColorBuffer(SAisData *ptr);				//kolory

	// bufor trójkatów
	void PrepareSmallShipVerticesBuffer(SAisData *ptr);			//vertexy
	void PrepareSmallShipTriangleIndicesBuffer(SAisData *ptr);  //indexy
	void PrepareSmallShipLineIndicesBuffer(SAisData *ptr);		//indexy lini
	void PrepareSmallShipColorBuffer(SAisData *ptr);			//kolory

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

	// bufor base station
	void PrepareBSVerticesBuffer(SAisData *ptr);
	void PrepareBSTriangleIndicesBuffer(SAisData *ptr);
	void PrepareBSLineIndicesBuffer(SAisData *ptr);
	void PrepareBSColorBuffer(SAisData *ptr);
	
	
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
	void Interpolate();
	bool InterpolatePosition();
	bool InterpolateHDT();
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateTextures(void);
	bool CreateShipsVBO();
	bool CreateTrianglesVBO();
	bool CreateSmallShipsVBO();
	bool CreateAtonsVBO();
	bool CreateBSVBO();
	bool CreateShipLightsVBO();
	//void CopySelectedPtr(SAisData *ptr);
	//void FreeSelectedPtr();

	void DeleteShipsVBO();
	void DeleteTrianglesVBO();
	void RenderShipNames();
	void RenderSelection();
	void SetInvalid();
	void SetFrequency(int id);
	void SetShip(SFunctionData *data);
	void SetSmoothScaleFactor(double _Scale);
	void SetValues(bool lmb);
	bool IsTriangleBuffer();
	bool IsShipBuffer();
	bool IsSmallShipBuffer();
	bool IsShipLightsBuffer();
	bool IsAtonBuffer();
	bool IsBSBuffer();
	void SetSelection();
	void CopyInt(CNaviArray <int> *a, CNaviArray <int> *b);
	void CopyNvPoint2d(CNaviArray <nvPoint2d> *src, CNaviArray <nvPoint2d> *dst);
	void CopyNvRGBA(CNaviArray <nvRGBA> *src, CNaviArray <nvRGBA> *dst);
	void CopySAisNames(CNaviArray <SAisNames*> *src, CNaviArray <SAisNames*> *dst);
	void SetPtr0();
	void SetPtr1();
	void CopyBuffers();
	void SetBuffers();
	void ClearBuffers();
	void SelectShip();
	void SelectSmallShip();
	void SelectTriangle();
	void SelectAton();
	void SelectBS();
	void ShowFrameWindow(bool show);
	void Synchro();
	void SendSynchroSignal();
	void ShowMenu();
	
	void PrepareShipBuffer(SAisData *ptr);
	void PrepareAtonBuffer(SAisData *ptr);
	void PrepareBSBuffer(SAisData *ptr);
	void PrepareTriangleBuffer(SAisData *ptr);
	void CheckTriangleBuffer(SAisData *ptr);
		
	void Generate();
	void RenderGPS();
	void RenderCOG();
	void RenderHDT();
	void RenderBS();
	void RenderSmallScale();
	void RenderNormalScale();
	void _RenderShips();
	void _RenderSmallShips();
	void _RenderTriangles();
	void _RenderAtons();
	void _RenderBS();
	void _RenderShipLights();

	void RenderSmallShips();
	void RenderPosition();
	void RenderShips();
	void RenderTriangles();
	void RenderPoints();
	void RenderAtons();
	void RenderShipLights();
	

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
	void ReindexDevices();
	SAisData *GetSelectedPtr();
	
	SData *GetData();
	wxArrayPtrVoid *GetDevicesList();
	
	int GetDisplaySignalType();
	int GetDeviceId();
	bool GetEnableControlsFlag();

	void OnTicker1Start();
	void OnTicker1Stop();
	void OnTicker1Tick();

	void OnTicker2Start();
	void OnTicker2Stop();
	void OnTicker2Tick();

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
	static void *OnData(void *NaviMapIOApiPtr, void *Params);			// dane
	static void *GetAisBuffer(void *NaviMapIOApiPtr, void *Params);		// ais buffer
	static void *OnSynchro(void *NaviMapIOApiPtr, void *Params);		// opcje
	
};	

#ifdef __cplusplus
}
#endif

#endif