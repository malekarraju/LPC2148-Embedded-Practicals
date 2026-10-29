#include <LPC214X.H>

#define RS (1<<8)
#define E  (1<<9)

// Column Output
#define C1 (1<<16)
#define C2 (1<<17)
#define C3 (1<<18)
#define C4 (1<<19)
// Rows Input
#define R1 (1<<20)
#define R2 (1<<21)
#define R3 (1<<22)
#define R4 (1<<23)

void Delay(int);
void Lcd_Cmd(char);
void Lcd_Data(char);
void Lcd_String(const char*);
void Lcd_Inti();
char Keypad(void);

char c;

int main()
{  
	// one time execution PORT Direction
	IODIR0 |= 0x3FF;  //0011 1111 1111
	IO1DIR |= (0xF0<<16); // 1111 0000
	
	//IODIR0 = 0X000003FF; //LCD DATA PINS O/P
	//IODIR1 = 0X00F00000; // ROW-O/P(1) & COL I/P
	
	// LCD intialization
    Lcd_Inti();

    // use because program stuck here
	while(1)
	{
		c=Keypad();
		
		if(c != '\0')
		{
			if(c == 'C')
			{
				Lcd_Cmd(0x01);
			}
			else Lcd_Data(c);
		}
		
	}
	
	return 0;
}

// Function Defination

char Keypad(void)
{
	//ROW1 Scan
	IO1CLR |= R1;
	IO1SET |= R2 | R3 | R4;
	
	if(!(IO1PIN&C1))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C1)); // continue for true
		return '7';
	}
	if(!(IO1PIN&C2))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C2)); // continue for true
		return '8';
	}
	if(!(IO1PIN&C3))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C3)); // continue for true
		return '9';
	}
	if(!(IO1PIN&C4))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C4)); // continue for true
		return '/';
	}
	
		//ROW2 Scan
	IO1CLR |= R2;
	IO1SET |= R1 | R3 | R4;
	
	if(!(IO1PIN&C1))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C1)); // continue for true
		return '4';
	}
	if(!(IO1PIN&C2))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C2)); // continue for true
		return '5';
	}
	if(!(IO1PIN&C3))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C3)); // continue for true
		return '6';
	}
	if(!(IO1PIN&C4))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C4)); // continue for true
		return 'x';
	}
	
		//ROW3 Scan
	IO1CLR |= R3;
	IO1SET |= R1 | R2 | R4;
	
	if(!(IO1PIN&C1))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C1)); // continue for true
		return '1';
	}
	if(!(IO1PIN&C2))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C2)); // continue for true
		return '2';
	}
	if(!(IO1PIN&C3))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C3)); // continue for true
		return '3';
	}
	if(!(IO1PIN&C4))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C4)); // continue for true
		return '-';
	}
	
		//ROW4 Scan
	IO1CLR |= R4;
	IO1SET |= R1 | R2 | R3;
	
	if(!(IO1PIN&C1))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C1)); // continue for true
		return 'C';
	}
	if(!(IO1PIN&C2))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C2)); // continue for true
		return '0';
	}
	if(!(IO1PIN&C3))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C3)); // continue for true
		return '=';
	}
	if(!(IO1PIN&C4))  // initial 1=0; when sw pressed 0=1
	{
		while(!(IO1PIN&C4)); // continue for true
		return '+';
	}
	
	return '\0';
}

void Lcd_Inti()
{	
	/* LCD initi. */
	Lcd_Cmd(0x38); // 8 bit mode, 2 lines, 5x7 Matrix
	Lcd_Cmd(0x0E); // Lcd on, Cursor on 0x0f for Blink
	Lcd_Cmd(0x01); // Clear Screen
	Lcd_Cmd(0x06); // Inc Cursor
	Lcd_Cmd(0x80); // 1st Row, 1st Pos/Col
}

void Lcd_String(const char* str)
{
	while(*str != '\0')
	{
		Lcd_Data(*str);
		str++;
	}
}

void Lcd_Cmd(char cm)
{
	IOSET0|= cm; 
	
	IOCLR0 |= RS;  // Command Mode RS=0
	// IOCLR0 |= RW;  // Write to LCD RW=0, connecting to ground
	IOSET0 |= E;  // E=1
	Delay(300);
	IOCLR0 |= E;   // E= 0;
	
	IOCLR0 |= cm;
}

void Lcd_Data(char dt)
{
	IOSET0 |= dt; 
	
	IOSET0 |= RS;  // Data mode RS=1
	// IOCLR0 |= RW;  // Write to LCD RW=0, connecting to ground
	IOSET0 |= E;  // E=1
	Delay(300);
	IOCLR0 |= E;   // E= 0;.
	
	IOCLR0 |= dt; 
}

void Delay(int a)
{
	int i,j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}

