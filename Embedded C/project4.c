#include<reg51.h>
#include"delay_header.h"
#include"lcd_driver.h"
code struct dat
{
	unsigned char sid;
	unsigned long int id;
}d[3] = {{1,12345671},{2,12345672},{3,12345673}};
unsigned char c=0,n=0;
unsigned char list[5];
unsigned long int x=0;
void compare(unsigned long int s);
void check(unsigned char s);
void entry(unsigned char s);
void exit(unsigned char s,unsigned char i);
void main()
{
	lcd_init();
	lcd_str("Welcome");
	SCON = 0x50;
	TMOD = 0x20;
	TH1=TL1=253;
	TR1 = 1;
	EA = EX0 = IT0 = ES = 1;
	while(1);
}

void serial(void) interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
		x = x*10 + (SBUF-48);
		c++;
		if(c==8) compare(x);
	}
}

void compare(unsigned long int s)
{
	unsigned char i;
	x=0;c=0;
	for(i=0;i<3;i++)
	{
		if(s==d[i].id)
		{
			check(d[i].sid);
			return;
		}
	}
	lcd_cmd(0x01);
	lcd_str("Invalid");
}

void check(unsigned char s)
{
	unsigned char i;
	if(n==0)
		goto call;
	for(i=0;i<n;i++)
	{
		if(s==list[i])
		{
			exit(s,i);
			return;
		}
	}
	call: entry(s);
}

void entry(unsigned char s)
{
	lcd_cmd(0x01);
	lcd_str("ENTRY...");
	lcd_cmd(0xc0);
	list[n++] = s;
	lcd_num(s);
}

void exit(unsigned char s,unsigned char i)
{
	lcd_cmd(0x01);
	lcd_str("EXIT...");
	lcd_cmd(0xc0);
	for(;i<4;i++)
		list[i] = list[i+1];
	list[4] = 0;
	n--;
	lcd_num(s);
}

//Write the time
/*
void main()
{
	unsigned char time[] = {0x50,0x59,0x71};
	time_write(time);
}
*/