/// file: voltorbFlip.c
/// author: rmh2805@rit.edu
/// purpose: An implementation of voltorbFlip in C (for command line)

#include <stdio.h>
#include "card.h"

struct card_s {
    unsigned val;
    unsigned notes;
    bool flipped;
};

//============================<Memory Modification>============================//
card_t createCard (unsigned val) {
    if(val < 0 || val > 3)
        return NULL;
        
    
    card_t new = malloc(sizeof(struct card_s));
    if(new == NULL)
        return NULL;
    
    new->val = val;
    new->notes = 0;
    new->flipped = false;
    
    return new;
}

void deleteCard (card_t card) {
    if(card != NULL)
        free(card);
}
//==================================<Setters>==================================//
void addNote (card_t card, unsigned noteValue) {
    if (card != NULL) {
        if(noteValue == 0 && !noted0(card)){
            card->notes += 1;
        } else if(noteValue == 1 && !noted1(card)){
            card->notes += 2;
        } else if(noteValue == 2 && !noted2(card)){
            card->notes += 4;
        } else if(noteValue == 3 && !noted3(card)){
            card->notes += 8;
        }
    }
}

void rmNote(card_t card, unsigned noteValue){
    if (card != NULL) {
        if(noteValue == 0 && noted0(card)){
            card->notes -= 1;
        } else if(noteValue == 1 && noted1(card)){
            card->notes -= 2;
        } else if(noteValue == 2 && noted2(card)){
            card->notes -= 4;
        } else if(noteValue == 3 && noted3(card)){
            card->notes -= 8;
        }
    }
}

void flipCard (card_t card) {
    if (card != NULL) {
        card->flipped = true;
    }
}

//==================================<Getters>==================================//
unsigned getVal (card_t card) {
    if(card == NULL)
        return 4;
    
    return card->val;
}

unsigned getNotes (card_t card) {
    if(card == NULL)
        return 16;
    
    return card->notes;
}

bool beenFlipped (card_t card) {
    if(card == NULL)
        return false;
    return card->flipped;
}

bool noted0 (card_t card) {
    if(card == NULL)
        return false;
    
    unsigned val = card->notes;
    
    if(noted3(card))
        val -= 8;
    if(noted2(card))
        val -= 4;
    if(noted1(card))
        val -= 2;
    
    return val >= 1;
}

bool noted1 (card_t card) {
    if(card == NULL)
        return false;
    
    unsigned val = card->notes;
    
    if(noted3(card))
        val -= 8;
    if(noted2(card))
        val -= 4;
    
    return val >= 2;
}

bool noted2 (card_t card) {
    if(card == NULL)
        return false;
    
    unsigned val = card->notes;
    
    if(noted3(card))
        val -= 8;
    
    return val >= 4;
}

bool noted3 (card_t card) {
    if(card == NULL)
        return false;
    
    return card->notes >= 8;
}

//=================================<Printers>==================================//
void printCard (card_t card) {
    printVertBorder();
    printf("\n");
    printTopRow(card);
    printf("\n");
    printMidRow(card);
    printf("\n");
    printBottomRow(card);
    printf("\n");
    printVertBorder();
    printf("\n");
}

void printVertBorder () {
    printf("+===+");
}

void printTopRow (card_t card) {
    if(card != NULL) {
        if(card->flipped)
            printf("|   |");
        else
            printf("|%c|%c|",noted0(card)?'0':' ' , noted1(card)?'1':' ');
    } else 
        printf("| | |");
}

void printMidRow (card_t card) {
    
    if(card != NULL) {
        if(card->flipped)
            printf("| %d |", card->val);
        else
            printf("|=+=|");
    } else
        printf("|=+=|");
}

void printBottomRow (card_t card) {
    
    if(card != NULL) {
        if(card->flipped)
            printf("|   |");
        else
            printf("|%c|%c|",noted2(card)?'2':' ' , noted3(card)?'3':' ');
    } else
        printf("|%c|%c|",noted2(card)?'2':' ' , noted3(card)?'3':' ');
}
