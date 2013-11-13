#ifndef __PARSER
#define __PARSER

#include <wx/wx.h>
#include <vector>
#include "conf.h"
#include "protocol.h"

class CParser
{
	SData m_Data;
	CNaviBroker *m_Broker;
	std::vector<SDefinition> m_DataDefinition;
	std::vector<SPosition> m_PositionDefinition;
	
	char ConvertChar(char data);
	char *ConvertStr(char *str);
	void SetValidData();
	void SetFunction(int id_function, double *values);
		
public:
	CParser();
	~CParser();
		
	void Parse(unsigned char *line);
	void SetDefinition(int device_type);
	void SetBroker(CNaviBroker *broker);
		
};


#endif
