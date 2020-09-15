#include<reg51.h>
#include"delay_driver.h"
#include"lcd_driver.h"
#define LCD P3
sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;
void main()
{
	char h,m,s;
	h=m=s=0;
	lcd_init();
	while(1)
	{
		delay(1000);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_number(h);
		lcd_data(':');
		lcd_number(m);
		lcd_data(':');
		lcd_number(s);
		s++;
		if(s==60)
			m++,s=0;
		if(m==60)
			h++,m=0;
		if(h==12)
			h=0;
	}
}