/// file: voltorbFlip.c
/// author: rmh2805@rit.edu
/// purpose: An implementation of voltorbFlip in C (for command line)

#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"
#include "card.h"

int main () {
    card_t card = createCard(0);
    flipCard(card);
    printCard(card);
    deleteCard(card);
    
    card = createCard(1);
    flipCard(card);
    printCard(card);
    deleteCard(card);
    
    card = createCard(2);
    flipCard(card);
    printCard(card);
    deleteCard(card);
    
    card = createCard(3);
    flipCard(card);
    printCard(card);
    deleteCard(card);
    
    card = createCard(0);
    for(int i = 0; i <= 3; i++){
        printCard(card);
        addNote(card, i);
    }
    for(int i = 0; i <= 3; i++){
        printCard(card);
        rmNote(card, i);
    }
    printCard(card);
    deleteCard(card);

    return EXIT_SUCCESS;
}
