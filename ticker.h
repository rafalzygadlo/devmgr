#ifndef __TICKER
#define __TICKER
#if defined (_WIN32) || defined(_WIN64)
#include <windows.h>
#endif



class CTicker
#ifdef TIMER	
	:public wxTimer
#endif
#ifdef THREAD
	:public wxThread
#endif
{
	void *Parent;
	bool Exit;
	int Tick;
	int Id;
	int _Sleep;
	bool _Stop;
	
#if defined (_WIN32) || defined(_WIN64)
	DWORD ThreadID;
	HANDLE TickerHANDLE;
	static DWORD WINAPI Ticker(void *Param);
#endif
#if defined(_LINUX32) || defined(_LINUX64)
	static void *Ticker(void *Param);
#endif
	
	bool GetExit();
	void SendSignal();
	void OnTickerStart();
	void OnTickerStop();
	void OnTickerTick();
#ifdef THREAD
	void *Entry();
#endif

public:
	CTicker(void *parent, int id);
	~CTicker();
#ifdef THREAD
	void Start(int sleep);
	void Stop();
#endif
#ifdef TIMER
	void Notify();
#endif	
};

#endif