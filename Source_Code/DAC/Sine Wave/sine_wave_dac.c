// Sine Wave (DAC)

#include <LPC214X.H>

void Delay(int);
	
int main(void)
{
	int i;
	   unsigned int sine_wave[42]={512,591,665,742,808,873,926,968,998,1017,1023,
																 1017,998,968,926,873,808,742,665,591,512,
																 436,359,282,216,211,151,97,55,25,6,0,
																 6,25,55,97,151,211,216,282,359,436};
	
	PINSEL1 = 0x00080000; // AOUT of ADC
	
	while(1)
	{
		// Sine wave generator
			for(i=0;i<42;i++)
				DACR = sine_wave[i]<<6;
	}
}
	
void Delay(int a)
{
	int i,j;
	for(i=0; i<=a; i++)
		for(j=0; j<=a; j++);
}
