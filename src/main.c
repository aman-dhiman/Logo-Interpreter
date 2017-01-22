#include <stdio.h>
#include <header.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define PENUP 0
#define PENDOWN 1
#define VALID 1
#define HT 0
#define ST 1

int main () {
    initscr ();
    cbreak ();

    char input[100];
    char inputCopy[100];
    char *tokenOne, *tokenTwo, *tokenThree, *color, character;
    int locY, locX, amount, direction, penMode, preMode, validMove, homeX, homeY, turtle;
    FILE *fCommand;

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);

    locY = 18;
    locX = 49;
    homeY = 18;
    homeX = 49;
    direction = UP;
    penMode = PENDOWN;
    preMode = PENUP;
    turtle = ST;
    fCommand = fopen ("commands.txt", "w");
    color = "white";

    drawBoard ();

    getInput (input);

    do {
        for (int i = 0; i < 100; i++) {
            inputCopy[i] = input[i];
        }
        if (fCommand != NULL) {
            writeToFile (fCommand, input);
        }
        tokenOne = strtok (inputCopy, " ");
        tokenTwo = strtok (NULL, " ");
        tokenThree = strtok (NULL, " ");
        if (tokenTwo != NULL) {
            if (strcmp (tokenOne, "setpencolor") == 0) {
                if (strcmp (tokenTwo, "white") == 0) {
                    color = "white";
                }
                else if (strcmp (tokenTwo, "blue") == 0) {
                    color = "blue";
                }
                else if (strcmp (tokenTwo, "green") == 0) {
                    color = "green";
                }
                else if (strcmp (tokenTwo, "red") == 0) {
                    color = "red";
                }
                else if (strcmp (tokenTwo, "yellow") == 0) {
                    color = "yellow";
                }
            }
            else {
                amount = atol (tokenTwo);
            }
        }
        else {
            amount = 0;
        }
        checkValid (tokenOne, tokenTwo, tokenThree, direction, locY, locX, preMode,
                    &validMove, amount, turtle);

        if (strcmp (color, "white") == 0) {
            attron(COLOR_PAIR(1));
        }
        else if (strcmp (color, "blue") == 0) {
            attron(COLOR_PAIR(2));
        }
        else if (strcmp (color, "green") == 0) {
            attron(COLOR_PAIR(3));
        }
        else if (strcmp (color, "red") == 0) {
            attron(COLOR_PAIR(4));
        }
        else if (strcmp (color, "yellow") == 0) {
            attron(COLOR_PAIR(5));
        }

        if (validMove == VALID) {
            makeMove (tokenOne, &character, amount, &direction, &locY, &locX, homeY, homeX,
                      &penMode, preMode, &turtle);
        }
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(3));
        attroff(COLOR_PAIR(4));
        attroff(COLOR_PAIR(5));

        clearInput ();
        clearMessage ();
        printMessage (input, tokenOne, tokenTwo, tokenThree,  penMode, validMove);
        if ((strcmp (tokenOne, "fd") == 0)||(strcmp (tokenOne, "bk") == 0)) {
            preMode = penMode;
        }
        getInput (input);
    }
    while (strcmp (input, "quit") != 0);

fclose (fCommand);
endwin ();
return 0;
}
