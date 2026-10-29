#include <LPC214X.H>

#define LED1 (1<<10)
#define LED2 (1<<11)
#define DELAY_COUNT 300

void Pattern_1(void);
void Pattern_2(void);
void Pattern_3(void);
void Delay(int);
	
int main()
{
		IODIR0 = 0x000003FF;  // config P0.10 & P0.11 as output by seting 1;
	
	while(1)
	{
		Pattern_1();
		Pattern_2();
		Pattern_3();
	}
	
	return 0;
}


void Pattern_1(void)
{
	int i;
	for(i=0; i<10; i++)
	{
		IOSET0 |= (1<<i);
		Delay(DELAY_COUNT);
		
		IOCLR0 |= (1<<i);
		Delay(DELAY_COUNT);
	}
}

void Pattern_2(void)
{
	int i;
	for(i=0; i<10; i++)
	{
		IOSET0 |= (1<<i) | (1<<(i+1));
		Delay(DELAY_COUNT);
		
		IOCLR0 |= (1<<i) | (1<<(i+1));
		Delay(DELAY_COUNT);
	}
}

void Pattern_3(void)
{
	int i;
	for(i=0; i<10; i++)
	{
		IOSET0 |= (1<<i) | (1<<(i+1)) | (1<<(i+2));
		Delay(DELAY_COUNT);
		
		IOCLR0 |= (1<<i) | (1<<(i+1)) | (1<<(i+2));
		Delay(DELAY_COUNT);
	}
}

void Delay(int x)
{
	int i, j;
		for(i=0; i<x; i++)
			for(j=0; j<x; j++);
}