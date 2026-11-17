
#include <LPC214X.H>

#define SW1 (1<<14)
#define SW2 (1<<15)
#define SW3 (1<<16)

#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)

int main(void)
{
	IODIR0 |= LED1 | LED2 | LED3;  // led direct. as output
	IODIR0 &= ~(SW1 | SW2 | SW3); // 0.4 SW1 0.5 SW2  input

	
	while(1)
	{
		if((IOPIN0 & (SW1)) == 0)
		{
			IOCLR0 = LED1;
		}
		else IOSET0 = LED1;	
		
		if((IOPIN0 & (SW2)) == 0)
		{
			IOCLR0 = LED2;
		}
		else IOSET0 = LED2;	
		
		if((IOPIN0 & (SW3)) == 0) // work reverse
		{
			IOSET0 = LED3;
		}
		else IOCLR0 = LED3;	
	}
	
	return 0;
}

