#define LEDS P1
sbit sw=P0^0;
void switch_left(char n)
{
	unsigned char i;
	for(;n>0;n--)
		for(i=0;i<8;i++)
			if(sw==0)
			{
				delay_1ms(2);
				LEDS = (1<<i)^0x0f;
				while(sw==0);
			}
}
void switch_right(char n)
{
	unsigned char i;
	for(;n>0;n--)
		for(i=0;i<8;i++)
			if(sw==0)
			{
				delay_1ms(2);
				LEDS = (0x80>>i)^0x0f;
				while(sw==0);
			}
}
void switch_convergence(char n)
{
	unsigned char i;
	for(;n>0;n--)
		for(i=0;i<4;i++)
			if(sw==0)
			{
				delay_1ms(2);
				LEDS = (1<<i)^0x0f^(0x80>>i);
				while(sw==0);
			}
}
void switch_divergence(char n)
{
	unsigned char i;
	for(;n>0;n--)
		for(i=4;i<8;)
			if(sw==0)
			{
				delay_1ms(2);
				LEDS = (1<<i)^0x0f^(0x80>>i++);
				while(sw==0);
			}
}