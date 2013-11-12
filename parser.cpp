#include "parser.h"
#include "protocol.h"
#include "tools.h"

CParser::CParser()
{
	
}

CParser::~CParser()
{
	m_DataDefinition.clear();
	m_PositionDefinition.clear();
}

void CParser::SetDefinition(int device_type)
{
	
	m_DataDefinition.clear();
	m_PositionDefinition.clear();
	
	CProtocol Protocol;
	int counter = 0;
	
	SDevices *device = Protocol.GetDevice(device_type);
	
	SDefinition *Definition;
	Protocol.GetDefinitionById(device->id,counter,*&Definition);

	for(size_t i = 0; i < counter; i++)
	{
		m_DataDefinition.push_back(Definition[i]);

		int len;
		SPosition *Position;
		Protocol.GetPositionsById(Definition[i].id_signal,len,*&Position);

		for(size_t j = 0; j < len; j++)
		{
			m_PositionDefinition.push_back(Position[j]);			
		}
		
		delete Position;

	}
		
	delete Definition;
		
}

SData *CParser::Parse(unsigned char *line)
{
	
	//sygna³ nowej lini
			
	SDefinition DataDefinition;
	for( size_t d = 0; d < m_DataDefinition.size() ; d++ ) 
	{

		DataDefinition = m_DataDefinition[d];

		if( (MemPos( (const unsigned char*)line, (int)strlen((char*)line), (const unsigned char*)DataDefinition.marker, (int)strlen( DataDefinition.marker ), 0 ) != -1 ) ) 
		{	// linia zawiera dane, które nale¿y wyci¹æ

			char *ValidLine = GetSentenceFromLine((char*)line, DataDefinition.marker );	
			int Size;
			char **StrList = ExplodeStr(ValidLine, ",", &Size);
			free( ValidLine );
			
			memset( &Data, 0, sizeof(SData) );
			strcpy(Data.marker, DataDefinition.marker);
			Data.id = DataDefinition.id_signal;
			size_t WriteStrPor = 0;	// pozycja sk³adania ³añcucha wynikowego
			bool ValidData = false;	// flaga wa¿noœci danych
			SPosition PositionDefinition;
			
			for(size_t i = 0; i < m_PositionDefinition.size(); i++ ) 
			{
				PositionDefinition = m_PositionDefinition[i];

				if(m_DataDefinition[d].id_signal == m_PositionDefinition[i].id_signal)
				{
					char *MarkerValue = StrList[ PositionDefinition.position ];
					MarkerValue = ConvertStr(MarkerValue);
					if( MarkerValue != NULL ) 
					{
						size_t MarkerValueSize = strlen( MarkerValue );
						memcpy( Data.value + WriteStrPor, MarkerValue, MarkerValueSize );
						WriteStrPor += MarkerValueSize;
						ValidData = true;
					}
				}
			}
							
			FreeStrList( StrList, Size );
			
			// trzeba zmieniæ nie zwraca wszystkiego
			if( ValidData )
				return &Data;
			//......................................
		}

	}
	
	return NULL;
}

char *CParser::ConvertStr(char *str)
{
	if(str == NULL)
		return NULL;
	
	size_t len = strlen(str);
	for(size_t i = 0; i < len; i++)
	{
		char a = str[i];
		if(isalpha(a))
			str[i] = ConvertChar(a);
	}

	return str;
}

char CParser::ConvertChar(char data)
{
	switch(data)
	{
		case 'W': data = '-'; break;
		case 'S': data = '-'; break;
		case 'N': data = ' '; break;
		case 

		default: data = data;
	}

	return data;
}
