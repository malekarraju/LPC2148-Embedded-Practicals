
#include <LPC214X.H>

void Delay(int);

int main()
{
	unsigned char arr[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};
	int i;

	IODIR1 |= (0x7F<<16); // LED output 1.16 - 1.22  0111 1111

	while(1)
	{
		for(i=0; i<=9; i++)
		{	
			IOCLR1 = (0x7F<<16);
			IOSET1 = arr[i]<<16;
			Delay(2500);
		}
	}
}

