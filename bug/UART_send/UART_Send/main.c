/*
 * UART.c
 *
 * Created: 6/26/2021 9:04:03 AM
 * Author : of Kings
 */ 

#define	F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdint.h>

void uart_init();	//khoi dong uart
void uart_char(unsigned char); //ham phat du lieu 1 ki tu
void uart_string(unsigned char*);//ham phat 1 chuoi ki tu
void uart_number(uint16_t);//ham phat 1 so 



int main(void)
{
    uart_init();
	
	uart_number(1234);
	while(1)
	{

	}
	
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