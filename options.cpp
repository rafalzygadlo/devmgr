#include "conf.h"
#include "tools.h"
#include "options.h"
#include <wx/stdpaths.h>
#include <wx/fileconf.h>

double m_FontSize = DEFAULT_FONT_SIZE;
bool m_ShowNames = false;
bool m_ShowHDT = true;
bool m_ShowCOG = true;
bool m_ShowGPS = true;
bool m_ShowObjects = true;
int m_Filter = DEFAULT_FILTER;
char m_SearchText[64];
int m_Frequency = DEFAULT_FREQUENCY;
int m_ViewFontScale = DEFAULT_VIEW_FONT_SCALE;
int m_COGTime = DEFAULT_COG_TIME;
int m_HDTTime = DEFAULT_HDT_TIME;
int m_COGLineWidth = DEFAULT_COG_LINE_WIDTH;
int m_HDTLineWidth = DEFAULT_HDT_LINE_WIDTH;
int m_COGLineStyle = DEFAULT_COG_LINE_STYLE;
int m_HDTLineStyle = DEFAULT_HDT_LINE_STYLE;
bool m_SearchTextChanged = true;
bool m_FilterChanged = true;
bool m_AisDataChanged = true;
bool m_StartAnimation = false;
int m_AisTimeout = AIS_TIMEOUT;
int m_AisTimeoutRemove = AIS_TIMEOUT_REMOVE;
bool m_SetShipPosition = false;
double m_ShipState[MAX_SHIP_VALUES_LEN];
double m_ShipGlobalState[MAX_SHIP_VALUES_LEN];

float m_CPA = DEFAULT_CPA;
float m_TCPA = DEFAULT_TCPA;
bool m_VTSMode = false;

nvRGBA ColorShip0A, ColorShip1A, ColorShip2A, ColorShipBorderA;
nvRGBA ColorShip0B, ColorShip1B, ColorShip2B, ColorShipBorderB;
nvRGBA ColorAton, ColorHDT, ColorCOG, ColorGPS, ColorBS;

void SetCPA(float val)
{
	m_CPA = val;
}

float GetCPA()
{
	return m_CPA;
}

void SetTCPA(float val)
{
	m_TCPA = val;
}

float GetTCPA()
{
	return m_TCPA;
}

void SetHDTLineStyle(int value)
{
	m_HDTLineStyle = value;
}

int  GetHDTLineStyle()
{
	return m_HDTLineStyle;
}

void SetCOGLineStyle(int value)
{
	m_COGLineStyle = value;
}

int GetCOGLineStyle()
{
	return m_COGLineStyle;
}

void SetHDTLineWidth(int value)
{
	m_HDTLineWidth = value;
}

int GetHDTLineWidth()
{
	return m_HDTLineWidth;
}

void SetCOGLineWidth(int value)
{
	m_COGLineWidth = value;
}

int GetCOGLineWidth()
{
	return m_COGLineWidth;
}

void SetCOGTime(int value)
{
	m_COGTime = value;
}

int GetCOGTime()
{
	return m_COGTime;
}

void SetHDTTime(int value)
{
	m_HDTTime = value;
}

int GetHDTTime()
{
	return m_HDTTime;
}

void SetFontSize( float size)
{
	m_FontSize = size/10;
}

float GetFontSize()
{
	return m_FontSize;
}

bool GetShowNames()
{
	return m_ShowNames;
}

void SetShowNames(bool value)
{
	m_ShowNames = value;
}

bool GetShowHDT()
{
	return m_ShowHDT;
}

void SetShowHDT(bool value)
{
	m_ShowHDT = value;
}

bool GetShowGPS()
{
	return m_ShowGPS;
}

void SetShowGPS(bool value)
{
	m_ShowGPS = value;
}

bool GetShowCOG()
{
	return m_ShowCOG;
}

void SetShowCOG(bool value)
{
	m_ShowCOG = value;
}

nvRGBA GetDefaultColor(int type)
{
	nvRGBA rgba;
	switch(type)
	{
		case SHIP_BORDER_COLORA:	rgba.R = 0;		rgba.G = 0;		rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_0A:			rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_1A:			rgba.R = 255;	rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_2A:			rgba.R = 255;	rgba.G = 0;		rgba.B = 0;		rgba.A = 200;	break;
		
		case SHIP_BORDER_COLORB:	rgba.R = 0;		rgba.G = 0;		rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_0B:			rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_1B:			rgba.R = 255;	rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_2B:			rgba.R = 255;	rgba.G = 0;		rgba.B = 0;		rgba.A = 200;	break;
		
		case ATON_COLOR:			rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case COG_COLOR:				rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case HDT_COLOR:				rgba.R = 0;		rgba.G = 0;		rgba.B = 255;	rgba.A = 200;	break;
		case GPS_COLOR:				rgba.R = 0;		rgba.G = 0;		rgba.B = 255;	rgba.A = 200;	break;
		case BASE_STATION_COLOR:	rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
	
	}
		
	return rgba;
}

