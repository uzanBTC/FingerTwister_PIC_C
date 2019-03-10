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
static enum {FSM_TEST1,FSM_TEST2,FSM_IDLE, FSM_READY_LIGHT, FSM_READY_OFF, FSM_MOTOR_READY, FSM_LED_READY, FSM_DETECT_PREPARE,
            FSM_INFORM,FSM_LOSE_B} current_state;
            
            
            /*written*/void initialAll(); // used to initialize all parameters
            void turnOffP1(); // turn off all LED of player1 (MUX1))
            void turnOffP2(); // turn off all LED of player2 (MUX2))
            void turnOnLEDP1(int num); //1~7 means LED1~7, 9 means all
            void turnOnLEDP2(int num); //1~7 means LED1~7, 9 means all
            void detectButton(); //control MUX3 to detect button
            void closeMu4(); // control MUX4 to detect the empty pin
            /*written*/void generateFingerAndTile(int f, int t); // generate random numbers for finger and tile (1~5 and 1~7 respectively)
            void motorGoTo(int num); // set positions for motor, 1~5 indicates 5 fingers
            /*written*/void sweepTile(int t); // to sweep tiles, as well as button, used to change attribute touched
            /*written*/void setLevel(int t); // used to give value for time
           // used to record the analog values for both players.
            /*written*/void buzzer(int f); // used to generate different                             
            /*written*/void transitionInitial(); //set all 0 to parameters in transition
            void turnOnAllP1(); // only used in LOOSE_B turn on all LED and Buzzer
            int readFinger(double value);
            void getValue();
            
            int index; //used to read values
            
            
/********************************************************************
 * Function:        void fsm_game_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        This init sets the start state for this FSM and
 *                  may initialize some counters          
 ********************************************************************/
