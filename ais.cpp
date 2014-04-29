#include "ais.h"
#include "tools.h"
#include <stdio.h>
#include "options.h"

CNaviArray <ais_t*> vAisData;
CNaviArray <ais_t*> vAisSearch;
SAisData *AisData = NULL;
CNaviArray <SAisData*> vAisBuffer;
int option = 0;
bool m_SearchReady = false;

const wchar_t *nvHazardousCargo[2][6] = 
{
	{
		L"Cones/Lights 0",
		L"Cones/Lights 1",
		L"Cones/Lights 2",
		L"Cones/Lights 3",
		L"B-Flag",
		L"N/A",
	},

	{
	}

};



const wchar_t *nvSpeedQuality[2][4] = 
{ 
	{
		L"Low/GNSS", 
		L"High", 
	},
	{
	}

};

const wchar_t *nvCourseQuality[2][4] = 
{ 
	{
		L"Low/GNSS", 
		L"High", 
	},
	{
	}

};

const wchar_t *nvHeadingQuality[2][4] = 
{ 
	{
		L"Low", 
		L"High", 
	},
	{
	}

};

const wchar_t *nvLoaded[2][4] = 
{ 
	{
		L"N/A",
		L"Loaded",
		L"Unloaded",
		L"N/A",
	},
	
	{
	
	}
};


const wchar_t *nvDTE[2][2] = 
{ 
	{
		L"Data terminal ready", 
		L"Not ready (default)",
	},
	
	{
	
	}
};

const wchar_t *nvShipTypes[2][100] = 
{ 
	{
		L"N/A",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Wing in ground (WIG), all ships of this type",
		L"Wing in ground (WIG), Hazardous category A",
		L"Wing in ground (WIG), Hazardous category B",
		L"Wing in ground (WIG), Hazardous category C",
		L"Wing in ground (WIG), Hazardous category D",
		L"Wing in ground (WIG), Reserved for future use",
		L"Wing in ground (WIG), Reserved for future use",
		L"Wing in ground (WIG), Reserved for future use",
		L"Wing in ground (WIG), Reserved for future use",
		L"Wing in ground (WIG), Reserved for future use",
		L"Fishing",
		L"Towing",
		L"Towing: length exceeds 200m or breadth exceeds 25m",
		L"Dredging or underwater ops",
		L"Diving ops",
		L"Military ops",
		L"Sailing",
		L"Pleasure Craft",
		L"Reserved",
		L"Reserved",
		L"High speed craft (HSC), all ships of this type",
		L"High speed craft (HSC), Hazardous category A",
		L"High speed craft (HSC), Hazardous category B",
		L"High speed craft (HSC), Hazardous category C",
		L"High speed craft (HSC), Hazardous category D",
		L"High speed craft (HSC), Reserved for future use",
		L"High speed craft (HSC), Reserved for future use",
		L"High speed craft (HSC), Reserved for future use",
		L"High speed craft (HSC), Reserved for future use",
		L"High speed craft (HSC), No additional information",
		L"Pilot Vessel",
		L"Search and Rescue vessel",
		L"Tug",
		L"Port Tender",
		L"Anti-pollution equipment",
		L"Law Enforcement",
		L"Spare - Local Vessel",
		L"Spare - Local Vessel",
		L"Medical Transport",
		L"Noncombatant ship according to RR Resolution No. 18",
		L"Passenger, all ships of this type",
		L"Passenger, Hazardous category A",
		L"Passenger, Hazardous category B",
		L"Passenger, Hazardous category C",
		L"Passenger, Hazardous category D",
		L"Passenger, Reserved for future use",
		L"Passenger, Reserved for future use",
		L"Passenger, Reserved for future use",
		L"Passenger, Reserved for future use",
		L"Passenger, No additional information",
		L"Cargo, all ships of this type",
		L"Cargo, Hazardous category A",
		L"Cargo, Hazardous category B",
		L"Cargo, Hazardous category C",
		L"Cargo, Hazardous category D",
		L"Cargo, Reserved for future use",
		L"Cargo, Reserved for future use",
		L"Cargo, Reserved for future use",
		L"Cargo, Reserved for future use",
		L"Cargo, No additional information",
		L"Tanker, all ships of this type",
		L"Tanker, Hazardous category A",
		L"Tanker, Hazardous category B",
		L"Tanker, Hazardous category C",
		L"Tanker, Hazardous category D",
		L"Tanker, Reserved for future use",
		L"Tanker, Reserved for future use",
		L"Tanker, Reserved for future use",
		L"Tanker, Reserved for future use",
		L"Tanker, No additional information",
		L"Other Type, all ships of this type",
		L"Other Type, Hazardous category A",
		L"Other Type, Hazardous category B",
		L"Other Type, Hazardous category C",
		L"Other Type, Hazardous category D",
		L"Other Type, Reserved for future use",
		L"Other Type, Reserved for future use",
		L"Other Type, Reserved for future use",
		L"Other Type, Reserved for future use",
		L"Other Type, no additional information",
	},
		
	{
	}

};

const wchar_t *nvEPFDFixTypes[2][16] = 
{ 
	{
		L"N/A",
		L"GPS",
		L"GLONASS",
		L"Combined GPS/GLONASS",
		L"Loran-C",
		L"Chayka",
		L"Integrated navigation system",
		L"Surveyed",
		L"Galileo",
		L"N/A",
		L"N/A",
		L"N/A",
		L"N/A",
		L"N/A",
		L"N/A",
		L"N/A",
	},
	
	{

	}
};

const wchar_t *nvManeuverIndicator[2][3] = 
{ 
	//EN
	{
		L"N/A",
		L"No special maneuver",
		L"Special maneuver (such as regional passing arrangement)",
	},
	
	{


	}

};

const wchar_t *nvNavigationStatus[2][16] = 
{
	//EN
	{
		L"Under way using engine",
		L"At anchor",
		L"Not under command",
		L"Restricted manoeuverability",
		L"Constrained by her draught",
		L"Moored",
		L"Aground",
		L"Engaged in Fishing",
		L"Under way sailing",
		L"Reserved for future amendment of Navigational Status for HSC",
		L"Reserved for future amendment of Navigational Status for WIG",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"Reserved for future use",
		L"N/A",

	},
	
	{
	
	}

};

struct ais_mid MID[] =
{	
	#include "data/mid.dat"
	{-1,-1},
};

ais_mid *ais_get_mid(unsigned int mmsi)
{
	char _mmsi[9];
	char _mid[4];
	memset(_mid,0,4);
	int mid = 0;
	itoa(mmsi,_mmsi,10);
	memcpy(_mid,_mmsi,3);

	mid = atoi(_mid);
	int i = 0;
	while(MID[i].id != -1)
	{
		if(MID[i].id == mid)
			return &MID[i];
		i++;
	}
	
	return NULL;

}

void ais_set_option(int val)
{
	option |= val;
}

void ais_save_file()
{
	FILE *f;
		
	wxString str = GetAisFile();
	wxCharBuffer buffer = str.ToUTF8();
	const char *fname = buffer.data();

	if( (f = fopen(fname , "wb" )) == NULL )
		return;

	for(size_t i = 0; i < vAisData.Length(); i++)
	{
		ais_t *ais = vAisData.Get(i);
		if(ais->valid[AIS_MSG_5])
		{
			fwrite(&ais->mmsi,sizeof(unsigned int),1,f);		//mmsi
			fwrite(&ais->type5,sizeof(ais_t::msg5),1,f);		//msg5
		}
	}

	fclose(f);

}

void ais_load_file()
{
	FILE *f;
	
	wxString str = GetAisFile();
	wxCharBuffer buffer = str.ToUTF8(); 
	const char *fname = buffer.data();
		
	f = fopen(fname , "rb" );
	
	if( f == NULL )
		return;

	size_t size = nvFileSize(fname);
	int count = size / sizeof(ais_t);
	rewind(f);
	
	while(!feof(f))
	{
		ais_t *ais = (ais_t*)malloc(sizeof(ais_t));
		memset(ais,0,sizeof(ais_t));

		size_t rec = fread(&ais->mmsi,sizeof(unsigned int),1,f);		//mmsi
		rec = fread(&ais->type5,sizeof(ais_t::msg5),1,f);				//msg5
		
		if(rec == 1)
		{
			ais->valid[AIS_MSG_5] = true;
			vAisData.Append(ais);
		}else{
			free(ais);
		}
	
	}
			
	fclose( f );

}
void toupper(char *str)
{
	size_t len = strlen(str);
	for(size_t i = 0; i < len;i++)
	{
		str[i] = toupper(str[i]);
	}
}

void ais_clear_search_buffer()
{
	vAisSearch.Clear();
}

bool ais_get_filter(ais_t *ais)
{
	
	for(size_t i = 0; i < AIS_MESSAGES_LENGTH; i++)
	{
		if(ais->valid[i + 1] &&	IS_BIT_SET(GetFilter(),i))
			return true;
	}

	return false;

}
bool ais_get_search_ready()
{
	return m_SearchReady;
}

void ais_set_search_buffer(char *str)
{
	vAisSearch.Clear();
	m_SearchReady = false;

	for(size_t i = 0; i < vAisData.Length(); i++)
	{
		ais_t *ais = ais_get_item(i);
		char mmsi[12];
		
		SAisData data;
		if(ais_set_name(ais,&data))
		{
			toupper(str);
			toupper(data.name);

			if( (strstr(data.name, str) != NULL || strstr(itoa(ais->mmsi,mmsi,10) , str) != NULL) && ais_get_filter(ais)) 
				vAisSearch.Append(ais);
		}else{
			
			if( strstr(itoa(ais->mmsi,mmsi,10) , str) != NULL && ais_get_filter(ais)) 
				vAisSearch.Append(ais);
		}
	
	}
	m_SearchReady = true;
	
}

size_t ais_get_search_item_count()
{
	return vAisSearch.Length();
}

ais_t *ais_get_search_item(size_t idx)
{
	ais_t *ais = vAisSearch.Get(idx);
	return ais;
}

void ais_sort()
{
	
	size_t len = vAisData.Length();
	/*
	for(size_t i = 0; i < len; i++)
	{	
		for(size_t j = 0; j < len - 1; j++)
		{
			if(strcmp(vAist[j]-> Devices[j].name,Devices[j + 1].name) > 0)
			{
				SDevices tmp;
				tmp = Devices[j];
				Devices[j] = Devices[j + 1];
				Devices[j + 1] = tmp;
			}
			
		}
	}

	*/
}
CNaviArray <SAisData*> *ais_get_buffer()
{
	return &vAisBuffer;
}

size_t ais_get_item_count()
{
	return vAisData.Length();
}

ais_t *ais_get_item(size_t idx)
{
	ais_t *ais = vAisData.Get(idx);
	return ais;
}

void ais_free_list()
{
	for(size_t  i = 0; i < vAisData.Length(); i++)
	{
		free(vAisData.Get(i));
	}
	
	vAisData.Clear();
}

void ais_free_buffer()
{
	for(size_t  i = 0; i < vAisBuffer.Length(); i++)
	{
		free(vAisBuffer.Get(i));
	}
	
	vAisBuffer.Clear();
}

ais_t *ais_msg_exists(int mmsi)
{
	for(size_t  i = 0; i < vAisData.Length(); i++)
	{
		ais_t *ais = vAisData.Get(i);
		if(ais->mmsi == mmsi)
			return ais;
	}

	return NULL;
}

SAisData *ais_buffer_exists(int mmsi)
{
	for(size_t  i = 0; i < vAisBuffer.Length(); i++)
	{
		SAisData *ptr = vAisBuffer.Get(i);
		if(ptr->mmsi == mmsi)
			return ptr;
	}

	return NULL;
}


