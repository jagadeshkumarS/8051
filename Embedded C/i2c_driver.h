#include<intrins.h>
sbit scl = P3^2;
sbit sda = P3^3;

/*
//For EEPROM
void main()
{
	lcd_init();
	lcd_str("i2c EEProm:");
	delay_1ms(500);
	i2c_slavewrite_str(0xa0,0x00,"JAGADESH");
	lcd_cmd(0xc0);
	lcd_str(i2c_slaveread_str(0xa0,0x00));
	while(1);
}
*/

void start(void)
{
	scl = 1;
	sda = 1;
	sda = 0;
}

void stop(void)
{
	sda = 0;
	scl = 1;
	sda = 1;
}

void bytewrite(char d)
{
	unsigned char j;
	for(j=0;j<8;j++)
	{
		scl = 0;
		sda = d&(0x80>>j);
		scl = 1;		
	}
}

unsigned char byteread(void)
{
	unsigned char j,buf=0;
	for(j=0;j<8;j++)
	{

		scl = 0;
		_nop_();
		scl = 1;
		if(sda)
			buf |= (0x80>>j);
	}
	return buf;
}

void ack(void)
{
	scl = 0;
	sda = 1;
	scl = 1;
	//while(sda==1);
	scl = 0;
}

void noack(void)
{
	scl = 0;
	sda = 1;
	scl = 1;
	scl = 0;
}

void i2c_slavewrite(unsigned char sa,unsigned char ra,unsigned char dt)
{
	start();
	bytewrite(sa);
	ack();
	bytewrite(ra);
	ack();
	bytewrite(dt);
	ack();
	stop();
	delay_1ms(10);
}

unsigned char i2c_slaveread(unsigned char sa,unsigned char ra)
{
	unsigned char buff;

	//Dummy Write
	start();
	bytewrite(sa);
	ack();
	bytewrite(ra);
	ack();

	//Read Operation
	start();
	bytewrite(sa|1);
	ack();
	buff = byteread();
	noack();
	stop();
	
	return buff;
}

/*
void i2c_slavewrite_str(unsigned char sa,unsigned char ra,unsigned char *p)
{
	unsigned char i;
	for(i=0;p[i];i++)
		i2c_slavewrite(sa,ra+i,p[i]);
}

unsigned char *i2c_slaveread_str(unsigned char sa,unsigned char ra)
{
	unsigned char i;
	idata unsigned char s[20];
	for(i=0;i<10;i++)
	{
		s[i] = i2c_slaveread(sa,ra+i);
		if(s[i] == '\0')
			break;
	}
	return s;
}
*/

//For RTC
//unsigned char time[] = {0x50,0x59,0x71}; //in main
void time_write(unsigned char *time)
{
	char i;
	for(i=0;i<3;i++)
		i2c_slavewrite(0xd0,0x00+i,time[i]);
}

void date_write(unsigned char *date)
{
	char i;
	for(i=0;i<4;i++)
		i2c_slavewrite(0xd0,0x03+i,date[i]);
}

void time_read(void)
{
	unsigned char t,s;char i;
	for(i=2;i>=0;i--) {
		t = i2c_slaveread(0xd0,0x00+i);
		if(i==2) {
			if(0x40&t) s=(0x20&t)?1:0;
				t = 0x1f&t;
		}
		lcd_num(t>>4);
		lcd_num(t&0x0f);
		if(i!=0) lcd_data(':');
	}
	lcd_data(' ');
	if(s==1) lcd_str("PM");
	else lcd_str("AM");
}

void date_read(void)
{
	unsigned char t;char i;
	for(i=0;i<3;i++) {
		t = i2c_slaveread(0xd0,0x04+i);
		lcd_num(t>>4);
		lcd_num(t&0x0f);
		if(i!=2) lcd_data(':');
	}
	lcd_data(' ');
	t = i2c_slaveread(0xd0,0x03);
	switch(t)
	{
		case 1 : lcd_str("sun"); break;
		case 2 : lcd_str("mon"); break;
		case 3 : lcd_str("tue"); break;
		case 4 : lcd_str("wed"); break;
		case 5 : lcd_str("thu"); break;
		case 6 : lcd_str("fri"); break;
		case 7 : lcd_str("sat"); break;
	}
}