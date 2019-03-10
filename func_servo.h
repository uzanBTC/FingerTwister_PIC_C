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

#ifndef _FUNC_SERVO_
#define	_FUNC_SERVO_

/** I N C L U D E S *************************************************/  
#include "config.h"

#if ENABLE_SERVO == TRUE

/** D E F I N E S ***************************************************/
#ifndef SERVO_CHANNELS
    #error "Servo enabled, but no channels defined"
#endif

/** P U B L I C   V A R I A B L E S *********************************/
// when a variable is declared 'extern' it also has to be declared in
// the corresponding .c file without the 'extern' keyword
extern unsigned char servo_setpoint[SERVO_CHANNELS];

/** P U B L I C   P R O T O T Y P E S *******************************/
void SERVO_init(void);
void SERVO_setPosition(unsigned char channel, unsigned char position);
unsigned char SERVO_getPosition(unsigned char channel);
void SERVO_ISR(void);

#endif

#endif

