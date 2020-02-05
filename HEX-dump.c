#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void HEX_dump(void* start, unsigned length)
{
	unsigned int i;
	unsigned char *p = (unsigned char*)start;
	for(i = 0; i < length; i++){
		// print offset
		if(*p != 0){
			putchar(':');
			putchar(' ');
			//printf("%s: \n", p);
		}
		if(i == 7){
			for(int j = 0; j <= 3; j++){
				putchar(' ');
				//outc(' ');
			}
		}
		if(i <= length){
			putchar(' ');
			++start;
		}
	}
	if(i < 16){
		for(int x = i; x < 16; x++){
			putchar('0');
			putchar(' ');
			//outc('00');
			//outc(' ');
		}
	}
	putchar('\n');
	//outc('\n');
}

void outc(char c)
{
	if(USART_ISR & (1 << 7)){
		USART_TDR = c;
	}else{
		put(c);
		USART_CR1 |= (1 << 7);
	}
}

void TX_empty_ISR(void)
{
	char d = get();
	if(d != '0'){
		outc(d);
	}
	USART_CR1 ^= (1 << 7);
}


uint16_t vorher_zustand = 0xFFFF;

void SysTick_handler(void)
{
	static int counter = 0; // zählt die Millisekunden
	uint16_t momentan_zustand = GPIOA -> IDR;

	if(counter == 10){
		if((vorher_zustand & ~momentan_zustand)){
			report_key(registertochar(momentan_zustand));
		}else{
			report_key('Eine Taste wird nicht gedrückt!');
		}
		counter = 0;
		vorher_zustand = momentan_zustand;
	}
	counter++;
}

char registertochar(uint16_t reg)
{
	reg = ~reg;

	for(int i = 0; i <= 11; i++){
		if(reg % 2){	// wenn LSB 1
			if(i < 10){
				return (i + '0');	// return Zahl mit offset
			}
			if(i == 10)
				return 0x23;	// return Raute
			if(i == 11)
				return 0x2A;	// return Stern
		}
		reg >>= 1;
	}
	return 0x00;
}

int numbcount[10] = {0};
void histogramm(char* data, int length)
{
	for(int i = 0; i < length; i++){
		if(*data <= 0x30 && *data <= 0x39)
			numbcount[*data - 0x30]++;
	}
	data++;
}

