/*
 * UART_receive.c
 *
 * Created: 6/26/2021 11:48:21 AM
 * Author : of Kings
 */ 
 #define F_CPU 8000000ul

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <compat/deprecated.h>	//sbi or cbi
#include "LCD.h"

void uart_char(unsigned char);
void uart_string(unsigned char*);
void uart_init();

volatile uint8_t data[16];
volatile int cnt = 0;


int main(void)
{
	//LCD_init();
	//LCD_number_xy(2,3,123456);
	uart_init();
	
    while (1) 
    {	
    }
}

ISR(USART_RXC_vect)	//ngat khi USART hoan tat nhan 
{	
	data[cnt] = UDR;
	if(data[cnt] != '\n')
	{
		cnt++;
	}
	else
	{
		//LCD_number_xy(1,0,data);
		uart_string(data);
	}
	
}

void uart_init()
{
	//set baud rate 57.6k, f=8MHz
	UBRRH = 0;
	UBRRL = 8;
	//set khung truyen va bo nhan du lieu
	UCSRA = 0x00;
	//set thanh ghi UCSRC
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);	//su dung 8bit data
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);		//kich hoat bo truyen, nhan du lieu | cho phep ngat khi nhan ket thuc
	
	//cho phep ngat toan cuc
	sei();
}
void uart_char(unsigned char chr)
{
	while (bit_is_clear(UCSRA,UDRE));	//lap vo han khi UDRE=0; khi UDRE=1 con trong thi thoat 
	UDR = chr;
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
