/// file: board.c
/// author: rmh2805@rit.edu
/// purpose: An implementation of a voltorb flip board

#include "board.h"

struct board_s {
    linkedList_t data;
    size_t score;
    size_t toReveal;
    bool gameOver;
};

static card_t getCell (board_t board, size_t row, size_t col) {
    if(board == NULL)
        return NULL;
    if(board->data == NULL)
        return NULL;
        
    linkedList_t rowLs = getIdx(board->data, row);
    if(rowLs == NULL)
        return NULL;
    
    return getIdx(rowLs, col);
}

static void printTopBanner () {
    printf("    ");
    for (size_t i = 0; i < k_Side_Len; i++) {
        printf("| %c ", 'A' + i);
    }
    printf("|\n");
}

static void printVertBorderBoard () {
    printf("===+");
    for (size_t i = 0; i < k_Side_Len; i++) {
        printVertBorder();
    }
    printf("++===\n");
}

static void printTopRowBoard(linkedList_t row){
    printf("   |");
    size_t rowScore = 0;
    for (size_t i = 0; i < k_Side_Len; i++) {
        card_t cell = getIdx(row, i);
        printTopRow(cell);
        if(!beenFlipped(cell))
            rowScore += getVal(cell);
    }
    printf("|| %ld\n", rowScore);
}

static void printMidRowBoard(linkedList_t row, size_t rowNum){
    printf(" %ld |", rowNum);
    for (size_t i = 0; i < k_Side_Len; i++) {
        printMidRow(getIdx(row, i));
    }
    printf("||\n");
}

static void printBottomRowBoard(linkedList_t row){
    printf("   |");
    size_t mines = 0;
    size_t available = 5;
    for (size_t i = 0; i < k_Side_Len; i++) {
        card_t cell = getIdx(row, i);
        
        printBottomRow(cell);
        if(getVal(cell) == 0 && getNotes(cell) != 1){
            mines += 1;
        } 
        
        if (getNotes(cell) == 1 || beenFlipped(cell)) {
            available -= 1;
        }
    }
    printf("||%ld/%ld\n", mines, available);
}

static void printBottomBanner (board_t board) {
    size_t mines[5];
    size_t availables[5];
    
    printf("    ");
    
    for (size_t col = 0; col < k_Side_Len; col++) {
        size_t score = 0;
        size_t mine = 0;
        size_t available = 5;
        
        for(size_t row = 0; row < k_Side_Len; row++){
            card_t cell = getCell(board, row, col);
            unsigned val = getVal(cell);
            if (val == 0 && getNotes(cell) != 1) {
                mine += 1;
            }
            
            if (getNotes(cell) == 1 || beenFlipped(cell)) {
                available -= 1;
            }
            
                
            if(!beenFlipped(cell))
                score += getVal(cell);
        }
        
        printf("|%3ld", score);
        
        mines[col] = mine;
        availables[col] = available;
    }
    printf("|\n    ");
    for (size_t col = 0; col < k_Side_Len; col++) {
        printf("|%ld/%ld", mines[col], availables[col]);
    }
    printf("|\n");
}

void freeRow (void* row) {
    deleteLinkedList(row);
}

void freeCell (void* cell){
    deleteCard(cell);
}

//==========================<Allocation and Freeing>===========================//
board_t createBord () {
    board_t new = malloc(sizeof(struct board_s));
    
    if(new == NULL)
        return NULL;
    
    new->data = createLinkedList(freeRow);
    if(new->data == NULL){
        deleteBoard(new);
        return NULL;
    }
    
    new->gameOver = true;
    new->score = 0;
    new->toReveal = 0;
    
    for(int r = 0; r < k_Side_Len; r++){
        linkedList_t row = createLinkedList(freeCell);
        if(row == NULL){
            deleteBoard(new);
            return NULL;
        }
        append(new->data, row);
        
        for(int c = 0; c < k_Side_Len; c++){
            unsigned val = rand() % (k_Max_Card_Val + 1);
            
            if(val != 0 && val != 1) {
                new->gameOver = false;
                new->toReveal += 1;
            }
            
            card_t cell = createCard(val);
            if(cell == NULL){
                deleteBoard(new);
                return NULL;
            }
            append(row, cell);
        }
        
    }
    
    return new;
}

