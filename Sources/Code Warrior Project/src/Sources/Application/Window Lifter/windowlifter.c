#include "typedefs.h"
#include"windowlifter.h"	//Window lifter main application
#include"GPIO.h"			//Register Mod
uint8_t led = 10;
unsigned int limitup = 0;
unsigned int limitdown = 0;
extern unsigned int antipinch = 0;

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
		if(led == 1){
			SIU.GPDO[led].R = 1;
			limitdown = 1;
		}
		else{
			SIU.GPDO[led].R = 1;
			led--;
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
		if(antipinch){
			for(led = led; led > 1;){
				SIU.GPDO[led].R = 1;
				led--;
				delay(400);
			}
			limitdown = 1;
		}
		else{
			//Nothing.
		}
		if(led == 1){
			SIU.GPDO[led].R = 1;
			limitdown = 1;
		}
		else{
			SIU.GPDO[led].R = 1;
			led--;
			delay(400);
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
			SIU.GPDO[led].R = 0;
			limitup = 1;
		}
		else{
			SIU.GPDO[led].R = 0;
			led++;
			delay(500);
		}
	}
	if(!limitdown && antipinch)
			autodown();
	if(antipinch){
		antipinch = 0;
		delay(5000);
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
	while(!limitup && !antipinch){
		if(led == 10){
			SIU.GPDO[led].R = 0;
			limitup = 1;
		}
		else{
			if(bapinch || antipinch){
				antipinch = 1;
				autodown();
			}
			else{
				SIU.GPDO[led].R = 0;
				led++;
				delay(500);
			}
		}
	}
	if(!limitdown && antipinch)
			autodown();
	if(antipinch){
		antipinch = 0;
		delay(5000);
	}
	limitdown = 0;
}