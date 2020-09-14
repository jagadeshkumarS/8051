#include<reg51.h>
#include"delay_driver.h"
#include"i2c_driver.h"
#include"lcd_driver.h"
unsigned char time[] = {0x50,0x59,0x71};
void main()
{
	unsigned char t,s;
		signed char i;
	lcd_init();
	lcd_str("i2c RTC:");
	for(i=0;i<3;i++)
		i2c_slavewrite(0xd0,0x00+i,time[i]);
	while(1) {
		lcd_cmd(0xc0);
		for(i=2;i>=0;i--) {
			t = i2c_slaveread(0xd0,0x00+i);
			if(i==2) {
				if(0x40&t) s=(0x20&t)?1:0;
					t = 0x1f&t;
			}
			lcd_num(((t>>4)*10)+(t&0x0f));
			if(i!=0) lcd_data(':');
		}
		lcd_data(' ');
		if(s==1) lcd_str("PM  ");
		else lcd_str("AM  ");
	}
}