#ifndef __TOOLS_H
#define __TOOLS_H

#include <wx/wx.h>
#include "NaviBroker.h"
#include "reader.h"
#include "GeometryConfig.h"

wxString GetProductInfo();
wxString GetProductName();
wxMutex *GetMutex();
void FreeMutex();

wxMutex *GetSearchMutex();
void FreeSearchMutex();
void InitSearchMutex();

wxString GetPluginConfigPath();
wxString GetPluginDataFilePath();
wxString GetWorkDir(void);
void PrintInfo(CNaviBroker *Broker,wchar_t *text);	// drukuj info na mapie
char **ExplodeStr(const char *str, const char *separator, int *size);
void FreeStrList(char **list, int length);
time_t GetUTCTimeNow(void);
char *GetSentenceFromLine(const char *line, const char *identyfier);
int MemPos(const unsigned char *Memory, int MemorySize, const unsigned char *Search, int SearchSize, int StartAt = 0 );
const wchar_t *GetMsg(int id);
bool SetGlobalPrioryty(int fid);
bool Set_RMC_COG();
bool Set_VTG_COG();
bool Check_HDT();
int GetLanguageId();
CReader *CreateSerialDevice(wxString name, char *port, int baud, int dtype, bool run);
CReader *CreateSocketDevice(wxString name, wxString host, int port, int dtype, bool run);
double _nvToRad( double angle );
void Reset(double *tab);
void RotateZ( double x, double y, double &out_x, double &out_y, double radangle);
double nvDistance(double lon1, double lat1, double lon2, double lat2, int distanceunit);
bool IsUndefined(double *idx, size_t size);
void SetFrequencyTable(int id);
int GetMaxFrequency();
int GetFrequency(int id);
void NewLonLat(int seconds, double lon, double lat, double sog, double cog, double *new_lon, double *new_lat);
bool IsPointInsideMesh(nvPoint2f *point, nvPoint2d *points, int points_length, int *indices, int indices_length );
wxString ConvertDegree(float degree);
wxString FormatLongitude(float x); 
wxString FormatLatitude(float y);
void InitMutex();
double GetShipHeight(SAisData *ptr);
double GetShipWidth(SAisData *ptr);
double ToPort(SAisData *ptr);
double ToBow(SAisData *ptr);
double ToStern(SAisData *ptr);
double ToStarboard(SAisData *ptr);
double GetTriangleWidth(double smooth_scale);
double GetTriangleHeight(double smooth_scale);
wxString GetAisFile();
wxString RGBAToStr(nvRGBA *RGB);
nvRGBA StrToRGBA(wxString str);
double GetMilesPerDegree(double x, double y);
double nvBearing(double lon1, double lat1, double lon2, double lat2);
bool GetShipImage(int mmsi, char *&buffer, int *size);
#endif