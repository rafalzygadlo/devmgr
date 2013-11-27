#include "parser.h"
#include "protocol.h"
#include "tools.h"
#include "GeometryTools.h"

CParser::CParser()
{
	m_Broker = NULL;
}

CParser::~CParser()
{
	m_DataDefinition.clear();
	m_PositionDefinition.clear();
}

void CParser::SetBroker(CNaviBroker *broker)
{
	m_Broker = broker;
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

void CParser::Parse(unsigned char *line)
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
			
			memset( &m_Data, 0, sizeof(SData) );
			strcpy(m_Data.marker, DataDefinition.marker);
			m_Data.id = DataDefinition.id_signal;
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
						memcpy(m_Data.value + WriteStrPor, MarkerValue, MarkerValueSize );
						WriteStrPor += MarkerValueSize;
						ValidData = true;
					}
				}
			}
							
			FreeStrList( StrList, Size );
			if( ValidData )
				SetValidData();
			
		}

	}
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
		case 'E' :data = ' '; break;

		default: data = data;
	}

	return data;
}

double CParser::DD( float DM ) 
{

	int ddeg = ( int )(DM / 100);
	double min =  ( double )( DM / 100 - ddeg);
	double x = double ( min / 60 ) * 100;
	double a = ( double ) ddeg + x;

	return a;

}

double CParser::ConvertValue(int signal_id,double data)
{
	double value = data;
	switch(signal_id)
	{
		case SIGNAL_GGA_LAT:
		case SIGNAL_GLL_LAT:
		case SIGNAL_RMC_LAT:
		case SIGNAL_GGA_LON:
		case SIGNAL_GLL_LON:
		case SIGNAL_RMC_LON:
			value = DD(data);
		break;

	}

	return value;
}

void CParser::SetValidData()
{

	CFunctions Functions;
	CFunctiond Functiond;
	size_t len = Functions.GetLen();
	
	int id_signal = m_Data.id;
	int params_count = 0;
	
	for(size_t i  = 0; i < len; i++)
	{
		SFunctions *funcs = Functions.Get(i);
		size_t count = Functiond.GetLen();
		
		for(size_t j  = 0; j < count; j++)
		{
			SFunctiond *funcd = Functiond.Get(j);

			if(funcd->id_signal == id_signal)
			{
				//Reset(funcs->values);
				funcs->values[funcd->index] = ConvertValue(id_signal,atof(m_Data.value));
				SetFunction(funcd->id,funcs->values);
			}

		}
	
	}

}

void CParser::Reset(float *tab)
{
	tab[0] = NAVI_UNDEFINED;
	tab[1] = NAVI_UNDEFINED;
	tab[2] = NAVI_UNDEFINED;
	tab[3] = NAVI_UNDEFINED;
	tab[4] = NAVI_UNDEFINED;
	tab[5] = NAVI_UNDEFINED;
				
}
void CParser::SetFunction(int id_function, double *values)
{
	SFunctionData Function;
		
	Function.id_function = id_function;
	memcpy(Function.values,values,sizeof(double) * MAX_VALUES_LEN);
	
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnFuncData",&Function);
	
	
}
