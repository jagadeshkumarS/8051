#include<stdlib.h>

/*
void main()
{
	uart_init();
	uart_tx(uart_rx());
	uart_stx("Working");
	while(1)
		uart_stx(uart_srx());
}
*/

void uart_init(void)
{
	SCON = 0x50;
	TMOD = 0x20;
	TH1=TL1=253;
	TR1 = 1;
}

void uart_tx(char c)
{
	SBUF = c;
	while(TI==0);
	TI = 0;
}

char uart_rx(void)
{
	while(RI==0);
	RI = 0;
	return SBUF;
}

void uart_stx(char *s)
{
	while(*s)
		uart_tx(*s++);
}

char *uart_srx(void)
{
	char i;
	idata char p[20];
	for(i=0;;i++)
	{
		p[i] = uart_rx();
		if(p[i]=='\r') break;
	}
	p[i+1] = '\0';
	return p;
}

/*
char *uart_srx(void)
{
	unsigned char i;
	char *p = malloc(1);
	for(i=0;;i++)
	{
		p[i] = uart_rx();
		if(p[i]=='\r') break;
		else if(i>0) realloc(p,i+1);
	}
	p[i+1] = '\0';
	return p;
}
*/