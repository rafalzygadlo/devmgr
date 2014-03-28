#include "signals.h"

CNaviArray <SData*> vSignalBuffer;

SData *GetDeviceSignal(size_t id)
{
	return vSignalBuffer.Get(id);
}

size_t GetDeviceSignalCount()
{
	return vSignalBuffer.Length();
}

SData *SignalExists(size_t id)
{
	for(size_t  i = 0; i < vSignalBuffer.Length(); i++)
	{
		SData *ptr = vSignalBuffer.Get(i);
		if(ptr->id == id)
			return ptr;
	}

	return NULL;
}

void SignalAppend(SData *ptr)
{
	SData *_ptr = SignalExists(ptr->id);
	if(_ptr == NULL)
	{
		SData *data = (SData*)malloc(sizeof(SData));
		memcpy(data ,ptr,sizeof(SData));
		vSignalBuffer.Append(data);
	
	}else{
	
		memcpy(_ptr,ptr,sizeof(SData));
	}

}

void SignalsFree()
{
	for(size_t  i = 0; i < vSignalBuffer.Length(); i++)
	{
		SData *ptr = vSignalBuffer.Get(i);
		free(ptr);
	}
	
	vSignalBuffer.Clear();
}
