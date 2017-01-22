#include <header.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define PENUP 0
#define PENDOWN 1
#define VALID 1
#define EXTRA 2
#define OUTOFBOUNDS 3
#define INVALIDCOMMAND 4
#define INVALIDAMOUNT 5
#define INVALIDINPUT 6
#define NOTCOLOR 7
#define HT 0
#define ST 1

void drawBoard() {
    for (int x = 0; x < 99; x++) {
        mvaddch (35, x, 45);
        mvaddch (37, x, 45);
        mvaddch (39, x, 45);
    }
    mvaddch (18, 49, '#');
    mvaddstr (36, 88, "[PEN DOWN]");
    move (38, 0);
    refresh();
}

void getInput(char *input) {
    getstr(input);
}

void writeToFile (FILE *file, char *input) {
    strcat (input, "\n");
    fputs (input, file);
}

void checkValid (char *tokenOne, char *tokenTwo, char *tokenThree, int direction,
                 int locY, int locX, int preMode, int *validMove, int amount, int turtle) {
    char theChar;
    int penMode, nextY, nextX;
    penMode = PENUP;
    *validMove = VALID;
    nextY = locY;
    nextX = locX;

    if (tokenThree != NULL) {
        *validMove = EXTRA;
    }
    else if (tokenTwo != NULL) {
        if ((strcmp (tokenOne, "fd") != 0)&&(strcmp (tokenOne, "bk") != 0)&&
            (strcmp (tokenOne, "rt") != 0)&&(strcmp (tokenOne, "lt") != 0)&&
            (strcmp (tokenOne, "pd") != 0)&&(strcmp (tokenOne, "pu") != 0)&&
            (strcmp (tokenOne, "st") != 0)&&(strcmp (tokenOne, "ht") != 0)&&
            (strcmp (tokenOne, "home") != 0)&&(strcmp (tokenOne, "setpencolor") != 0)) {
            *validMove = INVALIDCOMMAND;
        }
        else if ((strcmp (tokenOne, "setpencolor") == 0)&&((strcmp (tokenTwo, "white") != 0)&&
                 (strcmp (tokenTwo, "blue") != 0)&&(strcmp (tokenTwo, "green") != 0)&&
                 (strcmp (tokenTwo, "red") != 0)&&(strcmp (tokenTwo, "yellow") != 0 ))) {
            *validMove = NOTCOLOR;
        }
        else if (amount == 0) {
            *validMove = INVALIDAMOUNT;
        }
        else if ((strcmp (tokenOne, "pd") == 0)||(strcmp (tokenOne, "pu") == 0)||
                 (strcmp (tokenOne, "st") == 0)||(strcmp (tokenOne, "ht") == 0)||
                 (strcmp (tokenOne, "home") == 0)) {
            *validMove = INVALIDINPUT;
        }
        else if ((strcmp (tokenOne, "fd") == 0)||(strcmp (tokenOne, "bk") == 0)) {
            makeMove (tokenOne, &theChar, amount, &direction, &nextY, &nextX, 0, 0, 
                      &penMode, preMode, &turtle);
            mvaddch (nextY, nextX, theChar);

            if ((nextY > 34)||(nextY < 0)||(nextX > 98)||(nextX < 0)) {
                *validMove = OUTOFBOUNDS;
            }
            if (turtle == ST) {
                mvaddch (locY, locX, '#');
            }

        }
    }
    else if (tokenOne != NULL) {
        if ((strcmp (tokenOne, "fd") != 0)&&(strcmp (tokenOne, "bk") != 0)&&
            (strcmp (tokenOne, "rt") != 0)&&(strcmp (tokenOne, "lt") != 0)&&
            (strcmp (tokenOne, "pd") != 0)&&(strcmp (tokenOne, "pu") != 0)&&
            (strcmp (tokenOne, "st") != 0)&&(strcmp (tokenOne, "ht") != 0)&&
            (strcmp (tokenOne, "home") != 0)&&(strcmp (tokenOne, "setpencolor") != 0)) {
            *validMove = INVALIDCOMMAND;
        }

        else if ((strcmp (tokenOne, "fd") == 0)||(strcmp (tokenOne, "bk") == 0)||
            (strcmp (tokenOne, "rt") == 0)||(strcmp (tokenOne, "lt") == 0)||
            (strcmp (tokenOne, "setpencolor") == 0)) {
            *validMove = INVALIDAMOUNT;
        }
    }
    move (38, 0);
}

