#ifndef __PARSER
#define __PARSER

#include <wx/wx.h>
#include <vector>
#include "conf.h"
#include "protocol.h"

class CParser
{
	SData Data;
	std::vector<SDefinition> m_DataDefinition;
	std::vector<SPosition> m_PositionDefinition;
	void Prepare(SData data);
	char ConvertChar(char data);
	char *ConvertStr(char *str);
	void SetValidData();
		
public:
	CParser();
	~CParser();
		
	void Parse(unsigned char *line);
	void SetDefinition(int device_type);
		
};


#endif
