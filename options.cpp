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


nvRGBA ColorShip0, ColorShip1, ColorShip2, ColorAton, ColorHDT, ColorCOG, ColorGPS, ColorShipBorder;

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
		case SHIP_BORDER_COLOR:	rgba.R = 0;		rgba.G = 0;		rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_0:		rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_1:		rgba.R = 255;	rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case SHIP_COLOR_2:		rgba.R = 255;	rgba.G = 0;		rgba.B = 0;		rgba.A = 200;	break;
		case ATON_COLOR:		rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case COG_COLOR:			rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case HDT_COLOR:			rgba.R = 0;		rgba.G = 0;		rgba.B = 255;	rgba.A = 200;	break;
		case GPS_COLOR:			rgba.R = 0;		rgba.G = 0;		rgba.B = 255;	rgba.A = 200;	break;
	
	}
		
	return rgba;
}

nvRGBA GetColor(int type)
{
	nvRGBA rgba;
	switch(type)
	{
		case SHIP_BORDER_COLOR:	rgba.R = ColorShipBorder.R;	rgba.G = ColorShipBorder.G;	rgba.B = ColorShipBorder.B;	rgba.A = ColorShipBorder.A;	break;
		case SHIP_COLOR_0:		rgba.R = ColorShip0.R;		rgba.G = ColorShip0.G;		rgba.B = ColorShip0.B;		rgba.A = ColorShip0.A;		break;
		case SHIP_COLOR_1:		rgba.R = ColorShip1.R;		rgba.G = ColorShip1.G;		rgba.B = ColorShip1.B;		rgba.A = ColorShip1.A;		break;
		case SHIP_COLOR_2:		rgba.R = ColorShip2.R;		rgba.G = ColorShip2.G;		rgba.B = ColorShip2.B;		rgba.A = ColorShip2.A;		break;
		case ATON_COLOR:		rgba.R = ColorAton.R;		rgba.G = ColorAton.G;		rgba.B = ColorAton.B;		rgba.A = ColorAton.A;		break;
		case COG_COLOR:			rgba.R = ColorCOG.R;		rgba.G = ColorCOG.G;		rgba.B = ColorCOG.B;		rgba.A = ColorCOG.A;		break;
		case HDT_COLOR:			rgba.R = ColorHDT.R;		rgba.G = ColorHDT.G;		rgba.B = ColorHDT.B;		rgba.A = ColorHDT.A;		break;
		case GPS_COLOR:			rgba.R = ColorGPS.R;		rgba.G = ColorGPS.G;		rgba.B = ColorGPS.B;		rgba.A = ColorGPS.A;		break;
	}
		
	return rgba;
}

void SetColor(int type, nvRGBA color)
{
	switch(type)
	{
		case SHIP_BORDER_COLOR:	ColorShipBorder.R = color.R;	ColorShipBorder.G = color.G;	ColorShipBorder.B = color.B;	ColorShipBorder.A = color.A;	break;	
		case SHIP_COLOR_0:		ColorShip0.R = color.R;			ColorShip0.G = color.G;			ColorShip0.B = color.B;			ColorShip0.A = color.A;			break;
		case SHIP_COLOR_1:		ColorShip1.R = color.R;			ColorShip1.G = color.G;			ColorShip1.B = color.B;			ColorShip1.A = color.A;			break;
		case SHIP_COLOR_2:		ColorShip2.R = color.R;			ColorShip2.G = color.G;			ColorShip2.B = color.B;			ColorShip2.A = color.A;			break;
		case ATON_COLOR:		ColorAton.R = color.R;			ColorAton.G = color.G;			ColorAton.B = color.B;			ColorAton.A = color.A;			break;
		case COG_COLOR:			ColorCOG.R = color.R;			ColorCOG.G = color.G;			ColorCOG.B = color.B;			ColorCOG.A = color.A;			break;
		case HDT_COLOR:			ColorHDT.R = color.R;			ColorHDT.G = color.G;			ColorHDT.B = color.B;			ColorHDT.A = color.A;			break;
		case GPS_COLOR:			ColorGPS.R = color.R;			ColorGPS.G = color.G;			ColorGPS.B = color.B;			ColorGPS.A = color.A;			break;
	}

}

