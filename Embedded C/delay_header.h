void delay_1ms(int n)
{
	unsigned char i;
	for(;n>0;n--)
	{
		for(i=250;i>0;i--);
		for(i=247;i>0;i--);
	}
}

/*
void delay(int n)
{
	TMOD=0X00;
	for(;n>0;n--)
	{
	TH0=0xe1;
	TL0=0x1d;
	TR0=1;
	TF0=0;
	while(TF0==0);
	TR0=0;
	TF0=0;
	}
}
*/