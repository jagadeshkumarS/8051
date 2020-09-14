sbit cs = P1^6;
sbit mosi = P1^4;
sbit miso = P1^5;
sbit clk = P1^3;

//For MCP3204 ADC
/*
void main()
{
	lcd_init();
	lcd_str("SPI MCP3204:");
	while(1)
	{
		lcd_cmd(0xc0);
		lcd_float(spi_adc_read(0,0));
	}
}
*/

float spi_adc_read(bit d1,bit d0)
{
	unsigned int buf = 0;
	char j;
	//clk=mosi=1;//default case
	cs = 0;//chip select
	clk=0,mosi=1,clk=1;//start condition
	clk=0,mosi=1,clk=1;//single ended mode
	clk=0,clk=1;//d2 don't care
	clk=0,mosi=d1,clk=1;
	clk=0,mosi=d0,clk=1;
	clk=0,clk=1;//for sampling
	clk=0,clk=1;//for null bit
	
	for(j=11;j>=0;j--)
	{
		clk=0;
		if(miso==1) buf |= (1<<j);
		clk=1;
	}
	cs = 1;//stop condition
	return ((buf*5.0)/4096);
}