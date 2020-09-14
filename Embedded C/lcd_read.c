#include<reg51.h>
#define lcd P3
sbit rs = P2^0;
sbit rw = P2^1;
sbit en = P2^2;
void delay_1ms(int n);
void lcd_init(void);
void lcd_cmd(unsigned char k);
void lcd_data(unsigned char k);
	
void main()
{
	lcd_init();
	lcd_data('A');
	lcd_data('B');
	lcd_data('I');
	while(1);
}

void lcd_init(void)
{
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}

void lcd_cmd(unsigned char k)
{
	lcd = k;
	rs = 0;
	rw = 0;
	en = 1;
	delay_1ms(2);
	en = 0;
}

void lcd_data(unsigned char k)
{
	lcd = k;
	rs = 1;
	rw = 0;
	en = 1;
	delay_1ms(2);
	rw = 1;
	while(P3^7==1);
	en = 0;
}

void delay_1ms(int n)
{
	unsigned char i;
	for(;n>0;n--)
	{
		for(i=250;i>0;i--);
		for(i=247;i>0;i--);
	}
}