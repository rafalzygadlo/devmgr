#include "ais.h"
#include <stdio.h>

std::vector <ais_t*> vAis;

ais_t *ais_msg_exists(int mmsi)
{
	for(size_t  i = 0; i < vAis.size(); i++)
	{
		ais_t *ais = vAis[i];
		if(ais->mmsi == mmsi)
			return ais;
	}

	return NULL;

}

int ais_binary_decode(unsigned char *bits, size_t bitlen)
{
	ais_t *ais;
	int mmsi;
	mmsi = UBITS(8, 30);
	bool add = false;

	ais = ais_msg_exists(mmsi);
	
	if(!ais)
	{	
		ais = (ais_t*)malloc(sizeof(ais_t));
		memset(ais,0,sizeof(ais_t));
		add = true;
	}
    
	uint64_t type =	UBITS(0, 6);
	ais->mmsi = UBITS(8, 30);
    ais->repeat = UBITS(6, 2);

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
	

	}

	vAis.push_back(ais); // wyciek jak morze ba³tyckie

	return type;
	
}
/* Position Report */
void ais_message_1(unsigned char *bits, ais_t *ais)
{
	
	ais->type1.status = UBITS(38, 4);
	ais->type1.turn = SBITS(42, 8);
	ais->type1.speed = UBITS(50, 10);
	ais->type1.accuracy	= UBITS(60, 1)!=0;
	ais->type1.lon = SBITS(61, 28);
	ais->type1.lat = SBITS(89, 27);
	ais->type1.course = UBITS(116, 12);
	ais->type1.heading = UBITS(128, 9);
	ais->type1.second = UBITS(137, 6);
	ais->type1.maneuver	= UBITS(143, 2);
	//ais->type1.spare	= UBITS(145, 3);
	ais->type1.raim = UBITS(148, 1)!=0;
	ais->type1.radio = UBITS(149, 19);
		
}

/* Base Station Report */
/* UTC/Date Response */
/* 4,11 */
void ais_message_4(unsigned char *bits, ais_t *ais)
{
	 
	//PERMISSIVE_LENGTH_CHECK(168)
		
	ais->type4.year		= UBITS(38, 14);
	ais->type4.month	= UBITS(52, 4);
	ais->type4.day		= UBITS(56, 5);
	ais->type4.hour		= UBITS(61, 5);
	ais->type4.minute	= UBITS(66, 6);
	ais->type4.second	= UBITS(72, 6);
	ais->type4.accuracy	= UBITS(78, 1)!=0;
	ais->type4.lon		= SBITS(79, 28);
	ais->type4.lat		= SBITS(107, 27);
	ais->type4.epfd		= UBITS(134, 4);
	//ais->type4.spare	= UBITS(138, 10);
	ais->type4.raim		= UBITS(148, 1)!=0;
	ais->type4.radio	= UBITS(149, 19);

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
	
	ais->type5.ais_version  = UBITS(38, 2);
	ais->type5.imo          = UBITS(40, 30);
	UCHARS(70, ais->type5.callsign);
	UCHARS(112, ais->type5.shipname);
	ais->type5.shiptype     = UBITS(232, 8);
	ais->type5.to_bow       = UBITS(240, 9);
	ais->type5.to_stern     = UBITS(249, 9);
	ais->type5.to_port      = UBITS(258, 6);
	ais->type5.to_starboard = UBITS(264, 6);
	ais->type5.epfd         = UBITS(270, 4);
	ais->type5.month        = UBITS(274, 4);
	ais->type5.day          = UBITS(278, 5);
	ais->type5.hour         = UBITS(283, 5);
	ais->type5.minute       = UBITS(288, 6);
	ais->type5.draught      = UBITS(294, 8);
	UCHARS(302, ais->type5.destination);
	if (bitlen >= 423)
	    ais->type5.dte          = UBITS(422, 1);
	//ais->type5.spare        = UBITS(423, 1);

}

