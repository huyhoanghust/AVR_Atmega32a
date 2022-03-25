/*
 * final.c
 *
 * Created: 7/11/2021 12:19:13 AM
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

 void send(unsigned char);

 uint8_t data[3];
 int cnt = 0;
 uint16_t val;

 int main(void)
 {
	 LCD_init();
	
	 DDRA	= 0xFF;
	 PORTA	= 0x00;
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

	 while (1)
	 {
	 }
 }
 void send(unsigned char chr)
 {
	 while (bit_is_clear(UCSRA,UDRE));	//lap vo han khi UDRE=0; khi UDRE=1 con trong thi thoat
	 UDR = chr;
 }

 ISR(USART_RXC_vect)	//ngat khi USART hoan tat nhan
 {
	 data[cnt] = UDR;
	 if(data[cnt] == '$')
	 {
		 val = data[0]|(data[1] << 8);
	 }
	 if (val == 341)
	 {
		PORTA = 0xff;
		LCD_string_xy(1,4,"Canh bao");
		 _delay_ms(1000);
	 }
	 PORTA = 0;
	 cnt++;
	 
 }