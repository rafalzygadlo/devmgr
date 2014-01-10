#include "ais.h"
#include <stdio.h>

unsigned char bits[48] = {};
void ais_binary_decode(unsigned char *bits, size_t bitlen)
{
    bool structured;
    unsigned int u;
    int i;
		
	uint64_t type = UBITS(0, 6);
    uint64_t repeat = UBITS(6, 2);
    uint64_t mmsi = UBITS(8, 30);

	switch(type)
	{
		case AIS_MSG_1:	printf("1\n"); break;
		case 2:		printf("2\n"); break;
		case 3:		printf("3\n"); break;
		case 4:		printf("4\n"); break;
		case 5:		printf("5\n"); break;
		case 6:		printf("6\n"); break;
		case 7:		printf("7\n"); break;
		case 8:		printf("8\n"); break;
		case 9:		printf("9\n"); break;
		case 10:	printf("10\n"); break;
		case 11:	printf("11\n"); break;
		case 12:	printf("12\n"); break;
		case 13:	printf("13\n"); break;
		case 14:	printf("14\n"); break;
		case 15:	printf("15\n"); break;
		case 16:	printf("16\n"); break;
		case 17:	printf("17\n"); break;
		case 18:	printf("18\n"); break;
		case 19:	printf("19\n"); break;
		case 20:	printf("20\n"); break;
		case 21:	printf("21\n"); break;
		case 22:	printf("22\n"); break;
		case 23:	printf("23\n"); break;
		case 24:	printf("24\n"); break;
		case 25:	printf("25\n"); break;
		case 26:	printf("26\n"); break;
		case 27:	printf("27\n"); break;

	}
	
}

void ais_message_1(ais1 ais)
{
	ais.status		= UBITS(38, 4);
	ais.turn		= SBITS(42, 8);
	ais.speed		= UBITS(50, 10);
	ais.accuracy	= UBITS(60, 1)!=0;
	ais.lon			= SBITS(61, 28);
	ais.lat			= SBITS(89, 27);
	ais.course		= UBITS(116, 12);
	ais.heading		= UBITS(128, 9);
	ais.second		= UBITS(137, 6);
	ais.maneuver	= UBITS(143, 2);
	//ais->type1.spare	= UBITS(145, 3);
	ais.raim		= UBITS(148, 1)!=0;
	ais.radio		= UBITS(149, 19);
}


void to6bit(char *data, unsigned char *&bits, size_t *length)
{
	size_t len = (strlen(data) * 6) / 8;

	bits = (unsigned char*)malloc(len);
	memset(bits,1,len);
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
			//return false;
	    //}
	}
	/*@ +shiftnegative @*/
    }
	
	
}
