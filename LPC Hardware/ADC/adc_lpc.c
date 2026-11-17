#include <LPC214X.H>

void lcd_data(char);
void lcd_com(char);
void lcd_str(char *);
void Delay(int);
void init(void);
void initPLL(void);
void display(void);

#define rs (1<<17)
#define rw (1<<18)
#define e (1<<19)

int main()
{
	// Configure P0.29 as AD0.2
	PINSEL1 = 0X04000000;
	IODIR1 = 0x00ff0000;
	
	//initPLL();
  init();

    lcd_str("ADC VALUE:");

    while(1)
    {
        // Select AD0.1, power up ADC, start conversion
        AD0CR = 0x01200304;
 
        // Wait for ADC conversion to complete
        while ((AD0GDR & (1 << 31)) == 0);

        display();

        Delay(100);
    }

    return 0;
}

/*void initPLL(void)
{
    PLL0CON = 0x01;
    PLL0CFG = 0x24;

    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    while ((PLL0STAT & (1 << 10)) == 0);

    PLL0CON = 0x03;

    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    VPBDIV = 0x00;   // PCLK = CCLK
}*/

void display(void)
{
	int temp, i;
	int data[4];
	
  temp = (AD0GDR >> 6) & 0x3FF;
	lcd_com(0xc0);
  for(i=0 ; i<4 ;i++)
	{
		data[i]=temp%10+'0';
		temp = temp/10;
	}
	for(i=3 ; i>=0 ; i--)
		lcd_data(data[i]);
}


void lcd_str(char *str)
{
	while(*str !='\0')
	{
		lcd_data(*str);
		str++;
	}
}

void init(void)
{
	lcd_com(0x02);      // 4-bit mode
  lcd_com(0x28);      // 2 lines, 5x7 matrix
	lcd_com(0x0e); 			//lcd on , cursor on
	lcd_com(0x01); 			//clear screen
	Delay(10);
	lcd_com(0x06); 			//inc cursor
	lcd_com(0x80);      // 1st row, 1st position
}

void lcd_com(char cm)
{
	char temp;
  // Higher nibble
  temp = cm & 0xF0;
	IOCLR1 |= rs;
	IOSET1 |= temp<<16;
	IOCLR1 |= rw;
	IOSET1 |= e;
	Delay(5);
	IOCLR1 |= e;
	IOCLR1 = temp<<16;
	
	 // Lower nibble
  temp = (cm & 0x0F) << 4;
	IOCLR1 |= rs;
	IOSET1 |= temp<<16;
	IOCLR1 |= rw;
	IOSET1 |= e;
	Delay(5);
	IOCLR1 |= e;
	IOCLR1 = temp<<16;
}

void lcd_data(char dt)
{
	char temp;
  // Higher nibble
  temp = dt & 0xF0;
	IOSET1 |= rs;
	IOSET1 |= temp<<16;
	IOCLR1 |= rw;
	IOSET1 |= e;
	Delay(200);
	IOCLR1 |= e;
	Delay(5);
	IOCLR1 = temp<<16;
	
	 // Lower nibble
  temp = (dt & 0x0F) << 4;
	IOSET1 |= rs;
	IOSET1 |= temp<<16;
	IOCLR1 |= rw;
	IOSET1 |= e;
	Delay(200);
	IOCLR1 |= e;
	Delay(5);
	IOCLR1 = temp<<16;
}

void Delay(int a)
{
	int i, j;
	for(i=0; i<a; i++)
		for(j=0; j<a; j++);
}