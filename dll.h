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
#include "positiondialog.h"
#include "reader.h"
#include "object.h"
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
	//double m_ShipState[MAX_SHIP_VALUES_LEN];
	double m_ShipStaticState[MAX_SHIP_VALUES_LEN];
	double m_ShipOldStaticState[MAX_SHIP_VALUES_LEN]; // dane starsze o jeden tick
	//double m_ShipGlobalState[MAX_SHIP_VALUES_LEN];
	int m_ShipTicks[MAX_SHIP_VALUES_LEN];
	int m_ShipTimes[MAX_SHIP_VALUES_LEN];
	bool m_ShipValidFrequencyTable[MAX_SHIP_VALUES_LEN];
	bool m_ShipValidFrequency;
	double m_LastHDT;
	int m_OldPositionTick, m_OldHDTTick;
	int m_SignalID, m_MaxFrequencyID;
	int m_GlobalFrequency[MAX_SHIP_VALUES_LEN];
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
	CTicker *m_Ticker1, *m_Ticker2, *m_TickerAnim;
	//double m_MilesPerDeg;
	nvFastFont *m_NameFont, *m_MMSIFont;
	bool m_Prepare;
	int m_MaxFrequency;
	int m_ShipTick;
	int m_ShipInterval,m_AisBufferInterval;
	bool m_Position_Exists,m_NewHDT;
	bool m_HDTChanged,m_PositionChanged, m_LATChanged ,m_LONChanged;
	bool m_Interpolation;
	double m_OldHDT;
	int m_GlobalTick, m_OldGlobalTick;
	double m_Factor;
	float m_MapScale,m_OldMapScale;
	double m_MapX,m_MapY,m_MouseLmbX,m_MouseLmbY;
	int m_SelectedVertexId;
	nvPoint2f ptt0,ptt1;
	bool m_FirstTime;
	double m_ScreenX1,m_ScreenY1,m_ScreenX2,m_ScreenY2;
	int m_CurrentId;
	bool m_MouseLmb, m_MouseDLmb,m_MouseUp;
	CMyFrame *m_MyFrame;
	nvCircle m_MapCircle;
	bool m_Render;
	int m_COGTime,m_HDTTime;
	bool m_SearchTextChanged,m_FilterChanged;
	float m_AnimMarkerSize;
	bool m_AnimStarted;
	int	m_AnimTick;
	double m_Angle;
	int m_BufferCount;


	TTexture *m_TextureTGA_0;
	GLuint m_TextureID_0;
	GLuint m_SmallShipArrayBuffer, m_SmallShipTriangleIndicesBuffer, m_SmallShipLineIndicesBuffer, m_SmallShipColorBuffer;
	GLuint m_ShipsArrayBuffer, m_ShipsLineIndicesBuffer, m_ShipsTriangleIndicesBuffer,m_ShipsColorBuffer;
	GLuint m_TrianglesArrayBuffer, m_TrianglesTriangleIndicesBuffer,m_TrianglesLineIndicesBuffer, m_TrianglesColorBuffer;
	GLuint m_AtonArrayBuffer, m_AtonTriangleIndicesBuffer, m_AtonLineIndicesBuffer, m_AtonColorBuffer;
	GLuint m_BSArrayBuffer, m_BSTriangleIndicesBuffer, m_BSLineIndicesBuffer, m_BSColorBuffer;
	GLuint m_ShipLightsArrayBuffer,m_ShipLightsTriangleIndicesBuffer;
	GLuint m_SARArrayBuffer,m_SARTriangleIndicesBuffer,m_SARLineIndicesBuffer,m_SARColorBuffer;

	int m_SmallShipTriangleLength, m_SmallShipLineLength;
	int m_TrianglesTriangleLength, m_TrianglesLineLength;
	int m_ShipTriangleLength, m_ShipLineLength;
	int m_AtonTriangleLength, m_AtonLineLength;
	int m_BSTriangleLength, m_BSLineLength;
	int m_ShipLightsTriangleLength;
	int m_SARLineLength, m_SARTriangleLength;

	bool m_Ready;
	int m_ThreadCounter;
	bool m_ShipRender;
	bool m_ShowFrameWindow;
	nvPoint2d m_HdtPoint,m_HdtLastPoint;
	CPositionDialog *m_PositionDialog;
	//int m_FakeCounter;


	// bufory punkt�w
	// SHIP
	CNaviArray <nvPoint2d> m_PointsBuffer0;					CNaviArray <nvPoint2d> m_PointsBuffer1;					CNaviArray <nvPoint2d> *m_CurrentPointsBufferPtr;				// bufor punkt�w tr�jk�t�w SHIP
	CNaviArray <nvPoint2d> m_ShipVerticesBuffer0;			CNaviArray <nvPoint2d> m_ShipVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentShipVerticesBufferPtr;			// bufor index�w tr�jk�t�w SHIP
	CNaviArray <int> m_ShipTriangleIndicesBuffer0;			CNaviArray <int>  m_ShipTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentShipTriangleIndicesBufferPtr;
	CNaviArray <int> m_ShipLineIndicesBuffer0;				CNaviArray <int>  m_ShipLineIndicesBuffer1;				CNaviArray <int> *m_CurrentShipLineIndicesBufferPtr;			// bufor index�w lini SHIP
	CNaviArray <nvRGBA> m_ShipColorBuffer0;					CNaviArray <nvRGBA> m_ShipColorBuffer1;					CNaviArray <nvRGBA> *m_CurrentShipColorBufferPtr;
	
	// SHIP tr�jkat
	CNaviArray <nvPoint2d> m_TriangleVerticesBuffer0;		CNaviArray <nvPoint2d> m_TriangleVerticesBuffer1;		CNaviArray <nvPoint2d> *m_CurrentTriangleVerticesBufferPtr;
	CNaviArray <int> m_TrianglesTriangleIndicesBuffer0;		CNaviArray <int>  m_TrianglesTriangleIndicesBuffer1;	CNaviArray <int> *m_CurrentTrianglesTriangleIndicesBufferPtr;	// bufor index�w tr�jk�t�w SHIP
	CNaviArray <int> m_TrianglesLineIndicesBuffer0;			CNaviArray <int>  m_TrianglesLineIndicesBuffer1;		CNaviArray <int> *m_CurrentTrianglesLineIndicesBufferPtr;		// bufor index�w lini SHIP
	CNaviArray <nvRGBA> m_TrianglesColorBuffer0;			CNaviArray <nvRGBA> m_TrianglesColorBuffer1;			CNaviArray <nvRGBA> *m_CurrentTrianglesColorBufferPtr;
	
	// SHIP small ship
	CNaviArray <nvPoint2d> m_SmallShipVerticesBuffer0;		CNaviArray <nvPoint2d> m_SmallShipVerticesBuffer1;		CNaviArray <nvPoint2d> *m_CurrentSmallShipVerticesBufferPtr;
	CNaviArray <int> m_SmallShipTriangleIndicesBuffer0;		CNaviArray <int>  m_SmallShipTriangleIndicesBuffer1;	CNaviArray <int> *m_CurrentSmallShipTriangleIndicesBufferPtr;	// bufor index�w tr�jk�t�w SHIP
	CNaviArray <int> m_SmallShipLineIndicesBuffer0;			CNaviArray <int>  m_SmallShipLineIndicesBuffer1;		CNaviArray <int> *m_CurrentSmallShipLineIndicesBufferPtr;		// bufor index�w lini SHIP
	CNaviArray <nvRGBA> m_SmallShipColorBuffer0;			CNaviArray <nvRGBA> m_SmallShipColorBuffer1;			CNaviArray <nvRGBA> *m_CurrentSmallShipColorBufferPtr;

	//SHIP linie HDG,COG,Turn(ROT)
	CNaviArray <nvPoint2d> m_COGVerticesBuffer0;			CNaviArray <nvPoint2d> m_COGVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentCOGVerticesBufferPtr;			// SHIP linie COG
	CNaviArray <nvPoint2d> m_HDGVerticesBuffer0;			CNaviArray <nvPoint2d> m_HDGVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentHDGVerticesBufferPtr;			// SHIP linie HDG
	CNaviArray <nvPoint2d> m_ROTVerticesBuffer0;			CNaviArray <nvPoint2d> m_ROTVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentROTVerticesBufferPtr;			// SHIP linie HDG
	
	// bufor punkt�w tr�jk�t�w ATON
	CNaviArray <nvPoint2d> m_AtonVerticesBuffer0;			CNaviArray <nvPoint2d> m_AtonVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentAtonVerticesBufferPtr;
	CNaviArray <int> m_AtonTriangleIndicesBuffer0;			CNaviArray <int> m_AtonTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentAtonTriangleIndicesBufferPtr;
	CNaviArray <int> m_AtonLineIndicesBuffer0;				CNaviArray <int> m_AtonLineIndicesBuffer1;				CNaviArray <int> *m_CurrentAtonLineIndicesBufferPtr;
	CNaviArray <nvRGBA> m_AtonColorBuffer0;					CNaviArray <nvRGBA> m_AtonColorBuffer1;					CNaviArray <nvRGBA> *m_CurrentAtonColorBufferPtr;

	// bufor punkt�w tr�jk�t�w BS
	CNaviArray <nvPoint2d> m_BSVerticesBuffer0;				CNaviArray <nvPoint2d> m_BSVerticesBuffer1;				CNaviArray <nvPoint2d> *m_CurrentBSVerticesBufferPtr;
	CNaviArray <int> m_BSTriangleIndicesBuffer0;			CNaviArray <int> m_BSTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentBSTriangleIndicesBufferPtr;
	CNaviArray <int> m_BSLineIndicesBuffer0;				CNaviArray <int> m_BSLineIndicesBuffer1;				CNaviArray <int> *m_CurrentBSLineIndicesBufferPtr;
	CNaviArray <nvRGBA> m_BSColorBuffer0;					CNaviArray <nvRGBA> m_BSColorBuffer1;					CNaviArray <nvRGBA> *m_CurrentBSColorBufferPtr;

	// bufor �wiate�
	//CNaviArray <nvPoint2d> m_ShipLightsVerticesBuffer0;	CNaviArray <nvPoint2d> m_ShipLightsVerticesBuffer1;		CNaviArray <nvPoint2d> *m_CurrentShipLightsVerticesBufferPtr;
	//CNaviArray <int> m_ShipLightsTriangleIndicesBuffer0;	CNaviArray <int> m_ShipLightsTriangleIndicesBuffer1;	CNaviArray <int> *m_CurrentShipLightsTriangleIndicesBufferPtr;
	
	// bufor track
	CNaviArray <nvPoint2d> m_TrackVerticesBuffer0;			CNaviArray <nvPoint2d> m_TrackVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentTrackVerticesBufferPtr;

	// bufor SAR
	CNaviArray <nvPoint2d> m_SARVerticesBuffer0;			CNaviArray <nvPoint2d> m_SARVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentSARVerticesBufferPtr;
	CNaviArray <int> m_SARTriangleIndicesBuffer0;			CNaviArray <int> m_SARTriangleIndicesBuffer1;			CNaviArray <int> *m_CurrentSARTriangleIndicesBufferPtr;
	CNaviArray <int> m_SARLineIndicesBuffer0;				CNaviArray <int> m_SARLineIndicesBuffer1;				CNaviArray <int> *m_CurrentSARLineIndicesBufferPtr;

	// bufor kolizyjnych punkt�w statkow CPA
	//CNaviArray <nvPoint2d> m_CPAVerticesBuffer0;			CNaviArray <nvPoint2d> m_CPAVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentCPAVerticesBufferPtr;			// CPA linie

	// bufor kolizyjnych punkt�w SHIP CPA
	//CNaviArray <nvPoint2d> m_ShipCPAVerticesBuffer0;		CNaviArray <nvPoint2d> m_ShipCPAVerticesBuffer1;			CNaviArray <nvPoint2d> *m_CurrentShipCPAVerticesBufferPtr;			// Ship CPA linie

	//Swiat�a
	CObject *m_Light0, *m_Light1, *m_Light2;

	//Fake ship
	CObject *m_CPA,*m_ShipCPA;
	CObject	*m_FakeShip,*m_FakeBow,*m_FakeStern;
	CNaviArray <SAisData> m_FakeShips;
	nvPoint2d m_ShipBow ,m_ShipStern;
	

	CNaviArray <CObject*> m_ObjectArray;

	CNaviArray <SIdToId> m_IdToTriangleId;
	CNaviArray <SIdToId> m_IdToShipId;
	CNaviArray <SIdToId> m_IdToAtonId;
	CNaviArray <SIdToId> m_IdToSmallShipId;
	CNaviArray <SIdToId> m_IdToBSId;
	CNaviArray <SIdToId> m_IdToSARId;

	// bufor koordynat tekstur
	//CNaviArray <nvPoint2float> m_TriangleTexCoordsBuffer0;
	//CNaviArray <nvPoint2float>  m_TriangleTexCoordsBuffer1;
	// pointer na aktualny bufor
	//CNaviArray <nvPoint2float> *m_CurrentTriangleTexCoordsBufferPtr;
	
	// bufor nazw obiekt�w mmsi, shipname
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
	void PrepareCPABuffer();
	void PrepareCPAFontBuffer(SAisData *ptr1, SAisData *ptr2, double cpa, double tcpa, double d1, double d2);
	void PrepareShipCPABuffer();
	void PrepareAisBuffer();
	void PrepareSearchBuffer();
	void PrepareTimeoutBuffer();
	void PreparePointsBuffer(SAisData *ptr);
	void PrepareShipNamesBuffer(SAisData *ptr);
	void PrepareShipLightsBuffer(SAisData *ptr);
	void PrepareShipLightsBuffer0(SAisData *ptr);
	void PrepareShipLightsBuffer1(SAisData *ptr);
	void PrepareShipLightsBuffer2(SAisData *ptr);
	void PrepareShipLightsVerticesBuffer(SAisData *ptr);
	void PrepareShipLightsTriangleIndicesBuffer(SAisData *ptr);
	
	// bufor tr�jkat�w
	void PrepareTriangleVerticesBuffer(SAisData *ptr);			//vertexy
	void PrepareTriangleTriangleIndicesBuffer(SAisData *ptr);   //indexy
	void PrepareTriangleLineIndicesBuffer(SAisData *ptr);		//indexy lini
	void PrepareTriangleColorBuffer(SAisData *ptr);				//kolory

	// bufor ma�ych statkow
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

	//buffor tras statkow
	void PrepareTrackVerticesBuffer(SAisData *ptr);
	//bufor SAR
	void PrepareSARVerticesBuffer(SAisData *ptr);
	void PrepareSARTriangleIndicesBuffer(SAisData *ptr);
	void PrepareSARLineIndicesBuffer(SAisData *ptr);

	// bufor lini COG
	void PrepareCOGVerticesBuffer(SAisData *ptr);
	// bufor linii HDG
	void PrepareHDGVerticesBuffer(SAisData *ptr);
	
	// bufor ROT
	void PrepareROTVerticesBuffer(SAisData *ptr,double angle, bool right);
	//void PrepareROTLineIndicesBuffer(SAisData *ptr, bool right);

	//bufor CPA
	void PrepareCPAVerticesBuffer(nvPoint2d pt1, nvPoint2d pt2);

	//bufor CPA
	void PrepareShipCPAVerticesBuffer(SAisData *ptr);

	bool IsOnScreen(double x , double y);
	bool VisibleStateChanged();
	void RunThread();
	void SendShipData();
	bool NewPosition(int time);
	bool NewHDT(int time,double *va);
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
	bool CreateSARVBO();
	//void CopySelectedPtr(SAisData *ptr);
	//void FreeSelectedPtr();

	void DeleteShipsVBO();
	void DeleteTrianglesVBO();
	void RenderShipNames();
	void RenderSelection();
	void SetInvalid();
	void SetFrequency(int id);
	void SetShip(SFunctionData *data);
	void SetSmoothScale(double _Scale);
	void SetValues(bool lmb);
	bool IsTriangleBuffer();
	bool IsShipBuffer();
	bool IsSARBuffer();
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
	void SelectSAR();
	void ShowFrameWindow(bool show);
	void Synchro();
	void SendSynchroSignal();
	void ShowMenu();
	void SetAngle(SAisData *ptr);
	void CheckCollision();
	void CheckShipCollision();
	void _SetShipPosition();
	

	// fake ship
	void OnSetShip();		//ustawia ship danymi z urzadzenia
	void FakeShipBuffer(SAisData ptr);
	void FakeArrow(nvPoint2d p1, nvPoint2d p2, float hdg1, float hdg2, CObject *ptr);
	///................................
		
	void PrepareShipBuffer(SAisData *ptr);
	void PrepareAtonBuffer(SAisData *ptr);
	void PrepareBSBuffer(SAisData *ptr);
	void PrepareTriangleBuffer(SAisData *ptr);
	void CheckTriangleBuffer(SAisData *ptr);
	void PrepareSARBuffer(SAisData *ptr);
	void PrepareROTBuffer(SAisData *ptr);
		
	void Generate();
	void RenderGPS();
	void RenderCOG();
	void RenderHDT();
	void RenderROT();
	void RenderCPA();
	void RenderShipCPA();
	void RenderFakeShip();
	void RenderTracks();
	void RenderBS();
	void RenderSmallScale();
	void RenderNormalScale();
	void RenderAnimation();
	void _RenderROT();
	void _RenderShips();
	void _RenderSmallShips();
	void _RenderTriangles();
	void _RenderAtons();
	void _RenderBS();
	void _RenderShipLights();
	void _RenderSAR();

	void RenderSmallShips();
	void RenderPosition();
	void RenderShips();
	void RenderTriangles();
	void RenderPoints();
	void RenderAtons();
	void RenderSAR();
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
	void AddDeviceFunc(CReader *ptr); // pomocnicza funkcja kiedy urzadzenie dodawane z display plugina wysy�any jest sygna� zwrotny
	void RemoveDevice(CReader *ptr);
	void StartDevice(CReader *ptr);
	void StopDevice(CReader *ptr);
	void ReindexDevices();
	void SetPosition();
	void SetShip(int id,double value);
		
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

	void OnTickerAnimTick();

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
	virtual void SetLanguage(int LanguageID);
		
	// funkcje dost�pne dla innych plugin�w
	static void *OnDeviceSignal(void *NaviMapIOApiPtr, void *Params);	// serial signal (recnnec, on data etc...)
	static void *OnDeviceData(void *NaviMapIOApiPtr, void *Params);		// dane kt�re by�y w definicji s� dost�pne
	static void *GetParentPtr(void *NaviMapIOApiPtr, void *Params);
	static void *AddDevice(void *NaviMapIOApiPtr, void *Params);
	static void *OnFunctionData(void *NaviMapIOApiPtr, void *Params);
	static void *OnNewAisObject(void *NaviMapIOApiPtr, void *Params);	// nowe dane do tablicy ais
	static void *OnData(void *NaviMapIOApiPtr, void *Params);			// dane
	static void *GetAisCount(void *NaviMapIOApiPtr, void *Params);		// ais count
	static void *GetAisItem(void *NaviMapIOApiPtr, void *Params);		// ais count
	static void *OnSynchro(void *NaviMapIOApiPtr, void *Params);		// opcje
	static void *MutexLock(void *NaviMapIOApiPtr, void *Params);		// mutex lock
	static void *MutexUnlock(void *NaviMapIOApiPtr, void *Params);		// mutex unlock
		
};	

#ifdef __cplusplus
}
#endif

#endif