#include "stdbool.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "Stopwatch.h"

void oneShotConfigure(void){
	
	SYSCTL_RCGCTIMER_R |= 0x01;
    TIMER0_CTL_R = 0x0;
    TIMER0_CFG_R = 0x4; 
    TIMER0_TAMR_R = 0x11;
    TIMER0_TAPR_R |= 0xF4;
    TIMER0_TAILR_R = 0xffff;                     
}
	
void enableTimer(){
	TIMER0_CTL_R |= 0x03;
	return;
	
}

void disableTimer(){
	TIMER0_CTL_R &= ~(0x01);
	return;
}


bool getOvrFlwFlg(){
	if((TIMER0_RIS_R & 0x1) != 0){
		TIMER0_ICR_R = 0x1;
		return true;
	}
	else
		return false;

}

void displayTime(int sec, int min, int hour){
	if(hour != 0){
		LCD_Int(hour);
		LCD_data(':');
	}
	
	if(min != 0){
		LCD_Int(min);
		LCD_data(':');
	}
	
	LCD_Int(sec);
}

void displaySecFractions(){
	
	// val of current timer with prescaler
	unsigned int Val = TIMER0_TAV_R;
	double x = 0;
	int y = 0;
	
	// val / 244(prescaler) * 65535(max value of 16 bit timer)
	x = (Val / 15990540.0);
	LCD_data('.');
	
	// taking only 5 decimal points to display on lcd
	y = (int)(x * 100000);
	LCD_Int(y);
}

void BlinkLed (void){
	for(int i = 0; i < 10; ++i) {
    	GPIO_PORTF_DATA_R ^= 0x2;
		SysTick_Wait1ms(500);
    }
}
