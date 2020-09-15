#include<reg51.h>
#include<stdlib.h>
void uart_init(void);
void uart_tx(unsigned char c);
unsigned char uart_rx(void);
void uart_stx(unsigned char *s);
//unsigned char *uart_srx(unsigned char *);
void main()
{
	unsigned char i=0;
	char *p = (char *)malloc(1);
	uart_init();

	while(1)
	{
		for(i=0;;i++)
		{
			realloc(p,i+1);
			p[i] = uart_rx();
			if(p[i]=='\r')
				break;
		}
		p[i] = '\0';
		uart_stx(p);
	}
}

void uart_init(void)
{
	SCON = 0x50;
	TMOD = 0x20;
	TH1=TL1=253;
	TR1 = 1;
}

void uart_tx(unsigned char c)
{
	SBUF = c;
	while(TI==0);
	TI = 0;
}

unsigned char uart_rx(void)
{
	while(RI==0);
	RI = 0;
	return SBUF;
}

void uart_stx(unsigned char *s)
{
	while(*s)
		uart_tx(*s++);
}

/*
unsigned char *uart_srx()
{
	unsigned char i=0;
	char *p = (char *)malloc(i+1);
	do
	{
		if(i>0)
			realloc(p,i+1);
		p[i] = uart_rx();
	}while(p[i++]!='\r');
	p[i] = '\0';
	return p;
}
*/

/*
unsigned char *uart_srx(unsigned char *p)
{
	unsigned char i;
	for(i=0;;i++)
	{
		p[i] = uart_rx();
		if(p[i] == '\r')
			break;
	}
	p[i] = '\0';
	return p;
}
*/