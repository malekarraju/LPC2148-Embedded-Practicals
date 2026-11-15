#include <LPC214X.H>

#define RS (1<<0)
#define E (1<<1)

void Delay(int);
void Lcd_Cmd(char);
void Lcd_Data(unsigned char);
void Lcd_String(char*);
void Lcd_Inti(void);
void Display(void);
void PLL_Init(void);


int main()
{ 
	PINSEL1 = 0x10000000; // config ADC pin of AD0.3	
	PINSEL0 = 0x00000C00; // config ADC channel AD0.7
	
	IODIR0= 0xFF03;  //1111 1111 0000 0011  for LCD 
	
	PLL_Init(); // PLL initialization 
	
	// LCD intialization
  Lcd_Inti();
	//LCD INIT
	
		Lcd_String("AD03 Value:");
	  Lcd_Cmd(0xC0);
		Lcd_String("AD07 Value:");
	
	while(1)
	{
		AD0CR = 0x01200308; // Configure AD0.3, ADC clock divider = 3, ADC powered on
    while (!(AD0GDR & (1 << 31))); 	// Wait for conversion to complete
		
		Lcd_Cmd(0x8C);
		Delay(10);
    Display(); // Display the ADC result
		Delay(100);
		
		AD0CR = 0x01200380; // Configure AD0.7, ADC clock divider = 3, ADC powered on
    while (!(AD0GDR & (1 << 31))); // Wait for conversion to complete
		
		Lcd_Cmd(0xCC);
		Delay(10);
    Display(); // Display the ADC result
		Delay(100);
	}
	return 0;
}

// Function Defination

void Lcd_Inti()
{	
	 //LCD initi. 
	Lcd_Cmd(0x38); // 8 bit mode, 2 lines, 5x7 Matrix
	Lcd_Cmd(0x0E); // Lcd on, Cursor on 0x0f for Blink
	Lcd_Cmd(0x01); // Clear Screen
	Lcd_Cmd(0x06); // Inc Cursor
	Lcd_Cmd(0x80); // 1st Row, 1st Pos/Col
}

void Lcd_String(char* str)
{
	while(*str != '\0')
	{
		Lcd_Data(*str);
		str++;
	}
}

void Lcd_Cmd(char cm)
{
	IOCLR0 = 0xFF<<8;
	
	IOSET0 = cm<<8;

	
	IOCLR0 |= RS;  // Command Mode RS=0
	IOSET0 |= E;  // E=1
	Delay(10);
	IOCLR0 |= E;   // E= 0;
	Delay(10);
	
	IOCLR0 = 0xFF<<8;
}

void Lcd_Data(unsigned char dt)
{
	IOCLR0 = 0xFF<<8;
	
	IOSET0 = dt<<8;
	
	IOSET0 |= RS;  // data Mode RS=1
	IOSET0 |= E;  // E=1
	Delay(200);
	IOCLR0 |= E;   // E= 0;
	Delay(10);
	
	IOCLR0 = 0xFF<<8;
}

void Delay(int a)
{
	int i,j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}

void Display()
{
	unsigned char a,b,c,d;
	unsigned int val;
	
	val = AD0GDR;
	val = (val>>6) & 0x3FF;
	
	a = val/1000; //1
	b = (val/100)%10; // 0
	c = (val/10)%10; // 2
	d = val % 10; // 3

	Lcd_Data(a+48);
	Lcd_Data(b+48);
	Lcd_Data(c+48);
	Lcd_Data(d+48);
}

void PLL_Init(void)
{
	// To generate 60MHz from 12MHz crystal
	PLL0CON = 0x01; // PLL active but not connect
	PLL0CFG = 0x24; // set PSEL=2  and MSEL=5-1 assume -1
	
	PLL0FEED = 0xAA; 
	PLL0FEED = 0x55;
	
	while(!(PLL0STAT & (1<<10))); // wait for feed 0100 0000 0000
	PLL0CON = 0x03; //1 1 PLL connect
	
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	
	VPBDIV = 0x00; // set PCLK 15Mhz
}
