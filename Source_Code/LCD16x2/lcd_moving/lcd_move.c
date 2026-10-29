#include <LPC214X.H>

#define RS (1<<8)
#define E (1<<9)

void Delay(int);
void Lcd_Cmd(char);
void Lcd_Data(char);
void Lcd_String(const char*);
void Lcd_Inti();


int main()
{  
	int i;
	// one time execution PORT Direction
	IODIR0= 0x3FF;  //0011 1111 1111
	
	// LCD intialization
    Lcd_Inti();

    // use because program stuck here
	while(1)
	{
		Lcd_String("LPC2148");
		for(i=0; i>=0; i++)
		{
			Lcd_Cmd(0x1c);
		}
	}
	
	return 0;
}

// Function Defination

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

