#include <LPC21xx.H>
#define rs 1<<17
#define rw 1<<18
#define en 1<<19


void delay(int a){
	int i,j;
	for(i=0;i<128;i++){
		for(j=0;j<a;j++);
	}
}


void lcdcom1(int c){
	int temp;
	
		IOCLR1=rs;
		IOCLR1=rw;
		IOSET1=en;
	temp=(c&0xf0)<<16;		//we get 1st nibble
	IOSET1=IOSET1|temp;
	delay(10);
	IOCLR1=en;
		IOCLR1=temp;


		IOCLR1=rs;
			IOCLR1=rw;
		IOSET1=en;
		temp=(c&0x0f)<<20;
	//temp=temp<<4;
	IOSET1=IOSET1|temp;	//we get 2nd nibble
	delay(10);
	IOCLR1=en;
		IOCLR1=temp;
}


void lcddata(char cd){
	int temp;
	
		IOSET1=rs;
		IOCLR1=rw;
		IOSET1=en;
	temp=(cd&0xf0)<<16;		//we get 1st nibble
	IOSET1=IOSET1|temp;
	delay(10);
	IOCLR1=en;
		IOCLR1=temp;
	
		IOSET1=rs;
			IOCLR1=rw;
		IOSET1=en;
		temp=(cd&0x0f)<<20;
	//temp=temp<<4;
	IOSET1=IOSET1|temp;	//we get 2nd nibble
	delay(10);
	IOCLR1=en;
		IOCLR1=temp;


}
void msg(char *st){
	while(*st!='\0'){
		lcddata(*st);
		st++;
	}
	delay(100);
}


int main(){
	IO1DIR  = 0x00FE0000; 
	 
	lcdcom1(0x02);	// 4 bit mode 
	delay(100);
	lcdcom1(0x28);	// 4 bit mode 5x7 Matrix/pixel
	delay(100);
	lcdcom1(0x0f);
	delay(100);
	lcdcom1(0x01);
	delay(100);
		lcdcom1(0x06);
		lcdcom1(0x0c);
	
		while(1){
					lcdcom1(0x80);
	msg("ARJUN BHOSALE");
				lcdcom1(0xc0);
			msg("  LPC2148  ");
	delay(100);	
		}
}