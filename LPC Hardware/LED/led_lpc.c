#include <LPC214X.H>

#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)

void Delay(int);
	
int main()
{
		IODIR0 |= LED1 | LED2 | LED3;   // config P0.10 & P0.11 as output by seting 1;
	
	while(1)
	{
		IOCLR0 |= LED1;  // 1 LED ON Hardware config. SET off CLR on
		Delay(1000);
		
		IO0SET |= LED1;  // 2 LED OFF
		Delay(1000);
		
		IOCLR0 |= LED2;  // 2 LED ON
		Delay(1000);
		
		IO0SET |= LED2;  // 2 LED OFF
		Delay(1000);
		
		IOCLR0 |= LED3;  // 3 LED ON
		Delay(1000);
		
		IO0SET |= LED3;  // 3 LED OFF
		Delay(1000);
	}
	
	return 0;
}

void Delay(int x)
{
	int i, j;
		for(i=0; i<x; i++)
			for(j=0; j<x; j++);
}