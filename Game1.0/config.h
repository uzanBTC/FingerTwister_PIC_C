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

#ifndef _CONFIG_H
#define _CONFIG_H

/** D E F I N E S ***************************************************/
#define TRUE 1
#define FALSE 0

/* Uncomment the line below if you want to use the ADC */
// #define ENABLE_ADC TRUE

/* If you are using the ADC specify how many channels you are using
 * for every channel you can read the ADC value from ADC_value[] */
#define ADC_CHANNELS    1
#define ENABLE_ADC  TRUE

/* Uncomment the line below if you want to use the IO expander 
 * BE AWARE: When using the IO expander RC7 and RB1 are used for communication
 * RB0 can only be used as output, in this example we use it as CS */
// #define ENABLE_IOEXP TRUE

#define IOEXP_DATA          LATCbits.LATC7
#define IOEXP_CLK           LATBbits.LATB1
#define IOEXP_CS            LATBbits.LATB0

/* Uncomment the line below if you want to use the audio module */
// #define ENABLE_AUDIO TRUE

/* Specify the pin for your audio output, every digital output can be used */
#define AUDIO_OUT           LATBbits.LATB3

/* Uncomment the line below if you want to use a servo */
// #define ENABLE_SERVO TRUE

/* If you are using a servo specify how many you are using
 * for every servo you need to alter the SERVO_ISR() method in func_servo.c 
 * to update the outputs for the servo's */
#define SERVO_CHANNELS 1

/* Define all out- and inputs with readable names */
#define PRG_BUTTON      PORTCbits.RC0
#define LED1_OUT        LATCbits.LATC2
#define LED2_OUT        LATCbits.LATC1
#define SERVO1_OUT      LATBbits.LATB1
//#define PWM_OUT         LATBbits.LATB7

/** I N C L U D E S *************************************************/
#include <xc.h>
#include "func_adc.h"
#include "func_pwm.h"
#include "func_ioexp.h"
#include "func_audio.h"
#include "func_servo.h"


/** G L O B A L   P U B L I C   V A R I A B L E S *******************/
// when a variable is declared 'extern' it also has to be declared in
// the corresponding .c file without the 'extern' keyword
//extern unsigned char led1_output;
extern unsigned int time_count;
extern unsigned int timerForP1;
extern unsigned int timerForP2;
extern unsigned int swwep;
extern unsigned int touchedA;
extern unsigned int touchedB;
extern double fingerA;
extern double fingerB;
extern unsigned int sweep;
// this is an example for implementing a stepper motor
// in your game FSM you can store the direction and amount of steps in a variable
// the IO FSM will read out this variable to set the apropriate outputs
// we use an array here, in case you have multiple stepper motors
//extern unsigned char stepper_steps[1];
//extern unsigned char stepper_direction[1];

// this is an example for implementing a PWM on one of the output pins
// you can configure the PWM output in the fsm_io.c file
//extern unsigned char PWM_duty[1];

/** P U B L I C   P R O T O T Y P E S *******************************/

/** F S M   R O U T I N E S *****************************************/
void fsm_io_init(void);
void fsm_io(void);

void fsm_game_init(void);
void fsm_game(void);

#endif
//EOF----------------------------------------------------------------

