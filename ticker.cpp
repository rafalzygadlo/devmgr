#include "conf.h"
#include "ticker.h"
#include "display.h"
#include "dll.h"


CTicker::CTicker(void *parent, int id)
	:wxTimer()
{
	Exit = false;
	Parent = parent;
	Id = id;
}

CTicker::~CTicker()
{

}

/*
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
		
		if(GetTickCount()
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
*/

void CTicker::Notify()
{
	switch(Id)
	{
		case TICK_0:	((CMapPlugin*)Parent)->OnTicker1Tick();		break;
		case TICK_2:	((CMapPlugin*)Parent)->OnTicker2Tick();		break;
		case TICK_1:	((CDisplayPlugin*)Parent)->OnTickerTick();	break;
	}
}

bool CTicker::GetExit()
{
	return Exit;
}