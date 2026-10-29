// not working , printing 8 only
// comman anode
#include <LPC214X.H>

void Delay(int);

int main()
{
	unsigned char arr[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90}; // common anode
	int i;


	IODIR1 |= (0x7F<<16); // 7seg output 0.0 - 0.06 0111 1111

	while(1)
	{
		for(i=0; i<=9; i++)
		{	
			IOSET1 |= (arr[i]<<16);
			Delay(200);
			IOCLR1 |= (0x7F<<16);
		}
	}
}

void Delay(int a)
{
	int i, j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}
