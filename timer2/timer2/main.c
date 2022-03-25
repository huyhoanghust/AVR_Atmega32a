/*
 * timer2.c
 *
 * Created: 5/22/2021 2:56:02 PM
 * Author : of Kings
 */ 
 //dao gia tri tren chan PB5 ssau 100us
#include <avr/io.h>

void dekay_100us(void);
int main(void)
{
    /* Replace with your application code */
	DDRB |=1<<DDRB5;
	PORTB &=~(1<<PORTB5);
	TCNT0 = 156;
	TCCR0 &=~((1<<WGM01)|(1<<WGM00));
    while (1) 
    {
		PORTB |=1<<PORTB5;
		delay_100us();
		PORTB &=~(1<<PORTB5);
		delay_100us();
    }
}
void delay_100us(void)
{
	TCCR0 |=1<<CS01;
	while(!(TIFR&(1<<TOV0)));
	TIFR |=1<<TOV0;
	TCCR0 &=~(1<<CS01);
	TCNT0 =156;
}
