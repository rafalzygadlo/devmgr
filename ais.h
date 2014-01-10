#ifndef __AIS
#define __AIS

#include "bits.h"
#include <stdlib.h>
#include <string.h>

#define AIS_MSG_1	1
#define AIS_MSG_2	2

#define BITS_PER_BYTE	8
#define UBITS(s, l)	ubits((unsigned char *)bits, s, l, false)
#define SBITS(s, l)	sbits((signed char *)bits, s, l, false)
#define UCHARS(s, to)	from_sixbit((unsigned char *)bits, s, sizeof(to)-1, to)
#define ENDCHARS(s, to)	from_sixbit((unsigned char *)bits, s, (bitlen-(s))/6,to)

//char *data = "177KQJ5000G?tO`K>RA1wUbN0TKH";
//char *data = "54Rp5d02;<KuK8<SP00l58U<0000000000000017;P9@27?`0:ii6CR@@000";

//const char sixchr[65] = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_ !\"#$%&'()*+,-./0123456789:;<=>?";


#define AIS_TURN_HARD_LEFT	-127
#define AIS_TURN_HARD_RIGHT	127
#define AIS_TURN_NOT_AVAILABLE	128
#define AIS_SPEED_NOT_AVAILABLE	1023
#define AIS_SPEED_FAST_MOVER	1022		/* >= 102.2 knots */
#define AIS_LATLON_DIV	600000.0
#define AIS_LON_NOT_AVAILABLE	0x6791AC0
#define AIS_LAT_NOT_AVAILABLE	0x3412140
#define AIS_COURSE_NOT_AVAILABLE	3600
#define AIS_HEADING_NOT_AVAILABLE	511
#define AIS_SEC_NOT_AVAILABLE	60
#define AIS_SEC_MANUAL		61
#define AIS_SEC_ESTIMATED	62
#define AIS_SEC_INOPERATIVE	63


typedef struct ais1
{
	unsigned int status;		/* navigation status */
	signed turn;				/* rate of turn */
	unsigned int speed;			/* speed over ground in deciknots */
	bool accuracy;				/* position accuracy */
	int lon;					/* longitude */
	int lat;					/* latitude */
	unsigned int course;		/* course over ground */
	unsigned int heading;		/* true heading */
	unsigned int second;		/* seconds of UTC timestamp */
	unsigned int maneuver;		/* maneuver indicator */
	//unsigned int spare;	spare bits */
	bool raim;					/* RAIM flag */
	unsigned int radio;			/* radio status bits */
};

void to6bit(char *data, unsigned char *&bits, size_t *length);
void ais_binary_decode(unsigned char *bits, size_t bitlen);


#endif