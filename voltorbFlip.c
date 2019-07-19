/// file: voltorbFlip.c
/// author: rmh2805@rit.edu
/// purpose: An implementation of the Voltorb Flip from pokemon HG in C (Command line only)


// Standard Library includes
#include <stdlib.h> // General functions and type definition
#include <stdio.h>  // Game IO
#include <time.h>   // Set the seed
#include <string.h> // Command parsing

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
    
    
    char* buf;
    
    return EXIT_SUCCESS;
}

