/// file: voltorbFlip.c
/// author: rmh2805@rit.edu
/// purpose: An implementation of voltorbFlip in C (for command line)

#ifndef  _CARD_H_
#define  _CARD_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct card_s * card_t;

card_t createCard(unsigned char val);

void deleteCard(card_t card);

#endif //_CARD_H_
