/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %main.c%
* Instance:         
* %version:         1 %
* %created_by:      uid734106 %
* %date_created:    Thu Jul  2 10:28:43 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : 	This file calls for the actions to be implement		  */
/*                      this include automatic, manual and antipinch functions*/
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 02/07/2015  |                               | Roberto Palos    */
/* Integration under Continuous CM                                            */
/*============================================================================*/
/* Includes */
/* -------- */
#include "typedefs.h"
#include"windowlifter.h"	//Window lifter main application
#include"GPIO.h"			//Register Mod

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
uint8_t led = 10;
unsigned int limitup = 1;
unsigned int limitdown = 0, antipinch = 0;

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
	SIU.GPDO[0].R = 0;
	while(b_down && !limitdown){
		SIU.GPDO[led].R = 1;
		led--;
		delay(400);
		if(!led){
			limitdown = 1;
			led++;
		}
	}
	limitup = 0;
	SIU.GPDO[0].R = 1;
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
	SIU.GPDO[11].R = 0;
	while(b_up && !limitup){
		
		SIU.GPDO[led].R = 0;
		led++;
		delay(400);
		if(led == 11){
			limitup = 1;
			led--;
		}
	}
	limitdown = 0;
	SIU.GPDO[11].R = 1;
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
	SIU.GPDO[0].R = 0;
	while(!limitdown){
		SIU.GPDO[led].R = 1;
		led--;
		delay(400);
		if(!led){
			limitdown = 1;
			led++;
		}
	}
	limitup = 0;
	SIU.GPDO[0].R = 1;
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
	SIU.GPDO[11].R = 0;
	while(!limitup){
		SIU.GPDO[led].R = 0;
		led++;
		delay(400);
		if(led == 11){
			limitup = 1;
			led--;
		}
	}
	limitdown = 0;
	SIU.GPDO[11].R = 1;
}

void pinchup(void){
	
}