
/* Ruler 1         2         3         4         5         6         7        */

/**********  melody_player.c  ***********/
/*                                                                            */
/*   Purpose: Play a short melody stored in array                             */
/*                                                                            */
/*   Notes:   Generation of tone in a parallel port is executed by software   */
/*                                                                            */
/**************************/

/*********  Hardware Implementation  **********/
/*                                                                            */
/*                 -----------    Purpose: Evaluate skills in algorithmic   */
/*    *------------| Dn        |    thinking, specifically in concurrent FSM. */
/*    |            |           |                                              */
/*     >           |           |    Origin: Code adapted by Juan C. Giraldo,  */
/*   <             |           |    in March 31th, 2016 from below link       */
/*     >  1 KOhm   |           |    in order to evaluate the competence in    */
/*   <             |  Arduino  |    using, designing and implementing         */
/*    |            |           |    Concurrent FSM (Finite State Machines).   */
/*    +            |           |                                              */
/*  /   \          |           |                                              */
/* ( ( ) ) Buzzer  |           |    A buzzer is connected through a resistor  */
/*  \   /          |           |    to pin number n in Arduino. This code     */
/*    +            |           |    is implemented with Play_Melody().        */
/*    *------------| GND       |                                              */
/*                 -----------                                              */
/*   Original source: http://www.princetronics.com/supermariothemesong/       */
/*                                                                            */
/**************************/

#include "melody_player-2.h"


#include "super_mario-2.h"


typedef enum {
    FALSE, TRUE
} BOOLEAN;

typedef enum {
    PLAYING_NOTES,
    GENERATING_CYCLE,
    KEEPING_HIGH_LEVEL,
    KEEPING_LOW_LEVEL,
    PAUSING_BETWEEN_TONES
} STATE_T;

typedef struct {
  TONE_T  *melody;
  unsigned int  melody_size;
  double  melody_pause;
  int   melody_pin;
  unsigned long previous, current;
  unsigned long halfcycle_in_micros;
  unsigned long max_cycles;
  unsigned int note;
  unsigned long cycles;
  BOOLEAN finish;
  STATE_T  state;
  }FSM_T;




/***********  main functions  ***********/

FSM_T Melody_0;
FSM_T Melody_1;


unsigned int Size_2   = sizeof( Super_Mario )/sizeof( TONE_T );


double       Pause_1 = 0.2;
double       Pause_2 = 0.1;


const int Pin_1 = 1;

/*********  Definition of Functions  ********/

void Play_Melody( FSM_T *);
 
void Initiate_Play_Melody(
FSM_T       *fsm_ptr,
TONE_T      *melody,       /* In: Array of tones/length  */
unsigned int melody_size,  /* In: Size of previous array */
double       melody_pause, /* In: Pause between notes    */
int          melody_pin  ) /* In: Defined output pin     */

{
    /*Part 1: inicializar parametro de variables*/
    fsm_ptr->melody             =melody;
    fsm_ptr->melody_size        =melody_size;
    fsm_ptr->melody_pause       =melody_pause;
    fsm_ptr->melody_pin         =melody_pin;
    
    /*Part 2: inicializar contexto de variables*/
    
    fsm_ptr->note                       =0;
    fsm_ptr->halfcycle_in_micros        =0;
    fsm_ptr->max_cycles                 =0;
    fsm_ptr->previous                   =0;
    fsm_ptr->current                    =0;
    fsm_ptr->cycles                     =0;
    fsm_ptr->state                      =PLAYING_NOTES;
    fsm_ptr->finish                     =FALSE;


}/*Initiate_Play_Melody*/

void setup(void)
{

    pinMode( Pin_1, OUTPUT);

    Initiate_Play_Melody(&Melody_0, Super_Mario, Size_2, Pause_2, Pin_1);
    


} /* setup */



void loop(void)
{
  Play_Melody(&Melody_0);
 

  }


void
Play_Melody( FSM_T  *fsm_ptr){
if( !fsm_ptr->finish) {  

    switch( fsm_ptr->state ) {

        case PLAYING_NOTES:
            if( fsm_ptr->note < fsm_ptr->melody_size ) {
                fsm_ptr->halfcycle_in_micros = 1000000 / fsm_ptr->melody[fsm_ptr->note].tone / 2;
                fsm_ptr->max_cycles  = fsm_ptr->melody[fsm_ptr->note].tone * fsm_ptr->melody[fsm_ptr->note].length / 1000;
                fsm_ptr->cycles = 0;
                fsm_ptr->state = GENERATING_CYCLE;
            } else {
                fsm_ptr->finish = TRUE;
                //lines for playing again
                //fsm_ptr->note=0;
                //fsm_ptr->state= GENERATING_CYCLE;
            }
        break;

        case GENERATING_CYCLE:
            if( fsm_ptr->cycles < fsm_ptr->max_cycles ) {
                digitalWrite( fsm_ptr->melody_pin, HIGH );
                fsm_ptr->current = fsm_ptr->previous = micros();
                fsm_ptr->state = KEEPING_HIGH_LEVEL;
            } else {
                fsm_ptr->current = fsm_ptr->previous = millis();
                fsm_ptr->state = PAUSING_BETWEEN_TONES;
            }
        break;

        case KEEPING_HIGH_LEVEL:
            if( fsm_ptr->current - fsm_ptr->previous < fsm_ptr->halfcycle_in_micros ) {
                fsm_ptr->current = micros();
                fsm_ptr->state = KEEPING_HIGH_LEVEL;
            } else {
                digitalWrite( fsm_ptr->melody_pin, LOW );
                fsm_ptr->current = fsm_ptr->previous = micros();
                fsm_ptr->state = KEEPING_LOW_LEVEL;
            }
        break;

        case KEEPING_LOW_LEVEL:
            if( fsm_ptr->current - fsm_ptr->previous < fsm_ptr->halfcycle_in_micros ) {
                fsm_ptr->current = micros();
                fsm_ptr->state = KEEPING_LOW_LEVEL;
            } else {
                digitalWrite( fsm_ptr->melody_pin, LOW );
                fsm_ptr->cycles++;
                fsm_ptr->state = GENERATING_CYCLE;
            }
        break;

        case PAUSING_BETWEEN_TONES:
            if( fsm_ptr->current - fsm_ptr->previous < fsm_ptr->melody[fsm_ptr->note].length * fsm_ptr->melody_pause ) {
                fsm_ptr->current = millis();
                fsm_ptr->state = PAUSING_BETWEEN_TONES;
            } else {
                fsm_ptr->note++;
                fsm_ptr->state = PLAYING_NOTES;
            }
        break;

    } /* switch */

} /* while */

} /* Play_Melody */