void makeMove (char *tokenOne, char *theChar, int amount, int *direction, int *locY, 
               int *locX, int homeY, int homeX, int *penMode, int preMode, int *turtle) {

    if (strcmp (tokenOne, "home") == 0) {
        if (preMode == PENUP) {
            mvaddch (*locY, *locX, ' ');
        }
        else {
            mvaddch (*locY, *locX, 'o');
        }

        *locY = homeY;
        *locX = homeX;
        move (*locY, *locX);
        if (*turtle == ST) {
            addch ('#');
        }
    }

    else if (strcmp (tokenOne, "fd") == 0) {
        switch (*direction) {
            case UP:
                if (*penMode == PENDOWN) {
                    for (int y = *locY; y >= *locY - amount; y--) {
                        mvaddch (y, *locX, 'o');
                    }
                }
                else {
                    switch (preMode) {
                        case PENUP:
                            mvaddch (*locY, *locX, ' ');
                            break;

                        case PENDOWN:
                            mvaddch (*locY, *locX, 'o');
                            break;
                    }
                }
                *locY = *locY - amount;
                move (*locY, *locX);
                *theChar = inch();
                if (*turtle == ST) {
                    mvaddch (*locY, *locX, '#');
                }
                break;

            case RIGHT:
                if (*penMode == PENDOWN) {
                    for (int x = *locX; x <= *locX + amount; x++) {
                        mvaddch (*locY, x, 'o');
                    }
                }
                else {
                    switch (preMode) {
                        case PENUP:
                            mvaddch (*locY, *locX, ' ');
                            break;

                        case PENDOWN:
                            mvaddch (*locY, *locX, 'o');
                            break;
                    }
                }
                *locX = *locX + amount;
                move (*locY, *locX);
                *theChar = inch();
                if (*turtle == ST) {
                    mvaddch (*locY, *locX, '#');
                }
                break;

            case DOWN:
                if (*penMode == PENDOWN) {
                    for (int y = *locY; y <= *locY + amount; y++) {
                        mvaddch (y, *locX, 'o');
                    }
                }
                else {
                    switch (preMode) {
                        case PENUP:
                            mvaddch (*locY, *locX, ' ');
                            break;

                        case PENDOWN:
                            mvaddch (*locY, *locX, 'o');
                            break;
                    }
                }
                *locY = *locY + amount;
                move (*locY, *locX);
                *theChar = inch();
                if (*turtle == ST) {
                    mvaddch (*locY, *locX, '#');
                }
                break;

            case LEFT:
                if (*penMode == PENDOWN) {
                    for (int x = *locX; x >= *locX - amount; x--) {
                        mvaddch (*locY, x, 'o');
                    }
                }
                else {
                    switch (preMode) {
                        case PENUP:
                            mvaddch (*locY, *locX, ' ');
                            break;

                        case PENDOWN:
                            mvaddch (*locY, *locX, 'o');
                            break;
                    }
                }
                *locX = *locX - amount;
                move (*locY, *locX);
                *theChar = inch();
                if (*turtle == ST) {
                    mvaddch (*locY, *locX, '#');
                }
                break;
        }
    }
    else if (strcmp (tokenOne, "bk") == 0) {
        switch (*direction) {
            case UP:
                if (*penMode == PENDOWN) {
                    for (int y = *locY; y <= *locY + amount; y++) {
                        mvaddch (y, *locX, 'o');
                    }
                }
                else {
                    switch (preMode) {
                        case PENUP:
                            mvaddch (*locY, *locX, ' ');
                            break;

                        case PENDOWN:
                            mvaddch (*locY, *locX, 'o');
                            break;
                    }
                }
                *locY = *locY + amount;
                move (*locY, *locX);
                *theChar = inch();
                if (*turtle == ST) {
                    mvaddch (*locY, *locX, '#');
                }
                break;

            case RIGHT:
                if (*penMode == PENDOWN) {
                    for (int x = *locX; x >= *locX - amount; x--) {
                        mvaddch (*locY, x, 'o');
                    }
                }
                else {
                    switch (preMode) {
                        case PENUP:
                            mvaddch (*locY, *locX, ' ');
                            break;

                        case PENDOWN:
                            mvaddch (*locY, *locX, 'o');
                            break;
                    }
                }
                *locX = *locX - amount;
                move (*locY, *locX);
                *theChar = inch();
                if (*turtle == ST) {
                    mvaddch (*locY, *locX, '#');
                }
                break;

            case DOWN:
                if (*penMode == PENDOWN) {
                    for (int y = *locY; y >= *locY - amount; y--) {
                        mvaddch (y, *locX, 'o');
                    }
                }
                else {
                    switch (preMode) {
                        case PENUP:
                            mvaddch (*locY, *locX, ' ');
                            break;

                        case PENDOWN:
                            mvaddch (*locY, *locX, 'o');
                            break;
                    }
                }
                *locY = *locY - amount;
                move (*locY, *locX);
                *theChar = inch();
                if (*turtle == ST) {
                    mvaddch (*locY, *locX, '#');
                }
                break;

            case LEFT:
                if (*penMode == PENDOWN) {
                    for (int x = *locX; x <= *locX + amount; x++) {
                        mvaddch (*locY, x, 'o');
                    }
                }
                else {
                    switch (preMode) {
                        case PENUP:
                            mvaddch (*locY, *locX, ' ');
                            break;

                        case PENDOWN:
                            mvaddch (*locY, *locX, 'o');
                            break;
                    }
                }
                *locX = *locX + amount;
                move (*locY, *locX);
                *theChar = inch();
                if (*turtle == ST) {
                    mvaddch (*locY, *locX, '#');
                }
                break;
        }
    }
    
    else if (strcmp (tokenOne, "rt") == 0) {
        switch (*direction) {
            case UP:
                if (amount == 90) {
                    *direction = RIGHT;
                }
                break;

            case RIGHT:
                if (amount == 90) {
                    *direction = DOWN;
                }
                break;

            case DOWN:
                if (amount == 90) {
                    *direction = LEFT;
                }
                break;

            case LEFT:
                if (amount == 90) { 
                    *direction = UP;
                }
                break;
        }
    }

    else if (strcmp (tokenOne, "lt") == 0) {
        switch (*direction) {
            case UP:
                if (amount == 90) {
                    *direction = LEFT;
                }
                break;

            case RIGHT:
                if (amount == 90) {
                    *direction = UP;
                }
                break;

            case DOWN:
                if (amount == 90) {
                    *direction = RIGHT;
                }
                break;

            case LEFT:
                if (amount == 90) {
                    *direction = DOWN;
                }
                break;
        }
    }

    else if (strcmp (tokenOne, "pd") == 0) {
        *penMode = PENDOWN;
    }

    else if (strcmp (tokenOne, "pu") == 0) {
        *penMode = PENUP;
    }

    else if (strcmp (tokenOne, "st") == 0) {
        *turtle = ST;
        mvaddch (*locY, *locX, '#');
    }

    else if (strcmp (tokenOne, "ht") == 0) {
        *turtle = HT;
        if (preMode == PENUP) {
        mvaddch (*locY, *locX, ' ');
        }
        else {
        mvaddch (*locY, *locX, 'o');
        }
    }

    move (38, 0);
}

