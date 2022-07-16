#include "../main.h"

#ifdef Linux

void GetScreenSize(int* rows, int* columns) {
	getmaxyx(stdscr, *rows, *columns);
}

uint64_t GetBytesFree() {
	return sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
}

/* See https://gist.github.com/dagon666/8194870 */
void SetBlocking(bool setting) {
	if (setting)
		noraw();
	else raw();
}

inline void NewLine() {
	addch('\n');
}

#endif
