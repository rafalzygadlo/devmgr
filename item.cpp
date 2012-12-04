#include "item.h"

CItem::CItem()
{
	m_Serial = NULL;
}

CItem::~CItem()
{
}

void CItem::SetSerial(CMySerial *serial)
{
	m_Serial = serial;
}

CMySerial *CItem::GetSerial()
{
	return m_Serial;
}
