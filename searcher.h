#ifndef SEARCHER_H
#define SEARCHER_H

#if defined(_LINUX32) || defined(_LINUX64)
#include <pthread.h>
#endif
#include "serial_port.h"
#include "wizard.h"

class CWizard;
class CSearcher:public CSerial
{
	CWizard *m_Wizard;
	int m_BadCRCCount, m_BaudIndex, m_BaudCount, m_InvalidNMEACount;
	void NextBaud();

    public:
	CSearcher(CWizard *wizard);
	~CSearcher();
	
	virtual void OnConnect();
	virtual void OnValidNMEA();
	virtual void OnInvalidNMEA();
	virtual void OnNoSignal();
	virtual void OnNewTalker(STalker talker);
	virtual void OnReconnect();
	virtual void OnAfterMainLoop();
	virtual void OnBadCRC();
	virtual void OnNoNewTalker();
	
};

#endif