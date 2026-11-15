// sw4_wave4_dac	
#include <LPC214X.H>

#define SW1 1<<19
#define SW2 1<<18
#define SW3 1<<17
#define SW4 1<<16

void Delay(int);
	
int main(void)
{
	int i;
	   unsigned int sine_wave[42]={512,591,665,742,808,873,926,968,998,1017,1023,
																 1017,998,968,926,873,808,742,665,591,512,
																 436,359,282,216,211,151,97,55,25,6,0,
																 6,25,55,97,151,211,216,282,359,436};
	
	PINSEL1 = 0x00080000; // AOUT of ADC
	IO1DIR &= ~(SW1 | SW2 | SW3| SW4); // set as input pins
	
	while(1)
	{
		if(!(IO1PIN & SW1))
		{	// Triangular wave generator
			for(i=0;i<=0x3FF;i++)
				DACR = i<<6;
			for(i=0x3FF;i>=0x000;i--)
				DACR = i<<6;
		}
		else if(!(IO1PIN & SW2))
		{	// Swatooth wave generator
			for(i=0;i<=0x3FF;i++)
				DACR = i<<6;
		}
		else if(!(IO1PIN & SW3))
		{	// Square wave generator
			DACR = (0x3FF<<6); // 
			Delay(100);
			DACR = (0x000<<6);
			Delay(100);
		}
		else if(!(IO1PIN & SW4))
		{	// Sine wave generator
			for(i=0;i<42;i++)
				DACR = sine_wave[i]<<6;
		}
	}
	return 0;
}
	
void Delay(int a)
{
	int i,j;
	for(i=0; i<=a; i++)
		for(j=0; j<=a; j++);
}
