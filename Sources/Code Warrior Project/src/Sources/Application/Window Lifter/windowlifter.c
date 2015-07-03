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
//#include "stdtypedef.h"
#include"windowlifter.h"	//Window lifter main application
#include"GPIO.h"			//Register Mod

#define green 0
#define blue 11
#define transition 400
/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
T_UBYTE rub_ledposition = 10;
T_UBYTE rub_limitup = 1;
T_UBYTE rub_limitdown = 0, antipinch = 0;

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
	SIU.GPDO[green].R = 0;
	while(b_down && !rub_limitdown){
		SIU.GPDO[rub_ledposition].R = 1;
		rub_ledposition--;
		delay(transition);
		if(!rub_ledposition){
			rub_limitdown = 1;
			rub_ledposition++;
		}
	}
	rub_limitup = 0;
	SIU.GPDO[green].R = 1;
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
	SIU.GPDO[blue].R = 0;
	while(b_up && !rub_limitup){
		
		SIU.GPDO[rub_ledposition].R = 0;
		rub_ledposition++;
		delay(transition);
		if(rub_ledposition == 11){
			rub_limitup = 1;
			rub_ledposition--;
		}
	}
	rub_limitdown = 0;
	SIU.GPDO[blue].R = 1;
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
	SIU.GPDO[green].R = 0;
	while(!rub_limitdown){
		SIU.GPDO[rub_ledposition].R = 1;
		rub_ledposition--;
		delay(transition);
		if(!rub_ledposition){
			rub_limitdown = 1;
			rub_ledposition++;
		}
	}
	rub_limitup = 0;
	SIU.GPDO[green].R = 1;
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
	SIU.GPDO[blue].R = 0;
	while(!rub_limitup){
		SIU.GPDO[rub_ledposition].R = 0;
		rub_ledposition++;
		delay(transition);
		if(rub_ledposition == 11){
			rub_limitup = 1;
			rub_ledposition--;
		}
	}
	rub_limitdown = 0;
	SIU.GPDO[blue].R = 1;
}

void pinchup(void){
	
}