//LCD 4-bit Mode
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
	// one time execution PORT Direction
	IODIR0= (0x3F<<4);  //0011 1111 0000
	
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
	/* LCD initi. in 4-bit Mode*/
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
	
	temp = (cm&0xF0); // Higher Nibbel 
	
	IOSET0|= temp;
	
	IOCLR0 |= RS; // Command Mode RS=0
	IOSET0 |= E;  // E=1
	Delay(300);
	IOCLR0 |= E;  // E= 0;
	
	IOCLR0 |= temp;
	
		
	temp= (cm&0x0F)<<4; // Lower Nibbel 
	
	IOSET0|= temp;
	
	IOSET0 |= E; // E=1
	Delay(300);
	IOCLR0 |= E; // E= 0;
	
	IOCLR0 |= temp;
}

void Lcd_Data(char dt)
{
	char temp=dt;
	
	// Higher Nibbel 
	IOSET0|= (temp&0xF0);
	
	IOSET0 |= RS;  // Data Mode RS=1
	
	IOSET0 |= E;  // E=1
	Delay(300);
	IOCLR0 |= E;   // E= 0;
	
	IOCLR0 |= (temp&0xF0);
	
		// Lower Nibbel 
	IOSET0|= (temp&0x0F)<<4;
	
	IOSET0 |= E;  // E=1
	Delay(300);
	IOCLR0 |= E;   // E= 0;
	
	IOCLR0 |= (temp&0x0F)<<4;
}

void Delay(int a)
{
	int i,j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}