void fsm_game_init(void) {
	current_state = FSM_IDLE;//FSM_IDLE;
    index = 0;
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
     
        case FSM_TEST1:
            sweepTile(1);
            
            if(fingerP2>1.4);
            {current_state = FSM_TEST2;
            transitionInitial();
            
            }
            
            break;
     
        
        case FSM_TEST2:
            if(fingerP2 < 3.65)
            {
                turnOnLEDP2(1);
            }
            
            if ((fingerP2 > 3.65)&&(fingerP2 < 3.8))
            {
                turnOnLEDP2(2);
            }
            
            if ((fingerP2 > 3.8)&&(fingerP2 < 3.95))
            {
                turnOnLEDP2(3);
            }
            
            if ((fingerP2 > 3.95)&&(fingerP2 < 4.1))
            {
                turnOnLEDP2(4);
            }
            
            if ((fingerP2 > 4.1)&&(fingerP2 < 4.25))
            {
                turnOnLEDP2(5);
            }
            
            if ((fingerP2 >= 4.25)&&(fingerP2 < 4.4))
            {
                turnOnLEDP2(6);
            }
            
            if (fingerP2 >= 4.4)
            {
                turnOnLEDP2(7);
            }
            
            if(time_count == 2000)
            {
                current_state = FSM_TEST1;
                transitionInitial();
                fingerP2 = 0;
                
            }
            
            break;
        case FSM_IDLE :
        // *** outputs ***
           
            turnOffP1();
            turnOffP2();
            motorGoTo(1);
            closeMu4();
            detectButton();
        // *** transitions ***
            
            if(start == 1)
            {
                current_state = FSM_READY_LIGHT;
                transitionInitial();
                ready_loop = 0;
            }
            break;
            
        case FSM_READY_LIGHT:
           // *** outputs ***
            
            turnOnLEDP1(9);
            turnOnLEDP2(9);
            closeMu4();
            detectButton();
        // *** transitions ***
            
            if(time_count < 500)
            {
            current_state = FSM_READY_LIGHT;
            }
            
            if(time_count > 250)
            {
                if(start == 1)
                {
                    current_state = FSM_IDLE;
                    initialAll();
                } 
                
                if(time_count >=500)
            {
            current_state = FSM_READY_OFF;
            transitionInitial();
            ready_loop++;
            }
            }
            
            break;
            
            case FSM_READY_OFF :
        // *** outputs ***
                
                turnOffP1();
                turnOffP2();
                closeMu4();
                detectButton();
            
        // *** transitions ***
                
                if(time_count < 500)
            {
                current_state = FSM_READY_OFF;
            }
            
                if(time_count > 250)
            {
                if(start == 1)
                {
                    current_state = FSM_IDLE;
                    initialAll();
                } 
            }
                
                if(time_count >=500)
            {
            current_state = FSM_READY_LIGHT;
            transitionInitial();
            }
                
                if(ready_loop == 3)
                {
                    current_state = FSM_MOTOR_READY;
                    transitionInitial();
                    ready_loop = 0;
                    generateFingerAndTile(finger, tile);
                }
                
                
            break;
            
            case FSM_MOTOR_READY :
        // *** outputs ***
                
                motorGoTo(finger);
                turnOffP1();
                turnOffP2();
                closeMu4();
                detectButton();
        // *** transitions ***
                
                if(start == 1)
                {
                    current_state = FSM_IDLE;
                    initialAll();
                }
                
                if(time_count == 50)
                {
                    transitionInitial();
                    setLevel(game_loop);  //setLevel change to int
                    game_loop++;               
                    current_state = FSM_LED_READY;
                }
            break;
            
            case FSM_LED_READY :
        // *** outputs ***
                
                turnOnLEDP1(tile);
                turnOnLEDP2(tile);
                
                    
        // *** transitions *** 
                
                
                
                if(time_count < time)
                {
                    current_state = FSM_LED_READY;
                    sweepTile(tile);
                }
                else
                {
                    current_state = FSM_INFORM;
                    
                    transitionInitial();
                }
                
              
            break;
            
          case FSM_INFORM :
        // *** outputs ***
              
              buzzer(0);
              turnOffP2();
              closeMu4();
              detectButton();
        // *** transitions ***
              
           if(start == 1)
                {
                    current_state = FSM_IDLE;
                    initialAll();
                }
              
              if(time_count == 500)
              {
                  if(fingerP2 != finger)
                  {
                    current_state = FSM_LOSE_B;
                    transitionInitial();
                  }
                  
                                  
                 
                  if(fingerP2 == finger)
                  {
                      current_state = FSM_MOTOR_READY;
                      transitionInitial();
                      generateFingerAndTile(finger,tile);
                      
                  }
              }
            break;  
            
            
          case FSM_LOSE_B :
        // *** outputs ***
              
              turnOnAllP1();
              turnOffP2();
              detectButton();
              closeMu4();
        // *** transitions *** 
              
              if(start == 1)
                {
                    current_state = FSM_IDLE;
                    initialAll();
                }
              
              if(time_count >= 1000)
              {
                  current_state = FSM_IDLE;
                  initialAll();
              }
            break;
           
          
            
        default:
            current_state = FSM_IDLE;
            initialAll();
            break;
    }
}
    
void initialAll()
{
    time_count = 0; 
    start = 0; 
    sweep = 0; 
    touched = 0; 
    fingerP1 = 0; 
    fingerP2 = 0; 
    ready_loop = 0; 
    tile = 0; 
    finger = 0; 
    time = 0; 
    game_loop = 0;
}

void transitionInitial()
{
    time_count = 0;
    sweep = 0;
    start = 0;
    
}

void getValue()
{
    double temp_fingerP2;
    temp_fingerP2 = (values[0] + values[1] + values[2] + values[3] + values[4] + values[5] + values[6] + values[7] + values[8] + values[9])/10;
    fingerP2 = readFinger(temp_fingerP2);
}


void generateFingerAndTile(int f, int t)
{
    int temp_finger;
    int temp_tile;
    
    temp_finger = (rand() % 5) + 1;
    temp_tile = (rand() % 7) + 1;
    
    while ((temp_finger == f))
    {
    temp_finger = (rand() % 5) + 1;
    }
    
    while (temp_tile == t)
    {
    temp_tile = (rand() % 7) + 1;
    }

    finger = temp_finger;
    tile = temp_tile;
    
}

