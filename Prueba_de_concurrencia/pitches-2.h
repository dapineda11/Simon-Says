/* Ruler 1         2         3         4         5         6         7        */

/********************************  pitches.h  *********************************/
/*                                                                            */
/*   Purpose: Definition of frequencies of tones in a keyboard piano          */
/*                                                                            */
/*   Origin:  Written and tested by ------------, August 21th, 2015           */
/*                                                                            */
/*   Notes:                                                                   */
/*   This file defines 9 octaves of musical notes in a piano keyboard.        */
/*   Every octave has 12 different notes: The 7 notes C, D, E, F, G, A, B,    */
/*   and the 5 notes CS, DS, FS, GS, AS.                                      */
/*                                                                            */
/*   This file was built from excel file named "note_freq.xls" by jcgiraldo   */
/*                                                                            */
/*   The difference with the original file are:                               */
/*   Prefix "NOTE_" were eliminated to write longer melodies in file.         */
/*   This file contains more notes than original one.                         */
/*                                                                            */
/******************************************************************************/

#ifndef PITCHES_H
#define PITCHES_H

/**************************** Symbolic  Constants *****************************/

#define QT     0 /* QUIET */
#define SIL   18000

#define C0    16
#define CS0   17
#define D0    18
#define DS0   19
#define E0    21
#define F0    22
#define FS0   23
#define G0    24
#define GS0   26
#define A0    28
#define AS0   29
#define B0    31

#define C1    33
#define CS1   35
#define D1    37
#define DS1   39
#define E1    41
#define F1    44
#define FS1   46
#define G1    49
#define GS1   52
#define A1    55
#define AS1   58
#define B1    62

#define C2    65
#define CS2   69
#define D2    73
#define DS2   78
#define E2    82
#define F2    87
#define FS2   92
#define G2    98
#define GS2  104
#define A2   110
#define AS2  117
#define B2   123

#define C3   131
#define CS3  139
#define D3   147
#define DS3  156
#define E3   165
#define F3   175
#define FS3  185
#define G3   196
#define GS3  208
#define A3   220
#define AS3  233
#define B3   247

#define C4   262 /* MIDDLE C */
#define CS4  277
#define D4   294
#define DS4  311
#define E4   330
#define F4   349
#define FS4  370
#define G4   392
#define GS4  415
#define A4   440 /* REFERENCE */
#define AS4  466
#define B4   494

#define C5   523
#define CS5  554
#define D5   587
#define DS5  622
#define E5   659
#define F5   698
#define FS5  740
#define G5   784
#define GS5  831
#define A5   880
#define AS5  932
#define B5   988

#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976

#define C7  2093
#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951

#define C8  4186
#define CS8 4435
#define D8  4699
#define DS8 4978
#define E8  5274
#define F8  5588
#define FS8 5920
#define G8  6272
#define GS8 6645
#define A8  7040
#define AS8 7459
#define B8  7902

#endif /* PITCHES_H */
