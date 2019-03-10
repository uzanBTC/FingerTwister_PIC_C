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
#include <stdlib.h>
#include <pic18f2550.h>


/** D E F I N E S ***************************************************/
#define PUSHED 0
/** P R I V A T E   V A R I A B L E S *******************************/
static enum {FSM_IDLE, FSM_READY_LIGHT, FSM_READY, FSM_RANDOM_START, FSM_RANDOM_DETECT, FSM_CHECK, FSM_LOSE_A,
        FSM_LOSE_B, FSM_LOSE_AB
            } current_state;
            
            unsigned int randomFinger;
            unsigned int ready_time;
            unsigned int randomLight;
            unsigned int sweep;
            void lightUpOneLEDForPlayer1(int number);
            void lightUpOneLEDForPlayer2(int number);
            int readButton(void);
            int readFinger(double value);
            double sweepTilesOne(int num);
            double sweepTilesTwo(int num);
            void turnOffAllLEDOfPlayer2();
            void turnOffEverythingOfPlayer1();
            void turnOnAllLEDOfPlayer1();
            void turnOnAllLEDOfPlayer2();
            void turnOnBuzzer();
            void turnOnEverythingOfPlayer1();
            
/********************************************************************
 * Function:        void fsm_game_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        This init sets the start state for this FSM and
 *                  may initialize some counters          
 ********************************************************************/
void fsm_game_init(void) {
	current_state = FSM_IDLE;
    startADC();
}

/********************************************************************
 * Function:        void fsm_game(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        An implementation for a simple reaction game
 ********************************************************************/