nvRGBA GetColor(int type)
{
	nvRGBA rgba;
	switch(type)
	{
		case SHIP_BORDER_COLORA:	rgba.R = ColorShipBorderA.R;	rgba.G = ColorShipBorderA.G;	rgba.B = ColorShipBorderA.B;	rgba.A = ColorShipBorderA.A;	break;
		case SHIP_COLOR_0A:			rgba.R = ColorShip0A.R;			rgba.G = ColorShip0A.G;			rgba.B = ColorShip0A.B;			rgba.A = ColorShip0A.A;			break;
		case SHIP_COLOR_1A:			rgba.R = ColorShip1A.R;			rgba.G = ColorShip1A.G;			rgba.B = ColorShip1A.B;			rgba.A = ColorShip1A.A;			break;
		case SHIP_COLOR_2A:			rgba.R = ColorShip2A.R;			rgba.G = ColorShip2A.G;			rgba.B = ColorShip2A.B;			rgba.A = ColorShip2A.A;			break;
		case SHIP_BORDER_COLORB:	rgba.R = ColorShipBorderB.R;	rgba.G = ColorShipBorderB.G;	rgba.B = ColorShipBorderB.B;	rgba.A = ColorShipBorderB.A;	break;
		case SHIP_COLOR_0B:			rgba.R = ColorShip0B.R;			rgba.G = ColorShip0B.G;			rgba.B = ColorShip0B.B;			rgba.A = ColorShip0B.A;			break;
		case SHIP_COLOR_1B:			rgba.R = ColorShip1B.R;			rgba.G = ColorShip1B.G;			rgba.B = ColorShip1B.B;			rgba.A = ColorShip1B.A;			break;
		case SHIP_COLOR_2B:			rgba.R = ColorShip2B.R;			rgba.G = ColorShip2B.G;			rgba.B = ColorShip2B.B;			rgba.A = ColorShip2B.A;			break;
		case ATON_COLOR:			rgba.R = ColorAton.R;			rgba.G = ColorAton.G;			rgba.B = ColorAton.B;			rgba.A = ColorAton.A;			break;
		case COG_COLOR:				rgba.R = ColorCOG.R;			rgba.G = ColorCOG.G;			rgba.B = ColorCOG.B;			rgba.A = ColorCOG.A;			break;
		case HDT_COLOR:				rgba.R = ColorHDT.R;			rgba.G = ColorHDT.G;			rgba.B = ColorHDT.B;			rgba.A = ColorHDT.A;			break;
		case GPS_COLOR:				rgba.R = ColorGPS.R;			rgba.G = ColorGPS.G;			rgba.B = ColorGPS.B;			rgba.A = ColorGPS.A;			break;
		case BASE_STATION_COLOR:	rgba.R = ColorBS.R;				rgba.G = ColorBS.G;				rgba.B = ColorBS.B;				rgba.A = ColorBS.A;				break;
	}
		
	return rgba;
}

