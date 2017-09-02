#include "config_c30.h"					//configuration words - for C30. Use config.h for XC16
#include "gpio.h"
#include "delay.h"						//we use software delays
#include "systick.h"					//we use systick for timing
#include "lcd_3wi.h"					//3-wire lcd interface
#include <string.h>						//only if lcd routines are used
#include <math.h>						//only for benchmarking math routines
//#include "dhry.h"						//dhrystone benchmark

//hardware configuration
#define LED_PORT			PORTB
#define LED_DDR				TRISB
#define LED					(1<<5)
//end hardware configuration

//global defines

//global variables
char vRAM[17];
const char str0[]="24F Benchmark v1";
const char str1[]="tick=           ";
uint32_t tick0, tick1;
uint32_t tmp;

int main(void) {
	mcu_init();							//reset the mcu
	IO_OUT(LED_DDR, LED);				//led as output
	systick_init();						//reset systick
	lcd_init();							//reset the lcd
	strcpy(vRAM, str0); lcd_display(LCD_Line0, vRAM);
	while (1) {
		IO_SET(LED_PORT, LED);			//flip the led -> for external timing
		tick0=ticks();
		//put your code to be benchmarked here
		//empty -> 18 ticks @ O1, 28 ticks @ no optimization
		//PORTB;						//->19 ticks @ O1, 29 ticks @ no optimization
		//tick1=sin(tick0);				//3300 ticks
		//tick1=log(tick0);				//3100 ticks
		//tick1=sqrt(tick0);			//680 ticks
		//tick1=tan(tick0);				//3300 ticks
		//tick1=rand();					//97 ticks
		//tick1=pow(2.0, tick0);		//1200 ticks
		//tick1=floor(tick0);			//210 ticks -> vary with value of argument
		//vRAM[15]=(tmp % 10) + '0'; tmp /= 10;	//955 ticks
		//lcd_display(LCD_Line1, vRAM);	//8k ticks @ 4Mhz F_CPU
		//lcd_write(0,0);
		//strcpy(vRAM, str1);			//51 ticks
		//tmp = tick1;					//32 ticks
		//dhrystone();					//8.3M ticks
		tick1=ticks() - tick0;			//calculate time elapsed
		IO_CLR(LED_PORT, LED);			//for external timing

		//display tick0/1
		tmp = tick1;
		strcpy(vRAM, str1);
		vRAM[15]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[14]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[13]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[12]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[11]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[10]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[ 9]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[ 8]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[ 7]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[ 6]=(tmp % 10) + '0'; tmp /= 10;
		lcd_display(LCD_Line1, vRAM);
	}
}
