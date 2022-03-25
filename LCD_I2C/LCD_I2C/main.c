/*
 * LCD_I2C.c
 *
 * Created: 10/28/2021 11:25:24 AM
 * Author : of Kings
 */ 

#include <avr/io.h>
#include "i2c.h"
#include "LCD_I2C.h"
#include <avr/delay.h>
int main(void)
{
	int x = 3;
    i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	lcd_cmd(0x83);//dong 1 cot 4
	lcd_msg("I2C - LCD");
	lcd_cmd(0xC3);//dong 1 cot 4
	lcd_msg("hello");
	lcd_number(x);
	//_delay_ms(200);
	lcd_clear();
}