ais_t *ais_binary_decode(unsigned char *bits, size_t bitlen)
{
	
	ais_t *ais;
	int mmsi;
	mmsi = (int)UBITS(8, 30);
	bool add = false;
	ais = ais_msg_exists(mmsi);
	
	if(!ais)
	{	
		ais = (ais_t*)malloc(sizeof(ais_t));
		memset(ais,0,sizeof(ais_t));
		add = true;
	}
    
	uint64_t type =	UBITS(0, 6);
	ais->mmsi = (int)UBITS(8, 30);
    ais->repeat = (int)UBITS(6, 2);
	
	if(type <= AIS_MESSAGES_LENGTH)
		ais->valid[type] = true;

	if(ais_decode(bits,bitlen,ais,type))
	{
		if(add)
		{
			vAisData.Append(ais);
		}
	
	}else{
		
		if(add)
		{
			free(ais);
			ais = NULL;
		}
	}
	
	return ais;
}

bool ais_decode(unsigned char *bits, size_t bitlen, ais_t *ais, int type)
{
	bool result = false;
	
	switch(type)
	{
		case AIS_MSG_1:		
		case AIS_MSG_2:		
		case AIS_MSG_3:		ais_message_1(bits,ais);			result = true;	break;
		case AIS_MSG_4:		
		case AIS_MSG_11:	ais_message_4(bits,ais);			result = true;	break;
		case AIS_MSG_5:		ais_message_5(bits,bitlen,ais);		result = true;	break;
		case AIS_MSG_6:		ais_message_6(bits,bitlen,ais);		result = true;	break;
		case AIS_MSG_13:
		case AIS_MSG_7:		ais_message_7(bits,bitlen,ais);		result = true;	break;
		case AIS_MSG_8:		ais_message_8(bits,bitlen,ais);		result = true;	break;
		case AIS_MSG_9:		ais_message_9(bits,ais);			result = true;	break;
		case AIS_MSG_10:	ais_message_10(bits,ais);			result = true;	break;
		case AIS_MSG_12:	ais_message_12(bits,bitlen,ais);	result = true;	break;
		case AIS_MSG_14:	ais_message_14(bits,bitlen,ais);	result = true;	break;
		case AIS_MSG_15:	ais_message_15(bits,bitlen,ais);	result = true;	break;
		case AIS_MSG_16:	ais_message_16(bits,bitlen,ais);	result = true;	break;
		case AIS_MSG_17:	ais_message_17(bits,bitlen,ais);	result = true;	break;
		case AIS_MSG_18:	ais_message_18(bits,ais);			result = true;	break;
		case AIS_MSG_19:	ais_message_19(bits,ais);			result = true;	break;
		case AIS_MSG_20:	ais_message_20(bits,bitlen,ais);	result = true;	break;
		case AIS_MSG_21:	ais_message_21(bits,bitlen,ais);	result = true;	break;
		case AIS_MSG_22:	ais_message_22(bits,ais);			result = true;	break;
		case AIS_MSG_23:	ais_message_23(bits,ais);			result = true;	break;
		case AIS_MSG_24:	ais_message_24(bits,bitlen,ais);	result = true;	break;
		case AIS_MSG_25:	ais_message_25(bits,bitlen,ais);	result = true;	break;

		default:
			fprintf(stdout,"UNKNOWN %d\n",type);
			
	}

	return result;
}

void ais_prepare_buffer(ais_t *ais)
{
	if(ais == NULL)
		return;
	
	SAisData *AisData = ais_buffer_exists(ais->mmsi);
	bool add = false;
	
	if(AisData == NULL)
	{
		AisData = (SAisData*)malloc(sizeof(SAisData));
		memset(AisData,0,sizeof(SAisData));
		AisData->valid_pos = false;
		AisData->valid_dim = false;
		AisData->valid_cog = false;
		AisData->valid_hdg = false;
		AisData->valid_sog = false;
		AisData->valid_name = false;
		
		add = true;
	}
		
	AisData->mmsi = ais->mmsi;
	AisData->time = GetTickCount();
	bool exists = false;
	
	if(ais_set_lon_lat(ais,AisData))
	{
		exists = true;			// wystarczy ze mamy lon lat
		AisData->valid_pos = true;
	}	
	
	if(ais_set_name(ais,AisData))
		AisData->valid_name = true;

	if(ais_set_dim(ais,AisData))
		AisData->valid_dim = true;

	if(ais_set_cog(ais,AisData))
		AisData->valid_cog = true;
	
	if(ais_set_hdg(ais,AisData))
		AisData->valid_hdg = true;
	
	if(ais_set_sog(ais,AisData))
		AisData->valid_sog = true;
	
	AisData->ais_ptr = ais;

	memcpy(AisData->valid,ais->valid,sizeof(ais->valid));
			
	if(exists)
	{
		if(add)
			vAisBuffer.Append(AisData);
	}else{
	
		if(add) // dane nie istnieja ale była zaalokowana pamiec wiec zwalniamy
			free(AisData);
	}

}	

bool ais_set_lon_lat(ais_t *ais,  SAisData *ptr)
{
	
	if(ais->valid[AIS_MSG_1])	{	ptr->lon = get_lon_lat(ais->type1.lon);		ptr->lat = get_lon_lat(ais->type1.lat);		return true;	}
	if(ais->valid[AIS_MSG_2])	{	ptr->lon = get_lon_lat(ais->type1.lon);		ptr->lat = get_lon_lat(ais->type1.lat);		return true;	}
	if(ais->valid[AIS_MSG_3])	{	ptr->lon = get_lon_lat(ais->type1.lon);		ptr->lat = get_lon_lat(ais->type1.lat);		return true;	}
	if(ais->valid[AIS_MSG_4])	{	ptr->lon = get_lon_lat(ais->type4.lon);		ptr->lat = get_lon_lat(ais->type4.lat);		return true;	}
	if(ais->valid[AIS_MSG_9])	{	ptr->lon = get_lon_lat(ais->type9.lon);		ptr->lat = get_lon_lat(ais->type9.lat);		return true;	}
	if(ais->valid[AIS_MSG_17])	{	ptr->lon = get_lon_lat(ais->type17.lon);	ptr->lat = get_lon_lat(ais->type17.lat);	return true;	}
	if(ais->valid[AIS_MSG_18])	{	ptr->lon = get_lon_lat(ais->type18.lon);	ptr->lat = get_lon_lat(ais->type18.lat);	return true;	}
	if(ais->valid[AIS_MSG_19])	{	ptr->lon = get_lon_lat(ais->type19.lon);	ptr->lat = get_lon_lat(ais->type19.lat);	return true;	}
	if(ais->valid[AIS_MSG_21])	{	ptr->lon = get_lon_lat(ais->type21.lon);	ptr->lat = get_lon_lat(ais->type21.lat);	return true;	}
	if(ais->valid[AIS_MSG_27])	{	ptr->lon = get_lon_lat(ais->type27.lon);	ptr->lat = get_lon_lat(ais->type27.lat);	return true;	}
	
	
	if(ais->valid[AIS_MSG_8] )
	{	
		if(ais->type8.dac1fid11.valid)	{	ptr->lon  = ais->type8.dac1fid11.lon;	ptr->lat = ais->type8.dac1fid11.lat;	return true;	}
		if(ais->type8.dac1fid19.valid)	{	ptr->lon  = ais->type8.dac1fid19.lon;	ptr->lat = ais->type8.dac1fid19.lat;	return true;	}
		if(ais->type8.dac1fid31.valid)	{	ptr->lon  = ais->type8.dac1fid31.lon;	ptr->lat = ais->type8.dac1fid31.lat;	return true;	}
		if(ais->type8.dac200fid40.valid){	ptr->lon  = ais->type8.dac200fid40.lon;	ptr->lat = ais->type8.dac200fid40.lat;	return true;	}
	}
	
	return false;
}

//bool ais_set_aton_name(ais_t *ais, SAisData *ptr)
//{
	//if(ais->valid[AIS_MSG_21])
	//{
		//memcpy(ptr->aton_name,ais->type21.name,AIS_ATON_NAME);
	//}
	
	//return true;
//}
bool ais_set_draught(ais_t *ais, SAisData *ptr)
{
	if(ais->valid[AIS_MSG_5])
	{
		ptr->draught = ais->type5.draught;
		return true;
	}

	return false;
}

bool ais_set_mmsi(ais_t *ais, SAisData *ptr)
{
	ptr->mmsi = ais->mmsi;
	return true;
}

bool ais_set_turn(ais_t *ais, SAisData *ptr)
{
	if(ais->valid[AIS_MSG_1])	{	ptr->turn = ais->type1.turn;	return true;	}
	if(ais->valid[AIS_MSG_2])	{	ptr->turn = ais->type1.turn;	return true;	}
	if(ais->valid[AIS_MSG_3])	{	ptr->turn = ais->type1.turn;	return true;	}

	return false;
}

bool ais_set_callsign(ais_t *ais, SAisData *ptr)
{
	if(ais->valid[AIS_MSG_5])
	{
		memcpy(ptr->callsign,ais->type5.callsign,AIS_CALLSIGN_MAXLEN + 1);
		return true;
	}

	return false;
}

bool ais_set_name(ais_t *ais, SAisData *ptr)
{
	if(ais->valid[AIS_MSG_5])
	{
		memcpy(ptr->name,ais->type5.shipname,AIS_SHIPNAME_MAXLEN + 1);
		return true;
	}

	if(ais->valid[AIS_MSG_19])
	{
		memcpy(ptr->name,ais->type19.shipname,AIS_SHIPNAME_MAXLEN + 1);
		return true;
	}

	
	if(ais->valid[AIS_MSG_21])
	{
		memcpy(ptr->name,ais->type21.name,AIS_ATON_NAME_MAXLEN + 1);
		return true;
	}
	

	if(ais->valid[AIS_MSG_24])
	{
		memcpy(ptr->name,ais->type24.shipname,AIS_SHIPNAME_MAXLEN + 1);
		return true;
	}

	return false;
}

bool ais_set_dim(ais_t *ais, SAisData *ptr)
{
	if(ais->valid[AIS_MSG_5])
	{
		ptr->to_bow			= ais->type5.to_bow;
		ptr->to_stern		= ais->type5.to_stern;
		ptr->to_port		= ais->type5.to_port;	
		ptr->to_starboard	= ais->type5.to_starboard;
		return true;
	}

	if(ais->valid[AIS_MSG_19])
	{
		ptr->to_bow			= ais->type19.to_bow;
		ptr->to_stern		= ais->type19.to_stern;
		ptr->to_port		= ais->type19.to_port;	
		ptr->to_starboard	= ais->type19.to_starboard;
		return true;
	}

	/*
	if(ais->valid[AIS_MSG_21])
	{
		ptr->to_bow			= ais->type21.to_bow;		ptr->to_stern		= ais->type21.to_stern;
		ptr->to_port		= ais->type21.to_port;	
		ptr->to_starboard	= ais->type21.to_starboard;
		//memcpy(ptr->shipname,ais->type21. shipname,AIS_SHIPNAME_MAXLEN + 1);
	
		return true;
	}
	*/

	if(ais->valid[AIS_MSG_24])
	{
		ptr->to_bow			= ais->type24.dim.to_bow;
		ptr->to_stern		= ais->type24.dim.to_stern;
		ptr->to_port		= ais->type24.dim.to_port;	
		ptr->to_starboard	= ais->type24.dim.to_starboard;
		return true;
	}

	return false;
}

bool ais_set_cog(ais_t *ais, SAisData *ptr)
{
	if(ais->valid[AIS_MSG_1] || ais->valid[AIS_MSG_2] || ais->valid[AIS_MSG_3])
	{
		if(ais->type1.course != AIS_COURSE_NOT_AVAILABLE)
		{
			ptr->cog = get_cog(ais->type1.course);
			return true;
		}
	}

	if(ais->valid[AIS_MSG_18])
	{
		if(ais->type18.course != AIS_COURSE_NOT_AVAILABLE)
		{
			ptr->cog = get_cog(ais->type18.course);
			return true;
		}
	}

	return false;
}

