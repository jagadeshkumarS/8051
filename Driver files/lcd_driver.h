#define lcd P2
sbit rs = P1^5;
sbit rw = P1^6;
sbit en = P1^7;

/*
unsigned char cgram_data[]=
{
	0x0e,0x0b,0x11,0x11,0x11,0x11,0x1f,0x00,
	0x0e,0x0b,0x11,0x11,0x11,0x1f,0x1f,0x00,
	0x0e,0x0b,0x11,0x11,0x1f,0x1f,0x1f,0x00,
	0x0e,0x0b,0x11,0x1f,0x1f,0x1f,0x1f,0x00,
	0x0e,0x0b,0x1f,0x1f,0x1f,0x1f,0x1f,0x00,
	0x0e,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x00
};
*/

void lcd_cmd(unsigned char k);

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
	en = 0;
}

void lcd_str(unsigned char *p)
{
	while(*p)
		lcd_data(*p++);
}

/*
void cgram_write()
{
	unsigned char k;
	lcd_cmd(0x40);
	for(k=0;k<48;k++)
		lcd_data(cgram_data[k]);
	lcd_cmd(0x80);
}
*/

void lcd_num(int n)
{
	char i=0,a[10];
	if(n==0)
	{
		lcd_data('0');
		return;
	}
	else
	{
		if(n<0)
		{
			lcd_data('-');
			n=-n;
		}
		while(n)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
			lcd_data(a[i]);
	}
}

/*
void lcd_float(float f)
{
	lcd_num((int)f);
	lcd_data('.');
	lcd_num((f-(int)f)*10000);
}
*/

/*
void lcd_rotate_right(unsigned char n,unsigned char *p)
{
	unsigned char addr = 0x80,i,cnt=0x80;
	n=n*16+1;
	while(n--)
	{
		lcd_cmd(0x01);
		lcd_cmd(addr);
		for(i=0,cnt=addr;p[i];i++)
		{
			lcd_data(p[i]);
			if(cnt==0x8f) lcd_cmd(0x80);
			cnt++;
		}
		delay_1ms(100);
		if(addr==0x8f) addr = 0x80;
		else addr++;
	}
}
*/