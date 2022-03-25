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

void send(unsigned char); //ham phat du lieu 


int main(void)
{
	uint8_t data[3];
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

	//truyen data 9bit 341 = 1 0101 0101 
	uint16_t chr = 341;
	uint8_t val1, val2;
	val1 = chr & 0xFF;
	val2 = (chr >> 8);
	send (val1); //85
	_delay_ms(100);
	send (val2); //1
	_delay_ms(100);
	send ('$');
	
	//data[0] = val2;
	//data[1] = val1;
	//data[2] = '/n';
	//for(int i = 0; i<=2; i++)
	//{
		//send(data[i]);
	//}
}
void send(unsigned char chr)
{
	while (bit_is_clear(UCSRA,UDRE));	//lap vo han cho toi khi UDRE=1 thi thoat, UDRE=1 nghia la UDR dang trong 
	UDR = chr;	//gan du lieu vao thanh ghi UDR
}