bool ais_set_hdg(ais_t *ais, SAisData *ptr)
{
	if(ais->valid[AIS_MSG_1] || ais->valid[AIS_MSG_2] || ais->valid[AIS_MSG_3])
	{
		if(ais->type1.heading != AIS_HEADING_NOT_AVAILABLE)
		{
			ptr->hdg = get_hdg(ais->type1.heading);
			return true;
		}
	}

	if(ais->valid[AIS_MSG_18])
	{
		if(ais->type18.heading != AIS_HEADING_NOT_AVAILABLE)
		{
			ptr->hdg = get_hdg(ais->type18.heading);
			return true;
		}
	}

	return false;

}

bool ais_set_sog(ais_t *ais, SAisData *ptr)
{
	if(ais->valid[AIS_MSG_1] || ais->valid[AIS_MSG_2] || ais->valid[AIS_MSG_3])
	{
		if(ais->type1.speed != AIS_SPEED_NOT_AVAILABLE)
		{
			ptr->sog = get_speed(ais->type1.speed);
			return true;
		}
	}
	
	if(ais->valid[AIS_MSG_18])
	{
		if(ais->type18.speed != AIS_SPEED_NOT_AVAILABLE)
		{
			ptr->sog = get_speed(ais->type1.speed);
			return true;
		}
	}
	
	return false;

}


/* Position Report */
void ais_message_1(unsigned char *bits, ais_t *ais)
{
	ais->type1.status = (int)UBITS(38, 4);
	ais->type1.turn = (int)SBITS(42, 8);
	ais->type1.speed = (int)UBITS(50, 10);
	ais->type1.accuracy	= UBITS(60, 1)!=0;
	ais->type1.lon = (int)SBITS(61, 28);
	ais->type1.lat = (int)SBITS(89, 27);
	ais->type1.course = (int)UBITS(116, 12);
	ais->type1.heading = (int)UBITS(128, 9);
	ais->type1.second = (int)UBITS(137, 6);
	ais->type1.maneuver	= (int)UBITS(143, 2);
	//ais->type1.spare	= UBITS(145, 3);
	ais->type1.raim = UBITS(148, 1)!=0;
	ais->type1.radio = (int)UBITS(149, 19);
		
}

/* Base Station Report */
/* UTC/Date Response */
/* 4,11 */
void ais_message_4(unsigned char *bits, ais_t *ais)
{
	 
	//PERMISSIVE_LENGTH_CHECK(168)
	ais->type4.year		= (int)UBITS(38, 14);
	ais->type4.month	= (int)UBITS(52, 4);
	ais->type4.day		= (int)UBITS(56, 5);
	ais->type4.hour		= (int)UBITS(61, 5);
	ais->type4.minute	= (int)UBITS(66, 6);
	ais->type4.second	= (int)UBITS(72, 6);
	ais->type4.accuracy	= UBITS(78, 1)!=0;
	ais->type4.lon		= (int)SBITS(79, 28);
	ais->type4.lat		= (int)SBITS(107, 27);
	ais->type4.epfd		= (int)UBITS(134, 4);
	//ais->type4.spare	= UBITS(138, 10);
	ais->type4.raim		= UBITS(148, 1)!=0;
	ais->type4.radio	= (int)UBITS(149, 19);

}

/* Ship static and voyage related data */
void ais_message_5(unsigned char *bits, size_t bitlen, ais_t *ais)
{

	if (bitlen != 424) 
	{
	    /*
	     * For unknown reasons, a lot of transmitters in the wild ship
	     * with a length of 420 or 422.  This is a recoverable error.
	     */
	    if (bitlen < 420)
			return;
	}

	ais->type5.ais_version  = (int)UBITS(38, 2);
	ais->type5.imo          = (int)UBITS(40, 30);
	UCHARS(70, ais->type5.callsign);
	UCHARS(112, ais->type5.shipname);
	ais->type5.shiptype     = (int)UBITS(232, 8);
	ais->type5.to_bow       = (int)UBITS(240, 9);
	ais->type5.to_stern     = (int)UBITS(249, 9);
	ais->type5.to_port      = (int)UBITS(258, 6);
	ais->type5.to_starboard = (int)UBITS(264, 6);
	ais->type5.epfd         = (int)UBITS(270, 4);
	ais->type5.month        = (int)UBITS(274, 4);
	ais->type5.day          = (int)UBITS(278, 5);
	ais->type5.hour         = (int)UBITS(283, 5);
	ais->type5.minute       = (int)UBITS(288, 6);
	ais->type5.draught      = (int)UBITS(294, 8);
	UCHARS(302, ais->type5.destination);
	if (bitlen >= 423)
	    ais->type5.dte          = (int)UBITS(422, 1);
	//ais->type5.spare        = UBITS(423, 1);

}

/* Addressed Binary Message */
void ais_message_6(unsigned char *bits, size_t bitlen, ais_t *ais)
{

	if (bitlen < 88 || bitlen > 1008) 
	{
	    return;
	}

	ais->type6.seqno          = (int)UBITS(38, 2);
	ais->type6.dest_mmsi      = (int)UBITS(40, 30);
	ais->type6.retransmit     = UBITS(70, 1)!=0;
	//ais->type6.spare        = UBITS(71, 1);
	ais->type6.dac            = (int)UBITS(72, 10);
	ais->type6.fid            = (int)UBITS(82, 6);
	ais->type6.bitcount       = bitlen - 88;
	
	/* Inland AIS */
	if (ais->type6.dac == 200) 
	{
	    switch (ais->type6.fid) 
		{
			case 21:	/* ETA at lock/bridge/terminal */
				UCHARS(88, ais->type6.dac200fid21.country);
				UCHARS(100, ais->type6.dac200fid21.locode);
				UCHARS(118, ais->type6.dac200fid21.section);
				UCHARS(148, ais->type6.dac200fid21.terminal);
				UCHARS(178, ais->type6.dac200fid21.hectometre);
				ais->type6.dac200fid21.month	= (int)UBITS(208, 4);
				ais->type6.dac200fid21.day	= (int)UBITS(212, 5);
				ais->type6.dac200fid21.hour	= (int)UBITS(217, 5);
				ais->type6.dac200fid21.minute	= (int)UBITS(222, 6);
				ais->type6.dac200fid21.tugs	= (int)UBITS(228, 3);
				ais->type6.dac200fid21.airdraught	= (int)UBITS(231, 12);
				/* skip 5 bits */
			break;
			case 22:	/* RTA at lock/bridge/terminal */
				UCHARS(88, ais->type6.dac200fid22.country);
				UCHARS(100, ais->type6.dac200fid22.locode);
				UCHARS(118, ais->type6.dac200fid22.section);
				UCHARS(148, ais->type6.dac200fid22.terminal);
				UCHARS(178, ais->type6.dac200fid22.hectometre);
				ais->type6.dac200fid22.month	= (int)UBITS(208, 4);
				ais->type6.dac200fid22.day	= (int)UBITS(212, 5);
				ais->type6.dac200fid22.hour	= (int)UBITS(217, 5);
				ais->type6.dac200fid22.minute	= (int)UBITS(222, 6);
				ais->type6.dac200fid22.status	= (int)UBITS(228, 2);
				/* skip 2 bits */
			break;
			case 55:	/* Number of Persons On Board */
				ais->type6.dac200fid55.crew	= (int)UBITS(88, 8);
				ais->type6.dac200fid55.passengers	= (int)UBITS(96, 13);
				ais->type6.dac200fid55.personnel	= (int)UBITS(109, 8);
				/* skip 51 bits */
			break;
	    }
	}
	
	/* UK and Republic Of Ireland */
	if (ais->type6.dac == 235 || ais->type6.dac == 250) 
	{
	    switch (ais->type6.fid) 
		{
			case 10:	/* GLA - AtoN monitoring data */
				ais->type6.dac235fid10.ana_int	= (int)UBITS(88, 10);
				ais->type6.dac235fid10.ana_ext1	= (int)UBITS(98, 10);
				ais->type6.dac235fid10.ana_ext2	= (int)UBITS(108, 10);
				ais->type6.dac235fid10.racon    = (int)UBITS(118, 2);
				ais->type6.dac235fid10.light    = (int)UBITS(120, 2);
				ais->type6.dac235fid10.alarm    = (bool)UBITS(122, 1);
				ais->type6.dac235fid10.stat_ext	= (int)UBITS(123, 8);
				ais->type6.dac235fid10.off_pos  = (bool)UBITS(131, 1);
				/* skip 4 bits */
			break;
	    }
	}
	
	/* International */
	if (ais->type6.dac == 1)
	{
	    switch (ais->type6.fid) 
		{
			case 12:	/* IMO236 - Dangerous cargo indication */
				UCHARS(88, ais->type6.dac1fid12.lastport);
				ais->type6.dac1fid12.lmonth		= (int)UBITS(118, 4);
				ais->type6.dac1fid12.lday		= (int)UBITS(122, 5);
				ais->type6.dac1fid12.lhour		= (int)UBITS(127, 5);
				ais->type6.dac1fid12.lminute	= (int)UBITS(132, 6);
				UCHARS(138, ais->type6.dac1fid12.nextport);
				ais->type6.dac1fid12.nmonth		= (int)UBITS(168, 4);
				ais->type6.dac1fid12.nday		= (int)UBITS(172, 5);
				ais->type6.dac1fid12.nhour		= (int)UBITS(177, 5);
				ais->type6.dac1fid12.nminute	= (int)UBITS(182, 6);
				UCHARS(188, ais->type6.dac1fid12.dangerous);
				UCHARS(308, ais->type6.dac1fid12.imdcat);
				ais->type6.dac1fid12.unid		= (int)UBITS(332, 13);
				ais->type6.dac1fid12.amount		= (int)UBITS(345, 10);
				ais->type6.dac1fid12.unit		= (int)UBITS(355, 2);
				/* skip 3 bits */
			break;

			case 14:	/* IMO236 - Tidal Window */
				ais->type6.dac1fid32.month	= (int)UBITS(88, 4);
				ais->type6.dac1fid32.day	= (int)UBITS(92, 5);
	#define ARRAY_BASE 97
	#define ELEMENT_SIZE 93
		int u = 0;
		for (u = 0; ARRAY_BASE + (ELEMENT_SIZE*u) <= bitlen; u++) 
		{
		    int a = ARRAY_BASE + (ELEMENT_SIZE*u);
			ais->type6.dac1fid32.tidals[u].lat		= SBITS(a + 0, 27);
		    ais->type6.dac1fid32.tidals[u].lon		= SBITS(a + 27, 28);
		    ais->type6.dac1fid32.tidals[u].from_hour= UBITS(a + 55, 5);
		    ais->type6.dac1fid32.tidals[u].from_min	= UBITS(a + 60, 6);
		    ais->type6.dac1fid32.tidals[u].to_hour	= UBITS(a + 66, 5);
		    ais->type6.dac1fid32.tidals[u].to_min	= UBITS(a + 71, 6);
		    ais->type6.dac1fid32.tidals[u].cdir		= UBITS(a + 77, 9);
		    ais->type6.dac1fid32.tidals[u].cspeed	= UBITS(a + 86, 7);
		}
		ais->type6.dac1fid32.ntidals = u;
		
#undef ARRAY_BASE
#undef ELEMENT_SIZE
		
		break;
		}
	}
}

/* Binary acknowledge */
/* Safety Related Acknowledge */
void ais_message_7(unsigned char *bits, size_t bitlen, ais_t *ais)
{
	unsigned int mmsi[4];
	
	if (bitlen < 72 || bitlen > 158) 
	{
	    return;
	}
	
	for (size_t u = 0; u < sizeof(mmsi)/sizeof(mmsi[0]); u++)
	    if (bitlen > 40 + 32*u)
			mmsi[u] = (int)UBITS(40 + 32*u, 30);
	    else
			mmsi[u] = 0;
	
	ais->type7.mmsi1 = mmsi[0];
	ais->type7.mmsi2 = mmsi[1];
	ais->type7.mmsi3 = mmsi[2];
	ais->type7.mmsi4 = mmsi[3];
		
}

