#include <avr/io.h>
#include <util/delay.h>
#include "myLCD.h" //include th? vi?n myLCD
int main(){
	init_LCD(); //kh?i ??ng LCD
	clr_LCD(); // xóa toà b? LCD
	putChar_LCD(' '); //ghi 1 kho?ng tr?ng
	putChar_LCD(' '); //ghi 1 kho?ng tr?ng
	putChar_LCD('D'); //Hi?n th? kýt? 'D'
	print_LCD("emo of the",10); //hi?n th? 1 chu?i ký t?
	move_LCD(2,1); //di chuy?n cursor ??n dòng 2, c?t ??u tiên
	print_LCD("2x16 LCD Display",16); //hi?n th? chu?i th? 2
	while(1){

	};
}