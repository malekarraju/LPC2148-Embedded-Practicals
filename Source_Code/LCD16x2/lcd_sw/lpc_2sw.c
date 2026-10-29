#include <lpc214x.h>

#define RS (1<<8)
#define E (1<<9)
#define SW1 (IO1PIN & (1<<16))
#define SW2 (IO1PIN & (1<<17))

void Lcd_Cmd(char);
void Lcd_Data(char);
void Lcd_Initi();
void Lcd_String(char*);
void Delay(int);

int main(void)
{
	IO0DIR = 0x3FF; // 0011 1111 1111 LCD connection as output'1'
	IO1DIR = (0xC<<16); // 0011 SW1 and SW2 as input'0'
	
	Lcd_Initi();
	
	while(1)
	{
		if(SW1==0)
		{
			Lcd_String("Raju");
			Delay(200);
			Lcd_Cmd(0x01);
		}
		if(SW2==0)
		{
			Lcd_Cmd(0xC0);
			Lcd_String("Malekar");
			Delay(200);
			Lcd_Cmd(0x01);
		}
	}
	
	return 0;
}

void Lcd_String(char* str)
{
	while(*str != '\0')
	{
		Lcd_Data(*str);
		str++;
	}
}
void Lcd_Initi()
{
		/* LCD initi. */
	Lcd_Cmd(0x38); // 8 bit mode, 2 lines, 5x7 Matrix
	Lcd_Cmd(0x0E); // Lcd on, Cursor on 0x0f for Blink
	Lcd_Cmd(0x01); // Clear Screen
	Lcd_Cmd(0x06); // Inc Cursor
	Lcd_Cmd(0x80); // 1st Row, 1st Pos/Col
}

void Lcd_Cmd(char cm)
{
	IO0SET = cm;
	
	IO0CLR = RS; // command mode
	IO0SET = E; // Enable
	Delay(100);
	IO0CLR = E; // Disable
	
	IO0CLR  = cm;
}

void Lcd_Data(char dt)
{
	IO0SET = dt;
	
	IO0SET = RS; // data mode
	IO0SET = E; // Enable
	Delay(100);
	IO0CLR = E; // Disable
	
	IO0CLR  = dt;
}

void Delay(int a)
{
	int i,j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}