/* Binary Broadcast Message */
void ais_message_8(unsigned char *bits, size_t bitlen, ais_t *ais)
{
	bool structured = false;
	if (bitlen < 56 || bitlen > 1008) 
	{
	     return;
	}
	size_t i = 0;
	size_t u = 0;
	
	
	//ais->type8.spare        = UBITS(38, 2);
	ais->type8.dac            = (int)UBITS(40, 10);
	ais->type8.fid            = (int)UBITS(50, 6);
	ais->type8.bitcount       = bitlen - 56;
	structured = false;
	if (ais->type8.dac == 1)
	{
	    switch (ais->type8.fid) 
		{
			case 11:        /* IMO236 - Meteorological/Hydrological data */
				/* layout is almost identical to FID=31 from IMO289 */
				ais->type8.dac1fid11.valid		=true;
				ais->type8.dac1fid11.lat		= (int)SBITS(56, 24);
				ais->type8.dac1fid11.lon		= (int)SBITS(80, 25);
				ais->type8.dac1fid11.day		= (int)UBITS(105, 5);
				ais->type8.dac1fid11.hour		= (int)UBITS(110, 5);
				ais->type8.dac1fid11.minute		= (int)UBITS(115, 6);
				ais->type8.dac1fid11.wspeed		= (int)UBITS(121, 7);
				ais->type8.dac1fid11.wgust		= (int)UBITS(128, 7);
				ais->type8.dac1fid11.wdir		= (int)UBITS(135, 9);
				ais->type8.dac1fid11.wgustdir	= (int)UBITS(144, 9);
				ais->type8.dac1fid11.airtemp	= (int)UBITS(153, 11);
				ais->type8.dac1fid11.humidity	= (int)UBITS(164, 7);
				ais->type8.dac1fid11.dewpoint	= (int)UBITS(171, 10);
				ais->type8.dac1fid11.pressure	= (int)UBITS(181, 9);
				ais->type8.dac1fid11.pressuretend	= (int)UBITS(190, 2);
				ais->type8.dac1fid11.visibility	= (int)UBITS(192, 8);
				ais->type8.dac1fid11.waterlevel	= (int)UBITS(200, 9);
				ais->type8.dac1fid11.leveltrend	= (int)UBITS(209, 2);
				ais->type8.dac1fid11.cspeed		= (int)UBITS(211, 8);
				ais->type8.dac1fid11.cdir		= (int)UBITS(219, 9);
				ais->type8.dac1fid11.cspeed2	= (int)UBITS(228, 8);
				ais->type8.dac1fid11.cdir2		= (int)UBITS(236, 9);
				ais->type8.dac1fid11.cdepth2	= (int)UBITS(245, 5);
				ais->type8.dac1fid11.cspeed3	= (int)UBITS(250, 8);
				ais->type8.dac1fid11.cdir3		= (int)UBITS(258, 9);
				ais->type8.dac1fid11.cdepth3	= (int)UBITS(267, 5);
				ais->type8.dac1fid11.waveheight	= (int)UBITS(272, 8);
				ais->type8.dac1fid11.waveperiod	= (int)UBITS(280, 6);
				ais->type8.dac1fid11.wavedir	= (int)UBITS(286, 9);
				ais->type8.dac1fid11.swellheight	= (int)UBITS(295, 8);
				ais->type8.dac1fid11.swellperiod	= (int)UBITS(303, 6);
				ais->type8.dac1fid11.swelldir	= (int)UBITS(309, 9);
				ais->type8.dac1fid11.seastate	= (int)UBITS(318, 4);
				ais->type8.dac1fid11.watertemp	= (int)UBITS(322, 10);
				ais->type8.dac1fid11.preciptype	= (int)UBITS(332, 3);
				ais->type8.dac1fid11.salinity	= (int)UBITS(335, 9);
				ais->type8.dac1fid11.ice		= (int)UBITS(344, 2);
				structured = true;
			break;
			
			case 13:        /* IMO236 - Fairway closed */
				UCHARS(56, ais->type8.dac1fid13.reason);
				UCHARS(176, ais->type8.dac1fid13.closefrom);
				UCHARS(296, ais->type8.dac1fid13.closeto);
				ais->type8.dac1fid13.valid		=true;
				ais->type8.dac1fid13.radius 	= (int)UBITS(416, 10);
				ais->type8.dac1fid13.extunit	= (int)UBITS(426, 2);
				ais->type8.dac1fid13.fday   	= (int)UBITS(428, 5);
				ais->type8.dac1fid13.fmonth 	= (int)UBITS(433, 4);
				ais->type8.dac1fid13.fhour  	= (int)UBITS(437, 5);
				ais->type8.dac1fid13.fminute	= (int)UBITS(442, 6);
				ais->type8.dac1fid13.tday   	= (int)UBITS(448, 5);
				ais->type8.dac1fid13.tmonth 	= (int)UBITS(453, 4);
				ais->type8.dac1fid13.thour  	= (int)UBITS(457, 5);
				ais->type8.dac1fid13.tminute	= (int)UBITS(462, 6);
				/* skip 4 bits */
				structured = true;
			break;
	    
			case 15:        /* IMO236 - Extended ship and voyage */
				ais->type8.dac1fid15.airdraught	= (int)UBITS(56, 11);
				/* skip 5 bits */
				structured = true;
			break;
	    
			case 16:	    /* Number of Persons On Board */
				if (ais->type8.bitcount == 136)
					ais->type8.dac1fid16.persons = (int)UBITS(88, 13);/* 289 */
				else
					ais->type8.dac1fid16.persons = (int)UBITS(55, 13);/* 236 */
				structured = true;
			break;
	    
			case 17:        /* IMO289 - VTS-generated/synthetic targets */
#define ARRAY_BASE 56
#define ELEMENT_SIZE 122
				for (u = 0; ARRAY_BASE + (ELEMENT_SIZE*u) <= bitlen; u++) 
				{
					//target_t tp = ais->type8.dac1fid17.targets[u].id;
					int a = ARRAY_BASE + (ELEMENT_SIZE*u);
					ais->type8.dac1fid17.targets[u].idtype = (int)UBITS(a + 0, 2);
					switch (ais->type8.dac1fid17.targets[u].idtype) 
					{
						case DAC1FID17_IDTYPE_MMSI:
							ais->type8.dac1fid17.targets[u].id.mmsi	= (int)UBITS(a + 2, 42);
						break;
						case DAC1FID17_IDTYPE_IMO:
							ais->type8.dac1fid17.targets[u].id.imo	= (int)UBITS(a + 2, 42);
						break;
						case DAC1FID17_IDTYPE_CALLSIGN:
							UCHARS(a+2, ais->type8.dac1fid17.targets[u].id.callsign);
						break;
						default:
							UCHARS(a+2, ais->type8.dac1fid17.targets[u].id.other);
						break;
					}
					
					/* skip 4 bits */
					ais->type8.dac1fid17.valid = true;
					ais->type8.dac1fid17.targets[u].lat	= (int)SBITS(a + 48, 24);
					ais->type8.dac1fid17.targets[u].lon	= (int)SBITS(a + 72, 25);
					ais->type8.dac1fid17.targets[u].course	= (int)UBITS(a + 97, 9);
					ais->type8.dac1fid17.targets[u].second	= (int)UBITS(a + 106, 6);
					ais->type8.dac1fid17.targets[u].speed	= (int)UBITS(a + 112, 10);
				}
		ais->type8.dac1fid17.ntargets = u;
#undef ARRAY_BASE
#undef ELEMENT_SIZE
		structured = true;
		break;
	    
			case 19:        /* IMO289 - Marine Traffic Signal */
				ais->type8.dac1fid19.valid = true;
				ais->type8.dac1fid19.linkage	= (int)UBITS(56, 10);
				UCHARS(66, ais->type8.dac1fid19.station);
				ais->type8.dac1fid19.lon	= (int)SBITS(186, 25);
				ais->type8.dac1fid19.lat	= (int)SBITS(211, 24);
				ais->type8.dac1fid19.status	= (int)UBITS(235, 2);
				ais->type8.dac1fid19.signal	= (int)UBITS(237, 5);
				ais->type8.dac1fid19.hour	= (int)UBITS(242, 5);
				ais->type8.dac1fid19.minute	= (int)UBITS(247, 6);
				ais->type8.dac1fid19.nextsignal	= (int)UBITS(253, 5);
				/* skip 102 bits */
				structured = true;
			break;
	    
			case 21:        /* IMO289 - Weather obs. report from ship */
			break;
	    
			case 22:        /* IMO289 - Area notice - broadcast */
			break;
	    
			case 24:        /* IMO289 - Extended ship static & voyage-related data */
			break;
	    
			case 26:        /* IMO289 - Environmental */
			break;
	    
			case 27:        /* IMO289 - Route information - broadcast */
				ais->type8.dac1fid27.linkage	= (int)UBITS(56, 10);
				ais->type8.dac1fid27.sender	= (int)UBITS(66, 3);
				ais->type8.dac1fid27.rtype	= (int)UBITS(69, 5);
				ais->type8.dac1fid27.month	= (int)UBITS(74, 4);
				ais->type8.dac1fid27.day	= (int)UBITS(78, 5);
				ais->type8.dac1fid27.hour	= (int)UBITS(83, 5);
				ais->type8.dac1fid27.minute	= (int)UBITS(88, 6);
				ais->type8.dac1fid27.duration	= (int)UBITS(94, 18);
				ais->type8.dac1fid27.waycount	= (int)UBITS(112, 5);
#define ARRAY_BASE 117
#define ELEMENT_SIZE 55
				for (i = 0; i < ais->type8.dac1fid27.waycount; i++) 
				{
					int a = ARRAY_BASE + (ELEMENT_SIZE*i);
					ais->type8.dac1fid27.waypoints[i].lon	= (int)SBITS(a + 0, 28);
					ais->type8.dac1fid27.waypoints[i].lat	= (int)SBITS(a + 28, 27);
				}
#undef ARRAY_BASE
#undef ELEMENT_SIZE
				structured = true;
			break;
	    
			case 29:        /* IMO289 - Text Description - broadcast */
				ais->type8.dac1fid29.linkage   = (int)UBITS(56, 10);
				ENDCHARS(66, ais->type8.dac1fid29.text);
				structured = true;
			break;
	    
			case 31:        /* IMO289 - Meteorological/Hydrological data */
				ais->type8.dac1fid31.valid		= true;
				ais->type8.dac1fid31.lon		= (int)SBITS(56, 25);
				ais->type8.dac1fid31.lat		= (int)SBITS(81, 24);
				ais->type8.dac1fid31.accuracy       = (bool)UBITS(105, 1);
				ais->type8.dac1fid31.day		= (int)UBITS(106, 5);
				ais->type8.dac1fid31.hour		= (int)UBITS(111, 5);
				ais->type8.dac1fid31.minute		= (int)UBITS(116, 6);
				ais->type8.dac1fid31.wspeed		= (int)UBITS(122, 7);
				ais->type8.dac1fid31.wgust		= (int)UBITS(129, 7);
				ais->type8.dac1fid31.wdir		= (int)UBITS(136, 9);
				ais->type8.dac1fid31.wgustdir	= (int)UBITS(145, 9);
				ais->type8.dac1fid31.airtemp	= (int)SBITS(154, 11);
				ais->type8.dac1fid31.humidity	= (int)UBITS(165, 7);
				ais->type8.dac1fid31.dewpoint	= (int)SBITS(172, 10);
				ais->type8.dac1fid31.pressure	= (int)UBITS(182, 9);
				ais->type8.dac1fid31.pressuretend	= (int)UBITS(191, 2);
				ais->type8.dac1fid31.visgreater	= (int)UBITS(193, 1);
				ais->type8.dac1fid31.visibility	= (int)UBITS(194, 7);
				ais->type8.dac1fid31.waterlevel	= (int)UBITS(201, 12);
				ais->type8.dac1fid31.leveltrend	= (int)UBITS(213, 2);
				ais->type8.dac1fid31.cspeed		= (int)UBITS(215, 8);
				ais->type8.dac1fid31.cdir		= (int)UBITS(223, 9);
				ais->type8.dac1fid31.cspeed2	= (int)UBITS(232, 8);
				ais->type8.dac1fid31.cdir2		= (int)UBITS(240, 9);
				ais->type8.dac1fid31.cdepth2	= (int)UBITS(249, 5);
				ais->type8.dac1fid31.cspeed3	= (int)UBITS(254, 8);
				ais->type8.dac1fid31.cdir3		= (int)UBITS(262, 9);
				ais->type8.dac1fid31.cdepth3	= (int)UBITS(271, 5);
				ais->type8.dac1fid31.waveheight	= (int)UBITS(276, 8);
				ais->type8.dac1fid31.waveperiod	= (int)UBITS(284, 6);
				ais->type8.dac1fid31.wavedir	= (int)UBITS(290, 9);
				ais->type8.dac1fid31.swellheight	= (int)UBITS(299, 8);
				ais->type8.dac1fid31.swellperiod	= (int)UBITS(307, 6);
				ais->type8.dac1fid31.swelldir	= (int)UBITS(313, 9);
				ais->type8.dac1fid31.seastate	= (int)UBITS(322, 4);
				ais->type8.dac1fid31.watertemp	= (int)SBITS(326, 10);
				ais->type8.dac1fid31.preciptype	= (int)UBITS(336, 3);
				ais->type8.dac1fid31.salinity	= (int)UBITS(339, 9);
				ais->type8.dac1fid31.ice		= (int)UBITS(348, 2);
				structured = true;
			break;
		}
	}
	 
	
	if (ais->type8.dac == 200) 
	{
	    switch (ais->type8.fid) 
		{
			//case 21:	/* Inland ship static and voyage related data */
			case 10:	/* Inland ship static and voyage related data */
				UCHARS(56, ais->type8.dac200fid10.vin);
				ais->type8.dac200fid10.length	= (int)UBITS(104, 13);
				ais->type8.dac200fid10.beam	= (int)UBITS(117, 10);
				ais->type8.dac200fid10.type	= (int)UBITS(127, 14);
				ais->type8.dac200fid10.hazard	= (int)UBITS(141, 3);
				ais->type8.dac200fid10.draught	= (int)UBITS(144, 11);
				ais->type8.dac200fid10.loaded	= (int)UBITS(155, 2);
				ais->type8.dac200fid10.speed_q	= (bool)UBITS(157, 1);
				ais->type8.dac200fid10.course_q	= (bool)UBITS(158, 1);
				ais->type8.dac200fid10.heading_q	= (bool)UBITS(159, 1);
				/* skip 8 bits */
				structured = true;
			break;
	    
			case 23:
				ais->type8.dac200fid23.start_year	= (int)UBITS(56, 8);
				ais->type8.dac200fid23.start_month	= (int)UBITS(64, 4);
				ais->type8.dac200fid23.start_day	= (int)UBITS(68, 5);
				ais->type8.dac200fid23.end_year	= (int)UBITS(73, 8);
				ais->type8.dac200fid23.end_month	= (int)UBITS(81, 4);
				ais->type8.dac200fid23.end_day	= (int)UBITS(85, 5);
				ais->type8.dac200fid23.start_hour	= (int)UBITS(90, 5);
				ais->type8.dac200fid23.start_minute	= (int)UBITS(95, 6);
				ais->type8.dac200fid23.end_hour	= (int)UBITS(101, 5);
				ais->type8.dac200fid23.end_minute	= (int)UBITS(106, 6);
				ais->type8.dac200fid23.start_lon	= (int)SBITS(112, 28);
				ais->type8.dac200fid23.start_lat	= (int)SBITS(140, 27);
				ais->type8.dac200fid23.end_lon	= (int)SBITS(167, 28);
				ais->type8.dac200fid23.end_lat	= (int)SBITS(195, 27);
				ais->type8.dac200fid23.type	= (int)UBITS(222, 4);
				ais->type8.dac200fid23.min	= (int)SBITS(226, 9);
				ais->type8.dac200fid23.max	= (int)SBITS(235, 9);
				ais->type8.dac200fid23.intensity	= (int)UBITS(244, 2);
				ais->type8.dac200fid23.wind	= (int)UBITS(246, 4);
				/* skip 6 bits */
				structured = true;
			break;
	    
			case 24:
				UCHARS(56, ais->type8.dac200fid24.country);
#define ARRAY_BASE 68
#define ELEMENT_SIZE 25
				for (i = 0; ARRAY_BASE + (ELEMENT_SIZE*i) < (int)bitlen; i++) 
				{
					int a = ARRAY_BASE + (ELEMENT_SIZE*i);
					ais->type8.dac200fid24.gauges[i].id = (int)UBITS(a+0,  11);
					ais->type8.dac200fid24.gauges[i].level = (int)SBITS(a+11, 14);
				}
				ais->type8.dac200fid24.ngauges = i;
#undef ARRAY_BASE
#undef ELEMENT_SIZE
				/* skip 6 bits */
				structured = true;
			break;
	    
			case 40:
				ais->type8.dac200fid40.valid = true;
				ais->type8.dac200fid40.lon	= (int)SBITS(56, 28);
				ais->type8.dac200fid40.lat	= (int)SBITS(84, 27);
				ais->type8.dac200fid40.form	= (int)UBITS(111, 4);
				ais->type8.dac200fid40.facing	= (int)UBITS(115, 9);
				ais->type8.dac200fid40.direction	= (int)UBITS(124, 3);
				ais->type8.dac200fid40.status	= (int)UBITS(127, 30);
				/* skip 11 bits */
				structured = true;
			break;
	    }
	}
	/* land here if we failed to match a known DAC/FID */
	if (!structured)
	    (void)memcpy(ais->type8.bitdata, (char *)bits + (56 / BITS_PER_BYTE), (ais->type8.bitcount + 7) / 8);

}

