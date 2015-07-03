/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %main.c%
* Instance:         
* %version:         1 %
* %created_by:      uid734106 %
* %date_created:    Thu Jul  2 10:27:43 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : 	This File Describe The Main Purpose Of The Window	  */
/*						Window Lifter Practice	Calling The Functions.		  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 02/07/2015  |                               | Roberto Palos    */
/* Integration under Continuous CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include"GPIO.h"			//Register Mod
#include"pll.h"				//Initialization of HW
#include"PIT.h"				//Periodic Interrupts And Timers
#include"windowlifter.h"	//Window lifter main application

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 :	main
 *  Description          :	Main function. Keeps monitoring the
							up and down buttons until one gets pressed
							and then execute the respective up/down auto/manual
							window.
							doing nothing.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void main(){
	InitHW();	//Include All Functions To Initialize HW
	
	//Infinite Loop
	for(;;){
		while(bup || bdown){
			if(bdown){
				delay(10);
				if(bdown){
					delay(500);
					if(bdown){
						downmanual();
					}
					else{
						autodown();
					}
				}
			}
			else if(bup){
				delay(10);
				if(bup){
					delay(500);
					if(bup){
						upmanual();
					}
					else{
						autoup();
					}
				}
			}
		}
	}
}