void SetAlpha(int type, int value)
{
	switch(type)
	{
		case SHIP_COLOR_0:	ColorShip0.A = value;	break;
		case SHIP_COLOR_1:	ColorShip1.A = value;	break;
		case SHIP_COLOR_2:	ColorShip2.A = value;	break;
		case ATON_COLOR:	ColorAton.A = value;	break;	
	}

}

int GetAlpha(int type)
{
	int alpha = 0;
	switch(type)
	{
		case SHIP_COLOR_0:	alpha = ColorShip0.A;	break;
		case SHIP_COLOR_1:	alpha = ColorShip1.A;	break;
		case SHIP_COLOR_2:	alpha = ColorShip2.A;	break;
		case ATON_COLOR:	alpha = ColorAton.A;	break;
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

void SetSearchText(char *txt)
{
	memcpy(m_SearchText,txt,64);
}

char *GetSearchText()
{
	return m_SearchText;
}

int GetFrequency()
{
	return  DEFAULT_MAX_FREQUENCY / m_Frequency * 10;
}

void SetControlFrequency(int value)
{
	m_Frequency = value;
}

int GetControlFrequency()
{
	return m_Frequency;
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
	wxString _color;
	
	
	FileConfig->Read(_(KEY_SHIP_BORDER_COLOR),&_color,RGBAToStr(&GetDefaultColor(SHIP_BORDER_COLOR)));
	SetColor(SHIP_BORDER_COLOR,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_SHIP_COLOR_0),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_0)));
	SetColor(SHIP_COLOR_0,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_SHIP_COLOR_1),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_1)));
	SetColor(SHIP_COLOR_1,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_SHIP_COLOR_2),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_2)));
	SetColor(SHIP_COLOR_2,StrToRGBA(_color));

	FileConfig->Read(_(KEY_ATON_COLOR),&_color,RGBAToStr(&GetDefaultColor(ATON_COLOR)));
	SetColor(ATON_COLOR,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_COG_COLOR),&_color,RGBAToStr(&GetDefaultColor(COG_COLOR)));
	SetColor(COG_COLOR,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_HDT_COLOR),&_color,RGBAToStr(&GetDefaultColor(HDT_COLOR)));
	SetColor(HDT_COLOR,StrToRGBA(_color));
	
	FileConfig->Read(_(KEY_GPS_COLOR),&_color,RGBAToStr(&GetDefaultColor(GPS_COLOR)));
	SetColor(GPS_COLOR,StrToRGBA(_color));
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
	FileConfig->Write(_(KEY_SHIP_BORDER_COLOR),RGBAToStr(&GetColor(SHIP_BORDER_COLOR)));
	FileConfig->Write(_(KEY_SHIP_COLOR_0),RGBAToStr(&GetColor(SHIP_COLOR_0)));
	FileConfig->Write(_(KEY_SHIP_COLOR_1),RGBAToStr(&GetColor(SHIP_COLOR_1)));
	FileConfig->Write(_(KEY_SHIP_COLOR_2),RGBAToStr(&GetColor(SHIP_COLOR_2)));
	FileConfig->Write(_(KEY_COG_COLOR),RGBAToStr(&GetColor(COG_COLOR)));
	FileConfig->Write(_(KEY_HDT_COLOR),RGBAToStr(&GetColor(HDT_COLOR)));
	FileConfig->Write(_(KEY_GPS_COLOR),RGBAToStr(&GetColor(GPS_COLOR)));
	FileConfig->Write(_(KEY_COG_TIME),m_COGTime);
	FileConfig->Write(_(KEY_HDT_TIME),m_HDTTime);
	FileConfig->Write(_(KEY_COG_LINE_WIDTH),m_COGLineWidth);
	FileConfig->Write(_(KEY_HDT_LINE_WIDTH),m_HDTLineWidth);
	FileConfig->Write(_(KEY_COG_LINE_STYLE),m_COGLineStyle);
	FileConfig->Write(_(KEY_HDT_LINE_STYLE),m_HDTLineStyle);
	
	delete FileConfig;

}