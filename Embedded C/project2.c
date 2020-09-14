#include<reg51.h>
#include"delay_header.h"
#include"lcd_driver.h"
code struct dat
{
	unsigned char sid;
	long int id;
	char name[7];
	char amt;
}d[3] = {{1,12345671,"APPLE ",10},{2,12345672,"MANGO ",20},{3,12345673,"ORANGE",30}};
unsigned long int x=0;
unsigned char c=0,n=0,r=0;
unsigned char list[5]; 
void compare(unsigned long int s);
void main()
{
	lcd_init();
	lcd_str("Welcome");
	SCON = 0x50;
	TMOD = 0x20;
	TH1=TL1=253;
	TR1 = 1;
	EA = EX0 = EX1 = IT0 = IT1 = ES = 1;
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

void buying(unsigned char s)
{
	lcd_cmd(0x01);
	lcd_str("BUYING...");
	lcd_cmd(0xc0);
	list[n++] = s;
}

void removing(unsigned char s)
{
	unsigned char i,j;
	lcd_cmd(0x01);
	lcd_str("REJECTING...");
	lcd_cmd(0xc0);
	for(i=0;i<n;i++)
	{
		if(list[i] == s)
		{
			for(j=i;j<4;j++)
				list[j] = list[j+1];
			list[4] = 0;
			n--;
			return;
		}
	}
	lcd_str("NOT TAKEN");
}

void compare(unsigned long int s)
{
	unsigned char i;
	x=0;c=0;
	for(i=0;i<3;i++)
	{
		if(s==d[i].id)
		{
			if(r==0) buying(d[i].sid);
			else removing(d[i].sid);
			lcd_str(d[i].name);
			lcd_cmd(0xcd);
			lcd_num(d[i].amt);
			return;
		}
	}
	lcd_str("NO PRODUCT");
}

void reject(void) interrupt 0
{
	r=~r;
	lcd_cmd(0x01);
	if(r==0)
		lcd_str("BUYING...");
	else
		lcd_str("REJECTING...");
}

void total(void) interrupt 2
{
	unsigned char i,j,sum = 0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		{
			if(list[i]==d[j].sid)
			{
				sum += d[j].amt;
				goto end;
			}
		}
		end: continue;
	}
	lcd_cmd(0x01);
	lcd_str("TOTAL AMOUNT...");
	lcd_cmd(0xc0);
	lcd_num(sum);
	lcd_str(" RS");
}