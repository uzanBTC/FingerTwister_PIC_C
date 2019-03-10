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
 #define ENABLE_ADC TRUE

/* If you are using the ADC specify how many channels you are using
 * for every channel you can read the ADC value from ADC_value[] */
#define ADC_CHANNELS    2


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
 #define ENABLE_SERVO TRUE

/* If you are using a servo specify how many you are using
 * for every servo you need to alter the SERVO_ISR() method in func_servo.c 
 * to update the outputs for the servo's */
#define SERVO_CHANNELS 1

/* Define all out- and inputs with readable names */
#define PRG_BUTTON      PORTCbits.RC0
#define SERVO1_OUT      LATAbits.LATA5 //fixed

//define the multiplex
# define MUX1_A  LATCbits.LATC2
# define MUX1_B  LATCbits.LATC1
# define MUX1_C  LATCbits.LATC6
# define MUX2_A  LATBbits.LATB2
# define MUX2_B  LATBbits.LATB3
# define MUX2_C  LATBbits.LATB4
# define MUX3_A  LATBbits.LATB5
# define MUX3_B  LATBbits.LATB6
# define MUX3_C  LATBbits.LATB7
# define MUX4_A  LATAbits.LATA2
# define MUX4_B  LATAbits.LATA3
# define MUX4_C  LATAbits.LATA4
# define MUX1_EN LATBbits.LATB0

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
extern unsigned int time_count; //count time
extern unsigned int start; // start button
extern unsigned int sweep; // count 1 to 7
extern unsigned int touched; //whether one tile has been touched
extern double fingerP1; //detect which finger of P1
extern double fingerP2; //detect which finger of P2
extern unsigned int ready_loop; //detect how many times LED has shined
extern unsigned int tile; //determine which tile will be lighted up
extern unsigned int finger; //determine which finger will be used
extern unsigned int time; //used to control difficulty level
extern unsigned int game_loop; //how many rounds the game has been through
extern unsigned int realPushed; //detect if button pushed

extern unsigned char mux1_a;
extern unsigned char mux1_b;
extern unsigned char mux1_c;
extern unsigned char mux2_a;
extern unsigned char mux2_b;
extern unsigned char mux2_c;
extern unsigned char mux3_a;
extern unsigned char mux3_b;
extern unsigned char mux3_c;
extern unsigned char mux4_a;
extern unsigned char mux4_b;
extern unsigned char mux4_c;

extern double values[10];
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

