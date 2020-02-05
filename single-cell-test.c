#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum{true, false}bool;

uint32_t* single_c_t(uint32_t* begin, uint32_t* end)
{
	for(uint32_t* p = begin; *p <= end; p++){
		*p = 0xa5a5a5a5;
		if(*p != 0xa5a5a5a5)
			return p;
		*p = 0x00;
		if(*p != 0x00)
			return p;
	}
	return 0;
}

uint32_t* bit_link_t(uint32_t* begin, uint32_t* end)
{
	for(uint32_t* b = begin; *b <= end; b++){
		*b = 0x00;
	}
	for(uint32_t* b = begin; *b <= end; b++){
		*b = 0xff;
		for(uint32_t* q = begin; *q <= end; q++){
			if((b != q) && (*q != 0))
				return q;
		}
		*b = 0x00;
	}
	return 0;
}

#define DIGITS 16
bool check_card_number(char *input)
{
	uint8_t zahlen[DIGITS];
	for(int i = 0; i < DIGITS; i++){
		zahlen[i] = input[i] - '0';
	}
	for(int i = 0; i < DIGITS; i++){
		if((i % 2) == 0)
			zahlen[i] *= 2;	// die Zahl wird verdoppelt, wenn sie durch 2 teilbar ist
		if(zahlen[i] > 9) // die Zahl ist zweistellig, dann ist die neue Zahl die Quersumme
			zahlen[i] = zahlen[i] % 10 + zahlen[i] / 10;
	}
	//Quersumme  bilden
	unsigned int summe = 0;
	for(int i = 0; i < DIGITS; i++){
		summe += zahlen[i];
	}
	return summe % 10 == 0; // nur durch 10 teilbar, dann korrekt
}

int main()
{
	int zahl = 7;

	int *p = &zahl;
	printf("Zahl: %d\n", *p);
}
