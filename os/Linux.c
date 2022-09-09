#include "../main.h"

#ifdef Linux

bool is_blocking = false;

bool IsBlocking() {
	return is_blocking;
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
	is_blocking = setting;
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
	return chdir((const char*)folder) != -1;
}

void ReadLine(char* buffer) {
	char* temp = readline("");
	if (temp == NULL) {
		printf("?MEMORY ERROR\n");
		return;
	}
	strncpy(buffer, temp, LINE_SIZE);
	add_history(buffer);
	free(temp);
}

void get_autorun_file(char* path) {
	char home[512], username[80];
	memset(home, 0, 512);
	strncpy(home, "/home/", 512);
	struct passwd *pwd = getpwuid(getuid());
	if (getlogin_r(username, 80) == 0) {
		strncat(home, username, 512 - strlen(home));
		strncat(home, "/breakaway.bas", 512 - strlen(home));
		if (access(home, F_OK) == 0) {
			strncpy(path, home, 512);
			return;
		}
	}
	else if (pwd) {
		strncat(home, pwd->pw_name, 512 - strlen(home));
		strncat(home, "/breakaway.bas", 512 - strlen(home));
		strncpy(path, home, 512);
	}
	else strncpy(path, "/etc/breakaway.bas", 512);
}

#endif
