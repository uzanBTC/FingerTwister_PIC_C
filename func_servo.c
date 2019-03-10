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

/** I N C L U D E S *************************************************/
#include "func_servo.h"

/** P U B L I C   V A R I A B L E S *********************************/
// in order for the variable to be used in other file, it also has to
// be declared as 'extern' in the corresponding .h file
unsigned char servo_setpoint[SERVO_CHANNELS];

/** P R I V A T E   V A R I A B L E S *******************************/
// 'static' implies that the variable can only be used in this file
// (cfr. 'private' in Java)
static unsigned char servo_counter;

/** P R I V A T E   P R O T O T Y P E S *****************************/
// 'static' implies that the function can only be used in this file
// (cfr. 'private' in Java)
static void OpenTimer3(unsigned char intEnable);

/********************************************************************/
/** P U B L I C   D E C L A R A T I O N S ***************************/
/********************************************************************
 * Function:        void SERVO_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        Initializes all output channels for the PWM process
 ********************************************************************/
void SERVO_init() {
	servo_counter = 0;
	for(int i = 0; i < SERVO_CHANNELS; i++) {
        servo_setpoint[i] = 0;
    }
    OpenTimer3(TRUE);
}

/********************************************************************
 * Function:        void SERVO_setPosition(...)
 * PreCondition:    SERVO_init()
 * Input:           channel : the channel to be set
 *                  setpoint : the new setpoint
 * Output:          None
 * Overview:        Changes the setpoint for a certain servo and checks
 *                  if the setpoint is within the limits
 ********************************************************************/
void SERVO_setPosition(unsigned char channel, unsigned char setpoint) {
    if (setpoint < 1) setpoint = 1;
    if (setpoint > 32) setpoint = 32;
    if (channel < SERVO_CHANNELS) {
        servo_setpoint[channel] = setpoint;
    }
}

/********************************************************************
 * Function:        void SERVO_getPosition(...)
 * PreCondition:    SERVO_init()
 * Input:           channel : the channel to be read
 * Output:          the current setpoint
 * Overview:        reads out the setpoint for a certain servo
 ********************************************************************/
unsigned char SERVO_getPosition(unsigned char channel) {
    if (channel < SERVO_CHANNELS) {
        return servo_setpoint[channel];
    } else {
        return 0;
    }
}

/********************************************************************
 * Function:        void SERVO_ISR(void)
 * PreCondition:    SERVO_init()
 * Input:           None
 * Output:          None
 * Overview:        SERVO Interrupt service routine will process all
 *                  setpoints and set the outputs accordingly
 ********************************************************************/
void SERVO_ISR(void) {
    if (PIR2bits.TMR3IF == 1) {
        servo_counter = (servo_counter + 1u) % 40;
        if (servo_counter == 0) { 
            TMR3H = 230;
        }
        else if (servo_counter < 32) {
            TMR3H = 254;
            TMR3L = 164;
        } else {
            TMR3H = 0;
        }
       
        /**** PWM logic for toggling on setpoint ****/
        SERVO1_OUT = (servo_setpoint[0] > servo_counter);
        //SERVO2_OUT = (servo_setpoint[0] > servo_counter);
        //SERVO3_OUT = (servo_setpoint[1] > servo_counter);
        /**********************************************/
        
        PIR2bits.TMR3IF = 0;
    }
}

/********************************************************************/
/** P R I V A T E   D E C L A R A T I O N S *************************/
/********************************************************************
 * Function:        void OpenTimer3(unsigned char intEnable)
 * PreCondition:    None
 * Input:           intEnable: enable Timer3 interrupt
 * Output:          None
 * Overview:        Will initialize Timer3 given the parameters
 ********************************************************************/
static void OpenTimer3(unsigned char intEnable) {
    T3CONbits.T3RD16 = 0;
    T3CONbits.T3CKPS = 0b00;
    T3CONbits.TMR3ON = 1;
    T3CONbits.TMR3CS = 0;
    T3CONbits.T3NSYNC = 1;
          
    PIE2bits.TMR3IE = intEnable & 0x01;
    INTCONbits.GIE = (intEnable & 0x01) | INTCONbits.GIE;
    INTCONbits.PEIE = (intEnable & 0x01) | INTCONbits.PEIE;
    IPR2bits.TMR3IP = 0;
    PIR2bits.TMR3IF = 0;      // Clear Timer3 overflow flag
}

//EOF-----------------------------------------------------------------
