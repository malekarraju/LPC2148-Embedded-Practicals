
#include <LPC214X.H>

void Delay(int);

int main()
{
	unsigned char arr[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};
	int i;

	IODIR0 = 0x7F; // LED output 0.0 - 0.06

	while(1)
	{
		for(i=0; i<=9; i++)
		{	
			IOCLR0 = 0x7F;
			IOSET0 = arr[i];
			Delay(200);
		}
	}
}

void Delay(int a)
{
	int i, j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}



/*
#include <LPC214X.H>
void delay (void);

int main()
{ 
	int arr[] = { 0x0000003f,0x00000006,0x0000005b,0x0000004f ,0x00000066,0x0000006d,0x0000007d,0x00000007,0x0000007f,0x0000006f };
	int i,j;
	
IODIR0 = 0x000003FF;
	
	while(1)
	{
		for(i=0;i<=9;i++)
		{
			IOSET0 = arr[i];
			delay();
			IOCLR0 = 0x000003ff;

		
		}	
	}
}

void delay (void)
{
	int i,j;
	for(i=0;i<50;i++)
	 for(j=0;j<1000;j++);
}
*/