void fsm_game(void) {
    
    switch (current_state) { 
        case FSM_IDLE :
        // *** outputs ***
            turnOffEverythingOfPlayer1();
            turnOffAllLEDOfPlayer2();
            //used for the initialization of the motor
            
        // *** transitions ***
            if(readButton() == 1)
            {
                current_state = FSM_READY_LIGHT;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
            }
            break;
            
        case FSM_READY_LIGHT:
           // *** outputs ***
            if(time_count < 500)
            {
            turnOnAllLEDOfPlayer1();
            turnOnAllLEDOfPlayer2();
            }
        // *** transitions ***
            if(time_count == 500)
            {
                current_state = FSM_READY;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
            }
            break;
            
            case FSM_READY :
        // *** outputs ***
                if(time_count < 500)
                {
                    turnOffEverythingOfPlayer1();
                    turnOffAllLEDOfPlayer2();
                }
            
        // *** transitions ***
            if(time_count == 500)
            {
                current_state = FSM_READY_LIGHT;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time++;
            }
                
                if(ready_time == 3)
                {
                    current_state = FSM_RANDOM_START;
                    time_count = 0;
                    timerForP1 = 0;
                    timerForP2 = 0;
                    ready_time = 0;
                    randomFinger = rand()%5;
                    randomLight = rand()%7;
                }
            break;
            
            case FSM_RANDOM_START :
        // *** outputs ***
            /* this one is needed for the motor*/
            
        // *** transitions ***
            if( time_count==50)
            {
                current_state = FSM_RANDOM_DETECT;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                sweep = 0;
                touchedA = 0;
                touchedB = 0;
                fingerA = 0;
                fingerB = 0;
            }
            break;
            
            case FSM_RANDOM_DETECT :
        // *** outputs ***
            lightUpOneLEDForPlayer1(randomLight);
            lightUpOneLEDForPlayer2(randomLight);
           
            //read player1
            fingerA = sweepTilesOne(sweep);
            if(fingerA >= 0.8)
            {
            touchedA = 1;
            }
            //read player2
                fingerB = sweepTilesTwo(sweep);
                if(fingerB >= 0.8)
                {
                 touchedB = 1;
                }
                
                if(sweep == 7)
                {sweep = 0;}
            
        // *** transitions *** 
            if(time_count == 2000)
            {
                if((touchedA == 0)&&(touchedB == 0)) //C1: A and B neither touched the tile
                {
                current_state = FSM_LOSE_AB;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                }
                
                if((touchedA == 0)&&(touchedB == 1)) //C2: only B has touched a tile
                {
                    if(readFinger(fingerB) == randomFinger)//right touch
                    {
                current_state = FSM_LOSE_A;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                    }
                
                    if(readFinger(fingerB) != randomFinger)//wrong touch
                    {
                current_state = FSM_LOSE_AB;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                    }
                
                }
                
                if((touchedA == 1)&&(touchedB == 0)) //C3: only A has touched a tile
                {
                    if(readFinger(fingerA) == randomFinger)//right touch
                    {
                current_state = FSM_LOSE_B;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                    }
                
                    if(readFinger(fingerA) != randomFinger)//wrong touch
                    {
                current_state = FSM_LOSE_AB;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                    }
                
                }
                
                if((touchedA == 1)&&(touchedB == 1)) //C4: both have touched
                {
                    if((readFinger(fingerA) != randomFinger)&&(readFinger(fingerB) != randomFinger))//both are wrong
                    {
                current_state = FSM_LOSE_AB;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                    }
                
                    if((readFinger(fingerA) == randomFinger)&&(readFinger(fingerB) != randomFinger)) //A is correct
                    {
                current_state = FSM_LOSE_B;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                    }
                
                    if((readFinger(fingerA) != randomFinger)&&(readFinger(fingerB) == randomFinger)) //B is correct
                    {
                current_state = FSM_LOSE_A;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                    }
                    
                   if((readFinger(fingerA) == randomFinger)&&(readFinger(fingerB) == randomFinger)) //Both are correct
                    {
                    current_state = FSM_RANDOM_START;
                    time_count = 0;
                    timerForP1 = 0;
                    timerForP2 = 0;
                    ready_time = 0;
                    randomFinger = rand()%5;
                    randomLight = rand()%7;
                    touchedA = 0;
                    touchedB = 0;
                    fingerA = 0;
                    fingerB = 0;
                    } 
                }
            }
            break;
            
          case FSM_LOSE_A :
        // *** outputs ***
            turnOnBuzzer();
            turnOnAllLEDOfPlayer2();
            
        // *** transitions ***
            if(time_count == 600)
            {
                current_state = FSM_IDLE;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                touchedA = 0;
                touchedB = 0;
                fingerA = 0;
                fingerB = 0;
            }
            break;  
            
            
          case FSM_LOSE_B :
        // *** outputs ***
            turnOnEverythingOfPlayer1();
            turnOffAllLEDOfPlayer2();
            
        // *** transitions ***
            if(time_count == 600)
            {
                current_state = FSM_IDLE;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                touchedA = 0;
                touchedB = 0;
                fingerA = 0;
                fingerB = 0;
            }
            break;
            
            case FSM_LOSE_AB :
        // *** outputs ***
            turnOnBuzzer();
            turnOffAllLEDOfPlayer2();
            
        // *** transitions ***
            if(time_count == 600)
            {
                current_state = FSM_IDLE;
                time_count = 0;
                timerForP1 = 0;
                timerForP2 = 0;
                ready_time = 0;
                touchedA = 0;
                touchedB = 0;
                fingerA = 0;
                fingerB = 0;
            }
            break;
            
        default:
            current_state = FSM_IDLE;
            break;
    }
}
    


//This method can light up one specified LED for player1 based on numbers from 0 to 6
void lightUpOneLEDForPlayer1(int number)
{
    switch (number) {
        case 0:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 0;
            break;
        case 1:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 1;
            break;
        case 2:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 0;
            break;
        case 3:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 1;
            break;
        case 4:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 0;
            break;
        case 5:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 1;
            break;
        case 6:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 0;
            break;
}
}