void deleteBoard (board_t board) {
    if(board != NULL){
        deleteLinkedList(board->data);
        free(board);
    }
}

//==================================<Setters>==================================//
void flipCell (board_t board, size_t row, size_t col) {
    //IF given seemingly valid arguments
    if(board == NULL && row >= k_Side_Len && col >= k_Side_Len)
        return;
        
    //Grab our cell
    card_t cell = getCell(board, row, col);
        
        //If a valid cell && it hasn't been flipped
    if (cell == NULL || beenFlipped(cell))
        return;
        
    //flip it
    flipCard(cell);
    unsigned val = getVal(cell);
    
    if (val == 0) { 
        //If that flip ended the game, mark it
        board->gameOver = true;
        return;
    } 
    
    if(val != 1)
        board->toReveal -= 1;
    
    if (!board->gameOver && board->score == 0) {
        //Otherwise if game isn't over and this is first card, set initial score
        board->score = val;
    } else if (!board->gameOver) {
        //Otherwise, if game isn't over, update the score
        board->score = board->score * val;
    }
}

void noteCell (board_t board, size_t row, size_t col, unsigned noteVal) {
    //IF given seemingly valid arguments
    if(board == NULL && row >= k_Side_Len && col >= k_Side_Len)
        return;
        
    //Grab our cell
    card_t cell = getCell(board, row, col);
        
    //If a valid cell && it hasn't been flipped
    if (cell == NULL && beenFlipped(cell))
        return;
        
    switch(noteVal){
    case 0:
        if(noted0(cell))
            rmNote(cell, noteVal);
        else 
            addNote(cell, noteVal);
        break;
    case 1:
        if(noted1(cell))
            rmNote(cell, noteVal);
        else 
            addNote(cell, noteVal);
        break;
    case 2:
        if(noted2(cell))
            rmNote(cell, noteVal);
        else 
            addNote(cell, noteVal);
        break;
    case 3:
        if(noted3(cell))
            rmNote(cell, noteVal);
        else 
            addNote(cell, noteVal);
        break;
    }
}

void flipAll(board_t board){
    for (size_t row = 0; row < k_Side_Len; row++) {
        for (size_t col = 0; col < k_Side_Len; col++) {
            flipCell(board, row, col);
        }
    }
}

//==================================<Getters>==================================//
size_t scoreBoard (board_t board) {
    if(board == NULL)
        return 0;
        
    return board->score;
}

bool gameOver (board_t board) {
    if(board == NULL)
        return true;
    
    if(board->toReveal == 0)
        board->gameOver = true;
    
    return board->gameOver;
}

size_t cellsToReveal (board_t board) {
    if(board == NULL)
        return 0;
        
    return board->toReveal;
}

//=================================<Printers>==================================//
void printBoard (board_t board, const char * input) {
    if (board == NULL)
        return;
    
    printSeparator();
    printf("Score: %ld\n", board->score);
    printf("To Flip: %ld\n", board->toReveal);
    if(input == NULL)
        printf("\n\n");
    else
        printf("Your input: %s\n\n", input);
    
    printTopBanner();
    printVertBorderBoard();
    for (size_t i = 0; i < k_Side_Len; i++) {
        linkedList_t row = getIdx(board->data, i);
        printVertBorderBoard();
        printTopRowBoard(row);
        printMidRowBoard(row, i);
        printBottomRowBoard(row);
    }
    printVertBorderBoard();
    printVertBorderBoard();
    
    printBottomBanner(board);
}

void printSeparator(){
    printf("===+===+===+");
    printVertBorderBoard();
}
