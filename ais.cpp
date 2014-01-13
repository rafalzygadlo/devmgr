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
		case AIS_MSG_3:		ais_message_1(bits,ais); break;
		
		case AIS_MSG_4:		
		case AIS_MSG_11:	ais_message_4(bits,ais); break;
		
		case AIS_MSG_5:		ais_message_5(bits,bitlen,ais); break;

		case AIS_MSG_6:		printf("6\n");					break;
		case AIS_MSG_7:		printf("7\n");					break;
		case AIS_MSG_8:		printf("8\n");					break;
		case AIS_MSG_9:		printf("9\n");					break;
		case AIS_MSG_10:	printf("10\n"); break;
		case AIS_MSG_12:	printf("12\n"); break;
		case AIS_MSG_13:	printf("13\n"); break;
		case AIS_MSG_14:	printf("14\n"); break;
		case AIS_MSG_15:	printf("15\n"); break;
		case AIS_MSG_16:	printf("16\n"); break;
		case AIS_MSG_17:	printf("17\n"); break;
		case AIS_MSG_18:	printf("18\n"); break;
		case AIS_MSG_19:	printf("19\n"); break;
		case AIS_MSG_20:	printf("20\n"); break;
		case AIS_MSG_21:	printf("21\n"); break;
		case AIS_MSG_22:	printf("22\n"); break;
		case AIS_MSG_23:	printf("23\n"); break;
		case AIS_MSG_24:	printf("24\n"); break;
		case AIS_MSG_25:	printf("25\n"); break;
		case AIS_MSG_26:	printf("26\n"); break;
		case AIS_MSG_27:	printf("27\n"); break;

	}

	vAis.push_back(ais);

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

void to6bit(char *data, unsigned char *&bits, size_t *length)
{
	//size_t len = (strlen(data) * 6) / 8;
	size_t len = (strlen(data));

	bits = (unsigned char*)malloc(len);
	memset(bits,0,len);
	size_t bitlen = 0;

	for (char *cp = data; cp < data + strlen((char *)data); cp++) 
	{
	
	unsigned char ch;
	ch = *cp;
	ch -= 48;
	if (ch >= 40)
	    ch -= 8;
	
	for (int i = 5; i >= 0; i--) 
	{
		char a = (ch >> i);
	    if ((ch >> i) & 0x01) 
		{
			bits[bitlen / 8] |= (1 << (7 - bitlen % 8));
	    }
	    
		*length = bitlen++;
	    //if (bitlen > sizeof(bits)) 
		//{
			//gpsd_report(session->context->debug, LOG_INF,"overlong AIVDM payload truncated.\n");
			//int a = 0;
			//return false;
	    //}
	}
	/*@ +shiftnegative @*/
    }
	
	
}
