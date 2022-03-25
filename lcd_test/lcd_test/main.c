/*
 * lcd_test.c
 *
 * Created: 6/19/2021 9:06:58 PM
 * Author : of Kings
 */ 

#include <avr/io.h>
#include "LCD.h"

int main(void)
{
	int val = 1234;
	char chr[5] = "good";
    LCD_init();
	LCD_number_xy(1,8,val);
	LCD_string_xy(2,1,chr);
    while (1) 
    {
    }
}

