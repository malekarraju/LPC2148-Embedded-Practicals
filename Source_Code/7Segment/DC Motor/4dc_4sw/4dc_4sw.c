
#include <LPC214X.H>

//MOTOR PINS
#define IN1 (1<<0)
#define IN2 (1<<1)
#define IN3 (1<<2)
#define IN4 (1<<3)
#define IN5 (1<<4)
#define IN6 (1<<5)
#define IN7 (1<<6)
#define IN8 (1<<7)

// SWITCH PINS
#define SW1 (1<<16)
#define SW2 (1<<17)
#define SW3 (1<<18)
#define SW4 (1<<19)

#define ALL_MOTOR_PINS 0xFF


void ALL_CW(void);
void ALL_ACW(void);
void U2_CW(void);
void U2_ACW(void);

int main(void)
{
	IO0DIR |= ALL_MOTOR_PINS; // 1111 1111 output
	IO1DIR &= ~(SW1 | SW2 | SW3 | SW4); //  0000 input
	
	while(1)
	{
		
		if((IO1PIN&SW1)==0)
		{
			ALL_CW();
	  }
		
	  else if((IO1PIN&SW2)==0)
		{
			ALL_ACW();
	  }
		
		else if((IO1PIN&SW3)==0)
		{
			U2_CW();
	  }
		
		else if((IO1PIN&SW4)==0)
		{
			U2_ACW();
	  }
		
		else IO0CLR |= ALL_MOTOR_PINS;
		
	}
}

void ALL_CW(void)
{
	// Clock wise direction
			
			//M1
			IO0SET |= IN1;
			IO0CLR |= IN2;
			//M2
			IO0SET |= IN3;
			IO0CLR |= IN4;
			//M3
			IO0SET |= IN5;
			IO0CLR |= IN6;
			//M4
			IO0SET |= IN7;
			IO0CLR |= IN8;
}

void ALL_ACW(void)
{
	// anit clock-wise direction
	
			//M1
			IO0CLR |= IN1;
			IO0SET |= IN2;
			//M2
			IO0CLR |= IN3;
			IO0SET |= IN4;
			//M3
			IO0CLR |= IN5;
			IO0SET |= IN6;
			//M4
			IO0CLR |= IN7;
			IO0SET |= IN8;
}

void U2_CW(void)
{
	//upper two clock-wise direction
			//M1
			IO0SET |= IN1;
			IO0CLR |= IN2;
			//M2
			IO0SET |= IN3;
			IO0CLR |= IN4;

	//lower two anti clock-wise direction
			
			//M3
			IO0CLR |= IN5;
			IO0SET |= IN6;
			//M4
			IO0CLR |= IN7;
			IO0SET |= IN8;
}

void U2_ACW(void)
{
	//upper two ANTI clock-wise direction
			//M1
			IO0CLR |= IN1;
			IO0SET |= IN2;
			//M2
			IO0CLR |= IN3;
			IO0SET |= IN4;

	//lower two clock-wise direction
			
			//M3
			IO0SET |= IN5;
			IO0CLR |= IN6;
			//M4
			IO0SET |= IN7;
			IO0CLR |= IN8;
}

