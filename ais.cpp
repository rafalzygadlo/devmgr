#include "ais.h"
#include <stdio.h>

std::vector <ais_t*> vAist;
std::vector <ais_p*> vAisp;

void prepare_render_list(ais_t *aist, ais_p *aisp)
{
	//ais_p *list = (ais_p*)malloc(sizeof(ais_p)); 
		
	if(aist->type1.valid)
	{
		aisp->lat = aist->type1.lat;
		aisp->lat = aist->type1.lat;
		return;
	}
	
	if(aist->type4.valid)
	{
		aisp->lat = aist->type4.lat;
		aisp->lat = aist->type4.lat;
		return;
	}
		
}

ais_p *ais_pos_exists(int idx)
{
	if(vAisp.size() > idx)
		return vAisp[idx];
	else
		return NULL;
}


ais_t *ais_msg_exists(int mmsi)
{
	for(size_t  i = 0; i < vAisp.size(); i++)
	{
		ais_t *ais = vAist[i];
		if(ais->mmsi == mmsi)
			return ais;
	}

	return NULL;

}

int ais_binary_decode(unsigned char *bits, size_t bitlen)
{
	ais_t *ais;
	int mmsi;
	mmsi = (int)UBITS(8, 30);
	bool add = false;
	
	// mutex jest potrzebny
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

	switch(type)
	{
		case AIS_MSG_1:		
		case AIS_MSG_2:		
		case AIS_MSG_3:
			ais_message_1(bits,ais);		
		break;
		
		case AIS_MSG_4:		
		case AIS_MSG_11:	
			ais_message_4(bits,ais);		
		break;
		
		case AIS_MSG_5:		
			ais_message_5(bits,bitlen,ais); 
		break;
		
		case AIS_MSG_6:		
			ais_message_6(bits,bitlen,ais);	
		break;
		
		case AIS_MSG_13:
		case AIS_MSG_7:	
			ais_message_7(bits,bitlen,ais);	
		break;

		case AIS_MSG_8:
			ais_message_8(bits,bitlen,ais);
		break;
	

	}

	// mutex jest potrzebny
	if(add)
		vAist.push_back(ais); // wyciek jak morze ba³tyckie

	//ais_pos_exists(
	//prepare_render_list(ais,);
	
	return type;
	
}
/* Position Report */
void ais_message_1(unsigned char *bits, ais_t *ais)
{
	ais->type1.valid = true;
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
	ais->type4.valid = true;	
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
	
	ais->type5.valid = true;
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
	
	ais->type6.valid = true;
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
				ais->type6.dac235fid10.alarm    = UBITS(122, 1);
				ais->type6.dac235fid10.stat_ext	= (int)UBITS(123, 8);
				ais->type6.dac235fid10.off_pos  = UBITS(131, 1);
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
		/*
		for (int u = 0; ARRAY_BASE + (ELEMENT_SIZE*u) <= bitlen; u++) 
		{
		    int a = ARRAY_BASE + (ELEMENT_SIZE*u);
			struct tidal_t *tp = ais->type6.dac1fid32.tidals[u];
		    tp->lat	= SBITS(a + 0, 27);
		    tp->lon	= SBITS(a + 27, 28);
		    tp->from_hour	= UBITS(a + 55, 5);
		    tp->from_min	= UBITS(a + 60, 6);
		    tp->to_hour	= UBITS(a + 66, 5);
		    tp->to_min	= UBITS(a + 71, 6);
		    tp->cdir	= UBITS(a + 77, 9);
		    tp->cspeed	= UBITS(a + 86, 7);
		}
		ais->type6.dac1fid32.ntidals = u;
		*/
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
	
	ais->type7.valid = true;
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
	
	ais->type8.valid = true;
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
				ais->type8.dac1fid13.radius 	= UBITS(416, 10);
				ais->type8.dac1fid13.extunit	= UBITS(426, 2);
				ais->type8.dac1fid13.fday   	= UBITS(428, 5);
				ais->type8.dac1fid13.fmonth 	= UBITS(433, 4);
				ais->type8.dac1fid13.fhour  	= UBITS(437, 5);
				ais->type8.dac1fid13.fminute	= UBITS(442, 6);
				ais->type8.dac1fid13.tday   	= UBITS(448, 5);
				ais->type8.dac1fid13.tmonth 	= UBITS(453, 4);
				ais->type8.dac1fid13.thour  	= UBITS(457, 5);
				ais->type8.dac1fid13.tminute	= UBITS(462, 6);
				/* skip 4 bits */
				structured = true;
			break;
	    
			case 15:        /* IMO236 - Extended ship and voyage */
				ais->type8.dac1fid15.airdraught	= UBITS(56, 11);
				/* skip 5 bits */
				structured = true;
			break;
	    
			case 16:	    /* Number of Persons On Board */
				if (ais->type8.bitcount == 136)
					ais->type8.dac1fid16.persons = UBITS(88, 13);/* 289 */
				else
					ais->type8.dac1fid16.persons = UBITS(55, 13);/* 236 */
				structured = true;
			break;
	    
			case 17:        /* IMO289 - VTS-generated/synthetic targets */
#define ARRAY_BASE 56
#define ELEMENT_SIZE 122
				for (u = 0; ARRAY_BASE + (ELEMENT_SIZE*u) <= bitlen; u++) 
				{
					//target_t tp = ais->type8.dac1fid17.targets[u].id;
					int a = ARRAY_BASE + (ELEMENT_SIZE*u);
					ais->type8.dac1fid17.targets[u].idtype = UBITS(a + 0, 2);
					switch (ais->type8.dac1fid17.targets[u].idtype) 
					{
						case DAC1FID17_IDTYPE_MMSI:
							ais->type8.dac1fid17.targets[u].id.mmsi	= UBITS(a + 2, 42);
						break;
						case DAC1FID17_IDTYPE_IMO:
							ais->type8.dac1fid17.targets[u].id.imo	= UBITS(a + 2, 42);
						break;
						case DAC1FID17_IDTYPE_CALLSIGN:
							UCHARS(a+2, ais->type8.dac1fid17.targets[u].id.callsign);
						break;
						default:
							UCHARS(a+2, ais->type8.dac1fid17.targets[u].id.other);
						break;
					}
					
					/* skip 4 bits */
					ais->type8.dac1fid17.targets[u].lat	= SBITS(a + 48, 24);
					ais->type8.dac1fid17.targets[u].lon	= SBITS(a + 72, 25);
					ais->type8.dac1fid17.targets[u].course	= UBITS(a + 97, 9);
					ais->type8.dac1fid17.targets[u].second	= UBITS(a + 106, 6);
					ais->type8.dac1fid17.targets[u].speed	= UBITS(a + 112, 10);
				}
		ais->type8.dac1fid17.ntargets = u;
#undef ARRAY_BASE
#undef ELEMENT_SIZE
		structured = true;
		break;
	    
			case 19:        /* IMO289 - Marine Traffic Signal */
				ais->type8.dac1fid19.linkage	= UBITS(56, 10);
				UCHARS(66, ais->type8.dac1fid19.station);
				ais->type8.dac1fid19.lon	= SBITS(186, 25);
				ais->type8.dac1fid19.lat	= SBITS(211, 24);
				ais->type8.dac1fid19.status	= UBITS(235, 2);
				ais->type8.dac1fid19.signal	= UBITS(237, 5);
				ais->type8.dac1fid19.hour	= UBITS(242, 5);
				ais->type8.dac1fid19.minute	= UBITS(247, 6);
				ais->type8.dac1fid19.nextsignal	= UBITS(253, 5);
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
				ais->type8.dac1fid27.linkage	= UBITS(56, 10);
				ais->type8.dac1fid27.sender	= UBITS(66, 3);
				ais->type8.dac1fid27.rtype	= UBITS(69, 5);
				ais->type8.dac1fid27.month	= UBITS(74, 4);
				ais->type8.dac1fid27.day	= UBITS(78, 5);
				ais->type8.dac1fid27.hour	= UBITS(83, 5);
				ais->type8.dac1fid27.minute	= UBITS(88, 6);
				ais->type8.dac1fid27.duration	= UBITS(94, 18);
				ais->type8.dac1fid27.waycount	= UBITS(112, 5);
#define ARRAY_BASE 117
#define ELEMENT_SIZE 55
				for (i = 0; i < ais->type8.dac1fid27.waycount; i++) 
				{
					int a = ARRAY_BASE + (ELEMENT_SIZE*i);
					ais->type8.dac1fid27.waypoints[i].lon	= SBITS(a + 0, 28);
					ais->type8.dac1fid27.waypoints[i].lat	= SBITS(a + 28, 27);
				}
#undef ARRAY_BASE
#undef ELEMENT_SIZE
				structured = true;
			break;
	    
			case 29:        /* IMO289 - Text Description - broadcast */
				ais->type8.dac1fid29.linkage   = UBITS(56, 10);
				ENDCHARS(66, ais->type8.dac1fid29.text);
				structured = true;
			break;
	    
			case 31:        /* IMO289 - Meteorological/Hydrological data */
				ais->type8.dac1fid31.lon		= SBITS(56, 25);
				ais->type8.dac1fid31.lat		= SBITS(81, 24);
				ais->type8.dac1fid31.accuracy       = (bool)UBITS(105, 1);
				ais->type8.dac1fid31.day		= UBITS(106, 5);
				ais->type8.dac1fid31.hour		= UBITS(111, 5);
				ais->type8.dac1fid31.minute		= UBITS(116, 6);
				ais->type8.dac1fid31.wspeed		= UBITS(122, 7);
				ais->type8.dac1fid31.wgust		= UBITS(129, 7);
				ais->type8.dac1fid31.wdir		= UBITS(136, 9);
				ais->type8.dac1fid31.wgustdir	= UBITS(145, 9);
				ais->type8.dac1fid31.airtemp	= SBITS(154, 11);
				ais->type8.dac1fid31.humidity	= UBITS(165, 7);
				ais->type8.dac1fid31.dewpoint	= SBITS(172, 10);
				ais->type8.dac1fid31.pressure	= UBITS(182, 9);
				ais->type8.dac1fid31.pressuretend	= UBITS(191, 2);
				ais->type8.dac1fid31.visgreater	= UBITS(193, 1);
				ais->type8.dac1fid31.visibility	= UBITS(194, 7);
				ais->type8.dac1fid31.waterlevel	= UBITS(201, 12);
				ais->type8.dac1fid31.leveltrend	= UBITS(213, 2);
				ais->type8.dac1fid31.cspeed		= UBITS(215, 8);
				ais->type8.dac1fid31.cdir		= UBITS(223, 9);
				ais->type8.dac1fid31.cspeed2	= UBITS(232, 8);
				ais->type8.dac1fid31.cdir2		= UBITS(240, 9);
				ais->type8.dac1fid31.cdepth2	= UBITS(249, 5);
				ais->type8.dac1fid31.cspeed3	= UBITS(254, 8);
				ais->type8.dac1fid31.cdir3		= UBITS(262, 9);
				ais->type8.dac1fid31.cdepth3	= UBITS(271, 5);
				ais->type8.dac1fid31.waveheight	= UBITS(276, 8);
				ais->type8.dac1fid31.waveperiod	= UBITS(284, 6);
				ais->type8.dac1fid31.wavedir	= UBITS(290, 9);
				ais->type8.dac1fid31.swellheight	= UBITS(299, 8);
				ais->type8.dac1fid31.swellperiod	= UBITS(307, 6);
				ais->type8.dac1fid31.swelldir	= UBITS(313, 9);
				ais->type8.dac1fid31.seastate	= UBITS(322, 4);
				ais->type8.dac1fid31.watertemp	= SBITS(326, 10);
				ais->type8.dac1fid31.preciptype	= UBITS(336, 3);
				ais->type8.dac1fid31.salinity	= UBITS(339, 9);
				ais->type8.dac1fid31.ice		= UBITS(348, 2);
				structured = true;
			break;
		}
	 
	if (ais->type8.dac == 200) 
	{
	    switch (ais->type8.fid) 
		{
			case 21:	/* Inland ship static and voyage related data */
				UCHARS(56, ais->type8.dac200fid10.vin);
				ais->type8.dac200fid10.length	= UBITS(104, 13);
				ais->type8.dac200fid10.beam	= UBITS(117, 10);
				ais->type8.dac200fid10.type	= UBITS(127, 14);
				ais->type8.dac200fid10.hazard	= UBITS(141, 3);
				ais->type8.dac200fid10.draught	= UBITS(144, 11);
				ais->type8.dac200fid10.loaded	= UBITS(155, 2);
				ais->type8.dac200fid10.speed_q	= (bool)UBITS(157, 1);
				ais->type8.dac200fid10.course_q	= (bool)UBITS(158, 1);
				ais->type8.dac200fid10.heading_q	= (bool)UBITS(159, 1);
				/* skip 8 bits */
				structured = true;
			break;
	    
			case 23:
				ais->type8.dac200fid23.start_year	= UBITS(56, 8);
				ais->type8.dac200fid23.start_month	= UBITS(64, 4);
				ais->type8.dac200fid23.start_day	= UBITS(68, 5);
				ais->type8.dac200fid23.end_year	= UBITS(73, 8);
				ais->type8.dac200fid23.end_month	= UBITS(81, 4);
				ais->type8.dac200fid23.end_day	= UBITS(85, 5);
				ais->type8.dac200fid23.start_hour	= UBITS(90, 5);
				ais->type8.dac200fid23.start_minute	= UBITS(95, 6);
				ais->type8.dac200fid23.end_hour	= UBITS(101, 5);
				ais->type8.dac200fid23.end_minute	= UBITS(106, 6);
				ais->type8.dac200fid23.start_lon	= SBITS(112, 28);
				ais->type8.dac200fid23.start_lat	= SBITS(140, 27);
				ais->type8.dac200fid23.end_lon	= SBITS(167, 28);
				ais->type8.dac200fid23.end_lat	= SBITS(195, 27);
				ais->type8.dac200fid23.type	= UBITS(222, 4);
				ais->type8.dac200fid23.min	= SBITS(226, 9);
				ais->type8.dac200fid23.max	= SBITS(235, 9);
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
	    (void)memcpy(ais->type8.bitdata,
			 (char *)bits + (56 / BITS_PER_BYTE),
			 (ais->type8.bitcount + 7) / 8);

}

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