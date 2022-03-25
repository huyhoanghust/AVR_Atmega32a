#define F_CPU	16000000UL
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
//#include <stdint.h>


int main(void)
{
	DDRC=0xFF;
	PORTC=0x00;
	unsigned char led[]={0xFF,0b11100111,0b11000011,0b10000001,0b11110011,0b10101100,0b00000001,0};
	for(int i=0;i<strlen(led);i++)
	{
		PORTC=led[i];
		_delay_ms(500);
	}
}