void SetColor(int type, nvRGBA color)
{
	switch(type)
	{
		case SHIP_BORDER_COLORA:	ColorShipBorderA.R = color.R;	ColorShipBorderA.G = color.G;	ColorShipBorderA.B = color.B;	ColorShipBorderA.A = color.A;	break;	
		case SHIP_COLOR_0A:			ColorShip0A.R = color.R;		ColorShip0A.G = color.G;		ColorShip0A.B = color.B;		ColorShip0A.A = color.A;		break;
		case SHIP_COLOR_1A:			ColorShip1A.R = color.R;		ColorShip1A.G = color.G;		ColorShip1A.B = color.B;		ColorShip1A.A = color.A;		break;
		case SHIP_COLOR_2A:			ColorShip2A.R = color.R;		ColorShip2A.G = color.G;		ColorShip2A.B = color.B;		ColorShip2A.A = color.A;		break;

		case SHIP_BORDER_COLORB:	ColorShipBorderB.R = color.R;	ColorShipBorderB.G = color.G;	ColorShipBorderB.B = color.B;	ColorShipBorderB.A = color.A;	break;	
		case SHIP_COLOR_0B:			ColorShip0B.R = color.R;		ColorShip0B.G = color.G;		ColorShip0B.B = color.B;		ColorShip0B.A = color.A;		break;
		case SHIP_COLOR_1B:			ColorShip1B.R = color.R;		ColorShip1B.G = color.G;		ColorShip1B.B = color.B;		ColorShip1B.A = color.A;		break;
		case SHIP_COLOR_2B:			ColorShip2B.R = color.R;		ColorShip2B.G = color.G;		ColorShip2B.B = color.B;		ColorShip2B.A = color.A;		break;

		case ATON_COLOR:			ColorAton.R = color.R;			ColorAton.G = color.G;			ColorAton.B = color.B;			ColorAton.A = color.A;			break;
		case COG_COLOR:				ColorCOG.R = color.R;			ColorCOG.G = color.G;			ColorCOG.B = color.B;			ColorCOG.A = color.A;			break;
		case HDT_COLOR:				ColorHDT.R = color.R;			ColorHDT.G = color.G;			ColorHDT.B = color.B;			ColorHDT.A = color.A;			break;
		case GPS_COLOR:				ColorGPS.R = color.R;			ColorGPS.G = color.G;			ColorGPS.B = color.B;			ColorGPS.A = color.A;			break;
		case BASE_STATION_COLOR:	ColorBS.R = color.R;			ColorBS.G = color.G;			ColorBS.B = color.B;			ColorBS.A = color.A;			break;
	}

}

void SetAlpha(int type, int value)
{
	switch(type)
	{
		case SHIP_COLOR_0A:			ColorShip0A.A = value;	break;
		case SHIP_COLOR_1A:			ColorShip1A.A = value;	break;
		case SHIP_COLOR_2A:			ColorShip2A.A = value;	break;

		case SHIP_COLOR_0B:			ColorShip0B.A = value;	break;
		case SHIP_COLOR_1B:			ColorShip1B.A = value;	break;
		case SHIP_COLOR_2B:			ColorShip2B.A = value;	break;

		case ATON_COLOR:			ColorAton.A = value;	break;	
		case BASE_STATION_COLOR:	ColorBS.A = value;		break; 
	}

}

int GetAlpha(int type)
{
	int alpha = 0;
	switch(type)
	{
		case SHIP_COLOR_0A:			alpha = ColorShip0A.A;	break;
		case SHIP_COLOR_1A:			alpha = ColorShip1A.A;	break;
		case SHIP_COLOR_2A:			alpha = ColorShip2A.A;	break;

		case SHIP_COLOR_0B:			alpha = ColorShip0B.A;	break;
		case SHIP_COLOR_1B:			alpha = ColorShip1B.A;	break;
		case SHIP_COLOR_2B:			alpha = ColorShip2B.A;	break;

		case ATON_COLOR:			alpha = ColorAton.A;	break;
		case BASE_STATION_COLOR:	alpha = ColorBS.A;		break;
	}

	return alpha;
}

int GetFilter()
{
	return m_Filter;
}

void SetFilter(int val)
{
	m_Filter = val;
}

void SetFilterChanged(bool value)
{
	m_FilterChanged = value;
}

bool GetFilterChanged()
{
	return m_FilterChanged;
}

void SetSearchTextChanged(bool value)
{
	m_SearchTextChanged = value;
}

bool GetSearchTextChanged()
{
	return m_SearchTextChanged;
}

void SetSearchText(char *txt)
{
	memcpy(m_SearchText,txt,64);
}

char *GetSearchText()
{
	return m_SearchText;
}

int GetControlFrequency()
{
	return  m_Frequency;
}

void SetControlFrequency(int value)
{
	m_Frequency = value;
}

int GetViewFontScale()
{
	return m_ViewFontScale;
}

bool GetShowOBJECTS()
{
	return m_ShowObjects;
}

void SetShowOBJECTS(bool value)
{
	m_ShowObjects = value;
}

void SetViewFontScale(int value) 
{
	m_ViewFontScale = value;
}

void SetAisDataChanged(bool value)
{
	m_AisDataChanged = value;
}

bool GetAisDataChanged()
{
	return m_AisDataChanged;
}

bool GetStartAnimation()
{
	return m_StartAnimation;
}

void SetStartAnimation(bool value)
{
	m_StartAnimation = value;
}

bool GetVTSMode()
{
	return m_VTSMode;
}

void SetVTSMode(bool val)
{
	m_VTSMode = val;
}

