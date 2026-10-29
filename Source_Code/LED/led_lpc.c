#include <LPC214X.H>

#define LED1 (1<<10)
#define LED2 (1<<11)

void Delay(int);
	
int main()
{
		IODIR0 |= LED1 | LED2;   // config P0.10 & P0.11 as output by seting 1;
	
	while(1)
	{
		IOSET0 |= LED1 | LED2;  // 2 LED ON
		Delay(100);
		
		IO0CLR |= LED1 | LED2;  // 2 LED OFF
		Delay(100);
	}
	
	return 0;
}

void Delay(int x)
{
	int i, j;
		for(i=0; i<x; i++)
			for(j=0; j<x; j++);
}