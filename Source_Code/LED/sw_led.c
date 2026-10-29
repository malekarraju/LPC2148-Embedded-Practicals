#include <LPC214X.H>
	
int main(void)
{
	IODIR0 |= (1<<8);  // LED 1 output
	IODIR0 &= ~(1<<4); // SW 0 input
	
	while(1)
	{
		if((IOPIN0 & (1<<4)) == 0)
		{
			IOSET0 = (1<<8);
		}
		else IOCLR0 = (1<<8);	
	}
	
	return 0;
}
