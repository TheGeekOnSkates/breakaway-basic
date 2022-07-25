#include "../main.h"

#ifdef Linux

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>

extern uint8_t lastError;

void ListHistory() {
	/*
	NOTE: A lot of this code came from here:
	https://stackoverflow.com/questions/38792542/readline-h-history-usage-in-c
	And it works.  The problem is that if I run LIST HISTORY twice, it
	crashes with a double free or link list corruption-related error.
	
	Unfortunately, I have yet to find docs on GNU readline, so for now
	my take on this is, "Better a memory leak than a crash." (lol).
	That's why the free* lines are commented out.
	Someone would have to call LIST HISTORY a ridiculous number of times
	for it to ever actually become a problem.  It would be nice to know
	more about how readline works under the hood, where and when it calls
	malloc or calloc or whatever, but I've got my own memory to manage
	without worrying about some happy-go-crashy library. :D
	*/
	HISTORY_STATE *myhist = history_get_history_state ();
	HIST_ENTRY **mylist = history_list();
	for (int i = 0; i < myhist->length; i++) {
		printf (" %s\n", mylist[i]->line);
		/* free_history_entry(mylist[i]); */
	}
	printf("\n");
	/*
	free(myhist);
	free(mylist);
	*/
}

inline void DeleteHistory() {
	clear_history();
}

inline char* ReadLine(char* prompt) {
	return readline(prompt);
}

void AddToHistory(char* code) {
	add_history(code);
}

void GetScreenSize(int* rows, int* columns) {
	static struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	*rows = w.ws_row;
	*columns = w.ws_col;
}

uint64_t GetBytesFree() {
	return sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
}

/* See https://gist.github.com/dagon666/8194870 */
void SetBlocking(bool setting) {
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	if (setting) {
		t.c_lflag |= ICANON;
		t.c_lflag |= ECHO;
		fcntl(0, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);
	}
	else {
		t.c_lflag &= ~ICANON;
		t.c_lflag &= ~ECHO;
		fcntl(0, F_SETFL, O_NONBLOCK);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

inline void NewLine() {
	printf("\n");
}

inline void GoToFolder(char* folder) {
	char* newline = strstr(folder, "\n");
	if (newline != NULL) newline[0] = '\0';
	#if DEBUG_MODE
	printf("folder = \"%s\"\n", folder);
	#endif
	if (chdir((const char*)folder) == -1)
		lastError = SYSTEM_ERROR;
}

#endif
