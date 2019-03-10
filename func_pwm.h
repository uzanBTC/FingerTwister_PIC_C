/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * Processor:       PIC18F2550
 * Compiler:        XC8 1.35+
 * Author:          Jeroen Van Aken
 * Updated:         17/02/2016
 ********************************************************************/

#ifndef _FUNC_PWM_
#define _FUNC_PWM_

/** I N C L U D E S *************************************************/
#include "config.h"

/** D E F I N E S ***************************************************/
#define PWM_CHANNELS 1

/** P U B L I C   V A R I A B L E S *********************************/
// when a variable is declared 'extern' it also has to be declared in
// the corresponding .c file without the 'extern' keyword
extern unsigned char PWM_duty[PWM_CHANNELS];

/** P U B L I C   P R O T O T Y P E S *******************************/
void PWM_init(void);
void PWM_ISR(void);

#endif
//EOF-----------------------------------------------------------------
