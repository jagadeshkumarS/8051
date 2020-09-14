#include<reg51.h>
#include"delay_driver.h"
sbit led1=P1^0;
sbit led2=P1^1;
sbit led3=P1^2;
sbit led4=P1^3;
sbit sw1=P1^4;
sbit sw2=P1^5;
sbit sw3=P1^6;
sbit sw4=P1^7;
void main()
{
	while(1)
		if(sw1==0||sw2==0||sw3==0||sw4==0)
		{
			delay_1ms(2);
			led1=sw1;
			led2=sw2;
			led3=sw3;
			led4=sw4;
			while(sw1==0||sw2==0||sw3==0||sw4==0);
			led1=sw1;
			led2=sw2;
			led3=sw3;
			led4=sw4;
		}
}