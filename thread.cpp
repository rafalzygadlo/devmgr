#include "dll.h"
#include "thread.h"
#include "wizard.h"

CThread::CThread(void *parent)
	:wxThread()
{
	Parent = parent;
	
}

CThread::~CThread()
{
	IsWorking = false;
}
 
void CThread::Start()
{
	IsWorking = true;

	if (this->Create() == wxTHREAD_NO_ERROR )
    {
		this->SetPriority(WXTHREAD_DEFAULT_PRIORITY);
        this->Run();
    }

}

void CThread::SetWorkId(int id)
{
	WorkId = id;
}

void *CThread::Entry()
{
	switch(WorkId)
	{
		case WORK_WIZARD:			((CWizard*)Parent)->ThreadBegin(WorkId);	break;
		case WORK_RENDER_BUFFER:	((CMapPlugin*)Parent)->ThreadBegin();		break;
	}
	
	return 0;
}

bool CThread::GetIsWorking()
{
	return IsWorking;
}

void CThread::OnExit()
{
	IsWorking = false;
	
	switch(WorkId)
	{
		case WORK_WIZARD:			((CWizard*)Parent)->ThreadEnd(WorkId);	break;
		case WORK_RENDER_BUFFER:	((CMapPlugin*)Parent)->ThreadEnd();		break;
	}
}
