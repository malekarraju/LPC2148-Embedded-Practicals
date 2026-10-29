

#include <LPC214X.H>
	
int main(void)
{
	IODIR0 |= (3<<8);  // 0.8 LED1  0.9 lED2 output
	IODIR0 &= ~(3<<4); // 0.4 SW1 0.5 SW2  input

	
	while(1)
	{
		if((IOPIN0 & (1<<4)) == 0)
		{
			IOSET0 = (1<<8);
		}
		else IOCLR0 = (1<<8);	
		
		if((IOPIN0 & (1<<5)) == 0)
		{
			IOSET0 = (1<<9);
		}
		else IOCLR0 = (1<<9);	
	}
	
	return 0;
}