//This method can light up one specified LED for player2 based on numbers from 0 to 6
void lightUpOneLEDForPlayer2(int number)
{
    switch (number) {
        case 0:
            LATBbits.LB2 = 0;
            LATBbits.LB3 = 0;
            LATBbits.LB4 = 0;
            break;
        case 1:
            LATBbits.LB2 = 0;
            LATBbits.LB3 = 0;
            LATBbits.LB4 = 1;
            break;
        case 2:
            LATBbits.LB2 = 0;
            LATBbits.LB3 = 1;
            LATBbits.LB4 = 0;
            break;
        case 3:
            LATBbits.LB2 = 0;
            LATBbits.LB3 = 1;
            LATBbits.LB4 = 1;
            break;
        case 4:
            LATBbits.LB2 = 1;
            LATBbits.LB3 = 0;
            LATBbits.LB4 = 0;
            break;
        case 5:
            LATBbits.LB2 = 1;
            LATBbits.LB3 = 0;
            LATBbits.LB4 = 1;
            break;
        case 6:
            LATBbits.LB2 = 1;
            LATBbits.LB3 = 1;
            LATBbits.LB4 = 0;
            break;
}
}

//This method turns on the Buzzer
void turnOnBuzzer()
{     
    LATCbits.LC2 = 1;      
    LATCbits.LC1 = 1;
    LATCbits.LC6 = 1;
}

//This method turns on everything of player1
void turnOnEverythingOfPlayer1()
{
    switch (timerForP1){
        case 1:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 0;
            break; 
        case 2:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 1;
            break;
        case 3:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 0;
            break;
        case 4:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 1;
            break;
        case 5:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 0;
            break;
        case 6:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 1;
            break;
        case 7:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 0;
            break;
        case 8:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 1;
            timerForP1 = 0;
            break;
    
    }
}

//This method turns on all LED of player2
void turnOnAllLEDOfPlayer2()
{
switch (timerForP2){
        case 1:
            LATBbits.LB2 = 0;
            LATBbits.LB3 = 0;
            LATBbits.LB4 = 0;
            break; 
        case 2:
            LATBbits.LB2 = 0;
            LATBbits.LB3 = 0;
            LATBbits.LB4 = 1;
            break;
        case 3:
            LATBbits.LB2 = 0;
            LATBbits.LB3 = 1;
            LATBbits.LB4 = 0;
            break;
        case 4:
            LATBbits.LB2 = 0;
            LATBbits.LB3 = 1;
            LATBbits.LB4 = 1;
            break;
        case 5:
            LATBbits.LB2 = 1;
            LATBbits.LB3 = 0;
            LATBbits.LB4 = 0;
            break;
        case 6:
            LATBbits.LB2 = 1;
            LATBbits.LB3 = 0;
            LATBbits.LB4 = 1;
            break;
        case 7:
            LATBbits.LB2 = 1;
            LATBbits.LB3 = 1;
            LATBbits.LB4 = 0;
            timerForP2 = 0;
            break;
    }
}

//This method turns off everything of Player1
void turnOffEverythingOfPlayer1()
{
    if(timerForP1 < 145)
    {
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 0;
    }
    
    if(timerForP1 >= 145 && timerForP1 < 290)
    {
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 1;
    }
    
    if(timerForP1 >= 290 && timerForP1 < 435)
    {
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 0;
    }
    
        if(timerForP1 >= 435 && timerForP1 < 580)
        {
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 1;
        }
    
        if(timerForP1 >= 580 && timerForP1 < 725)
        {
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 0;
        }
    
        if(timerForP1 >= 725 && timerForP1 < 870)
        {
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 1;
        }
    
        if(timerForP1 >= 870 && timerForP1 < 999)
        {
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 0;
        }
    
        if(timerForP1 == 1000)
        {timerForP1 = 0;}
    }

//This method turns off everything of Player2
void turnOffAllLEDOfPlayer2()
{
LATCbits.LC2 = 1;
LATCbits.LC1 = 1;
LATCbits.LC6 = 1;
}

