/*******************************************************************************/
/**
\file       dummy.c
\brief      Dummy Functions
\author     Francisco Martinez
\version    1.0
\date       04/04/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Variable types and common definitions */
#include "typedefs.h"

/** Own headers */
#include "dummy.h"

/* GPIO routines prototypes */ 
#include "GPIO.h"

/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************/
/**
* \brief    Turn a combination of 4 LEDs with a unique blinking pattern, this funcation shall be 
* \brief    called periodically to operate. 
* \author   Francisco Martinez
* \return   void
*/

void Task_5ms(void);
void Task_10ms(void);
void Task_50ms(void);
void Task_100ms(void);

typedef struct  TaskStructTag{
	T_UWORD ruw_Counter;
	T_UWORD ruw_TopCount;
	tCallbackFunction cpfu_PerFunct;
	
}TASKSTRUCT;

TASKSTRUCT function_table_def[] = 
{
	{0,100,&Task_5ms},
	{0,200,&Task_10ms},
	{0,1000,&Task_50ms},
	{0,2000,&Task_100ms}	
};
TASKSTRUCT *rps_TaskPtr;



void Task_5ms(void)
{
	
	LED_TOGGLE(LED1);
	
}

void Task_10ms(void)
{
	
	LED_TOGGLE(LED2);
	
}

void Task_50ms(void)
{
	LED_TOGGLE(LED3);
	
	
}

void Task_100ms(void)
{
	LED_TOGGLE(LED4);
	
}






void Test(void)
{
    static T_UWORD rub_U16Counter = 0;
    
    rub_U16Counter++;
    
    if (rub_U16Counter == 1000)
    {
    	LED_TOGGLE(LED1);
    	rub_U16Counter = 0;	
    }

}

void dummy_500ms(void) 	
{	
		
	T_UBYTE i;
	
	rps_TaskPtr = &function_table_def[0];	
	
	for(i=0;i<4;i++)
	{
		
		rps_TaskPtr->ruw_Counter++;
		if(rps_TaskPtr->ruw_Counter == rps_TaskPtr->ruw_TopCount)
		{
			rps_TaskPtr->cpfu_PerFunct();
			rps_TaskPtr->ruw_Counter = 0;
		}
		rps_TaskPtr++;
	}
	
	
}

void dummy_endless_loop (void)
{
										
								
	rps_TaskPtr = &function_table_def[0];	
	while(1)
	{
		
		
	}	
}
