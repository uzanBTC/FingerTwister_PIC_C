
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
#include "func_pwm.h"

/** P U B L I C   V A R I A B L E S *********************************/
// in order for the variable to be used in other file, it also has to
// be declared as 'extern' in the corresponding .h file
unsigned char PWM_duty[PWM_CHANNELS];

/** P R I V A T E   V A R I A B L E S *******************************/
// 'static' implies that the variable can only be used in this file
// (cfr. 'private' in Java)
static unsigned char counter;

/** P R I V A T E   P R O T O T Y P E S *****************************/
// 'static' implies that the function can only be used in this file
// (cfr. 'private' in Java)
//static void OpenTimer2(unsigned char intEnable);

/********************************************************************/
/** P U B L I C   D E C L A R A T I O N S ***************************/
/********************************************************************
 * Function:        void PWM_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        Initializes all output channels for the PWM process
 ********************************************************************/
//void PWM_init(void) {
//	counter = 0;
//	for(int i = 0; i < PWM_CHANNELS; i++) {
//        PWM_duty[i] = 0;
//    }
   // OpenTimer2(TRUE);
	
    /**** Initialize all PWM outputs ****/
//	LATBbits.LATB7 = 0;
//	TRISBbits.TRISB7 = 0;
    //LATBbits.LATB3 = 0;
	//TRISBbits.TRISB3 = 0;
    //LATBbits.LATB2 = 0;
	//TRISBbits.TRISB2 = 0;
    /************************************/
//}

/********************************************************************
 * Function:        void PWM_ISR(void)
 * PreCondition:    PWM_init()
 * Input:           None
 * Output:          None
 * Overview:        PWM Interrupt service routine will process all PWM
 *                  duty cycles and set the outputs accordingly
 ********************************************************************/
/*void PWM_ISR(void) {
    if (PIR1bits.TMR1IF == 1) {
        TMR1H = 209;    // tuned to 100Hz
        counter = (counter + 1) % 10;
        
        /**** PWM logic for toggling on duty cycle ****/
        //LATBbits.LATB7 = (PWM_duty[0] > counter);
        //LATBbits.LATB3 = (PWM_duty[1] > counter);
        //LATBbits.LATB2 = (PWM_duty[2] > counter);
        /**********************************************/
        
        //PIR1bits.TMR1IF = 0;
   // }
//}

/********************************************************************/
/** P R I V A T E   D E C L A R A T I O N S *************************/
/********************************************************************
 * Function:        void OpenTimer1(unsigned char intEnable)
 * PreCondition:    None
 * Input:           intEnable: enable Timer1 interrupt
 * Output:          None
 * Overview:        Will initialize Timer1 given the parameters
 ********************************************************************/
/*static void OpenTimer1(unsigned char intEnable) {
    T1CONbits.RD16 = 0;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 1;

    TMR1H = 209;                // Tuned to 100Hz
    TMR1L = 0;
    
    PIE1bits.TMR1IE = intEnable & 0x01;
    INTCONbits.GIE = (intEnable & 0x01) | INTCONbits.GIE;
    INTCONbits.PEIE = (intEnable & 0x01) | INTCONbits.PEIE;
    IPR1bits.TMR1IP = 0;
    PIR1bits.TMR1IF = 0;      // Clear Timer1 overflow flag
}
*/
//EOF-----------------------------------------------------------------
