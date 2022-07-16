#include "main.h"

int peek(int x, int y) {
	if (x < 0 || y < 0) return -1;
	return mvwinch(stdscr, y, x);
}

bool poke(int x, int y, int value) {
	if (x < 0 || y < 0) return false;
	mvaddch(y, x, value);
	return true;
}
