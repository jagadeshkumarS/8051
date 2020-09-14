#define LEDS P1
void led_left(char n,int m)
{
	unsigned char i;
	for(;n>0;n--)
		for(i=0;i<8;i++)
		{
			LEDS = (1<<i)^0x0f;
			delay_1ms(m);
		}
}
void led_right(char n,int m)
{
	unsigned char i;
	for(;n>0;n--)
		for(i=0;i<8;i++)
		{
			LEDS = (0x80>>i)^0x0f;
			delay_1ms(m);
		}
}
void led_convergence(char n,int m)
{
	unsigned char i;
	for(;n>0;n--)
		for(i=0;i<4;i++)
		{
			LEDS = (1<<i)^0x0f^(0x80>>i);
			delay_1ms(m);
		}
}
void led_divergence(char n,int m)
{
	unsigned char i;
	for(;n>0;n--)
		for(i=4;i<8;i++)
		{
			LEDS = (1<<i)^0x0f^(0x80>>i);
			delay_1ms(m);
		}
}