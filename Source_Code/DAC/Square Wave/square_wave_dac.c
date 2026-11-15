		// Square wave generator
#include <LPC214X.H>

void Delay(int);
	
int main(void)
{
		int i;
	PINSEL1 = 0x00080000; // AOUT of ADC
	
	while(6)
	{
		// Square wave generator
			DACR = (0x3FF<<6); // 
			Delay(300);
			DACR = (0x000<<6);
			Delay(300);
	}
	return 0;
}

void Delay(int a)
{
	int i,j;
	for(i=0; i<=a; i++)
		for(j=0; j<=a; j++);
}
