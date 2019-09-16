#ifndef  _FLIP_DISP_H_
#define  _FLIP_DISP_H_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int startDisp (int *numRows, int* numCols);

void drawBoard ();

int stopDisp ();

void flipCard (int row, int col, int val);

void setIndic (int row, int col, int bombs, int score);

#endif //_FLIP_DISP_H_