/* Standard SAR Aircraft Position Report */
void ais_message_9(unsigned char *bits, ais_t *ais)
{

	//PERMISSIVE_LENGTH_CHECK(168);
	ais->type9.alt = (int)UBITS(38, 12);
	ais->type9.speed = (int)UBITS(50, 10);
	ais->type9.accuracy	= (bool)UBITS(60, 1);
	ais->type9.lon = (int)SBITS(61, 28);
	ais->type9.lat = (int)SBITS(89, 27);
	ais->type9.course = (int)UBITS(116, 12);
	ais->type9.second = (int)UBITS(128, 6);
	ais->type9.regional = (int)UBITS(134, 8);
	ais->type9.dte = (int)UBITS(142, 1);
	//ais->type9.spare		= UBITS(143, 3);
	ais->type9.assigned = UBITS(146, 1)!=0;
	ais->type9.raim	= UBITS(147, 1)!=0;
	ais->type9.radio = (int)UBITS(148, 19);

}

/* UTC/Date inquiry */
void ais_message_10(unsigned char *bits, ais_t *ais)
{
	//PERMISSIVE_LENGTH_CHECK(72);
	//ais->type10.spare        = UBITS(38, 2);
	ais->type10.dest_mmsi      = (int)UBITS(40, 30);
	//ais->type10.spare2       = UBITS(70, 2);
}

/* Safety Related Message */
void ais_message_12(unsigned char *bits, size_t bitlen, ais_t *ais)
{

	if (bitlen < 72 || bitlen > 1008) 
	{
	    return;
	}
	
	ais->type12.seqno          = (int)UBITS(38, 2);
	ais->type12.dest_mmsi      = (int)UBITS(40, 30);
	ais->type12.retransmit     = (bool)UBITS(70, 1);
	//ais->type12.spare        = UBITS(71, 1);
	ENDCHARS(72, ais->type12.text);

}

/* Safety Related Broadcast Message */
void ais_message_14(unsigned char *bits, size_t bitlen, ais_t *ais)
{

	if (bitlen < 40 || bitlen > 1008) 
	{
	    return;
	}
	//ais->type14.spare          = UBITS(38, 2);
	ENDCHARS(40, ais->type14.text);
}

/* Interrogation */
void ais_message_15(unsigned char *bits, size_t bitlen, ais_t *ais)
{
	if (bitlen < 88 || bitlen > 168) 
	{
	    return;
	}
	
	//(void)memset(&ais->type15, '\0', sizeof(ais->type15));
	//ais->type14.spare         = UBITS(38, 2);
	ais->type15.mmsi1		= (int)UBITS(40, 30);
	ais->type15.type1_1		= (int)UBITS(70, 6);
	ais->type15.type1_1		= (int)UBITS(70, 6);
	ais->type15.offset1_1	= (int)UBITS(76, 12);
	//ais->type14.spare2        = UBITS(88, 2);
	
	if (bitlen > 90) 
	{
	    ais->type15.type1_2	= (int)UBITS(90, 6);
	    ais->type15.offset1_2	= (int)UBITS(96, 12);
	    //ais->type14.spare3    = UBITS(108, 2);
	    if (bitlen > 110) 
		{
			ais->type15.mmsi2	= (int)UBITS(110, 30);
			ais->type15.type2_1	= (int)UBITS(140, 6);
			ais->type15.offset2_1	= (int)UBITS(146, 12);
			//ais->type14.spare4	= UBITS(158, 2);
	    }
	}

}


/* Assigned Mode Command */
void ais_message_16(unsigned char *bits, size_t bitlen, ais_t *ais)
{

	if (bitlen != 96 && bitlen != 144) 
	{
		return;
	}
	
	ais->type16.mmsi1		= (int)UBITS(40, 30);
	ais->type16.offset1		= (int)UBITS(70, 12);
	ais->type16.increment1	= (int)UBITS(82, 10);
	if (bitlen < 144)
	{
	    ais->type16.mmsi2 = ais->type16.offset2 = ais->type16.increment2 = 0;
	}else {
	    ais->type16.mmsi2	= (int)UBITS(92, 30);
	    ais->type16.offset2	= (int)UBITS(122, 12);
	    ais->type16.increment2	= (int)UBITS(134, 10);
	}
	
}


/* GNSS Broadcast Binary Message */
void ais_message_17(unsigned char *bits, size_t bitlen, ais_t *ais)
{
	if (bitlen < 80 || bitlen > 816) 
	{
	    return;
	}
	
	//ais->type17.spare     = UBITS(38, 2);
	ais->type17.lon			= UBITS(40, 18);
	ais->type17.lat			= UBITS(58, 17);
	//ais->type17.spare	    = UBITS(75, 4);
	ais->type17.bitcount    = bitlen - 80;
	(void)memcpy(ais->type17.bitdata, (char *)bits + (80 / BITS_PER_BYTE), (ais->type17.bitcount + 7) / 8);

}
	
/* Standard Class B CS Position Report */
void ais_message_18(unsigned char *bits, ais_t *ais)
{

//	PERMISSIVE_LENGTH_CHECK(168)
	ais->type18.reserved	= UBITS(38, 8);
	ais->type18.speed		= UBITS(46, 10);
	ais->type18.accuracy	= UBITS(56, 1)!=0;
	ais->type18.lon			= SBITS(57, 28);
	ais->type18.lat			= SBITS(85, 27);
	ais->type18.course		= UBITS(112, 12);
	ais->type18.heading		= UBITS(124, 9);
	ais->type18.second		= UBITS(133, 6);
	ais->type18.regional	= UBITS(139, 2);
	ais->type18.cs			= UBITS(141, 1)!=0;
	ais->type18.display 	= UBITS(142, 1)!=0;
	ais->type18.dsc     	= UBITS(143, 1)!=0;
	ais->type18.band    	= UBITS(144, 1)!=0;
	ais->type18.msg22   	= UBITS(145, 1)!=0;
	ais->type18.assigned	= UBITS(146, 1)!=0;
	ais->type18.raim		= UBITS(147, 1)!=0;
	ais->type18.radio		= UBITS(148, 20);
}

