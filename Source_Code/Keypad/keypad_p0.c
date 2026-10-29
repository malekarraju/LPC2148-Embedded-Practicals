


#include <LPC214X.H>


#define RS (1<<24)
#define E  (1<<25)


// Keypad Column
#define C1 (1<<0)
#define C2 (1<<1)
#define C3 (1<<2)

// Keypad Row 
#define R1 (1<<3)
#define R2 (1<<4)
#define R3 (1<<5)
#define R4 (1<<6)

void Delay(int);
void Lcd_Cmd(char);
void Lcd_Data(char);
void Lcd_Init(void);
char Keypad(void);

char c;

int main()
{
    
    IO1DIR |= 0x03FF0000;

    IO0DIR |= 0x00000007;
	  

    Lcd_Init();

    while(1)
    {
        c = Keypad();
        Lcd_Data(c);
        Delay(10);
    }
}

void Lcd_Init(void)
{
    Lcd_Cmd(0x38); // 8-bit mode, 2 lines, 5x7 dots
    Delay(5);
    Lcd_Cmd(0x0E); // Display on, cursor blinking
    Delay(5);
    Lcd_Cmd(0x01); // Clear display
    Delay(5);
    Lcd_Cmd(0x06); // Increment cursor
    Delay(5);
    Lcd_Cmd(0x80); // first line of lcd
    Delay(5);
}

void Lcd_Cmd(char cm)
{
   
    IO1SET = (cm << 16);

    IO1CLR = RS;
    IO1SET = E;
    Delay(1);
    IO1CLR = E;
    Delay(2);
	  IO1CLR = 0x00FF0000;
}

void Lcd_Data(char dt)
{
    
    
    IO1SET = (dt << 16);

    IO1SET = RS;
    IO1SET = E;
    Delay(1);
    IO1CLR = E;
    Delay(2);
	  IO1CLR = 0x00FF0000;
}

void Delay(int a)
{
    int i, j;

    for(i = 0; i < 1000; i++)
        for(j = 0; j < a; j++);
}

char Keypad(void)
{
    while(1)
    {
        // COLUMN 1
        IO0SET = C1 | C2 | C3;
        IO0CLR = C1;

        if(!(IO0PIN & R1))
        {
            while(!(IO0PIN & R1));
            return '1';
        }

        if(!(IO0PIN & R2))
        {
            while(!(IO0PIN & R2));
            return '4';
        }

        if(!(IO0PIN & R3))
        {
            while(!(IO0PIN & R3));
            return '7';
        }

        if(!(IO0PIN & R4))
        {
            while(!(IO0PIN & R4));
            return '*';
        }

        // COLUMN 2
        IO0SET = C1 | C2 | C3;
        IO0CLR = C2;

        if(!(IO0PIN & R1))
        {
            while(!(IO0PIN & R1));
            return '2';
        }

        if(!(IO0PIN & R2))
        {
            while(!(IO0PIN & R2));
            return '5';
        }

        if(!(IO0PIN & R3))
        {
            while(!(IO0PIN & R3));
            return '8';
        }

        if(!(IO0PIN & R4))
        {
            while(!(IO0PIN & R4));
            return '0';
        }

        // COLUMN 3
        IO0SET = C1 | C2 | C3;
        IO0CLR = C3;

        if(!(IO0PIN & R1))
        {
            while(!(IO0PIN & R1));
            return '3';
        }

        if(!(IO0PIN & R2))
        {
            while(!(IO0PIN & R2));
            return '6';
        }

        if(!(IO0PIN & R3))
        {
            while(!(IO0PIN & R3));
            return '9';
        }

        if(!(IO0PIN & R4))
        {
            while(!(IO0PIN & R4));
            return '#';
        }
    }
}





/*

// doubt ROWS and COLUMN as an input

#include <LPC214X.H>

#define RS (1<<24)
#define E  (1<<25)

// Column Output
#define C1 (1<<0)
#define C2 (1<<1)
#define C3 (1<<2)
#define C4 (1<<3)
// Rows Input
#define R1 (1<<4)
#define R2 (1<<5)
#define R3 (1<<6)
#define R4 (1<<7)

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
	IODIR0 |= (0x0F); // 1111 0000
	IO1DIR |= (0x3FF<<16);  //0011 1111 1111
	
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
	// LCD initi. //
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

*/