void clearInput() {
    for (int x = 0; x < 99; x++) {
        mvaddch (38, x, ' ');
    }
    move (38, 0);
    refresh();
}

void clearMessage() {
    for (int x = 0; x < 99; x++) {
        mvaddch (36, x, ' ');
    }
    move (38, 0);
    refresh();
}

void printMessage(char *input, char *tokenOne, char *tokenTwo, char *tokenThree, 
                  int penMode, int validMove) {
    switch (validMove) {
        case INVALIDCOMMAND:
            mvaddstr (36, 0, "Don't know how to ");
            addstr (tokenOne);
            break;

        case INVALIDAMOUNT:
            mvaddstr (36, 0, "Invalid Input for ");
            addstr (tokenOne);
            addstr (": add valid amount to the command");
            break;

        case INVALIDINPUT:
            mvaddstr (36, 0, "Don't know how to ");
            addstr (input);
            break;

        case EXTRA:
            mvaddstr (36, 0, "Don't know how to ");
            addstr (input);
            break;

        case OUTOFBOUNDS:
            mvaddstr (36, 0, "Not possible, out of limits");
            break;

        case NOTCOLOR:
            mvaddstr (36, 0, "Not an acceptable color, choose between white, blue, green,");
            addstr(" red or yellow");
            break;

        case VALID:
            if ((tokenTwo == NULL)&&(tokenOne != NULL)) {
                mvaddstr (36, 0, tokenOne);
            }
            else if ((tokenThree == NULL)&&(tokenTwo != NULL)) {
                mvaddstr (36, 0, tokenOne);
                addstr (" : ");
                addstr (tokenTwo);
            }
        break;
    }
    if (penMode == PENUP) {
        mvaddstr (36, 88, "[PEN UP]");
    }
    else {
        mvaddstr (36, 88, "[PEN DOWN]");
    }
    move (38, 0);
    refresh();
}