int GetAisTimeout()
{
	return m_AisTimeout;
}

void SetAisTimeout(int val)
{
	m_AisTimeout = val;
}

int GetAisTimeoutRemove()
{
	return m_AisTimeoutRemove;
}

void SetAisTimeoutRemove(int val)
{
	m_AisTimeoutRemove = val;
}

void SetShipStateFlag(bool val)
{
	m_SetShipPosition = val;
}

bool GetShipStateFlag()
{
	return m_SetShipPosition;
}
void SetShipState(int id, double val)
{
	m_ShipState[id] = val;
}

double *GetShipState()
{
	return m_ShipState;
}

double GetShipState(int id)
{
	return m_ShipState[id];
}

// global state
void SetShipGlobalState(int id, double val)
{
	m_ShipGlobalState[id] = val;
}

double *GetShipGlobalState()
{
	return m_ShipGlobalState;
}

double GetShipGlobalState(int id)
{
	return m_ShipGlobalState[id];
}


void ReadOptionsConfig()
{

	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	FileConfig->Read(_(KEY_SHOW_NAMES),&m_ShowNames, false);
	FileConfig->Read(_(KEY_FONT_SIZE),&m_FontSize, DEFAULT_FONT_SIZE);
	FileConfig->Read(_(KEY_SHOW_COG),&m_ShowCOG, true);
	FileConfig->Read(_(KEY_SHOW_HDT),&m_ShowHDT, true);
	FileConfig->Read(_(KEY_SHOW_GPS),&m_ShowGPS, true);
	FileConfig->Read(_(KEY_SHOW_OBJECTS),&m_ShowObjects, true);
	FileConfig->Read(_(KEY_FILTER),&m_Filter, DEFAULT_FILTER);
	FileConfig->Read(_(KEY_FREQUENCY),&m_Frequency, DEFAULT_FREQUENCY);
	FileConfig->Read(_(KEY_VIEW_FONT_SCALE),&m_ViewFontScale,DEFAULT_VIEW_FONT_SCALE);
	FileConfig->Read(_(KEY_COG_TIME),&m_COGTime, DEFAULT_COG_TIME);
	FileConfig->Read(_(KEY_HDT_TIME),&m_HDTTime, DEFAULT_HDT_TIME);
	FileConfig->Read(_(KEY_COG_LINE_WIDTH),&m_COGLineWidth, DEFAULT_COG_LINE_WIDTH);
	FileConfig->Read(_(KEY_HDT_LINE_WIDTH),&m_HDTLineWidth, DEFAULT_HDT_LINE_WIDTH);
	FileConfig->Read(_(KEY_COG_LINE_STYLE),&m_COGLineStyle, DEFAULT_COG_LINE_STYLE);
	FileConfig->Read(_(KEY_HDT_LINE_STYLE),&m_HDTLineStyle, DEFAULT_HDT_LINE_STYLE);
	FileConfig->Read(_(KEY_AIS_TIMEOUT),&m_AisTimeout, AIS_TIMEOUT);
	FileConfig->Read(_(KEY_AIS_TIMEOUT_REMOVE),&m_AisTimeoutRemove, AIS_TIMEOUT_REMOVE);


	FileConfig->Read(_(KEY_CPA),&m_CPA,DEFAULT_CPA);
	FileConfig->Read(_(KEY_TCPA),&m_TCPA,DEFAULT_TCPA);

	wxString _color;
	
	//Class A
	FileConfig->Read(_(KEY_SHIP_BORDER_COLORA),&_color,RGBAToStr(&GetDefaultColor(SHIP_BORDER_COLORA)));
	SetColor(SHIP_BORDER_COLORA,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_SHIP_COLOR_0A),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_0A)));
	SetColor(SHIP_COLOR_0A,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_SHIP_COLOR_1A),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_1A)));
	SetColor(SHIP_COLOR_1A,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_SHIP_COLOR_2A),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_2A)));
	SetColor(SHIP_COLOR_2A,StrToRGBA(_color));

	//Class B
	FileConfig->Read(_(KEY_SHIP_BORDER_COLORB),&_color,RGBAToStr(&GetDefaultColor(SHIP_BORDER_COLORB)));
	SetColor(SHIP_BORDER_COLORB,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_SHIP_COLOR_0B),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_0B)));
	SetColor(SHIP_COLOR_0B,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_SHIP_COLOR_1B),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_1B)));
	SetColor(SHIP_COLOR_1B,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_SHIP_COLOR_2B),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_2B)));
	SetColor(SHIP_COLOR_2B,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_ATON_COLOR),&_color,RGBAToStr(&GetDefaultColor(ATON_COLOR)));
	SetColor(ATON_COLOR,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_COG_COLOR),&_color,RGBAToStr(&GetDefaultColor(COG_COLOR)));
	SetColor(COG_COLOR,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_HDT_COLOR),&_color,RGBAToStr(&GetDefaultColor(HDT_COLOR)));
	SetColor(HDT_COLOR,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_GPS_COLOR),&_color,RGBAToStr(&GetDefaultColor(GPS_COLOR)));
	SetColor(GPS_COLOR,StrToRGBA(_color));

	FileConfig->Read(_(KEY_BS_COLOR),&_color,RGBAToStr(&GetDefaultColor(BASE_STATION_COLOR)));
	SetColor(BASE_STATION_COLOR,StrToRGBA(_color));
	
	

	delete FileConfig;

}

