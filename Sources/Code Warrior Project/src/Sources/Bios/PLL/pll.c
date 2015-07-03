/* MCU-specific derivative */
#include "MCU_derivative.h" 
/* Data types */
#include "typedefs.h"
/**************************************************************
 *  Name                 :	DisableWatchdog
 *  Description          :	Disable watchdog for no reboots when
							microcontroller enter in an infinite loop
							doing nothing.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void DisableWatchdog(void){
	SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
	SWT.SR.R = 0x0000d928;
	SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}
/**************************************************************
 *  Name                 :	InitTimer
 *  Description          :	Initialization fo timer for the use
							of delay function
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void InitTimer(void){
	STM.CR.R=0x00003F01;
	STM.CH[0].CCR.R=1;
	STM.CNT.R=0;
}
/**************************************************************
 *  Name                 :	InitModesAndClks
 *  Description          :	DRUN -> RUN0	enable CLKOUT
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void InitModesAndClock(void){
	ME.MER.R = 0x0000001D;          	/* Enable DRUN, RUN0, SAFE, RESET modes */
										/* Initialize PLL before turning it on: */
	CGM.FMPLL_CR.R = 0x02400100;    	/* 8 MHz xtal: Set PLL0 to 64 MHz */   
	ME.RUN[0].R = 0x001F0074;       	/* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */
	ME.RUNPC[1].R = 0x00000010; 		/* Peri. Cfg. 1 settings: only run in RUN0 mode */	
	ME.PCTL[92].R = 0x01;           	/* PIT, RTI: select ME_RUN_PC[1] */
	ME.PCTL[68].R = 0x01;				/* SIUL */
	/* Mode Transition to enter RUN0 mode: */
	ME.MCTL.R = 0x40005AF0;         	/* Enter RUN0 Mode & Key */
	ME.MCTL.R = 0x4000A50F;         	/* Enter RUN0 Mode & Inverted Key */  
	while (ME.GS.B.S_MTRANS){}     	/* Wait for mode transition to complete */
	/* Note: could wait here using timer and/or I_TC IRQ */
	while(ME.GS.B.S_CURRENTMODE != 4){;}/* Verify RUN0 is the current mode */
}
/**************************************************************
 *  Name                 :	InitPeriClkGen
 *  Description          :	Enable auxiliary clock 0-3 from PLL0
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void InitPeriClkGen(void){
	CGM.SC_DC[2].R = 0x80;          	/* MPC56xxB: Enable peri set 3 sysclk divided by 1 */
}
/**************************************************************
 *  Name                 :	InitSysclk
 *  Description          :	Initialize Fsys 40 Mhz PLL with 8 Mhz crystal.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void InitSysclk(void){
	InitModesAndClock();
	InitPeriClkGen();
}
/**************************************************************
 *  Name                 :	InitGPIO
 *  Description          :	Initialize outputs for leds and inputs
							for push-buttons
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void InitGPIO(void){
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
 *  Name                 :	InitLeds
 *  Description          :	On all leds for the simulation (window closed).
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void InitLeds(void){
	unsigned char a;
	for(a = 0; a < 12; a++){
		SIU.GPDO[a].R = 1;
	}
}
/**************************************************************
 *  Name                 : InitHW
 *  Description          :	Initialization of the hardware.
 *  Parameters           :  NONE
 *  Return               :	NONE
 *  Critical/explanation :    No
 **************************************************************/
void InitHW(void){
	DisableWatchdog();
	InitSysclk();
	InitTimer();
	InitGPIO();
	InitLeds();
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