#include <LPC214X.H>

#define IN1 (1<<0)
#define IN2 (1<<1)
#define EN  (1<<2)

int main(void)
{
	IO0DIR |= IN1 | IN2 | EN;
	while(1)
	{
		// Clock wise direction
		IO0SET |= IN1;
		IO0CLR |= IN2;
		IO0SET |= EN;
	}
	
}