/*
 * final.c
 *
 * Created: 7/25/2021 10:42:01 PM
 * Author : of Kings
 */ 
#define F_CPU 8000000ul

#include <avr/io.h>
#include <stdint.h>
#include <avr/sfr_defs.h>	//loop
#include <util/delay.h>

//uart
void uart_init();	//khoi dong uart
void uart_char(unsigned char); //ham phat du lieu 1 ki tu
void uart_string(unsigned char*);//ham phat 1 chuoi ki tu
void uart_number(uint16_t);//ham phat 1 so

//adc
uint16_t read_ADC();	//doc gia tri ADC vao thanh ghi ADCW
void led7(uint16_t);	//xuat ra led 7seg chung anot
void adc_init();

int main(void)
{
    adc_init();
	uart_init();
    while (1) 
    {   
		led7(read_ADC());
		uart_number(read_ADC());
    }
}

void adc_init()
{
	DDRC	= 0xFF; //ouput
	DDRB	= 0xFF;
	ADMUX	= (1<<REFS0)|(1<<MUX0); //set kenh ADC1 00001 va set REFS0 chon mode 2 dien ap tham chieu
	ADCSRA	= (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);	//set ADEN truoc khi set ADSC va chon xung clock 8 (011)
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

void uart_init()
{
	//set baud rate la 57.6k, f=8MHz, U2X=0 khong nhan doi toc do truyen
	//assign value vao UBRRH truoc, sau do UBRRL
	UBRRH = 0;
	UBRRL = 8;

	//set khung truyen va kich hoat bo nhan du lieu
	UCSRA = 0x00;	//khong nhan doi, khong su dung truyen thong da xu li
	//set URSEL len 1 de su dung thanh ghi UCSRC
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);	//set UCSZ0 va UCSZ1 len 1 de su dung data 8bit
	//kich hoat bo phat du lieu
	UCSRB = (1<<TXEN);
}
void uart_char(unsigned char chr)
{
	while (bit_is_clear(UCSRA,UDRE));	//lap vo han cho toi khi UDRE=1 thi thoat, UDRE=1 nghia la UDR dang trong
	UDR = chr;	//gan du lieu vao thanh ghi UDR
}
void uart_string(unsigned char* str)
{
	int i = 0;
	while (str[i]>0)
	{
		uart_char(str[i]);
		i++;
	}
	uart_char('\n');
}
void uart_number(uint16_t number)
{
	uint16_t num[16];
	sprintf(num, "%d", number);
	uart_string(num);
}