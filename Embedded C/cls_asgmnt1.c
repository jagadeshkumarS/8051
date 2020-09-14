#include<reg51.h>
#include"delay_header.h"
#define LEDS P1
void main()
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		LEDS = (0x80>>i)^0x0f^(1<<i);
		delay_1ms(2000);
	}
}