void buzzer(int f)
{
    if(f == 0)
    {
        if((sweep == 1)||(sweep == 3)||(sweep == 5))
        {
        MUX1_EN = 0;
        mux1_a = 1;
        mux1_b = 1;
        mux1_c = 1;
        }
        
        else
        {MUX1_EN = 1;}
    }
    
    if(f == 1)
    {
        if(sweep < 5)
        {
        MUX1_EN = 0;
        mux1_a = 1;
        mux1_b = 1;
        mux1_c = 1;
        }
        
        else
        {MUX1_EN = 1;}
    }
    
    if(f == 2)
        {
        MUX1_EN = 0;
        mux1_a = 1;
        mux1_b = 1;
        mux1_c = 1;
        }
    
}

void sweepTile(int t)
{
    double temp_p2_voltage;
    
    // player2 stays at one tile
    switch(t)
    {
        case 1: 
            mux4_a=0;
            mux4_b=0;
            mux4_c=0;
            break;
            
        case 2: 
            mux4_a=1;
            mux4_b=0;
            mux4_c=0;
            break;
            
        case 3: 
            mux4_a=0;
            mux4_b=1;
            mux4_c=0;
            break;
            
        case 4: 
            mux4_a=1;
            mux4_b=1;
            mux4_c=0;
            break;
            
        case 5: 
            mux4_a=0;
            mux4_b=0;
            mux4_c=1;
            break;
            
        case 6: 
            mux4_a=1;
            mux4_b=0;
            mux4_c=1;
            break;
            
        case 7: 
            mux4_a=0;
            mux4_b=1;
            mux4_c=1;
            break;
    }
    
      temp_p2_voltage = 5*(ADC_value[1])/1024;

      
          fingerP2 = readFinger(temp_p2_voltage);
      
   
}
      


void setLevel(int t)
{
    if(t < 3)
    {
        time = 5000 - 250*t;
    }
    
    if((t >= 3)&&(t < 5))
    {
        time = 5000 - 150*(t-2);
    }  
    
    else
    {
        time = 5000 - 10*(t-5);
    }
    
    if(time < 1000)
    {time = 1000;}
}
void closeMu4()
{
    mux4_a=1;
    mux4_b=1;
    mux4_c=1;
}

void turnOffP1() //close enable
{
    MUX1_EN=1;
}

void turnOffP2()  //switch to pin 7
{
    mux2_a = 1;
    mux2_b = 1;
    mux2_c = 1;
}

void motorGoTo(int num)
{
    switch(num)
    {
        case 1: servo_setpoint[0]=32;break; //thumb
        case 2: servo_setpoint[0]=22;break;//forefinger
        case 3: servo_setpoint[0]=15;break;//middle finger
        case 4: servo_setpoint[0]=8;break;//ring finger
        case 5: servo_setpoint[0]=1;break;//little finger
    }
}

void detectButton()
{
     mux3_a=1;
     mux3_b=1;
     mux3_c=1;
     
     if(ADC_value[0]>500 && realPushed==0)
     {
         realPushed=1;
         time_count=0;      
     }
     
     if(realPushed==1 && time_count>=200 && ADC_value[0]>500)
     {
         start=1;
         realPushed=0;
     }
}

