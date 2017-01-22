#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void drawBoard ();
void getInput (char *input);
void writeToFile (FILE *file, char *input);
void checkValid (char *tokenOne, char *tokenTwo, char *tokenThree, int direction,
                 int locY, int locX, int preMode, int *validMove, int amount, int turtle);
void makeMove (char *tokenOne, char *theChar, int amount, int *direction, int *locY, 
               int *locX, int homeY, int homeX, int *penMode, int preMode, int *turtle);
void clearInput ();
void clearMessage ();
void printMessage (char *input, char *tokenOne, char *tokenTwo, char *tokenThree, int penMode,
                   int validMove);