//This method turns on everything except the buzzer of player1
void turnOnAllLEDOfPlayer1()
{
    switch (timerForP1){
        case 1:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 0;
            break; 
        case 2:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 1;
            break;
        case 3:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 0;
            break;
        case 4:
            LATCbits.LC2 = 0;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 1;
            break;
        case 5:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 0;
            break;
        case 6:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 0;
            LATCbits.LC6 = 1;
            break;
        case 7:
            LATCbits.LC2 = 1;
            LATCbits.LC1 = 1;
            LATCbits.LC6 = 0;
            timerForP1 = 0;
            break;
    }
}




double sweepTilesOne(int num) //MULTIPLEX3
{
    switch(num)
    {
        case 1: 
            LATBbits.LB5=0;
            LATBbits.LB6=0;
            LATBbits.LB7=0;
            break;
            
        case 2: 
            LATBbits.LB5=0;
            LATBbits.LB6=0;
            LATBbits.LB7=1;
            break;
            
        case 3: 
            LATBbits.LB5=0;
            LATBbits.LB6=1;
            LATBbits.LB7=0;
            break;
            
        case 4: 
            LATBbits.LB5=0;
            LATBbits.LB6=1;
            LATBbits.LB7=1;
            break;
            
        case 5: 
            LATBbits.LB5=1;
            LATBbits.LB6=0;
            LATBbits.LB7=0;
            break;
            
        case 6: 
            LATBbits.LB5=1;
            LATBbits.LB6=0;
            LATBbits.LB7=1;
            break;
            
        case 7: 
            LATBbits.LB5=1;
            LATBbits.LB6=1;
            LATBbits.LB7=0;
            break;
    }
    
    if(PORTAbits.RA0 == 1)  //read voltage
    {
        return ADC_value[0];
    }
    else{return 0;}
            
}

double sweepTilesTwo(int num) //MULTIPLEX4
{
    switch(num)
    {
        case 1: 
            LATAbits.LA2=0;
            LATAbits.LA3=0;
            LATAbits.LA4=0;
            break;
            
        case 2: 
            LATAbits.LA2=0;
            LATAbits.LA3=0;
            LATAbits.LA4=1;
            break;
            
        case 3: 
            LATAbits.LA2=0;
            LATAbits.LA3=1;
            LATAbits.LA4=0;
            break;
            
        case 4: 
            LATAbits.LA2=0;
            LATAbits.LA3=1;
            LATAbits.LA4=1;
            break;
            
        case 5: 
            LATAbits.LA2=1;
            LATAbits.LA3=0;
            LATAbits.LA4=0;
            break;
            
        case 6: 
            LATAbits.LA2=1;
            LATAbits.LA3=0;
            LATAbits.LA4=1;
            break;
            
        case 7: 
            LATAbits.LA2=1;
            LATAbits.LA3=1;
            LATAbits.LA4=0;
            break;
    }
    
    if(PORTAbits.RA1==1)  //read voltage
    {        return ADC_value[1];
    }
    else{return 0;}
            
}

int readButton(void)
{
     LATBbits.LB5=1;
     LATBbits.LB6=1;
     LATBbits.LB7=1;
     
     if(PORTAbits.RA1==1){return 1;}
     else {return 0;}
}

int readFinger(double value) // thumb 2.36~2.56, forefinger: 2.16~2.35, middle finger: 1.94~2.15, ring finger: 1.69~1.89, little finger: 0.84~1.04
{
    if((value >= 2.36)&&(value <= 2.56))
    {return 0;}//thumb
    
    if((value >= 2.16)&&(value <= 2.35))
    {return 1;}//forefinger
    
    if((value >= 1.94)&&(value <= 2.15))
    {return 2;}//middle finger
    
    if((value >= 1.69)&&(value <= 1.89))
    {return 3;}//ring finger
    
    if((value >= 0.84)&&(value <= 1.04))
    {return 4;}//little finger
    
    else 
        return 9;
}