void turnOnLEDP1(int num)
{
    MUX1_EN=0;
    switch (num) {
        case 1:
            mux1_a = 0;
            mux1_b = 0;
            mux1_c = 0;
            break;
        case 2:
            mux1_a = 1;
            mux1_b = 0;
            mux1_c = 0;
            break;
        case 3:
            mux1_a = 0;
            mux1_b = 1;
            mux1_c = 0;
            break;
        case 4:
            mux1_a = 1;
            mux1_b = 1;
            mux1_c = 0;
            break;
        case 5:
            mux1_a = 0;
            mux1_b = 0;
            mux1_c = 1;
            break;
        case 6:
            mux1_a = 1;
            mux1_b = 0;
            mux1_c = 1;
            break;
        case 7:
            mux1_a = 0;
            mux1_b = 1;
            mux1_c = 1;
            break;
        case 9:
            switch (sweep) {
        case 1:
            mux1_a = 0;
            mux1_b = 0;
            mux1_c = 0;
            break;
        case 2:
            mux1_a = 1;
            mux1_b = 0;
            mux1_c = 0;
            break;
        case 3:
            mux1_a = 0;
            mux1_b = 1;
            mux1_c = 0;
            break;
        case 4:
            mux1_a = 1;
            mux1_b = 1;
            mux1_c = 0;
            break;
        case 5:
            mux1_a = 0;
            mux1_b = 0;
            mux1_c = 1;
            break;
        case 6:
            mux1_a = 1;
            mux1_b = 0;
            mux1_c = 1;
            break;
        case 7:
            mux1_a = 0;
            mux1_b = 1;
            mux1_c = 1;
            break;          
        }
        break;
}
}

void turnOnLEDP2(int num)
{
     switch (num) {
        case 1:
            mux2_a = 0;
            mux2_b = 0;
            mux2_c = 0;
            break;
        case 2:
            mux2_a = 1;
            mux2_b = 0;
            mux2_c = 0;
            break;
        case 3:
            mux2_a = 0;
            mux2_b = 1;
            mux2_c = 0;
            break;
        case 4:
            mux2_a = 1;
            mux2_b = 1;
            mux2_c = 0;
            break;
        case 5:
            mux2_a = 0;
            mux2_b = 0;
            mux2_c = 1;
            break;
        case 6:
            mux2_a = 1;
            mux2_b = 0;
            mux2_c = 1;
            break; 
        case 7:
            mux2_a = 0;
            mux2_b = 1;
            mux2_c = 1;
            break; 
         case 9:
            switch (sweep) {
        case 1:
            mux2_a = 0;
            mux2_b = 0;
            mux2_c = 0;
            break;
        case 2:
            mux2_a = 1;
            mux2_b = 0;
            mux2_c = 0;
            break;
        case 3:
            mux2_a = 0;
            mux2_b = 1;
            mux2_c = 0;
            break;
        case 4:
            mux2_a = 1;
            mux2_b = 1;
            mux2_c = 0;
            break;
        case 5:
            mux2_a = 0;
            mux2_b = 0;
            mux2_c = 1;
            break;
        case 6:
            mux2_a = 1;
            mux2_b = 0;
            mux2_c = 1;
            break;
        case 7:
            mux2_a = 0;
            mux2_b = 1;
            mux2_c = 1;
            break;
             }         
             break;

     }
}

void turnOnAllP1()  //all leds no include buzzer   turn on all p2
{
    MUX1_EN=0;
    switch (sweep){
        case 1:
            mux1_a = 0;      
            mux1_b = 0;
            mux1_c = 0;
           
            break; 
        case 2:
            mux1_a = 1;      
            mux1_b = 0;
            mux1_c = 0;
            break;
        case 3:
            mux1_a = 0;      
            mux1_b = 1;
            mux1_c = 0;
            break;
        case 4:
            mux1_a = 1;      
            mux1_b = 1;
            mux1_c = 0;
            break;
        case 5:
            mux1_a = 0;      
            mux1_b = 0;
            mux1_c = 1;
            break;
        case 6:
            mux1_a = 1;      
            mux1_b = 0;
            mux1_c = 1;
            break;
        case 7:
            mux1_a = 0;      
            mux1_b = 1;
            mux1_c = 1;          
            break;
    }
}



int readFinger(double value) // thumb 2.36~2.56, forefinger: 2.16~2.35, middle finger: 1.94~2.15, ring finger: 1.69~1.89, little finger: 0.84~1.04
{
    if(value >=4.3)
    {return 1;}//thumb
    
    if((value >= 3.8)&&(value <4.3))
    {return 2;}//forefinger
    
    if((value >= 2.8)&&(value <3.5))
    {return 3;}//middle finger
    
    if((value >=2)&&(value <2.7))
    {return 4;}//ring finger
    
    if((value >= 1)&&(value <2))
    {return 5;}//little finger
    
    else 
        return 9;
}

