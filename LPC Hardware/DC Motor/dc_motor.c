#include <LPC214X.H>

#define IN1 (1<<0)
#define IN2 (1<<1)

#define SW1 (1<<14)
#define SW2 (1<<15)

int main(void)
{
	IO0DIR |= IN1 | IN2; // 11 1111
	IO0DIR &= ~(SW1 | SW2); // 1100
	while(1)
	{
		if((IO0PIN&SW1)==0)
		{
			// Clock wise direction
			IO0SET |= IN1;
			IO0CLR |= IN2;
	  }
		else if((IO0PIN&SW2)==0)
		{
			// anit clock-wise direction
			IO0CLR |= IN1;
			IO0SET |= IN2;
	  }
		else 
		{
			IO0CLR |= (IN1 | IN2); // clear pins to stop motor
		}
	}
}