#ifndef __TICKER
#define __TICKER
#if defined (_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

class CTicker :public wxTimer
{
	void *Parent;
	bool Exit;
	int Tick;
	int Id;
	
#if defined (_WIN32) || defined(_WIN64)
	DWORD ThreadID;
	HANDLE TickerHANDLE;
	static DWORD WINAPI Ticker(void *Param);
#endif
#if defined(_LINUX32) || defined(_LINUX64)
	static void *Ticker(void *Param);
#endif
	
	bool GetExit();
	void OnTickerStart();
	void OnTickerStop();
	void OnTickerTick();


public:
	CTicker(void *parent, int id);
	~CTicker();
	void Notify();
	
};

#endif