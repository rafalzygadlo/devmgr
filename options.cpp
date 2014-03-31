#include "conf.h"
#include "tools.h"
#include "options.h"
#include <wx/stdpaths.h>
#include <wx/fileconf.h>

double m_FontSize = DEFAULT_FONT_SIZE;
bool m_ShowNames = false;
bool m_ShowHDT = true;
bool m_ShowCOG = true;
int m_Filter = DEFAULT_FILTER;

nvRGBA ColorShip0, ColorShip1, ColorShip2, ColorAton;

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
		case SHIP_COLOR_0:	rgba.R = 0;		rgba.G = 255;	rgba.B = 0;	rgba.A = 200;	break;
		case SHIP_COLOR_1:	rgba.R = 255;	rgba.G = 255;	rgba.B = 0;	rgba.A = 200;	break;
		case SHIP_COLOR_2:	rgba.R = 255;	rgba.G = 0;		rgba.B = 0;	rgba.A = 200;	break;
		case ATON_COLOR:	rgba.R = 0;		rgba.G = 255;	rgba.B = 0;	rgba.A = 200;	break;
	}
		
	return rgba;
}

nvRGBA GetColor(int type)
{
	nvRGBA rgba;
	switch(type)
	{
		case SHIP_COLOR_0:	rgba.R = ColorShip0.R;	rgba.G = ColorShip0.G;	rgba.B = ColorShip0.B;	rgba.A = ColorShip0.A;	break;
		case SHIP_COLOR_1:	rgba.R = ColorShip1.R;	rgba.G = ColorShip1.G;	rgba.B = ColorShip1.B;	rgba.A = ColorShip1.A;	break;
		case SHIP_COLOR_2:	rgba.R = ColorShip2.R;	rgba.G = ColorShip2.G;	rgba.B = ColorShip2.B;	rgba.A = ColorShip2.A;	break;
		case ATON_COLOR:	rgba.R = ColorAton.R;	rgba.G = ColorAton.G;	rgba.B = ColorAton.B;	rgba.A = ColorAton.A;	break;
	}
		
	return rgba;
}

void SetColor(int type, nvRGBA color)
{
	switch(type)
	{
		case SHIP_COLOR_0:	ColorShip0.R = color.R;	ColorShip0.G = color.G;	ColorShip0.B = color.B;	ColorShip0.A = color.A;	break;
		case SHIP_COLOR_1:	ColorShip1.R = color.R;	ColorShip1.G = color.G;	ColorShip1.B = color.B;	ColorShip1.A = color.A;	break;
		case SHIP_COLOR_2:	ColorShip2.R = color.R;	ColorShip2.G = color.G;	ColorShip2.B = color.B;	ColorShip2.A = color.A;	break;
		case ATON_COLOR:	ColorAton.R = color.R;	ColorAton.G = color.G;	ColorAton.B = color.B;	ColorAton.A = color.A;	break;
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

void ReadOptionsConfig()
{

	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	FileConfig->Read(_(KEY_SHOW_NAMES),&m_ShowNames, false);
	FileConfig->Read(_(KEY_FONT_SIZE),&m_FontSize, DEFAULT_FONT_SIZE);
	FileConfig->Read(_(KEY_SHOW_COG),&m_ShowCOG, true);
	FileConfig->Read(_(KEY_SHOW_HDT),&m_ShowHDT, true);
	FileConfig->Read(_(KEY_FILTER),&m_Filter, DEFAULT_FILTER);
	
	wxString _color;
	
	FileConfig->Read(_(KEY_SHIP_COLOR_0),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_0)));
	SetColor(SHIP_COLOR_0,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_SHIP_COLOR_1),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_1)));
	SetColor(SHIP_COLOR_1,StrToRGBA(_color));
		
	FileConfig->Read(_(KEY_SHIP_COLOR_2),&_color,RGBAToStr(&GetDefaultColor(SHIP_COLOR_2)));
	SetColor(SHIP_COLOR_2,StrToRGBA(_color));

	FileConfig->Read(_(KEY_ATON_COLOR),&_color,RGBAToStr(&GetDefaultColor(ATON_COLOR)));
	SetColor(ATON_COLOR,StrToRGBA(_color));
	
	
	delete FileConfig;

}

void WriteOptionsConfig()
{

	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetPluginConfigPath(),wxEmptyString);
	
	FileConfig->Write(_(KEY_SHOW_NAMES),m_ShowNames);
	FileConfig->Write(_(KEY_FONT_SIZE),m_FontSize);
	FileConfig->Write(_(KEY_SHOW_COG),m_ShowCOG);
	FileConfig->Write(_(KEY_SHOW_HDT),m_ShowHDT);
	FileConfig->Write(_(KEY_FILTER),m_Filter);

	FileConfig->Write(_(KEY_SHIP_COLOR_0),RGBAToStr(&GetColor(SHIP_COLOR_0)));
	FileConfig->Write(_(KEY_SHIP_COLOR_1),RGBAToStr(&GetColor(SHIP_COLOR_1)));
	FileConfig->Write(_(KEY_SHIP_COLOR_2),RGBAToStr(&GetColor(SHIP_COLOR_2)));
	
	delete FileConfig;


}