/* Extended Class B CS Position Report */
void ais_message_19(unsigned char *bits, ais_t *ais)
{
	//PERMISSIVE_LENGTH_CHECK(312)
	ais->type19.reserved     = UBITS(38, 8);
	ais->type19.speed        = UBITS(46, 10);
	ais->type19.accuracy     = UBITS(56, 1)!=0;
	ais->type19.lon          = SBITS(57, 28);
	ais->type19.lat          = SBITS(85, 27);
	ais->type19.course       = UBITS(112, 12);
	ais->type19.heading      = UBITS(124, 9);
	ais->type19.second       = UBITS(133, 6);
	ais->type19.regional     = UBITS(139, 4);
	UCHARS(143, ais->type19.shipname);
	ais->type19.shiptype     = UBITS(263, 8);
	ais->type19.to_bow       = UBITS(271, 9);
	ais->type19.to_stern     = UBITS(280, 9);
	ais->type19.to_port      = UBITS(289, 6);
	ais->type19.to_starboard = UBITS(295, 6);
	ais->type19.epfd         = UBITS(301, 4);
	ais->type19.raim         = UBITS(305, 1)!=0;
	ais->type19.dte          = UBITS(306, 1)!=0;
	ais->type19.assigned     = UBITS(307, 1)!=0;
	//ais->type19.spare      = UBITS(308, 4);

}

/* Data Link Management Message */
void ais_message_20(unsigned char *bits, size_t bitlen, ais_t *ais)
{
	if (bitlen < 72 || bitlen > 160) 
	{
		return;
	}
	
	//ais->type20.spare		= UBITS(38, 2);
	ais->type20.offset1		= UBITS(40, 12);
	ais->type20.number1		= UBITS(52, 4);
	ais->type20.timeout1	= UBITS(56, 3);
	ais->type20.increment1	= UBITS(59, 11);
	ais->type20.offset2		= UBITS(70, 12);
	ais->type20.number2		= UBITS(82, 4);
	ais->type20.timeout2	= UBITS(86, 3);
	ais->type20.increment2	= UBITS(89, 11);
	ais->type20.offset3		= UBITS(100, 12);
	ais->type20.number3		= UBITS(112, 4);
	ais->type20.timeout3	= UBITS(116, 3);
	ais->type20.increment3	= UBITS(119, 11);
	ais->type20.offset4		= UBITS(130, 12);
	ais->type20.number4		= UBITS(142, 4);
	ais->type20.timeout4	= UBITS(146, 3);
	ais->type20.increment4	= UBITS(149, 11);

}

/* Aid-to-Navigation Report */
void ais_message_21(unsigned char *bits, size_t bitlen, ais_t *ais)
{
	if (bitlen < 272 || bitlen > 360) 
	{
		return;
	}
		
	ais->type21.aid_type = UBITS(38, 5);
	from_sixbit((unsigned char *)bits,43, 20, ais->type21.name);
	ais->type21.accuracy     = UBITS(163, 1);
	ais->type21.lon          = SBITS(164, 28);
	ais->type21.lat          = SBITS(192, 27);
	ais->type21.to_bow       = UBITS(219, 9);
	ais->type21.to_stern     = UBITS(228, 9);
	ais->type21.to_port      = UBITS(237, 6);
	ais->type21.to_starboard = UBITS(243, 6);
	ais->type21.epfd         = UBITS(249, 4);
	ais->type21.second       = UBITS(253, 6);
	ais->type21.off_position = UBITS(259, 1)!=0;
	ais->type21.regional     = UBITS(260, 8);
	ais->type21.raim         = UBITS(268, 1)!=0;
	ais->type21.virtual_aid  = UBITS(269, 1)!=0;
	ais->type21.assigned     = UBITS(270, 1)!=0;
	//ais->type21.spare      = UBITS(271, 1);
	if (strlen(ais->type21.name) == 20 && bitlen > 272)
	    ENDCHARS(272, ais->type21.name + 20);

}

/* Channel Management */
void ais_message_22(unsigned char *bits,  ais_t *ais)
{
	
	ais->type22.channel_a    = UBITS(40, 12);
	ais->type22.channel_b    = UBITS(52, 12);
	ais->type22.txrx         = UBITS(64, 4);
	ais->type22.power        = UBITS(68, 1);
	ais->type22.addressed    = UBITS(139, 1);
	
	if (!ais->type22.addressed) 
	{
	    ais->type22.area.ne_lon     = SBITS(69, 18);
	    ais->type22.area.ne_lat     = SBITS(87, 17);
	    ais->type22.area.sw_lon     = SBITS(104, 18);
	    ais->type22.area.sw_lat     = SBITS(122, 17);
	
	} else {
	
		ais->type22.mmsi.dest1		= UBITS(69, 30);
	    ais->type22.mmsi.dest2		= UBITS(104, 30);
	}
	
	ais->type22.band_a       = UBITS(140, 1);
	ais->type22.band_b       = UBITS(141, 1);
	ais->type22.zonesize     = UBITS(142, 3);
	
}

/* Group Assignment Command */
void ais_message_23(unsigned char *bits,  ais_t *ais)
{
	ais->type23.ne_lon		= SBITS(40, 18);
	ais->type23.ne_lat      = SBITS(58, 17);
	ais->type23.sw_lon      = SBITS(75, 18);
	ais->type23.sw_lat      = SBITS(93, 17);
	ais->type23.stationtype = UBITS(110, 4);
	ais->type23.shiptype    = UBITS(114, 8);
	ais->type23.txrx        = UBITS(144, 4);
	ais->type23.interval    = UBITS(146, 4);
	ais->type23.quiet       = UBITS(150, 4);

}

/* Class B CS Static Data Report */
void ais_message_24(unsigned char *bits, size_t bitlen, ais_t *ais)
{

	switch (UBITS(38, 2)) 
	{
		/* save incoming 24A shipname/MMSI pairs in a circular queue */	
		case 0:
	    {
			//struct ais_type24a_t *saveptr = &type24_queue->ships[type24_queue->index];
			//saveptr->mmsi = ais->mmsi;
			//UCHARS(40, saveptr->shipname);
			//++type24_queue->index;
			//type24_queue->index %= MAX_TYPE24_INTERLEAVE;
	    }
	    //ais->type24.a.spare	= UBITS(160, 8);

	    UCHARS(40, ais->type24.shipname);
//	    ais->type24.part = part_a;
	    return;
		case 1:
	    
			ais->type24.shiptype = UBITS(40, 8);
			/*
			* In ITU-R 1371-4, there are new model and serial fields
			* carved out of the right-hand end of vendorid, which is
			* reduced from 7 chars to 3.  To cope with older AIS
			* implementations conforming to revision 3 and older,
			* unpack the trailing bits *both* ways; truly
			* revision-4-conformant implementations will have up to
			* four characters of trailing garbage on the vendorid,
			* and older implementations will have garbafe in the
			* model and serial fields.
			*/
			UCHARS(48, ais->type24.vendorid);
			ais->type24.model = UBITS(66, 4);
			ais->type24.serial = UBITS(70, 20);
			UCHARS(90, ais->type24.callsign);
			
			if (AIS_AUXILIARY_MMSI(ais->mmsi)) 
			{
				ais->type24.mothership_mmsi   = UBITS(132, 30);
			} else {
				ais->type24.dim.to_bow        = UBITS(132, 9);
				ais->type24.dim.to_stern      = UBITS(141, 9);
				ais->type24.dim.to_port       = UBITS(150, 6);
				ais->type24.dim.to_starboard  = UBITS(156, 6);
			}
			//ais->type24.b.spare	    = UBITS(162, 8);

			/* search the 24A queue for a matching MMSI */
			//for (i = 0; i < MAX_TYPE24_INTERLEAVE; i++) 
			//{
				//if (type24_queue->ships[i].mmsi == ais->mmsi) 
				//{
					//(void)strlcpy(ais->type24.shipname,  type24_queue->ships[i].shipname,  sizeof(type24_queue->ships[i].shipname));
					/* prevent false match if a 24B is repeated */
					//type24_queue->ships[i].mmsi = 0;
					//ais->type24.part = both;
					//return;
				//}
			//}

			/* no match, return Part B */
//			ais->type24.part = part_b;
			return;
	
	default:
	   return;
	}

}

/* Binary Message, Single Slot */
void ais_message_25(unsigned char *bits, size_t bitlen, ais_t *ais)
{

	/* this check and the following one reject line noise */
	if (bitlen < 40 || bitlen > 168) 
	{
	    return;
	}
	
	ais->type25.addressed	= (bool)UBITS(38, 1);
	ais->type25.structured	= (bool)UBITS(39, 1);
	if (bitlen < (unsigned)(40 + (16 * ais->type25.structured) + (30 * ais->type25.addressed)))
	{
		return;
	}
	
	if (ais->type25.addressed)
	    ais->type25.dest_mmsi   = UBITS(40, 30);
	if (ais->type25.structured)
	    ais->type25.app_id      = UBITS(40 + ais->type25.addressed * 30,16);
	/*
	 * Not possible to do this right without machinery we
	 * don't yet have.  The problem is that if the addressed
	 * bit is on, the bitfield start won't be on a byte
	 * boundary. Thus the formulas below (and in message type 26)
	 * will work perfectly for broadcast messages, but for addressed
	 * messages the retrieved data will be led by the 30 bits of
	 * the destination MMSI
	 */
	ais->type25.bitcount       = bitlen - 40 - 16 * ais->type25.structured;
	/* bit 40 is exactly 5 bytes in; 2 bytes is 16 bits */
	(void)memcpy(ais->type25.bitdata, (char *)bits+5 + 2 * ais->type25.structured, (ais->type25.bitcount + 7) / 8);
	
}

void from_sixbit(unsigned char *bitvec, unsigned int start, int count, char *to)
/* beginning at bitvec bit start, unpack count sixbit characters */
{
    /*@ +type @*/
#ifdef S_SPLINT_S
    /* the real string causes a splint internal error */
    const char sixchr[] = "abcd";
#else
    const char sixchr[65] =	"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_ !\"#$%&'()*+,-./0123456789:;<=>?";
#endif /* S_SPLINT_S */
    int i;

    /* six-bit to ASCII */
    for (i = 0; i < count; i++) {
	char newchar;
	newchar = sixchr[ubits(bitvec, start + 6 * i, 6U, false)];
	if (newchar == '@')
	    break;
	else
	    to[i] = newchar;
    }
    to[i] = '\0';
    /* trim spaces on right end */
    for (i = count - 2; i >= 0; i--)
	if (to[i] == ' ' || to[i] == '@')
	    to[i] = '\0';
	else
	    break;
    /*@ -type @*/
}

void to6bit(char *data, size_t *datalen, unsigned char *&bits, size_t *bitlen)
{
	size_t len = (strlen(data));
	int newlen = *datalen + len;
	bits = (unsigned char*)realloc(bits, newlen);
	memset(bits + *datalen , 0, len);
	size_t blen = *bitlen;
	*datalen = newlen;
	
	for (char *cp = data; cp < data + strlen((char *)data); cp++) 
	{
	
		unsigned char ch;
		ch = *cp;
		ch -= 48;
		if (ch >= 40)
			ch -= 8;
		
		for (int i = 5; i >= 0; i--) 
		{
			if((blen / 8) > newlen)
				int a = 0;
			
			char a = (ch >> i);
			if ((ch >> i) & 0x01) 
			{
				int a =	(1 << (7 - blen % 8));
				bits[blen / 8] |= a;
			}
	    
			blen++;
			*bitlen = blen;
		}
	
    }
	
}

