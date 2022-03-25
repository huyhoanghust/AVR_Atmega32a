/*
 * timer.c
 *
 * Created: 5/22/2021 2:09:40 PM
 * Author : of Kings
 * Tao xung vuong tren chan PB.5 voi duty cycle =50% normal mode
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	//buoc 1: load gia tri phu hop vao TCNT0
	TCNT0 = 0x05;

	//buoc 2 thiet lap mode hoat dong cho timer: normal mode
	TCCR0 &=~((1<<WGM00)|(1<<WGM01));

    while (1) 
    {
		
    }
}
void delay_random(void)
{
		TCCR0 |=1<<CS00;   // no prescaling
		//buoc 3: ktra co TOV0
		while(!TIFR & (1<<TOV0));
		//buoc 4: dung timer
		TCCR0 &=~(1<<CS00);
		//buoc 5: clear co TOV0
		TIFR |= 1<<TOV0;
}

