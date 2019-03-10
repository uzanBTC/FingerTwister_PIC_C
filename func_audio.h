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

#ifndef _FUNC_AUDIO_
#define	_FUNC_AUDIO_

/** I N C L U D E S *************************************************/  
#include "config.h"

#if ENABLE_AUDIO == TRUE

/** D E F I N E S ***************************************************/
#ifndef AUDIO_OUT
  #error "Audio enabled, but no output selected"
#endif

// define the notes with the correct pre-loaded value for the timer
#define C1    42655
#define D1    45340
#define E1    47385
#define F1    48408
#define G1    50287
#define A2    51935
#define B2    53435
#define C2    54106
#define D2    55358
#define E2    56485
#define F2    56985
#define G2    57935
#define A3    58767
#define B3    59515
#define C3    59825

/** P U B L I C   V A R I A B L E S *********************************/
// when a variable is declared 'extern' it also has to be declared in
// the corresponding .c file without the 'extern' keyword

/** P U B L I C   P R O T O T Y P E S *******************************/
void AUDIO_init(void);
void AUDIO_play(unsigned int freq);
void AUDIO_stop(void);
void AUDIO_ISR(void);

#endif

#endif

