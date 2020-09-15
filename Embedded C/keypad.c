#include<reg51.h>
sbit r0 = P1^0;
sbit r1 = P1^1;
sbit r2 = P1^2;
sbit r3 = P1^3;
sbit c0 = P1^4;
sbit c1 = P1^5;
sbit c2 = P1^6;
sbit c3 = P1^7;
unsigned char keys[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
unsigned char keyread(void)
{
	int r=-1,c=-1;
	while(1)
	{
		c0=c1=c2=c3=1;
		r0=r1=r2=r3=0;
		while(c0&c1&c2&c3);

		r0 = 0; r1=r2=r3=1;
		if((c0&c1&c2&c3)==0)
		{
			r = 0;
			break;
		}
		
		r1 = 0; r0=r2=r3=1;
		if((c0&c1&c2&c3)==0)
		{
			r = 1;
			break;
		}

		r2 = 0; r1=r0=r3=1;
		if((c0&c1&c2&c3)==0)
		{
			r = 2;
			break;
		}

		r3 = 0; r1=r2=r0=1;
		if((c0&c1&c2&c3)==0)
		{
			r = 3;
			break;
		}
	}
	
	if(c0==0) c = 0;
	else if(c1==0) c = 1;
	else if(c2==0) c = 2;
	else if(c3==0) c = 3;
	
	while((c0&c1&c2&c3)==0);
	
	return keys[r][c];
}