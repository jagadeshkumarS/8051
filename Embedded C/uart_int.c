#include<reg51.h>
#include"delay_driver.h"
#include"lcd_driver.h"
void uart_init();
void main()
{
	char c='A';
	lcd_init();
	uart_init();
	lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_data(c++);
	SBUF='A';
	while(1)
	{
		c++;
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_data(c);
		delay_1ms(100);
	}
}

void uart_init()
{
	SCON = 0x50;
	EA = ES = 1;
	TMOD = 0x20;
	TH1=TL1=253;
	TR1 = 1;
}

void serial(void) interrupt 4
{
	lcd_cmd(0x02);
	lcd_string("Interrupt");
	delay_1ms(100);
	TI=0;
	RI=0;
}