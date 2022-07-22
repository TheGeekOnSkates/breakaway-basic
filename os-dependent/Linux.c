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
