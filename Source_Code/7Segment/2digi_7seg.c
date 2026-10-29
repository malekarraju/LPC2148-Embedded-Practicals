// Two digit + decimal 7 segment Display
#include <LPC214X.H>

void Delay(int);

int main(void)
{
		unsigned char arr[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};
	int i,j,k;
		
	IODIR0 = 0x3FF; // 0011 1111 1111 set pin 0.0-0.9 as output pin
	
	while(1)
	{
			for(i=0; i<10; i++) // Tens loop
			{
				for(j=0; j<10; j++) // units loop
				{
					for(k=0; k<10; k++) // refersh display by continuously switching 
					{
						
						// second display
						IOSET0 = (1<<8) | (1<<9); // both display is off, bcz CC are active low
						
						IOCLR0 = 0x7F;
						IOSET0 = arr[i];
						
						IOSET0 = (1<<7);  // Decimal off
						IOCLR0 = (1<<8); // display 1 on CC active low
						Delay(40);
						
						// second display
						IOSET0 = (1<<8) | (1<<9); // both display is off, bcz CC are active low
						
						IO0CLR = 0x7F;
						IOSET0 = arr[j];
						
						IOCLR0 = (1<<7); // decimal off
						IOCLR0 = (1<<9); // display 2 on CC active low
						Delay(40);

					}
				}
			}
		
	}
	
	return 0;
}

void Delay(int a)
{
	volatile int i, j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}

