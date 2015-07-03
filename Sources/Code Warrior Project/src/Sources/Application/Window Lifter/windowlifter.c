#include "typedefs.h"
#include"windowlifter.h"	//Window lifter main application
#include"GPIO.h"			//Register Mod
uint8_t led = 10;
unsigned int limitup = 0;
unsigned int limitdown = 0;
unsigned int antipinch = 0;

/**************************************************************
 *  Name                 :	downmanual
 *  Description          :	Function that keeps pulling down the window
							while the push buttons keeps pressed.
							doing nothing.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void downmanual(void){
	while(bdown && !limitdown){
		if(led == 0){
			limitdown = 1;
		}
		else{
			led--;
			SIU.GPDO[led].R = 0;
			delay(500);	
		}
	}
	limitup = 0;
}
/**************************************************************
 *  Name                 :	autodown
 *  Description          :	Function that pull down the window tills
							gets all open.
							doing nothing.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void autodown(void){
	while(!limitdown){
		if(led == 0){
			limitdown = 1;
			if(antipinch){
				delay(5000);
				antipinch = 0;
			}
		}
		else{
			delay(400);
			SIU.GPDO[led].R = 0;
			led--;
		}
	}
	limitup = 0;
}
/**************************************************************
 *  Name                 :	upmanual
 *  Description          :	Function that push up the window while
							the push button keeps pressed.
							doing nothing.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void upmanual(void){
	if(bapinch){
		delay(10);
		if(bapinch){
			antipinch = 1;
			autodown();
		}
	}
	while(bup && !limitup){
		if(led == 10){
			limitup = 1;
		}
		else{
			led++;
			SIU.GPDO[led].R = 1;
			delay(500);
		}
	}
	limitdown = 0;
}
/**************************************************************
 *  Name                 :	autoup
 *  Description          :	Function that push up the window till
							gets fully closed.
							doing nothing.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void autoup(void){
	while(!limitup){
		if(led == 10){
			limitup = 1;
		}
		else{
			if(bapinch){
				antipinch = 1;
				autodown();
			}else{
				led++;
				SIU.GPDO[led].R = 1;
				delay(500);
			}
		}
	}
	limitdown = 0;
}