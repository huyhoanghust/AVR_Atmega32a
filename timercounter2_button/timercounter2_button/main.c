/*
 * timercounter2_button.c
 *
 * Created: 10/10/2021 9:29:05 PM
 * Author : of Kings
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

int main(void)
{
    DDRB	&= ~((1 << DDRB0)|(1 << DDRB2));
	PORTB	|= (1 << PORTB0)|(1 << PORTB2);

	DDRC	|= (1 << DDRC0)|(1 << DDRC1)|(1 << DDRC2)|(1 << DDRC3);
	PORTC	|= (1 << PORTC0)|(1 << PORTC1)|(1 << PORTC2)|(1 << PORTC3);
	//xung canh len 
	TCCR0	= (1 << CS02)|(1 << CS01)|(1 << CS00);
	TCNT0	= 0;

    while (1) 
    {
		if (TCNT0 == 10)
		{
			TCNT0	= 0;
		}
		PORTC	= TCNT0;
		if (bit_is_clear(PINB,2))
		{
			TCNT0	= 0;
			PORTC	= TCNT0;
		}
    }
}

