/// file: voltorbFlip.c
/// author: rmh2805@rit.edu
/// purpose: An implementation of voltorbFlip in C (for command line)

#ifndef  _CARD_H_
#define  _CARD_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct card_s * card_t;

//============================<Memory Modification>============================//
/**
  * Create an instance of a card ADT
  * 
  * @param val The value to assign to the card [0,3]
  * @return The allocated and created card (NULL if failed)
  */ 
card_t createCard (unsigned val);

/**
  * Frees the provided card
  * 
  * @param card The card to free
  */ 
void deleteCard (card_t card);

//==================================<Setters>==================================//
/**
  * Add a note to the given card
  * 
  * @param card The card to modify
  * @param noteValue The note to set on the card [0,3]
  */
void addNote(card_t card, unsigned noteValue);

/**
  * Removes a previously assigned note value from the card
  * 
  * @param card The card to modify
  * @param noteValue The value to remove from the note list
  */
void rmNote(card_t card, unsigned noteValue);

/**
  * Flip over this card
  * 
  * @param card The card to flip
  */
void flipCard (card_t card);

//==================================<Getters>==================================//
/**
  * Get the value of this card
  * 
  * @param card The card to check
  * @return the value (4 if failed)
  */
unsigned getVal (card_t card);

/**
  * Grab the notes of this card
  * 
  * @param card The card to check
  * @return A combined value [0,15] (16 if failed)
  * @note The bits, from most significant (8) to least significant (1) represent each possible digit in order (e.g. 8 -> 3)
  */
unsigned getNotes (card_t card);

/**
  * Checks if this card has been flipped
  * 
  * @param card The card to check
  * @return Whether or not this card has been flipped
  */
bool beenFlipped (card_t card);

/**
  * Checks if this card has 0 marked
  * 
  * @param card The card to check
  * @return Whether or not this card has 0 marked
  */
bool noted0 (card_t card);

/**
  * Checks if this card has 1 marked
  * 
  * @param card The card to check
  * @return Whether or not this card has 1 marked
  */
bool noted1 (card_t card);

/**
  * Checks if this card has 2 marked
  * 
  * @param card The card to check
  * @return Whether or not this card has 2 marked
  */
bool noted2 (card_t card);

/**
  * Checks if this card has 3 marked
  * 
  * @param card The card to check
  * @return Whether or not this card has 3 marked
  */
bool noted3 (card_t card);

//=================================<Printers>==================================//
/**
  * Prints a full representation of the card
  * 
  * @param card The card to print
  */
void printCard(card_t card);

/**
  * Prints the vertical border of a card
  */
void printVertBorder();

/**
  * Prints the top row of a card
  * 
  * @param card The card to print
  */
void printTopRow(card_t card);

/**
  * Prints the middle row of a card
  * 
  * @param card The card to print
  */
void printMidRow(card_t card);

/**
  * Prints the bottom row of a card
  * 
  * @param card The card to print
  */
void printBottomRow(card_t card);

#endif //_CARD_H_
