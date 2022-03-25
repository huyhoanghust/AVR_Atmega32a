/*
 * counter.c
 *
 * Created: 5/22/2021 3:28:53 PM
 * Author : of Kings
 */ 
 //dem xung canh len T0 cua led 7 segment
#include <avr/io.h>

void display (void);
int main(void)
{
    /* Replace with your application code */
	DDRD	|=(1<<DDRD0)|(1<<DDRD1)|(1<<DDRD2)|(1<<DDRD3);
	PORTD	= 0x00;
	//ctc mode
	TCCR0	|=1<<WGM01;

    while (1) 
    {
		display();
    }
}
void display (void)
{
	OCR0	=9;
	TCCR0	|= (1<<CS02)|(1<<CS01)|(1<<CS00);
	do
	{
		PORTD	= TCNT0;
	}
	while(!(TIFR&(1<<OCF0)));

	TIFR	|= 1<<OCF0;
}
