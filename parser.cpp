#include "parser.h"
#include "protocol.h"
#include "tools.h"
#include "ais.h"
#include "tools.h"

CParser::CParser()
{
	m_Broker = NULL;
	m_MessageId = -1;
	m_FragmentCount = 0;
	m_Bits = NULL;
	m_Bitlen = 0;
	m_OldLen = 0;
}

CParser::~CParser()
{
	m_DataDefinition.clear();
	m_PositionDefinition.clear();
	if(m_Bits)
		free(m_Bits);
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

void CParser::Parse( char *line)
{
	//fprintf(stdout,"%s",line);
	//sygna³ nowej lini
			
	m_Multipart = false;
	SDefinition DataDefinition;
	for( size_t d = 0; d < m_DataDefinition.size() ; d++ ) 
	{

		DataDefinition = m_DataDefinition[d];

		if( (MemPos( (const unsigned char*)line, (int)strlen((char*)line), (const unsigned char*)DataDefinition.marker, (int)strlen( DataDefinition.marker ), 0 ) != -1 ) ) 
		{	// linia zawiera dane, które nale¿y wyci¹æ

			char *ValidLine = GetSentenceFromLine((char*)line, DataDefinition.marker );
			if(ValidLine == NULL)
				return;
			
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
					if(PositionDefinition.position >= Size)
						break;
					char *MarkerValue = StrList[ PositionDefinition.position ];
					MarkerValue = ConvertStr(MarkerValue,m_DataDefinition[d].id_signal);
					if( MarkerValue != NULL ) 
					{
						size_t MarkerValueSize = strlen( MarkerValue );
						if(MarkerValueSize > MAX_VALUE_LENGTH)
							break;
						memcpy(m_Data.value + WriteStrPor, MarkerValue, MarkerValueSize );
						
						WriteStrPor += MarkerValueSize;
						ValidData = true;
					}
				}
			}
							
			FreeStrList( StrList, Size );
						
			switch(m_Data.id)
			{				
				case AIS_MESSAGE: AisParse(line); break;
			}
			
			if( ValidData )
			{
				//fprintf(stdout,"[%s][%s] data:[%s]\n",sids.GetById(s->id_sids)->name, s->name,m_Data.value);
				// ustawia funkcje definiowane w protocole
//				SetValuesArray(m_Data);
				m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnDevData",&m_Data);
				SetValidData();
			}
			
		}

	}
}

void CParser::AisParse(char *line)
{
	Ais(line);
}

bool CParser::Ais(char *line)
{
	
	int str_size;
	char **StrList = ExplodeStr(line, ",", &str_size);
	
	if(str_size != AIS_PARTS)
	{
		fprintf(stdout,"%d\n",str_size);
		FreeStrList( StrList, str_size );
		return false;
	}

	int fn = 0;
	int fc = 0;
	bool decode = true;
	fc = atoi(StrList[AIS_FRAGMENT_COUNTER]);		// fragment counter
	fn = atoi(StrList[AIS_FRAGMENT_NUMBER]);		//fragment number
	char *data = StrList[AIS_DATA];
	int pad = 0;
		
	if(fc > 1)
	{
		decode = false;
		//fprintf(stderr,"%s",line);
				
		int mid = atoi(StrList[AIS_MESSAGE_ID]);		// message ID
		
		if(m_MessageId == -1)	// zaczynamy
		{		
			m_FragmentCount = 0;
			m_MessageId = mid;
		}
		
		if(mid != m_MessageId)
		{
			m_FragmentCount = 0;
			m_MessageId = -1;
			FreeStrList( StrList, str_size );
			return false;
		}
		
		m_MessageId = mid;
		char *csum = StrList[AIS_CHECKSUM];		//AIS_CHECKSUM
		int last_size;
		char **last = ExplodeStr(csum,"*",&last_size);
		pad = atoi(last[0]); // AIS_PAD

		m_FragmentCount++;
		
		if(fn != m_FragmentCount)
		{
			m_FragmentCount = 0;
			m_MessageId = -1;
			FreeStrList( last, last_size );
			FreeStrList( StrList, str_size );
			return false;
		}
		
		FreeStrList( last, last_size );
		
				
		if(fc == m_FragmentCount)
		{
			m_FragmentCount = 0;
			m_MessageId = -1;
			decode = true;
			int a = 0;
		}
				
	}
	
	
	to6bit(data,&m_OldLen,m_Bits,&m_Bitlen);
	m_Bitlen -= pad;
	
	FreeStrList( StrList, str_size );
	
	bool new_data  = false;
	
	if(decode)
	{
		GetMutex()->Lock();
		ais_t *ais = ais_binary_decode(m_Bits,m_Bitlen);
		ais_prepare_buffer(ais);
		GetMutex()->Unlock();
		free(m_Bits);
		m_Bits = NULL;
		m_Bitlen = 0;
		m_OldLen = 0;
	}
	
	

	return new_data;
	
}

char *CParser::ConvertStr(char *str, int id_signal)
{
	// sygnaly nie konwertowane
	switch(id_signal)
	{
		case AIS_MESSAGE: return str;
	}

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
				//if(SetGlobalPrioryty(funcd->id_signal)) // dla HDT (cog?)
				//{
					Reset(funcs->values);
					funcs->values[funcd->index] = ConvertValue(id_signal,atof(m_Data.value));
					SetFunction(funcd->id,funcs->values);
				//}
			}

		}

	}

}

void CParser::SetFunction(int id_function, double *values)
{
	SFunctionData Function;
	Function.id_function = id_function;
	memcpy(Function.values,values,sizeof(double) * MAX_VALUES_LEN);
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_OnFuncData",&Function);
}