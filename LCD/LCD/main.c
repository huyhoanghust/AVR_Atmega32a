/*
 * LCD.c
 *
 * Created: 7/25/2021 9:17:45 PM
 * Author : of Kings
 */ 

#include <avr/io.h>
#include "LCD.h"

int main(void)
{
    init_LCD();
	clr_LCD();
	move_LCD(1,1);
	//print_LCD("good");
	move_LCD(2,2);
	LCD_Number(12323);
    while (1) 
    {
    }
}

