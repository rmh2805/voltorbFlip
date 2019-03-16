/// file: board.h
/// author: rmh2805@rit.edu
/// purpose: An implementation of a voltorb flip board

#ifndef  _BOARD_H_
#define  _BOARD_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "card.h"
#include "linkedList.h"

#define k_Side_Len 5

typedef struct board_s * board_t;

//==========================<Allocation and Freeing>===========================//
/**
  * Creates and allocates a game board
  * 
  * @note Will add size_t maxBombsPerRank, size_t maxSafeRanks
  * 
  * @param maxBombsPerRank The maximum number of bombs in a row or column (0 or >5 to disable)
  * @param maxSafeRanks The maximum number of rows/columns with no bombs (0 or > 5 to disable)
  * @return The created game board
  */
board_t createBord ();

/**
  * Destroys the given board
  * 
  * @param board The board to destroy
  */
void deleteBoard (board_t board);

//==================================<Setters>==================================//
/**
  * Gets the specified cell from the provided board
  * 
  * @param board The board to access
  * @param row The row to access
  * @param col The column to access
  */
void flipCell(board_t board, size_t row, size_t col);

/**
  * Add a note to the specified cell
  * 
  * @param board The board to modify
  * @param row The row to modify
  * @param col The column to modify
  * @param noteVal What note to set
  */
void noteCell(board_t board, size_t row, size_t col, unsigned noteVal);

void flipAll(board_t board);

//==================================<Getters>==================================//
/**
  * Gets the score of the game
  * 
  * @param board The score of this board
  */
size_t scoreBoard(board_t board);

/**
  * Checks if the provided board has finished its game
  * 
  * @param board The game board to check
  * @return Whether or not the game is over
  */ 
bool gameOver(board_t board);

/**
  * Checks the number of cells that need to be revealed
  * 
  * @param board The board to check
  * @return the number of cells left to reveal
  */
size_t cellsToReveal(board_t board);

//=================================<Printers>==================================//
/**
  * Prints out the board properly
  * 
  * @param board The board to print out
  */ 
void printBoard(board_t board, const char * input);

void printSeparator();

#endif //_BOARD_H_
