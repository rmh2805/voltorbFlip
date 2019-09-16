/// file: voltorbFlip.c
/// author: rmh2805@rit.edu
/// purpose: An implementation of the Voltorb Flip from pokemon HG in C (Command line only)

#define _DEFAULT_SOURCE

// Standard Library includes
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>   
#include <string.h> 
#include <ncurses.h>

// Helper file includes
#include "flipDisp.h"

// Constant Definitions
#define kBufSize 32 // Maximum length of a command

// Command flag definitions
#define kNoteFlag '#'
#define kSelectFlag '!'
#define kHelpFlag '?'
#define kQuitFlag '`'

//  Main Function definition
int main (int argc, char** argv) {
    //=======================<Initialization>=======================//
    long seed = time(0);    // Get seed from time
    if(argc > 1)    // If a seed was specified
        seed = strtol(argv[1], NULL, 0);    // Grab seed from args
    srand(seed);
    
    int numRows = 0, numCols = 0;
    if(startDisp(&numRows, &numCols)) 
        return EXIT_FAILURE;
    
    drawBoard();
    
    //==========//
    setIndic(-1, 0, 5, 0);
    flipCard(0, 0, 0);
    flipCard(0, 1, 1);
    flipCard(0, 2, 2);
    flipCard(0, 3, 3);
    getch();
    
    
    stopDisp();
    
    return EXIT_SUCCESS;
}

