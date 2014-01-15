#ifndef __PARSER
#define __PARSER

#include <wx/wx.h>
#include <vector>
#include "conf.h"
#include "protocol.h"
#include "NaviMapIOApi.h"

class CParser
{
	SData m_Data;
	bool m_Multipart;
	CNaviBroker *m_Broker;
	std::vector<SDefinition> m_DataDefinition;
	std::vector<SPosition> m_PositionDefinition;
	int m_MessageId,m_FragmentCount;
	unsigned char *m_Bits;
	size_t m_Bitlen, m_OldLen;
	
	char ConvertChar(char data);
	char *ConvertStr(char *str);
	double ConvertValue(int signal_id,double data);
	void SetValidData();
	void SetFunction(int id_function, double *values);
	void Reset(float *tab);
	double DD( float DM );
	void Ais(char *str);
	void AisFragments(char *val);
	void AisFragmentNumber(char *val);
	void AisSequentialMessageId(char *val);

		
public:
	CParser();
	~CParser();
		
	void Parse( char *line);
	void SetDefinition(int device_type);
	void SetBroker(CNaviBroker *broker);
		
};


#endif
