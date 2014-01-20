#ifndef __ITEM
#define __ITEM

#include <wx/wx.h>
#include <wx/treectrl.h>
#include "reader.h"

class CItem :public wxTreeItemData
{
		
	CReader *m_Reader;

public:

	CItem();
	~CItem();
		
	void SetReader(CReader *reader);
	CReader *GetReader();

};

#endif