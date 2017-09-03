//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

//#include "msp.h"
#include "gpio.h"					//we use gpio
#include "delay.h"					//we use software delay
#include "systick.h"				//we use systick
#include "coretick.h"				//we use coretick - as an alternative to systick
#include "dhry.h"					//we use dhrystone benchmark

//hardware configuration
//end hardware configuration

//global defines

//global variables
uint32_t tick0, tick1;

void main(void){

	mcu_init();									//reset the mcu
    systick_init();								//initialize systick
    coretick_init();							//reset coretick

    IO_OUT(LED_DDR, LED);						//led as output

    ei();
    while (1) {
    	IO_SET(LED_PORT, LED);					//set led
    	tick0=ticks();							//time stamp time0
    	//put your code to be benchmarked here
    	//empty -> 84 systicks / 32coreticks
    	//delayms(10);							//30684 systicks @ 3Mhz -> 30600 systicks net; 30620 coreticks -> 30588 coreticks net
    	//LED_PORT;								//97 systicks gross -> 13 systicks net; 41 coreticks gross -> 9 coreticks net
    	dhrystone();							//26.9M systicks; 26.9M coreticks
    	tick1=ticks() - tick0;					//calculate time elapsed
    	IO_CLR(LED_PORT, LED);					//clear led
    }
}
