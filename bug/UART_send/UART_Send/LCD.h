#define F_CPU 16000000ul
#include <util/delay.h>

#define LCD_DDR		DDRB
#define LCD_PORT	PORTB

#define RS	0
#define EN	1

void LCD_init(void);
void LCD_command(unsigned char);
void LCD_char(unsigned char);
void LCD_string(char*);
void LCD_string_xy(char, char, char*);

void LCD_command(unsigned char a)
{
	 LCD_PORT = (LCD_PORT & 0x0F) | (a & 0xF0); // xuat 4 bit muc cao khong lam anh huong toi cac cong con lai
	 LCD_PORT &= ~(1 << RS); //chan RS = 0 de ghi lenh
	 LCD_PORT |= (1 << EN); //chan EN = 1 cho LCD hoat dong
	 _delay_us(1);
	 LCD_PORT &=~(1 << EN);//EN=0 LCD tat
	 
	 _delay_us(200);

	 LCD_PORT = (LCD_PORT & 0x0F) | (a << 4);//xuat 4 bit muc thap
	 LCD_PORT |= (1 << EN); //chan EN = 1 cho LCD hoat dong
	 _delay_us(1);
	 LCD_PORT &=~(1 << EN);//EN=0 LCD tat
	_delay_us(2);
}

void LCD_char(unsigned char data)
{
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	LCD_PORT |= (1 << RS);
	LCD_PORT |= (1 << EN);
	_delay_us(1);
	LCD_PORT &=~(1 << EN);

	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	LCD_PORT |= (1 << EN); 
	_delay_us(1);
	LCD_PORT &=~(1 << EN);
	_delay_us(2);
}

void LCD_init(void)
{
	LCD_DDR = 0xFF;
	_delay_us(20);

	LCD_command(0x28); //set mode 4 bit
	LCD_command(0x02); //di chuyen con tro ve dau man hinh
	LCD_command(0x0C); //bat hien thi va tat con tro
	LCD_command(0x01); //clear screen
	_delay_us(2);
}

void LCD_string(char *str)
{
	int i;
	for (i = 0; str[i] != 0; i++)
	{
		LCD_char(str[i]);
	}
}

void LCD_string_xy(char row, char col, char*str)
{
	if (row == 1 && col < 16)
	LCD_command((col & 0x0f) | 0x80); // di chuyen con tro ve dau dong 1 roi cong voi col
	else if (row == 2 && col <16)
	LCD_command((col & 0x0f) | 0xC0); // di chuyen con tro ve dau dong 2 roi cong voi col
	LCD_string(str);

}