/*
 * interrupt.c
 *
 * Created: 5/15/2021 3:14:03 PM
 * Author : of Kings
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
int volatile x=0; 
int volatile y=0;
int main(void)
{ 
	//khi ch?a khai b�o DDRD=0
	//PD2 v� PD3 l� input
   //DDRD &=~((1<<DDRD2)|(1<<DDRD3));//1111 0011    0000 1100
   DDRD = 0;
   //C?u h�nh interrupt
   MCUCR = 0b00001010;//s??n xu?ng
   //C?u h�nh ng?t s??n l�n cho 2 ch�n INT0 v� INT1
   //MCUCR |=(1<<ISC11)|(1<<ISC10)|(1<<ISC01)|(1<<ISC00);
   //c?u h�nh ng?t, b?t ng?t tr�n ch�n INT1 v� INT0
   GICR = 0b11000000;
   //GICR |=(1<<INT1)|(1<<INT0);
   //B?t ng?t to�n c?c, b?t bit I c?a SREG
   sei();
   //cau hinh output
   DDRB = 0xF;
   DDRA = 0xF;
   //DDRB |=(1<<DDRB0)|(1<<DDRB1)|(1<<DDRB2)|(1<<DDRB3);//=F   0000 1111
   //DDRA |=(1<<DDRA0)|(1<<DDRA1)|(1<<DDRA2)|(1<<DDRA3);//=F   0000 1111
   while(1){
   //ch? c�u l?ch ti?p theo
   }
}
/*form
ISR(vecto ng?t)
{
......
}*/
ISR(INT1_vect)
{
	x=x+1;
	if(x>99)
	{
		x=0;
	}
	PORTA = x%10;
	PORTB = x/10;
}
ISR(INT0_vect)
{
	x=x-1;
	if(x<0)
	{
		x=99;
	}
	PORTA = x%10;
	PORTB = x/10;
}
