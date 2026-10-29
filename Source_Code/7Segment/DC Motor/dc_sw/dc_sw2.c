#include <LPC214X.H>

#define IN1 (1<<0)
#define IN2 (1<<1)
#define EN1 (1<<2)
#define EN2 (1<<3)
#define IN3 (1<<4)
#define IN4 (1<<5)

#define SW1 (1<<16)
#define SW2 (1<<17)

int main(void)
{
	IO0DIR |= 0x3F; // 11 1111
	IO1DIR |= (0xC<<16); // 1100
	while(1)
	{
		if((IO1PIN&SW1)==0)
		{
			// Clock wise direction
			IO0SET |= IN1;
			IO0CLR |= IN2;
			IO0SET |= EN1;
	  }
		else IO0CLR |= 0x07; // clear pins to stop motor
		
		if((IO1PIN&SW2)==0)
		{
			// anit clock-wise direction
			IO0CLR |= IN3;
			IO0SET |= IN4;
			IO0SET |= EN2;
	  }
		else IO0CLR |= 0x38; // clear pins to stop motor
	}
}