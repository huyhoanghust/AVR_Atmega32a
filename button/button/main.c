/*
 * button.c
 *
 * Created: 5/20/2021 1:02:51 AM
 * Author : of Kings
 */ 
 //button mac tich cuc o muc thap

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRC = 1<<DDRD0;//chan C0 la output
	PORTC = 0;//den tat
	DDRA = 0;//chan A0 la input
	PORTA = 1;//cho phep dien tro keo len
	//if(PINA == 0)
	//{
		//PORTC = ~PORTC;
	//}

    while (1) 
    {
	if(PINA == 0)
	{
		PORTC = !PORTC;
	}
    }
}

