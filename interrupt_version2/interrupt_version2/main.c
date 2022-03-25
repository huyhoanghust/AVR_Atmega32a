/*
 * interrupt_version2.c
 *
 * Created: 8/19/2021 1:14:41 PM
 * Author : of Kings
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

int volatile val;

int main(void)
{
    MCUCR	|= (1 << ISC10) | (1 << ISC00);	// xung canh xuong 
	GICR	|= (1 << INT1) | (1 << INT0);	// kich hoat ngat tren chan int1 va int0
	sei();	//set bit I cho phep ngat
	// cau hinh input
	DDRD	&= ~((1 << DDRD2) | (1 << DDRD3)); 
	// cho phep pull - up
	PORTD	|= (1 << PORTD2) | (1 << PORTD3);
	
	//xuat ra 7seg
	DDRC	= 0xFF;
    while (1) 
    {
    }
}

ISR(INT1_vect)
{
	val++;
	if(val>9) 
	val = 0;
	PORTC = val;
}
ISR(INT0_vect)
{
	val--;
	if (val<0)
	val = 9;
	PORTC = val;
}

