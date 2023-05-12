/* Ruler 1         2         3         4         5         6         7        */

/*****************************  melody_player.h  ******************************/
/*                                                                            */
/*   Purpose: Play a short melody stored in array                             */
/*                                                                            */
/*   Notes:   Generation of tone in a parallel port is executed by software   */
/*                                                                            */
/******************************************************************************/

#ifndef MELODY_PLAYER_H
#define MELODY_PLAYER_H

/**********************  Declarations of Tone Type (TONE_T)  ******************/

typedef struct {
    unsigned int  tone;   /* Tone [cycles per second: cps] */
    unsigned long length; /* Time for reproducing tone [milliseconds] */
} TONE_T;



/**********************  Declarations of Public Functions  ********************/

void Play_Tone( int tone_pin,
               unsigned int tone_in_cps, unsigned long tone_duration_in_millis );
void Play_Melody( TONE_T *melody,
                 unsigned int melody_size, double melody_pause, int melody_pin );

#endif /* MELODY_PLAYER_H */
