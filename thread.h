#ifndef __THREAD_H
#define __THREAD_H

#include <wx/wx.h>
#include "dll.h"

class CMapPlugin;
class CThread :public wxThread
{
	int WorkId;
	bool IsWorking;
	
	void *Parent;
	void *Params;
	void *Entry();
	void OnExit();
		
public:
	
	CThread(void *parent);
	~CThread();
	void Start(void);
	void SetWorkId(int id);
	bool GetIsWorking();
	
};


#endif 
