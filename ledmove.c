#include <stdint.h>

//#include <avr/io.h>

#define PORTA (*(volatile uint8_t *)0x3b)
#define DDRA  (*(volatile uint8_t *)0x3a)
#define PINA  (*(volatile uint8_t *)0x39)

#define PORTB (*(volatile uint8_t *)0x38)
#define DDRB  (*(volatile uint8_t *)0x37)
#define PINB  (*(volatile uint8_t *)0x36)

#define TASTBIT 0x02
#define OFFEN 	0x00

void warte_auf_taste(void);

void warte_auf_taste(void)
	{
	uint8_t zustand;
	do
		{
		zustand=(~PINB) & TASTBIT;
		}
	while( zustand != OFFEN);
	do
		{
		zustand=(~PINB) & TASTBIT;
		}
	while( zustand == OFFEN);
	}

int main()
	{
	uint8_t muster;
	DDRA=0xff;
	muster=0x01;
	for(;;)
		{
		PORTA=~muster;
		warte_auf_taste();
		muster *= 2;
		if( muster == 0)
			muster = 0x01;
		}
	}
