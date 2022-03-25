/*
 * timercounter_dinhthoi1ms.c
 *
 * Created: 10/9/2021 3:51:21 PM
 * Author : of Kings
 */ 
 //dinh thoi 1ms( doi trang thai tren chan PB0)
 #define F_CPU 8000000ul
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    DDRB	|= (1 << DDRB0);
	PORTB	&= ~(1 << PORTB0);
	//chon xung nhip prescaler = 64
	TCCR0	= (1 << CS01)|(1 << CS00);
	//gan gtri ban dau TCNT0 = 256 - (t*F_CPU)/clock
	TCNT0	= 131;
	//set co ngat
	TIMSK	= (1<<TOIE0);
	//cho phep ngat cuc bo
	sei();

    while (1) 
    {
    }
}

ISR(TIMER0_OVF_vect)
{
	TCNT0	= 131;
	//dao trang thai bit PB0
	PORTB ^= 1;	// ^ XOR: PORTB ^ 0000 0001
}

