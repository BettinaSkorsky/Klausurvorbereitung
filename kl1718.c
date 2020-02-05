#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t CRC_check(uint32_t *anfang, uint32_t *ende)
{
	uint32_t POLY = 0xedb88320;
	uint32_t crc= 0xffffffff;
	for(uint32_t *p = anfang; *p <= ende; p++){
		for(uint8_t mask = 8; mask > 0; mask--){
			if(crc & mask){
				crc ^= POLY;
			}else
				crc <<= 1;
		}
	}
	return crc;
}

void BCD_format(uint32_t number, uint8_t target[5])
{
	for(int i = 4; i >= 0; i--){
		uint8_t tmp = (number % 10);
		number /= 10;
		tmp += ((number % 10) << 4);
		target[i] =  tmp;
		number /= 10;

	}
}

int main()
{
	uint8_t arr[5] = {0};
	int numb = 1234567890;
	BCD_format(numb, arr);
	for(int i = 0; i < sizeof(arr); i++){
		printf("%x\n", arr[i]);
	}
}
