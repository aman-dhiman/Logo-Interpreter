target:
	gcc src/main.c src/functions.c -std=c99 -Wall -pedantic -lncurses -Iinclude -o run
