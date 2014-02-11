#include "conf.h"
#include "ticker.h"
#include "dll.h"

CTicker::CTicker(void *parent)
{
	Exit = false;
	Parent = parent;
	Tick = TICKER_SLEEP;
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
	((CMapPlugin*)Parent)->OnTickerStart();
}

void CTicker::OnTickerStop()
{
	((CMapPlugin*)Parent)->OnTickerStop();
}

void CTicker::OnTickerTick()
{  
	((CMapPlugin*)Parent)->OnTickerTick();
}
