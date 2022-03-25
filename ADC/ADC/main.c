/*
 * ADC.c
 *
 * Created: 7/1/2021 4:36:08 PM
 * Author : of Kings
 */ 

#define F_CPU 8000000ul

#include <avr/io.h>
#include <stdint.h>
#include <avr/sfr_defs.h>	//loop
#include <util/delay.h>

uint16_t read_ADC();	//doc gia tri ADC vao thanh ghi ADCW
void led7(uint16_t);	//xuat ra led 7seg chung anot

int main(void)
{
	DDRC	= 0xFF; //ouput
	DDRB	= 0xFF;

    ADMUX	= (1<<REFS0)|(1<<MUX0); //set kenh ADC1 00001 va set REFS0 chon mode 2 dien ap tham chieu

	ADCSRA	= (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);	//set ADEN truoc khi set ADSC va chon xung clock 8 (011)

    while (1) 
    {
		led7(read_ADC());
		if (read_ADC() > 341)
		{
			PORTB	= 0xFF;
		}
		else 
		{
			PORTB	= 0;
		}
    }
}

uint16_t read_ADC()
{
	ADCSRA |= (1<<ADSC);	// set ADSC sau khi set ADEN

	loop_until_bit_is_set(ADCSRA,ADIF);	//until ADIF == 1
	
	return ADCW;	//ADCW la thanh ghi 16bit gop tu 2 thanh ghi ADCL va ADCH

}

void led7(uint16_t val)
{
	uint16_t nghin, tram, chuc, dvi;

	dvi		= val % 10;
	val	/= 10;
	chuc	= val % 10;
	val	/= 10;
	tram	= val % 10;
	val	/=10;
	nghin	= val;

	PORTC	= nghin|(1<<4);
	_delay_ms(1);
	PORTC	= tram|(1<<5); //0010 0000 | (tram = 5 =0000 0101) = 0010 0101
	_delay_ms(1);
	PORTC	= chuc|(1<<6);
	_delay_ms(1);
	PORTC	= dvi|(1<<7);
	_delay_ms(1);
}


