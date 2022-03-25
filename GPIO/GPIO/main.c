#define F_CPU	8000000UL

#include <avr/io.h>
#include <stdint.h>
#include <compat/deprecated.h>
#include <util/delay.h>

#define LED_DDR		DDRC
#define LED_PORT	PORTC

#define LED_1		0
#define LED_1_DDR	DDRD
#define LED_1_PORT	PORTD

#define LED_2		1
#define LED_2_DDR	DDRD
#define LED_2_PORT	PORTD

const uint8_t code7Seg[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};

void led7seg_in(void);
void led7seg_display(uint8_t value);

void led7seg_in(void){
	LED_DDR=0xFF;
	LED_PORT=0xFF;

	sbi(LED_1_DDR, LED_1);	//Output
	sbi(LED_1_PORT, LED_1);	//High level
	
	sbi(LED_2_DDR, LED_2);	//Output
	sbi(LED_2_PORT, LED_2);	//High level
}
void led7seg_display(uint8_t value){

	LED_PORT = code7Seg[value / 10];
	cbi(LED_1_PORT, LED_1);	//Led 1 on
	_delay_ms(1);
	sbi(LED_1_PORT, LED_1);	//Led 1 off

	LED_PORT = code7Seg[value % 10];
	cbi(LED_2_PORT, LED_2);	//Led 2 on
	_delay_ms(1);
	sbi(LED_2_PORT, LED_2);	//Led 2 off
	
}


int main(void)
{
    led7seg_in();

    while (1) 
    {
		led7seg_display(12);
    }
}

