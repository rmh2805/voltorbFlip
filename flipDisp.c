#include "flipDisp.h"

#define indicPalette 2
#define unflipPalette 3
#define goodPalette 4
#define bombPalette 5


#define kNumFiles 5
#define kNumRanks 5
#define kCellWidth 7
#define kCellHeight 5

#define kMinRow 1
#define kMinCol 5
#define kMaxRow  kMinRow + (kNumRanks + 1) * kCellHeight + kNumRanks
#define kMaxCol  kMinCol + (kNumFiles + 1) * kCellWidth + kNumFiles

#define GET_LEFT_COL(colIn) kMinCol + (kCellWidth + 1) * (colIn + 1)
#define GET_TOP_ROW(rowIn) kMinRow + (kCellHeight + 1) * (rowIn + 1)

//=============================<Helper Functions>==============================//
void drawIndic (int rowIn, int colIn) {
    int row = GET_TOP_ROW(rowIn);
    int col = GET_LEFT_COL(colIn);
    
    wattron(stdscr, COLOR_PAIR(indicPalette));
    mvprintw(row + 0, col, "+=====+");
    mvprintw(row + 1, col, "|0: n |");
    mvprintw(row + 2, col, "|     |");
    mvprintw(row + 3, col, "|S: nn|");
    mvprintw(row + 4, col, "+=====+");
    refresh();
    wattroff(stdscr, COLOR_PAIR(indicPalette));
    move(0,0);
}

void drawBlankCard (int row, int col) {
    row = GET_TOP_ROW(row);
    col = GET_LEFT_COL(col);
    
    wattron(stdscr, COLOR_PAIR(unflipPalette));
    mvprintw(row + 0, col, "       ");
    mvprintw(row + 1, col, "       ");
    mvprintw(row + 2, col, "       ");
    mvprintw(row + 3, col, "       ");
    mvprintw(row + 4, col, "       ");
    refresh();
    wattroff(stdscr, COLOR_PAIR(unflipPalette));
    move(0,0);
}

//=============================<Extern Functions>==============================//
int startDisp (int *numRows, int* numCols) {
    //Start the curses environment and find the boundries of the window
    initscr();  // Start curses mode
    getmaxyx(stdscr, *numRows, *numCols);
    mvprintw( *numRows - 2, *numCols / 4, "maxCol is %d maxRow is %d", kMaxCol, kMaxRow);
    mvprintw( *numRows - 1, *numCols / 4, "screen is %d wide by %d high\n", *numCols, *numRows);
    
    if(*numRows <= kMaxRow || *numCols <= kMaxCol) {
        endwin(); 
        printf("Your terminal is too small\n");
        return 1;
    }
    
    if (has_colors() == FALSE) { 
        endwin(); 
        printf("Your terminal does not support color\n");
        return 1;
    }   
    
    start_color();
    init_pair(indicPalette, COLOR_BLACK, COLOR_WHITE);
    init_pair(unflipPalette, COLOR_WHITE, COLOR_YELLOW);
    init_pair(goodPalette, COLOR_BLACK, COLOR_GREEN);
    init_pair(bombPalette, COLOR_WHITE, COLOR_RED);

    return 0;
}

void drawBoard () {
    for(int col = 0; col < kNumFiles; col++) {
        drawIndic(-1, col);
        int center = GET_LEFT_COL(col) + kCellWidth/2;
        for(int row = 0; row < kNumRanks; row++) {
            mvaddch(GET_TOP_ROW(row) - 1, center, '|');
        } 
    }
    refresh();
    
    for(int row = 0; row < kNumRanks; row++) {
        drawIndic(row, -1);
        
        int center = GET_TOP_ROW(row) + kCellHeight/2;
        for(int col = 0; col < kNumFiles; col++) {
            mvaddch(center, GET_LEFT_COL(col) - 1, '-');
        } 
    }
    
    for(int row = 0; row < kNumRanks; row++) {
        for(int col = 0; col < kNumFiles; col++) {
            drawBlankCard(row, col);
        }
    }
    
    move(0,0);
    refresh();
}
/*
 *  int maxRow = minRow - 1 + cellHeight * numRanks;
    int maxCol = minCol - 1 + cellWidth * numFiles;

    mvaddch(minRow - 1, minCol - 1, '+');
    for(int col = minCol; col < maxCol + 1; col++) {
        mvaddch(minCol - 1, col, '-');
        refresh();
    }
    mvaddch(minRow - 1, maxCol + 1, '+');

    for (int row = minRow; row < maxRow + 1; row++) {
        mvaddch(row, minCol - 1, '|');
        for (int col = minCol; col < maxCol + 1; col ++) {
            int palette = blackPalette;

            if(((row - minRow) / cellHeight + (col - minCol) / cellWidth) % 2 == 0)
                palette = whitePalette;
            
            wattron(stdscr, COLOR_PAIR(palette));
            mvaddch(row, col, ' ');
            move(row, col);
            refresh();
            wattroff(stdscr, COLOR_PAIR(palette));   

        }
        mvaddch(row, maxCol + 1, '|');
        refresh();
    }

    mvaddch(maxRow + 1, minCol - 1, '+');
    for(int col = minCol; col < maxCol + 1; col++) {
        mvaddch(maxRow + 1, col, '-');
        refresh();
    }
    mvaddch(maxRow + 1, maxCol + 1, '+');

    refresh();

    for(int file = 0; file < numFiles; file++) {
        mvaddch(minRow - 2, cellWidth * file + minCol + cellWidth / 2, 'A' + file);
    }

    for(int rank = 0; rank < numRanks; rank++) {
        mvaddch(cellHeight * rank + minRow + cellHeight / 2, minCol - 2, '1' + rank);
    }
    move(0, 0);
 */

int stopDisp () {
    
    endwin(); 
    return 0;
}

void flipCard (int row, int col, int val) {
    int palette = bombPalette;
    if(val)
        palette = goodPalette;
    
    row = GET_TOP_ROW(row);
    col = GET_LEFT_COL(col);
    
    char* buf = malloc(7);
    sprintf(buf, "   %d   ", val);
    
    wattron(stdscr, COLOR_PAIR(palette));
    mvprintw(row + 0, col, "       ");
    mvprintw(row + 1, col, "       ");
    mvprintw(row + 2, col, buf);
    mvprintw(row + 3, col, "       ");
    mvprintw(row + 4, col, "       ");
    refresh();
    wattroff(stdscr, COLOR_PAIR(palette));
    move(0,0);
    free(buf);
}

void setIndic (int row, int col, int bombs, int score) {
    row = GET_TOP_ROW(row);
    col = GET_LEFT_COL(col);
    
    char* buf = malloc(7);
    wattron(stdscr, COLOR_PAIR(indicPalette));
    sprintf(buf, "|0: %d |", bombs);
    mvprintw(row + 1, col, buf);
    refresh();
    sprintf(buf, "|S: %02d|", score);
    mvprintw(row + 3, col, buf);
    refresh();
    wattroff(stdscr, COLOR_PAIR(indicPalette));
    move(0,0);
    free(buf);
    
}
