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
void SetSearchText(char *txt);
char *GetSearchText();
int GetFrequency();
void SetControlFrequency(int value);
int GetControlFrequency();
#endif