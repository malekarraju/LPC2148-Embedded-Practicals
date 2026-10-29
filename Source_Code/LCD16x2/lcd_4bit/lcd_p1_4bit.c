#include <lpc214x.h>

#define RS (1<<17)
#define RW (1<<18)
#define E (1<<19)

void Delay(int);
void Lcd_Cmd(char);
void Lcd_Data(char);
void Lcd_String(const char*);
void Lcd_Inti();

int main(void)
{
	// one time execution PORT Direction
	IO1DIR = (0x7F<<17); // 0111 1111
	
	// LCD intialization
    Lcd_Inti();
	
	    // use to continuously run programhere
	while(1)
	{
		Lcd_String("LPC2148: RAJU");
		Delay(1000);
		Lcd_Cmd(0x01);  //clear screen
	}
}

// Function Defination

void Lcd_Inti()
{	
	// LCD initi. in 4-bit Mode
	Lcd_Cmd(0x02); 
	Lcd_Cmd(0x28); // 8 bit mode, 2 lines, 5x7 Matrix
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
	char temp;
	temp=(cm&0xF0); // Extrtact Higher nibbel
	
	IO1SET |= temp<<16;
	
	IO1CLR |= RS; // RS=0 Command Mode
	IO1CLR |= RW; // RW=0 write mode 
	
	IO1SET |= E;  // E=1 enable
	Delay(100);
	IO1CLR |= E;  // E=0 disable
	
	IO1CLR |= temp<<16; // clr sent data
	
	temp |= (cm&0x0F); // Extrtact Lower nibbel
	IO1SET |= temp<<20;
	
	IO1SET |= E;  // E=1 enable
	Delay(100);
	IO1CLR |= E;  // E=0 disable
	
	IO1CLR |= temp<<20; // clr sent data
}

void Lcd_Data(char dt)
{
	char temp;
	temp=(dt&0xF0); // Extrtact Higher nibbel
	
	IO1SET |= temp<<16;
	IO1SET |= RS; // RS=1 Data Mode
	IO1CLR |= RW; // RW=0 write mode 
	
	IO1SET |= E;  // E=1 enable
	Delay(100);
	IO1CLR |= E;  // E=0 disable
	
	IO1CLR |= temp<<16; // clr sent data
	
	temp |= (dt&0x0F);
	IO1SET |= temp<<20;
	
	IO1SET |= E;  // E=1 enable
	Delay(100);
	IO1CLR |= E;  // E=0 disable
	
	IO1CLR |= temp<<20; // clr sent data
}

void Delay(int a)
{
	int i,j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}













/*

//LCD 4-bit Mode
#include <LPC214X.H>

#define RS (1<<17)
#define RW (1<<18)
#define E (1<<19)

void Delay(int);
void Lcd_Cmd(char);
void Lcd_Data(char);
void Lcd_String(const char*);
void Lcd_Inti();


int main()
{  
	// one time execution PORT Direction
	IODIR1 = (0x7F<<17);  // 0111 1 111 IODIR1 = 0x00ff0000; 
	
	// LCD intialization
    Lcd_Inti();

    // use because program stuck here
	while(1)
	{
		Lcd_String("LPC2148: RAJU");
		Delay(1000);
		Lcd_Cmd(0x01);  //clear screen
	}
	
	return 0;
}

// Function Defination

void Lcd_Inti()
{	
	LCD initi. in 4-bit Mode
	Lcd_Cmd(0x02); 
	Lcd_Cmd(0x28); // 8 bit mode, 2 lines, 5x7 Matrix
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
	unsigned long temp;
	
	temp = (cm&0xF0)<<16; // Higher Nibbel 0x20
	
	IOSET1 |= temp;
	
	IOCLR1 |= RS; // Command Mode RS=0
	IOSET1 |= E;  // E=1
	Delay(300);
	IOCLR1 |= E;  // E= 0;
	
	IOCLR1 |= temp;
	
		
	temp= (cm&0x0F)<<4; // Lower Nibbel 
	
	IOSET1 |= temp<<16;
	
	IOSET1 |= E; // E=1
	Delay(300);
	IOCLR1 |= E; // E= 0;
	
	IOCLR1 |= temp<<16;
}

void Lcd_Data(char dt)
{
	unsigned long temp=dt;
	
	temp = (dt&0xF0)<<16; // Higher Nibbel 0x20// Higher Nibbel 
	IOSET1 |= temp;
	
	IOSET1 |= RS;  // Data Mode RS=1
	
	IOSET1 |= E;  // E=1
	Delay(300);
	IOCLR1 |= E;   // E= 0;
	
	IOCLR1 |= temp;
	
	temp= (dt&0x0F)<<4; 	// Lower Nibbel 
	IOSET1 |= temp<<16;
	
	IOSET1 |= E;  // E=1
	Delay(300);
	IOCLR1 |= E;   // E= 0;
	
	IOCLR1 |= temp<<16;
}

void Delay(int a)
{
	int i,j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}

*/