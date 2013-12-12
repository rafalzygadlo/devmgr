#include "searcher.h"
#include "conf.h"

#if defined(_LINUX32) || defined(_LINUX64)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

CSearcher::CSearcher(CWizard *wizard):CSerial()
{   
	m_Wizard = wizard;
    m_BadCRCCount = 0;
    m_InvalidNMEACount = 0;
}

CSearcher::~CSearcher()
{

}

void CSearcher::OnValidNMEA()
{
    m_BadCRCCount = 0;
    m_InvalidNMEACount = 0;
}

void CSearcher::OnBadCRC()
{
    if(m_BadCRCCount > MAX_BAD_CRC)
    {
		Disconnect();
		m_BadCRCCount = 0;
    }
    
	m_BadCRCCount++;
}

void CSearcher::OnInvalidNMEA()
{
    if(m_InvalidNMEACount > MAX_INVALID_NMEA)
    {
		Disconnect();
		m_InvalidNMEACount = 0;
    }
    
    m_InvalidNMEACount++;
}

void CSearcher::OnConnect()
{
#ifdef DEBUG
    fprintf(stdout,"Scan %s %d\n",GetPortName(),GetBaudRate());
#endif    
}

void CSearcher::OnReconnect()
{
	Stop(false);
}

void CSearcher::OnNewTalker(STalker talker)
{
}

void CSearcher::OnNoNewTalker()
{
	Stop(false);
}

void CSearcher::OnNoSignal()
{
	Stop(false);
}

void CSearcher::OnAfterMainLoop()
{
	fprintf(stderr,"After main loop %s\n",GetPortName());
}