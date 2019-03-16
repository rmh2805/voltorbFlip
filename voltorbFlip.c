/// file: voltorbFlip.c
/// author: rmh2805@rit.edu
/// purpose: An implementation of voltorbFlip in C (for command line)

#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <string.h>

#include "card.h"
#include "board.h"

#define k_Buf_Size 32

#define k_Note_Flag '#'
#define k_Select_Flag '!'
#define k_Help_Flag '?'
#define k_Quit_Flag '`'

void printHelp () {
    printf("Note format: %c[row][col]\n", k_Note_Flag);
    printf("Selection format: %c[row][col]\n", k_Select_Flag);
    printf("To review help: %c\n", k_Help_Flag);
    printf("To quit the game: %c\n", k_Quit_Flag);
}

void printIntro () {
    printf("\t\t=====Welcome to Voltorb Flip=====\n\n");
    printHelp();
}

int main () {
    srand(time(0));
    
    char * buf = calloc(k_Buf_Size, sizeof(char));
    board_t board = createBord();
    if(board == NULL || buf == NULL)
        return EXIT_FAILURE;
    
    printIntro();
    printf("\nPress <Enter> to continue");
    fgets(buf, k_Buf_Size, stdin);
    
    
    printBoard(board, NULL);
    while(!gameOver(board)){
        printf("Enter your command: ");
        fgets(buf, k_Buf_Size, stdin);
        
        if (buf[0] == k_Quit_Flag) {
            buf[1] = '\0';
            flipAll(board);
            printBoard(board, buf);
        } else if (buf[0] == k_Help_Flag) {
            printSeparator();
            buf[1] = '\0';
            printf("Your input: %s\n\n", buf);
            printHelp();
            printf("\n");
        } else if (buf[0] == k_Note_Flag) {
            if (strlen(buf) >= 4) {
                int row = buf[1] - '0';
                int col = buf[2] - 'A';
                
                if(col < 0 || col >= k_Side_Len)
                    col = buf[2] - 'a';
                
                
                if (row < 0 || row >= k_Side_Len || 
                        col < 0 || col >= k_Side_Len) {
                    printBoard(board, "<Invalid Input>");
                } else {
                    for (size_t i = 3; i < strlen(buf); i++) {
                        int note = buf[i] - '0';
                        if (note >= 0 && note <= 3)
                            noteCell(board, row, col, note);
                    }
                    printBoard(board, buf);
                }
            } else {
                printBoard(board, "<Invalid Input>");
            }
        } else if (buf[0] == k_Select_Flag) {
            if (strlen(buf) >= 3) {
                buf[3] = '\0';
                int row = buf[1] - '0';
                int col = buf[2] - 'A';
                if(col < 0 || col >= k_Side_Len)
                    col = buf[2] - 'a';
                
                if (row < 0 || row >= k_Side_Len || 
                        col < 0 || col >= k_Side_Len) {
                    printBoard(board, "<Invalid Input>");
                } else {
                    flipCell(board, row, col);
                    if(gameOver(board))
                        flipAll(board);
                    printBoard(board, buf);
                }
            } else {
                printBoard(board, "<Invalid Input>");
            }
            
            
        } else {
            printBoard(board, "<Invalid Input>");
        }
    }
    
    printf("\nPress <Enter> to continue");
    fgets(buf, k_Buf_Size, stdin);
    free(buf);
    deleteBoard(board);
    printf("\n");
    return EXIT_SUCCESS;
}