void WriteOptionsConfig()
{

	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	
	FileConfig->Write(_(KEY_SHOW_NAMES),m_ShowNames);
	FileConfig->Write(_(KEY_FONT_SIZE),m_FontSize);
	FileConfig->Write(_(KEY_SHOW_COG),m_ShowCOG);
	FileConfig->Write(_(KEY_SHOW_HDT),m_ShowHDT);
	FileConfig->Write(_(KEY_SHOW_GPS),m_ShowGPS);
	FileConfig->Write(_(KEY_SHOW_OBJECTS),m_ShowObjects);
	FileConfig->Write(_(KEY_FILTER),m_Filter);
	FileConfig->Write(_(KEY_FREQUENCY),m_Frequency);
	FileConfig->Write(_(KEY_VIEW_FONT_SCALE),m_ViewFontScale);
	FileConfig->Write(_(KEY_SHIP_BORDER_COLORA),RGBAToStr(&GetColor(SHIP_BORDER_COLORA)));
	FileConfig->Write(_(KEY_SHIP_COLOR_0A),RGBAToStr(&GetColor(SHIP_COLOR_0A)));
	FileConfig->Write(_(KEY_SHIP_COLOR_1A),RGBAToStr(&GetColor(SHIP_COLOR_1A)));
	FileConfig->Write(_(KEY_SHIP_COLOR_2A),RGBAToStr(&GetColor(SHIP_COLOR_2A)));
	FileConfig->Write(_(KEY_SHIP_BORDER_COLORB),RGBAToStr(&GetColor(SHIP_BORDER_COLORB)));
	FileConfig->Write(_(KEY_SHIP_COLOR_0B),RGBAToStr(&GetColor(SHIP_COLOR_0B)));
	FileConfig->Write(_(KEY_SHIP_COLOR_1B),RGBAToStr(&GetColor(SHIP_COLOR_1B)));
	FileConfig->Write(_(KEY_SHIP_COLOR_2B),RGBAToStr(&GetColor(SHIP_COLOR_2B)));
	FileConfig->Write(_(KEY_COG_COLOR),RGBAToStr(&GetColor(COG_COLOR)));
	FileConfig->Write(_(KEY_HDT_COLOR),RGBAToStr(&GetColor(HDT_COLOR)));
	FileConfig->Write(_(KEY_GPS_COLOR),RGBAToStr(&GetColor(GPS_COLOR)));
	FileConfig->Write(_(KEY_BS_COLOR),RGBAToStr(&GetColor(BASE_STATION_COLOR)));
	FileConfig->Write(_(KEY_ATON_COLOR),RGBAToStr(&GetColor(ATON_COLOR)));

	FileConfig->Write(_(KEY_AIS_TIMEOUT),m_AisTimeout);
	FileConfig->Write(_(KEY_AIS_TIMEOUT_REMOVE),m_AisTimeoutRemove);



	FileConfig->Write(_(KEY_COG_TIME),m_COGTime);
	FileConfig->Write(_(KEY_HDT_TIME),m_HDTTime);
	FileConfig->Write(_(KEY_COG_LINE_WIDTH),m_COGLineWidth);
	FileConfig->Write(_(KEY_HDT_LINE_WIDTH),m_HDTLineWidth);
	FileConfig->Write(_(KEY_COG_LINE_STYLE),m_COGLineStyle);
	FileConfig->Write(_(KEY_HDT_LINE_STYLE),m_HDTLineStyle);

	FileConfig->Write(_(KEY_CPA),m_CPA);
	FileConfig->Write(_(KEY_TCPA),m_TCPA);

	delete FileConfig;

}