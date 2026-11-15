// Triangular wave generator
#include <LPC214X.H>

int main(void)
{
		int i;
	PINSEL1 = 0x00080000; // AOUT of ADC
	
	while(6)
	{
		// Triangular wave generator
		for(i=0x00; i<=0x3FF; i++) // 0x3FF = 1023
			DACR = (i<<6); // DACR |= (1<<16) | (1<<6)
		
		for(i=0x3FF; i>=0x00; i--) // 0x3FF = 1023
			DACR = (i<<6);
	}
	return 0;
}
