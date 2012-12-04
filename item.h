#ifndef __ITEM
#define __ITEM

#include <wx/wx.h>
#include <wx/treectrl.h>
#include "serial.h"

class CItem :public wxTreeItemData
{
		
	CMySerial *m_Serial;

public:

	CItem();
	~CItem();
		
	void SetSerial(CMySerial *serial);
	CMySerial *GetSerial();

};

#endif