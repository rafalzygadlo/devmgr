#ifndef __SIGNALS_H
#define __SIGNALS_H

#include "conf.h"
#include "NaviArray.h"

SData *SignalExists(size_t id);
void SignalAppend(SData *ptr);
SData *GetDeviceSignal(size_t id);
size_t GetDeviceSignalCount();
void SignalsFree();

#endif