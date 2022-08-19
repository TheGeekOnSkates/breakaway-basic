#include "../main.h"

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

inline bool GoToFolder(char* folder) {
	char* newline = strstr(folder, "\n");
	if (newline != NULL) newline[0] = '\0';
	return chdir((const char*)folder) == -1;
}
