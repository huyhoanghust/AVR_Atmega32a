/*
 * timercounter1_button.c
 *
 * Created: 10/16/2021 4:58:58 PM
 * Author : of Kings
 */ 
 /*
 co 1 sensor nhan biet so nguoi di vao cua
 khi dem duoc co 5 nguoi di vao thi luc do bao 
 lai cho may chu
 <=> dung 1 button khi bam du 5 lan thi led 7seg + 1
 */
#include <avr/io.h>
#include <avr/interrupt.h>

volatile char val = 0;

int main(void)
{
	//PORTB la input pull up
    DDRB	= 0;
	PORTB	= 0xFF;
	//led 7 seg
	DDRC	= 0xFF;
	PORTC	= 0;
	//chon mode 4, top la OCR1A, falling edge
	TCCR1B	= (1<<CS12)|(1<<CS11)|(1<<WGM12);
	//so sanh voi gia tri trong OCR1A
	OCR1A	= 4;
	//cho phep ngat Compare match khi so sanh TCNT1 voi OCR1A
	TIMSK	= (1<<OCIE1A);
	sei();

    while (1) 
    {
    }
}
ISR (TIMER1_COMPA_vect)
{
	val++;
	if (val == 10) 
	{
		val = 0;
	}
	PORTC	= val;
}

