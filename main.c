#include "tm4c123gh6pm.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "KeyPad.h"
#include "Port_INIT.h"
#include "Systick_Timer.h"
#include "LCD.h"
#include "StopWatch.h"



int main()
{
	// lcd data
	PORTB_init();
	// lcd control pc4-5 en,rs
	PORTC_init();
	// sw1, sw2
	PORTF_init();
	
	// for lcd functions
	Configure_SysTick();
	
	// for stopwatch
	oneShotConfigure();
	LCD_start();
	int sec = 0;
	int min = 0;
	int hour = 0;
	while(1){
		
		//sw1 starts, sw2 stops
		unsigned int sw1 = GPIO_PORTF_DATA_R & 0x10;
		unsigned int sw2 = GPIO_PORTF_DATA_R & 0x01;
		if(!sw1){
			while(1){		
				LCD_clear();
				displayTime(sec, min, hour);
				enableTimer();
				bool stopped = false;
				while(getOvrFlwFlg() == false){
					sw2 = GPIO_PORTF_DATA_R & 0x01;
					if(!sw2){
						disableTimer();
						displaySecFractions();
						stopped = true;
						break;
					}
				}
				if(stopped)
					break;
				
				if((++sec) == 60) {
					sec = 0;
					if((++min) == 60){
						min = 0;
						hour++;
					}
				}
			}
		}	
	}
}