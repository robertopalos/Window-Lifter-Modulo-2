/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %main.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      uid734106 %
* %date_created:    Wed Jul  1 15:05:00 2015 %
*=============================================================================*/
/* DESCRIPTION : Main C Code For Window Lifter                                */
/*============================================================================*/
/* FUNCTION COMMENT : This file call the functions and prototypes in different*/
/* sources.					                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#ifndef _Window_H        /*prevent duplicated includes*/
#define _Window_H
#include "typedefs.h"
#endif /* _Window_H */
#define 	pinch 64
#define 	up 65
#define 	down 66
#define		bdown	SIU.GPDI[down].R == 0
#define		bup		SIU.GPDI[up].R == 0
#define		bapinch	SIU.GPDI[pinch].R == 0

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
uint8_t led = 10;
unsigned int limitup = 0;
unsigned int limitdown = 0;
unsigned int antipinch = 0;

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */
static void InitHW(void);
static void InitSysclk(void);
static void InitModesAndClks(void);
static void InitPeriClkGen(void);
static void InitGPIO(void);
static void DisableWatchdog(void);
void InitLeds(void);
void NoInitLeds(void);
static void initTimer(void);
void downmanual(void);
void autodown(void);
void upmanual(void);
void autoup(void);


/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : InitHW
 *  Description          :	Initialization of the hardware.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
static void InitHW(void){
	DisableWatchdog();
	InitModesAndClks();
	initTimer();
	InitSysclk();
	InitGPIO();
	InitLeds();
}
/**************************************************************
 *  Name                 :	InitLeds
 *  Description          :	On all leds for the simulation (window closed).
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
 void InitLeds(void){
	unsigned int a;
	for(a = 0; a < 12; a++){
		SIU.GPDO[a].R = 1;
	}
}
/**************************************************************
 *  Name                 :	NoInitLeds
 *  Description          :	Off all leds for the simulation (window open).
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
 void NoInitLeds(void){
	unsigned int a;
	for(a = 0; a < 12; a++){
		SIU.GPDO[a].R = 0;
	}
}
/**************************************************************
 *  Name                 :	InitSysclk
 *  Description          :	Initialize Fsys 40 Mhz PLL with 8 Mhz crystal.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
 static void InitSysclk(void){
	InitModesAndClks();
	InitPeriClkGen();
}
/**************************************************************
 *  Name                 :	InitModesAndClks
 *  Description          :	DRUN -> RUN0	enable CLKOUT
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
 static void InitModesAndClks(void){
	/* Enter RUN0 with PLL as sys clk (64 MHz) with 8 MHz crystal reference. */								
	ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */								
	CGM.FMPLL_CR.R = 0x01200100;    /* 8MHz xtal: Set PLL0 to 64 MHz */								
	ME.RUNPC[0].R = 0x000000FE; /* enable peripherals run in all modes */								
	ME.RUN[0].R = 0x001F0074;       /* RUN0 cfg: IRCON,OSC0ON,PLL0ON,syclk=PLL */								
	/* Mode Transition to enter RUN0 mode: */								
	ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */								
	ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */								
	while (ME.GS.B.S_MTRANS) {} ;    /* Wait for mode transition to complete */								
	while(ME.GS.B.S_CURRENTMODE != 4) {}; /* Verify RUN0 is the current mode */																
	/* enable CLKOUT on PA0 */
	/* AF2 - PCR[0] - PA = 0b10 */
	SIU.PCR[0].R = 0x0A00;
	/* set CLKOUT divider of 4 */
	CGM.OCDS_SC.R = 0x22000000; /* div by 4, system FMPLL */ 
	CGM.OC_EN.B.EN = 1; 		/* enable CLKOUT signal */
}
/**************************************************************
 *  Name                 :	InitPeriClkGen
 *  Description          :	Enable auxiliary clock 0-3 from PLL0
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
 static void InitPeriClkGen(void){
	CGM.SC_DC[0].R = 0x80;  /* MPC56xxB: peri set 1 */
	CGM.SC_DC[1].R = 0x80;  /* MPC56xxB: peri set 2 */
	CGM.SC_DC[2].R = 0x80;  /* MPC56xxB: peri set 3 */    
}
/**************************************************************
 *  Name                 :	InitGPIO
 *  Description          :	Initialize outputs for leds and inputs
							for push-buttons
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
 static void InitGPIO(void){
	volatile counter = 0;
	for(counter = 0; counter < 12 ; counter++){
		SIU.GPDO[counter].R = 0;
		SIU.PCR[counter].R = 0x0200;
	}
	for(counter = 0; counter < 3 ; counter++){
		SIU.GPDI[counter + 64].R = 1;
		SIU.PCR[counter + 64].R = 0x0103;
	}
}
/**************************************************************
 *  Name                 :	InitTimer
 *  Description          :	Initialization fo timer for the use
							of delay function
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
 void initTimer(void){
	STM.CR.R=0x00003F01;
	STM.CH[0].CCR.R=1;
	STM.CNT.R=0;
}
/**************************************************************
 *  Name                 :	delay
 *  Description          :	Function that keeps the microcontroller
							in use for "x" * user input time in ms
 *  Parameters           :  (vuint32_t tiempo)
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
 void delay(vuint32_t tiempo){
	STM.CNT.R=0;
	while(STM.CNT.R<tiempo*1000){
	}
}
/**************************************************************
 *  Name                 :	DisableWatchdog
 *  Description          :	Disable watchdog for no reboots when
							microcontroller enter in an infinite loop
							doing nothing.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
static void DisableWatchdog(void){
	SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
	SWT.SR.R = 0x0000d928;
	SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}
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
			led--;
			SIU.GPDO[led].R = 0;
			delay(500);	
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
	InitHW();
	while(1){
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
/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/

