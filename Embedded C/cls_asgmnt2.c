#include<reg51.h>
#include"delay_header.h"
#define LEDS P1
void main()
{
	unsigned char i;
	for(i=0;i<256;i++)
	{
		LEDS = i^0x0f;
		delay_1ms(5000);
	}
}