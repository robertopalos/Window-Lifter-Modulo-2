/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %windowlifter.h%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      uid734106 %
* %date_created:    Thu Jul  2 10:27:43 2015 %
*=============================================================================*/
/* DESCRIPTION : Header with functions and defines to be called by windowlifter.c*/
/*============================================================================*/
/* FUNCTION COMMENT : Only prototipe of functions, defines for buttons	      */
/* 																              */
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

#ifndef WINDOWLIFTER_H                               /* To avoid double inclusion */
#define WINDOWLIFTER_H
#define 	up	 	64
#define 	down 	65
#define 	pinch 	66
#define		b_up	SIU.GPDI[up].R == 0
#define		b_down	SIU.GPDI[down].R == 0
#define		b_pinch	SIU.GPDI[pinch].R == 0
/* Functions prototypes */


void downmanual(void);
void autodown(void);
void upmanual(void);
void autoup(void);
void pinchup(void);

#endif