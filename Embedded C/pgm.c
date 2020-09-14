#include<reg51.h>
#include"delay_driver.h"
#include"lcd_driver.h"
#include"i2c_driver.h"
//#include"spi_driver.h"

void main()
{
	unsigned char t[] = {0x50,0x59,0x71};
	unsigned char d[] = {0x01,0x22,0x03,0x20};
	lcd_init();
	lcd_str("RTC:");
	lcd_cmd(0xc0);
	time_write(t);
	date_write(d);
	while(1)
	{
		lcd_cmd(0x84);
		time_read();
		lcd_cmd(0xc0);
		date_read();
	}
}