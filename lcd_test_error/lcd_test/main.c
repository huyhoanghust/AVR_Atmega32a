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
    LCD_init();
	LCD_number_xy(1,15,12345);
	LCD_string_xy(2,5,"good");
    while (1) 
    {
    }
}

