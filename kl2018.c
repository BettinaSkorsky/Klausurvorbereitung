#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{false, true}bool;

char* NMEA_frame_check(char *c)
{
	if(strlen(c) > 100 || *c != '$')
		return 0;
	for(int i = 0; i < strlen(c); i++){
		if(*(c + i) == '*'){
			return *(c + i + 1);
		}
	}
	return 0;
}

int NMEA_checksum_check(char *c)
{
	if(NMEA_frame_check(c) != 0)
		return hex2int(NMEA_frame_check(c)); // hex2int pseudecode
	return -1;
}

bool NMEA_checksum_line(char *c)
{
	unsigned char checksum = strtol(XOR_checksum, NULL, 16); // XOR_checksum globale Variable
	if(NMEA_frame_check(c) != 0 && NMEA_frameCheck() == checksum)
		return true;
	return false;
}

bool NMEA_append_checksum(char *c)
{
	unsigned char XOR_checksum = 0;

	if(NMEA_frame_check(c) != 0){
		while(*c != '*'){
			XOR_checksum ^= *c;
			c++;
		}
		c = strcat(c, XOR_checksum);
		c = strcat(c, "CR+LF");
	} else {
		return false;
	}
	return true;
}
