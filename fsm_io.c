/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * Processor:       PIC18F2550
 * Compiler:        XC8 1.35+
 * Author:          Jeroen Van Aken
 * Updated:         24/02/2017
 ********************************************************************/
/** I N C L U D E S *************************************************/
#include "config.h"

/** P R I V A T E   V A R I A B L E S *******************************/
static unsigned char servo_counter;
static unsigned char stepper_counter;
static unsigned char pwm_counter;

static enum {FSM_SETIO,       
        FSM_UPDATE_SERVO        
            } current_state;
            
/********************************************************************
 * Function:        void fsm_io_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        This init sets the start state for this FSM and
 *                  may initialize some counters          
 ********************************************************************/
void fsm_io_init(void) {
	current_state = FSM_SETIO;
}

/********************************************************************
 * Function:        fsm_io(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        A simple FSM that will start blinking a led on 
 *                  and off once you pushed a button.          
 ********************************************************************/
void fsm_io(void) {
   
    fsm_io_init();             
       
    
    switch(current_state)
    {
         case FSM_SETIO :
        // *** inputs ***
//            player_1 = ADC_value[0];    // store the previous AD value in variable
//            player_2 = ADC_value[1];
            startADC();             // start conversion for all new values
            // --> set MUX selector pins 
            MUX1_A=mux1_a;
            MUX1_B=mux1_b;
            MUX1_C=mux1_c;
            MUX2_A=mux2_a;
            MUX2_B=mux2_b;
            MUX2_C=mux2_c;
            MUX3_A=mux3_a;
            MUX3_B=mux3_b;
            MUX3_C=mux3_c;
            MUX4_A=mux4_a;
            MUX4_B=mux4_b;
            MUX4_C=mux4_c;
            

            
        // *** outputs ***
            
            
           // servo_counter++;
            // incrementing the PWM counter and setting the outputs
            //pwm_counter = (pwm_counter + 1) % 10;
            //PWM_OUT = (PWM_duty[0] > pwm_counter);
            
        // *** transitions ***
           // if (servo_counter >= 10) current_state = FSM_UPDATE_SERVO;
            break;
        
        case FSM_UPDATE_SERVO :
        // *** outputs ***
            for (char i = 0; i < SERVO_CHANNELS; i++) {
                SERVO_setPosition(i, servo_setpoint[i]);
            }
            servo_counter = 0;
        // *** transitions ***
            current_state = FSM_SETIO;
            break;
                 
        default:
            current_state = FSM_SETIO;
            break;
    }
    
}