float get_beam(unsigned int v)
{
	return (float)(v / 10);
}

float get_length(unsigned int v)
{
	return (float)(v / 10);
}

float get_draught_msg5(unsigned int v)
{
	return (float)(v / 10);
}

float get_draught_msg8(unsigned int v)
{
	return (float)(v / 100);
}

float get_speed(unsigned int v)
{
	return (float)(v * 0.1);
}

float get_cog(unsigned int v)
{
	return (float)(v * 0.1);
}

float get_hdg(unsigned int v)
{
	return (float)(v);
}

float get_lon_lat(int val)
{
	return (float)(val / AIS_LATLON_DIV);
}

wxString get_value_as_string(bool v)
{
	if(v)
		return GetMsg(MSG_TRUE);
	else
		return GetMsg(MSG_FALSE);
}

wxString get_value_as_string(char *v)
{
	wxString str(v,wxConvUTF8);
	return str;
}


wxString get_value_as_string(int v , bool check_na = false, int na_v = -1)
{
	if(check_na)
	{
		if(v == na_v)
			return GetMsg(MSG_NA);
	}
	
	return wxString::Format(_("%d"),v);

}

wxString get_value_as_string(unsigned int v , bool check_na = false, int na_v = -1)
{
	if(check_na)
	{
		if(v == na_v)
			return GetMsg(MSG_NA);
	}
	
	return wxString::Format(_("%d"),v);

}


wxString get_value_as_string(float v , bool check_na = false, int na_v = -1)
{
	if(check_na)
	{
		if(v == na_v)
			return GetMsg(MSG_NA);
	}
	
	return wxString::Format(_("%4.2f"),v);

}

wxString GetHtmlHeader(int type)
{
	wxString msg;
	
	switch(type)
	{
		case AIS_MSG_1: msg = GetMsg(MSG_AIS_1_NAME); break;
		case AIS_MSG_2: msg = GetMsg(MSG_AIS_2_NAME); break;
		case AIS_MSG_3: msg = GetMsg(MSG_AIS_3_NAME); break;
		case AIS_MSG_4: msg = GetMsg(MSG_AIS_4_NAME); break;
		case AIS_MSG_5: msg = GetMsg(MSG_AIS_5_NAME); break;
		case AIS_MSG_6: msg = GetMsg(MSG_AIS_6_NAME); break;
		case AIS_MSG_7: msg = GetMsg(MSG_AIS_7_NAME); break;
		case AIS_MSG_8: msg = GetMsg(MSG_AIS_8_NAME); break;
		case AIS_MSG_9: msg = GetMsg(MSG_AIS_9_NAME); break;
		case AIS_MSG_10: msg = GetMsg(MSG_AIS_10_NAME); break;
		case AIS_MSG_11: msg = GetMsg(MSG_AIS_11_NAME); break;
		case AIS_MSG_12: msg = GetMsg(MSG_AIS_12_NAME); break;
		case AIS_MSG_13: msg = GetMsg(MSG_AIS_13_NAME); break;
		case AIS_MSG_14: msg = GetMsg(MSG_AIS_14_NAME); break;
		case AIS_MSG_15: msg = GetMsg(MSG_AIS_15_NAME); break;
		case AIS_MSG_16: msg = GetMsg(MSG_AIS_16_NAME); break;
		case AIS_MSG_17: msg = GetMsg(MSG_AIS_17_NAME); break;
		case AIS_MSG_18: msg = GetMsg(MSG_AIS_18_NAME); break;
		case AIS_MSG_19: msg = GetMsg(MSG_AIS_19_NAME); break;
		case AIS_MSG_20: msg = GetMsg(MSG_AIS_20_NAME); break;
		case AIS_MSG_21: msg = GetMsg(MSG_AIS_21_NAME); break;
		case AIS_MSG_22: msg = GetMsg(MSG_AIS_22_NAME); break;
		case AIS_MSG_23: msg = GetMsg(MSG_AIS_23_NAME); break;
		case AIS_MSG_24: msg = GetMsg(MSG_AIS_24_NAME); break;
		case AIS_MSG_25: msg = GetMsg(MSG_AIS_25_NAME); break;
		case AIS_MSG_26: msg = GetMsg(MSG_AIS_26_NAME); break;
		case AIS_MSG_27: msg = GetMsg(MSG_AIS_27_NAME); break;
	}

	wxString str;
	str.Append(_("<table border=0 cellpadding=3 cellspacing=0>"));
	str.Append(wxString::Format(_("<tr><td colspan=2><b><a name=\"%d\">[%d] %s</a></b></td></tr>"),type,type,msg.wc_str()));
	
	return str;
}
wxString GetHtmlFooter()
{
	wxString str;
	str.Append(_("</table><br>"));
	return str;
}

wxString PrintHtmlAnchors(ais_t *msg)
{
	wxString str;
	str.Append(_("<table>"));
	
	for(size_t i = 0; i < AIS_MESSAGES_LENGTH;i++)
	{
		if(msg->valid[i])
			str.Append(wxString::Format(_("<tr><td><a href=\"#%d\">%s</a></td></tr>"),i,GetMsg(MSG_AIS_1_NAME + i - 1) ));

	}
	
	str.Append(_("</table>"));
	return str;
	
}

wxString PrintHtmlSimple(ais_t *msg)
{
	wxArrayString ar;
	wxString str;
	
	SAisData ptr;
	ptr.cog = AIS_COURSE_NOT_AVAILABLE;
	ptr.hdg = AIS_HEADING_NOT_AVAILABLE;
	ptr.lon = AIS_LON_NOT_AVAILABLE;
	ptr.lat = AIS_LAT_NOT_AVAILABLE;
	ptr.sog = AIS_SPEED_NOT_AVAILABLE;
	ptr.turn = AIS_TURN_NOT_AVAILABLE;
	ptr.draught = AIS_DRAUGHT_NOT_AVAILABLE;
		
	if(ais_set_name(msg,&ptr))
		ar.Add(get_value_as_string(ptr.name));
	else
		ar.Add(_("N/A"));

	ais_set_mmsi(msg,&ptr);
	ar.Add(get_value_as_string(ptr.mmsi));
	
	ais_mid *mid = ais_get_mid(ptr.mmsi);
	if(mid)
		ar.Add(mid->name);
	else
		ar.Add(_("N/A"));
	
	ais_set_callsign(msg,&ptr);
	ar.Add(get_value_as_string(ptr.callsign));
	
	ais_set_cog(msg,&ptr);
	ar.Add(get_value_as_string(ptr.cog,true,AIS_COURSE_NOT_AVAILABLE));
	
	ais_set_hdg(msg,&ptr);
	ar.Add(get_value_as_string(get_hdg(ptr.hdg),true,AIS_HEADING_NOT_AVAILABLE));
	
	ais_set_sog(msg, &ptr);
	ar.Add(get_value_as_string(ptr.sog,true,AIS_SPEED_NOT_AVAILABLE));

	ais_set_lon_lat(msg, &ptr);
	ar.Add(get_value_as_string(get_lon_lat(ptr.lat*AIS_LATLON_DIV),true,AIS_LAT_NOT_AVAILABLE));
	ar.Add(get_value_as_string(get_lon_lat(ptr.lon*AIS_LATLON_DIV),true,AIS_LON_NOT_AVAILABLE));
		
	ais_set_draught(msg, &ptr);
	ar.Add(get_value_as_string(get_draught_msg5(ptr.draught),true,AIS_DRAUGHT_NOT_AVAILABLE));

	str.Append(_("<table border=0 cellpadding=4 cellspacing=2>"));
	str.Append(wxString::Format(_("<tr><td colspan=2><font size=5><b>%s</b></font></td></tr>"),ar.Item(0)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_MMSI),ar.Item(1)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_FLAG),ar.Item(2)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_CALLSIGN),ar.Item(3)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_COG),ar.Item(4)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_HEADING),ar.Item(5)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_SPEED),ar.Item(6)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_LON),ar.Item(7)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_LAT),ar.Item(8)));
	str.Append(wxString::Format(_("<tr><td><b>%s</b></td><td>%s</td></tr>"),GetMsg(MSG_DRAUGHT),ar.Item(9)));
	str.Append(GetHtmlFooter());	

	return str;
}

wxString PrintHtmlMsg(ais_t *msg, int type)
{
	wxString str;
	wxArrayString ar;
	
	switch(type)
	{
		case AIS_MSG_1:	
		case AIS_MSG_2:	
		case AIS_MSG_3:	ar = PrepareMsg_1(msg->type1); break;
		case AIS_MSG_4:	ar = PrepareMsg_4(msg->type4); break;
		case AIS_MSG_5:	ar = PrepareMsg_5(msg->type5); break;
		
		
		case AIS_MSG_8:	ar = PrepareMsg_8(msg->type8); break;
	}
	
	str.Append(GetHtmlHeader(type));
		
	for(size_t i = 0; i < ar.size(); i+=2)
	{
		str.Append(wxString::Format(_("<tr><td>%s</td><td>%s</td></tr>"),ar.Item(i),ar.Item(i + 1)));
	}
	str.Append(wxString::Format(_("<tr><td><a href='#top'>%s</a></td></tr>"),GetMsg(MSG_GO_TOP)));
	str.Append(GetHtmlFooter());	

	return str;
}

wxArrayString PrepareMsg_1(ais_t::msg1 msg)
{
	wxArrayString ar;
	
	ar.Add(GetMsg(MSG_ACCURACY));			ar.Add(get_value_as_string(msg.accuracy));
	ar.Add(GetMsg(MSG_COG));				ar.Add(get_value_as_string(get_cog(msg.course), true, AIS_COURSE_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_HEADING));			ar.Add(get_value_as_string(msg.heading, true, AIS_HEADING_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_LAT));				ar.Add(get_value_as_string(get_lon_lat(msg.lat),true,AIS_LAT_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_LON));				ar.Add(get_value_as_string(get_lon_lat(msg.lon),true,AIS_LON_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_MANEUVER));			ar.Add(GetManeuverIndicator(msg.maneuver));
	ar.Add(GetMsg(MSG_RADIO));				ar.Add(get_value_as_string(msg.radio));
	ar.Add(GetMsg(MSG_RAIM));				ar.Add(get_value_as_string(msg.raim));
	ar.Add(GetMsg(MSG_SECOND));				ar.Add(get_value_as_string(msg.second,true,AIS_SEC_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_SPEED));				ar.Add(get_value_as_string(get_speed(msg.speed),true,AIS_SPEED_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_NAVIGATION_STATUS));	ar.Add(GetNavigationStatus(msg.status));
	ar.Add(GetMsg(MSG_TURN));				ar.Add(GetTurn(msg.turn));
	

	return ar;
}


wxArrayString PrepareMsg_4(ais_t::msg4 msg)
{
	wxArrayString ar;

	ar.Add(GetMsg(MSG_ACCURACY));	ar.Add(get_value_as_string(msg.accuracy));
	ar.Add(GetMsg(MSG_RAIM));		ar.Add(get_value_as_string(msg.raim));
	ar.Add(GetMsg(MSG_RADIO));		ar.Add(get_value_as_string(msg.radio));
	ar.Add(GetMsg(MSG_YEAR));		ar.Add(get_value_as_string(msg.year,true,AIS_YEAR_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_MONTH));		ar.Add(get_value_as_string(msg.month,true,AIS_MONTH_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_DAY));		ar.Add(get_value_as_string(msg.day,true,AIS_DAY_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_HOUR));		ar.Add(get_value_as_string(msg.hour,true,AIS_HOUR_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_MINUTE));		ar.Add(get_value_as_string(msg.minute,true,AIS_MINUTE_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_SECONDS));	ar.Add(get_value_as_string(msg.second,true,AIS_SECOND_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_LAT));		ar.Add(get_value_as_string(get_lon_lat(msg.lat),true,AIS_LAT_NOT_AVAILABLE).wc_str());
	ar.Add(GetMsg(MSG_LON));		ar.Add(get_value_as_string(get_lon_lat(msg.lon),true,AIS_LON_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_EPFD));		ar.Add(GetEPFDFixTypes(msg.epfd));

	return ar;

}

