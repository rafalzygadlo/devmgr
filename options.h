#ifndef __OPTIONS_H
#define __OPTIONS_H

void ReadOptionsConfig();
void WriteOptionsConfig();
float GetFontSize();
void SetFontSize( float size);
bool GetShowNames();
void SetShowNames(bool value);
bool GetShowHDT();
void SetShowHDT(bool value);
bool GetShowCOG();
void SetShowCOG(bool value);
nvRGBA GetColor(int type);
void SetColor(int type, nvRGBA color);
void SetAlpha(int type, int value);
int GetAlpha(int type);
void SetFilter(int val);
int GetFilter();
void SetFilterChanged(bool value);
bool GetFilterChanged();
void SetSearchText(char *txt);
char *GetSearchText();
bool GetSearchTextChanged();
void SetSearchTextChanged(bool value);
int GetFrequency();
void SetControlFrequency(int value);
int GetControlFrequency();
int GetViewFontScale();
void SetViewFontScale(int value);
bool GetShowGPS();
void SetShowGPS(bool value);
bool GetShowOBJECTS();
void SetShowOBJECTS(bool value);
void SetCOGTime(int value);
int GetCOGTime();
void SetHDTTime(int value);
int GetHDTTime();
void SetCOGLineWidth(int value);
int GetCOGLineWidth();
void SetHDTLineWidth(int value);
int GetHDTLineWidth();
void SetCOGLineStyle(int value);
int GetCOGLineStyle();
void SetHDTLineStyle(int value);
int GetHDTLineStyle();
void SetAisDataChanged(bool value);
bool GetAisDataChanged();
bool GetStartAnimation();
void SetStartAnimation(bool value);
void SetCPA(float v);
float GetCPA();
void SetTCPA(float v);
float GetTCPA();
bool GetVTSMode();
void SetVTSMode(bool val);

#endif