#define F_CPU 16000000ul
#include <util/delay.h>
#include <stdint.h>

#define LCD_DDR		DDRC
#define LCD_PORT	PORTC

#define RS	0
#define EN	1

void LCD_init(void);						//khoi dong lcd
void LCD_command(unsigned char);			//Ghi lech
void LCD_char(unsigned char);				//print ki tu
void LCD_string(char*);						//print 1 xau ki tu
void LCD_string_xy(char, char, char*);		//print 1 xau ki tu tai 1 vi tri hang x cot y
void LCD_clear();							//clear screen
void LCD_number_xy(char, char, uint32_t);	//print 1 so 

void LCD_command(unsigned char cmnd)
{
	 LCD_PORT = (LCD_PORT & 0x0F) | (cmnd & 0xF0); // xuat 4 bit muc cao khong lam anh huong toi cac cong con lai
	 LCD_PORT &= ~(1 << RS); //chan RS = 0 de ghi lenh
	 LCD_PORT |= (1 << EN); //chan EN = 1 cho LCD hoat dong
	 _delay_us(1);
	 LCD_PORT &=~(1 << EN);//EN=0 LCD tat
	 
	 _delay_us(200);

	 LCD_PORT = (LCD_PORT & 0x0F) | (cmnd << 4);//xuat 4 bit muc thap
	 LCD_PORT |= (1 << EN); //chan EN = 1 cho LCD hoat dong
	 _delay_us(1);
	 LCD_PORT &= ~ (1 << EN);//EN=0 LCD tat
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

	LCD_command(0x02);//di chuyen con tro ve dau man hinh
	LCD_command(0x28);//set mode 4bit
	LCD_command(0x0C);//bat hien thi va tat con tro
	LCD_command(0x06);//con tro tu dong di chuyen den vi tri tiep theo tren LCD
	LCD_command(0x01);//clear screen
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
	LCD_command((col & 0x0F) | 0x80); // di chuyen con tro ve dau dong 1 roi cong voi col
	else if (row == 2 && col <16)
	LCD_command((col & 0x0F) | 0xC0); // di chuyen con tro ve dau dong 2 roi cong voi col
	LCD_string(str);

}
void LCD_clear()
{
	LCD_command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_command (0x80);		/* Cursor at home position */
}

void LCD_number_xy(char row, char col, uint32_t number)	//print number example 1234
{
	uint32_t num[10];
	unsigned int i = 0;
	while (number / 10 !=0)
	{
		num[i++] = number % 10;				//4>i=0...3>i=1....2>i=2....1>i=3
		number /= 10;
	}
	num[i] = number;
	if (row == 1 && col < 16)
	LCD_command((col & 0x0F) | 0x80); // di chuyen con tro ve dau dong 1 roi cong voi col
	else if (row == 2 && col <16)
	LCD_command((col & 0x0F) | 0xC0); // di chuyen con tro ve dau dong 2 roi cong voi col

	for (int j = i; j >= 0; j--)
	{
		LCD_char(num[j] + 48);
	}

}
