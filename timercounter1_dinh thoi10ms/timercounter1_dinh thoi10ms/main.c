/*
 * timercounter1_dinh thoi10ms.c
 *
 * Created: 10/16/2021 3:05:38 PM
 * Author : of Kings
 */ 

 /*
 t=10ms; cpu=8mhz, prescaler=8 
 =>TCNT1 = 65536 - t*cpu/8 = 55536
 */

#define F_CPU 8000000ul

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    DDRA	= 0xFF;
	PORTA	= 0;
	//xet xung nhip prescaler = 8
	TCCR1B	= (1 << CS11);
	TCNT1	= 55536;
	TIMSK	= (1 << TOIE1);
	sei(); 
    while (1) 
    {
    }
}
ISR (TIMER1_OVF_vect)
{
	PORTA ^= 1;
	TCNT1 = 55536; 
}

