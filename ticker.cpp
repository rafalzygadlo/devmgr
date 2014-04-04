#include "conf.h"
#include "ticker.h"
#include "display.h"
#include "dll.h"

CTicker::CTicker(void *parent, int id)
{
	Exit = false;
	Parent = parent;
	Tick = TICKER_SLEEP;
	Id = id;
}

CTicker::~CTicker()
{

}

void CTicker::Start()
{
	Exit = false;
#if defined (_WIN32) || defined(_WIN64)
    TickerHANDLE = CreateThread( NULL, 0, Ticker, this, 0, &ThreadID);
#endif
#if defined(_LINUX32) || defined(_LINUX64)
    pthread_t thr;
    int ret = 0;
    ret = pthread_create(&thr,NULL,&Ticker,(void*)this);
    pthread_detach( thr );
#endif
}

#if defined (_WIN32) || defined(_WIN64)
DWORD WINAPI CTicker::Ticker(void *Param)
#endif
#if defined(_LINUX32) || defined(_LINUX64)
void *CTicker::Ticker(void *Param)
#endif
{

    CTicker *Ticker = ((CTicker*)Param);
    Ticker->OnTickerStart();
	
	DWORD tick = 0;
    
	while (true)
    {
		Ticker->OnTickerTick();
		
#ifdef _WIN32
        Sleep(Ticker->GetTick());
		
#endif
#if defined(_LINUX32) || defined(_LINUX64)
        usleep(TICKER_SLEEP * 1000);
#endif

		
		if(Ticker->GetExit())
			break;
    }

	Ticker->OnTickerStop();
    

return 0;

}

int CTicker::GetTick()
{
	return Tick;
}

bool CTicker::GetExit()
{
	return Exit;
}

void CTicker::SetTick(int tick)
{
	Tick = tick;
}

void CTicker::Stop()
{
	Exit = true;

#if defined(_WIN32) || defined(_WIN64)
    WaitForSingleObject(TickerHANDLE,INFINITE);
#endif
}

void CTicker::OnTickerStart()
{
	switch(Id)
	{
		case TICK_0:	((CMapPlugin*)Parent)->OnTicker1Start();		break;
		case TICK_1:	((CDisplayPlugin*)Parent)->OnTickerStart(); break;
		case TICK_2:	((CMapPlugin*)Parent)->OnTicker2Start();		break;
	}
}

void CTicker::OnTickerStop()
{
	switch(Id)
	{
		case TICK_0:	((CMapPlugin*)Parent)->OnTicker1Stop();		break;
		case TICK_1:	((CDisplayPlugin*)Parent)->OnTickerStop();	break;
		case TICK_2:	((CMapPlugin*)Parent)->OnTicker2Stop();		break;
	}
}

void CTicker::OnTickerTick()
{  
	switch(Id)
	{
		case TICK_0:	((CMapPlugin*)Parent)->OnTicker1Tick();		break;
		case TICK_1:	((CDisplayPlugin*)Parent)->OnTickerTick();	break;
		case TICK_2:	((CMapPlugin*)Parent)->OnTicker2Tick();		break;
	}

}
