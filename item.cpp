#include "item.h"

CItem::CItem()
{
	m_Reader = NULL;
}

CItem::~CItem()
{
}

void CItem::SetReader(CReader *reader)
{
	m_Reader = reader;
}

CReader *CItem::GetReader()
{
	return m_Reader;
}