wxArrayString PrepareMsg_5(ais_t::msg5 msg)
{
	wxArrayString ar;

	ar.Add(GetMsg(MSG_AIS_VERSION));	ar.Add(get_value_as_string(msg.ais_version));
	ar.Add(GetMsg(MSG_CALLSIGN));		ar.Add(get_value_as_string(msg.callsign));
	ar.Add(GetMsg(MSG_SHIPNAME));		ar.Add(get_value_as_string(msg.shipname));
	ar.Add(GetMsg(MSG_ETA_MONTH));		ar.Add(get_value_as_string(msg.month,true,AIS_MONTH_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_ETA_DAY));		ar.Add(get_value_as_string(msg.day,true,AIS_DAY_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_ETA_HOUR));		ar.Add(get_value_as_string(msg.hour,true,AIS_HOUR_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_ETA_MINUTE));		ar.Add(get_value_as_string(msg.minute,true,AIS_MINUTE_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_IMO_NUMBER));		ar.Add(get_value_as_string(msg.imo));
	ar.Add(GetMsg(MSG_DESTINATION));	ar.Add(get_value_as_string(msg.destination));
	ar.Add(GetMsg(MSG_SHIP_TYPE));		ar.Add(GetShipType(msg.shiptype));
	ar.Add(GetMsg(MSG_TO_BOW));			ar.Add(get_value_as_string(msg.to_bow));
	ar.Add(GetMsg(MSG_TO_STERN));		ar.Add(get_value_as_string(msg.to_stern));
	ar.Add(GetMsg(MSG_TO_PORT));		ar.Add(get_value_as_string(msg.to_port));
	ar.Add(GetMsg(MSG_TO_STARBOARD));	ar.Add(get_value_as_string(msg.to_starboard));
	ar.Add(GetMsg(MSG_LENGTH_WIDTH));	ar.Add(wxString::Format(_("%sx%s m"), get_value_as_string(msg.to_bow + msg.to_stern), get_value_as_string(msg.to_port + msg.to_starboard)) );
	ar.Add(GetMsg(MSG_DRAUGHT));		ar.Add(get_value_as_string(get_draught_msg5(msg.draught),true,AIS_DRAUGHT_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_DTE));			ar.Add(GetDTE(msg.dte));
	ar.Add(GetMsg(MSG_EPFD));			ar.Add(GetEPFDFixTypes(msg.epfd));
		
	return ar;

}

wxArrayString PrepareMsg_8(ais_t::msg8 msg)
{
	wxArrayString ar;
	ar.Add(GetMsg(MSG_DAC));	ar.Add(get_value_as_string(msg.dac));
	ar.Add(GetMsg(MSG_FID));	ar.Add(get_value_as_string(msg.fid));
	
	if(msg.dac == 1)
	{
		switch(msg.fid)
		{
	
			case 11: ar = PrepareMsg_8_1_11(msg.dac1fid11);	break;
			case 13: break;
			case 15: break;
			case 16: break;
			case 17: break;
			case 19: break;
			case 27: break;
			case 29: break;
			case 31: break;
		}
	}

	if(msg.dac == 200)
	{
		switch(msg.fid)
		{
			case 10: ar = PrepareMsg_8_200_10(msg.dac200fid10);	break;
			case 23: break;
			case 24: break;
			case 40: break; 
		}
	
	}

	return ar;
}

wxArrayString PrepareMsg_8_1_11(ais_t::msg8::msg8_1_11 msg)
{
	wxArrayString ar;
		
	ar.Add(GetMsg(MSG_LON));						ar.Add(get_value_as_string(get_lon_lat(msg.lon),true,DAC1FID11_LON_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_LAT));						ar.Add(get_value_as_string(get_lon_lat(msg.lat),true,DAC1FID11_LAT_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_DAY));						ar.Add(get_value_as_string(msg.day,true,AIS_DAY_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_HOUR));						ar.Add(get_value_as_string(msg.hour,true,AIS_HOUR_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_MINUTE));						ar.Add(get_value_as_string(msg.minute,true,AIS_MINUTE_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_AVERAGE_WIND_SPEED));			ar.Add(get_value_as_string(msg.wspeed,true,DAC1FID11_WSPEED_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_GUST_SPEED));					ar.Add(get_value_as_string(msg.wgust,true,DAC1FID11_WSPEED_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_WIND_DIR));					ar.Add(get_value_as_string(msg.wdir,true,DAC1FID11_WDIR_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_WIND_GUST_DIR));				ar.Add(get_value_as_string(msg.wgustdir,true,DAC1FID11_WDIR_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_AIR_TMP));					ar.Add(get_value_as_string(msg.airtemp,true,DAC1FID11_AIRTEMP_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_HUMIDITY));					ar.Add(get_value_as_string(msg.humidity,true,DAC1FID11_HUMIDITY_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_DEWPOINT));					ar.Add(get_value_as_string(msg.dewpoint,true,DAC1FID11_DEWPOINT_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_PRESSURE));					ar.Add(get_value_as_string(msg.pressure,true,DAC1FID11_PRESSURE_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_PRESSURE_TENDENCY));			ar.Add(get_value_as_string(msg.pressuretend,true,DAC1FID11_PRESSURETREND_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_H_VISIBILTY));				ar.Add(get_value_as_string(msg.visibility,true,DAC1FID11_VISIBILITY_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_WATER_LEVEL));				ar.Add(get_value_as_string(msg.waterlevel,true,DAC1FID11_WATERLEVEL_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_WATER_LEVEL_TREND));			ar.Add(get_value_as_string(msg.leveltrend,true,DAC1FID11_WATERLEVELTREND_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_SURFACE_CURRENT_SPEED));		ar.Add(get_value_as_string(msg.cspeed,true,DAC1FID11_CSPEED_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_SURFACE_CURRENT_DIRECTION));	ar.Add(get_value_as_string(msg.cdir,true,DAC1FID11_CDIR_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_SURFACE_CURRENT_SPEED));		ar.Add(get_value_as_string(msg.cspeed2,true,DAC1FID11_CSPEED_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_WAVE_HEIGHT));				ar.Add(get_value_as_string(msg.waveheight,true,DAC1FID11_WAVEHEIGHT_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_WAVE_PERIOD));				ar.Add(get_value_as_string(msg.waveperiod,true,DAC1FID11_WAVEPERIOD_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_WAVE_DIR));					ar.Add(get_value_as_string(msg.wavedir,true,DAC1FID11_WAVEDIR_NOT_AVAILABLE));

	return ar;
}

wxArrayString PrepareMsg_8_200_10(ais_t::msg8::msg8_200_10 msg)
{
	wxArrayString ar;

	ar.Add(GetMsg(MSG_VIN));					ar.Add(get_value_as_string(msg.vin));
	ar.Add(GetMsg(MSG_LENGTH));					ar.Add(get_value_as_string(get_length(msg.length),true,DAC200FID10_LENGTH_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_BEAM));					ar.Add(get_value_as_string(get_beam(msg.beam),true,DAC200FID10_BEAM_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_TYPE));					ar.Add(get_value_as_string(msg.type));
	ar.Add(GetMsg(MSG_HAZARD));					ar.Add(GetHazardousCargo(msg.hazard));
	ar.Add(GetMsg(MSG_DRAUGHT));				ar.Add(get_value_as_string(get_draught_msg8(msg.draught),true,DAC200FID10_DRAUGHT_NOT_AVAILABLE));
	ar.Add(GetMsg(MSG_LOADED_UNLOADED));		ar.Add(GetLoaded(msg.loaded));
	ar.Add(GetMsg(MSG_SPEED_INF_QUALITY));		ar.Add(GetSpeedQuality(msg.speed_q));
	ar.Add(GetMsg(MSG_COURSE_INF_QUALITY));		ar.Add(GetCourseQuality(msg.course_q));
	ar.Add(GetMsg(MSG_HEADING_INF_QUALITY));	ar.Add(GetHeadingQuality(msg.course_q));

	return ar;

}


wxArrayString PrepareMsg_21(ais_t::msg21 msg)
{
	wxArrayString ar;

	//ar.Add(GetMsg(MSG_ACCURACY));	ar.Add(get_value_as_string(msg.accuracy));
	//ar.Add(GetMsg(MSG_RAIM));		ar.Add(get_value_as_string(msg.raim));
	//ar.Add(GetMsg(MSG_RADIO));		ar.Add(get_value_as_string(msg.radio));
	//ar.Add(GetMsg(MSG_YEAR));		ar.Add(get_value_as_string(msg.year,true,AIS_YEAR_NOT_AVAILABLE));
	//ar.Add(GetMsg(MSG_MONTH));		ar.Add(get_value_as_string(msg.month,true,AIS_MONTH_NOT_AVAILABLE));
	//ar.Add(GetMsg(MSG_DAY));		ar.Add(get_value_as_string(msg.day,true,AIS_DAY_NOT_AVAILABLE));
	//ar.Add(GetMsg(MSG_HOUR));		ar.Add(get_value_as_string(msg.hour,true,AIS_HOUR_NOT_AVAILABLE));
	//ar.Add(GetMsg(MSG_MINUTE));		ar.Add(get_value_as_string(msg.minute,true,AIS_MINUTE_NOT_AVAILABLE));
	//ar.Add(GetMsg(MSG_SECONDS));	ar.Add(get_value_as_string(msg.second,true,AIS_SECOND_NOT_AVAILABLE));
	//ar.Add(GetMsg(MSG_LAT));		ar.Add(get_value_as_string(get_lon_lat(msg.lat),true,AIS_LAT_NOT_AVAILABLE).wc_str());
	//ar.Add(GetMsg(MSG_LON));		ar.Add(get_value_as_string(get_lon_lat(msg.lon),true,AIS_LON_NOT_AVAILABLE));
	//ar.Add(GetMsg(MSG_EPFD));		ar.Add(GetEPFDFixTypes(msg.epfd));

	return ar;

}


const wchar_t *GetTurn(int v)
{
	switch(v)
	{	
		case AIS_TURN_HARD_LEFT:		return GetMsg(MSG_TURN_HARD_LEFT);		
		case AIS_TURN_HARD_RIGHT:		return GetMsg(MSG_TURN_HARD_RIGHT);		
		case AIS_TURN_LEFT:				return GetMsg(MSG_TURN_LEFT);			
		case AIS_TURN_RIGHT:			return GetMsg(MSG_TURN_RIGHT);			
		case AIS_TURN_NOT_AVAILABLE:	return GetMsg(MSG_NA);					
		default:						return GetMsg(MSG_NA);
	}

}


const wchar_t *GetHazardousCargo(int id)
{
	return nvHazardousCargo[GetLanguageId()][id];
}

const wchar_t *GetSpeedQuality(int id)
{
	return nvSpeedQuality[GetLanguageId()][id];
}

const wchar_t *GetHeadingQuality(int id)
{
	return nvHeadingQuality[GetLanguageId()][id];
}

const wchar_t *GetCourseQuality(int id)
{
	return nvCourseQuality[GetLanguageId()][id];
}

const wchar_t *GetLoaded(int id)
{
	return nvLoaded[GetLanguageId()][id];
}

const wchar_t *GetDTE(int id)
{
	return nvDTE[GetLanguageId()][id];
}

const wchar_t *GetShipType(int id)
{
	return nvShipTypes[GetLanguageId()][id];
}

const wchar_t *GetEPFDFixTypes(int id)
{
	return nvEPFDFixTypes[GetLanguageId()][id];
}

const wchar_t *GetNavigationStatus(int id)
{
	return nvNavigationStatus[GetLanguageId()][id];
}

const wchar_t *GetManeuverIndicator(int id)
{
	return nvManeuverIndicator[GetLanguageId()][id];
}