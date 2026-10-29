// 8 digit digit 7 segment Display
#include <LPC214X.H>

void Delay(int);
void Digit(int,int);
	
unsigned char arr[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};

int main(void)
{
		
	int i,j,k,l,m,n,o,p,q;
		
	IODIR0 = 0xFFFF; // 1111 1111 1111 1111 set pin 0.0-0.15 as output pin
	
	while(1)
	{
			for(i=0; i<10; i++) // Ten Millions loop
			{
				for(j=0; j<10; j++) // Millions loop
				{
					for(k=0; k<10; k++) // Hundred Thousands loop
					{
						for(l=0; l<10; l++) // Ten Thousands loop
						{
							for(m=0; m<10; m++) // Thousands loop
							{
								for(n=0; n<10; n++) // Hundreds loop
								{
									for(o=0; o<10; o++) // Tens loop
									{
										for(p=0; p<10; p++) // units loop
										{
											for(q=0; q<1; q++) // refersh display by continuously switching 
											{
												Digit(i,8); //display1
												Digit(j,9); //display2
												Digit(k,10); //display3
												Digit(l,11); //display4
												Digit(m,12); //display5
												Digit(n,13); //display6
												Digit(o,14); //display7
												Digit(p,15); //display8
											}
										}
									}
								}
							}
						}
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

void Digit(int unit, int display)
{
	// first display
	IOSET0 = (0xFF<<8); // 1111 1111 1111 1111 all display is off, bcz CC are active low
												
	IOCLR0 = 0x7F; // clear display pins first
	IOSET0 = arr[unit]; // load value
												
	IOCLR0 = (1<<display); // display on CC active low
	Delay(10);
}