/* Addressed Binary Message */
void ais_message_6(unsigned char *bits, size_t bitlen, ais_t *ais)
{

	if (bitlen < 88 || bitlen > 1008) 
	{
	    return;
	}
	ais->type6.seqno          = UBITS(38, 2);
	ais->type6.dest_mmsi      = UBITS(40, 30);
	ais->type6.retransmit     = UBITS(70, 1)!=0;
	//ais->type6.spare        = UBITS(71, 1);
	ais->type6.dac            = UBITS(72, 10);
	ais->type6.fid            = UBITS(82, 6);
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
				ais->type6.dac200fid21.month	= UBITS(208, 4);
				ais->type6.dac200fid21.day	= UBITS(212, 5);
				ais->type6.dac200fid21.hour	= UBITS(217, 5);
				ais->type6.dac200fid21.minute	= UBITS(222, 6);
				ais->type6.dac200fid21.tugs	= UBITS(228, 3);
				ais->type6.dac200fid21.airdraught	= UBITS(231, 12);
				/* skip 5 bits */
			break;
			case 22:	/* RTA at lock/bridge/terminal */
				UCHARS(88, ais->type6.dac200fid22.country);
				UCHARS(100, ais->type6.dac200fid22.locode);
				UCHARS(118, ais->type6.dac200fid22.section);
				UCHARS(148, ais->type6.dac200fid22.terminal);
				UCHARS(178, ais->type6.dac200fid22.hectometre);
				ais->type6.dac200fid22.month	= UBITS(208, 4);
				ais->type6.dac200fid22.day	= UBITS(212, 5);
				ais->type6.dac200fid22.hour	= UBITS(217, 5);
				ais->type6.dac200fid22.minute	= UBITS(222, 6);
				ais->type6.dac200fid22.status	= UBITS(228, 2);
				/* skip 2 bits */
			break;
			case 55:	/* Number of Persons On Board */
				ais->type6.dac200fid55.crew	= UBITS(88, 8);
				ais->type6.dac200fid55.passengers	= UBITS(96, 13);
				ais->type6.dac200fid55.personnel	= UBITS(109, 8);
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
				ais->type6.dac235fid10.ana_int	= UBITS(88, 10);
				ais->type6.dac235fid10.ana_ext1	= UBITS(98, 10);
				ais->type6.dac235fid10.ana_ext2	= UBITS(108, 10);
				ais->type6.dac235fid10.racon    = UBITS(118, 2);
				ais->type6.dac235fid10.light    = UBITS(120, 2);
				ais->type6.dac235fid10.alarm    = UBITS(122, 1);
				ais->type6.dac235fid10.stat_ext	= UBITS(123, 8);
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
				ais->type6.dac1fid12.lmonth		= UBITS(118, 4);
				ais->type6.dac1fid12.lday		= UBITS(122, 5);
				ais->type6.dac1fid12.lhour		= UBITS(127, 5);
				ais->type6.dac1fid12.lminute	= UBITS(132, 6);
				UCHARS(138, ais->type6.dac1fid12.nextport);
				ais->type6.dac1fid12.nmonth		= UBITS(168, 4);
				ais->type6.dac1fid12.nday		= UBITS(172, 5);
				ais->type6.dac1fid12.nhour		= UBITS(177, 5);
				ais->type6.dac1fid12.nminute	= UBITS(182, 6);
				UCHARS(188, ais->type6.dac1fid12.dangerous);
				UCHARS(308, ais->type6.dac1fid12.imdcat);
				ais->type6.dac1fid12.unid		= UBITS(332, 13);
				ais->type6.dac1fid12.amount		= UBITS(345, 10);
				ais->type6.dac1fid12.unit		= UBITS(355, 2);
				/* skip 3 bits */
			break;

			case 14:	/* IMO236 - Tidal Window */
				ais->type6.dac1fid32.month	= UBITS(88, 4);
				ais->type6.dac1fid32.day	= UBITS(92, 5);
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
	
	for (u = 0; u < sizeof(mmsi)/sizeof(mmsi[0]); u++)
	    if (bitlen > 40 + 32*u)
			mmsi[u] = UBITS(40 + 32*u, 30);
	    else
			mmsi[u] = 0;
	
	ais->type7.mmsi1 = mmsi[0];
	ais->type7.mmsi2 = mmsi[1];
	ais->type7.mmsi3 = mmsi[2];
	ais->type7.mmsi4 = mmsi[3];
	
	break;
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