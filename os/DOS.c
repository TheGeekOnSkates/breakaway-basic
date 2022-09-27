#include "../main.h"

#ifdef DOS

bool is_blocking = false;

bool IsBlocking() {
	return is_blocking;
}

void GetScreenSize(int* rows, int* columns) {
	*rows = 25;
	*columns = 80;
}

uint64_t GetBytesFree() {
	/* TO-DO: Figure out how to do this in DOS */
	return 1234567;
}

/* See https://gist.github.com/dagon666/8194870 */
void SetBlocking(bool setting) {
	/* TO-DO: Figure out how to do this in DOS */
}

inline bool GoToFolder(char* folder) {
	char* newline = strstr(folder, "\r");
	if (newline != NULL) newline[0] = '\0';
	return chdir((const char*)folder) != -1;
}

void ReadLine(char* buffer) {
	fgets(buffer, LINE_SIZE, stdin);
}

void get_autorun_file(char* path) {
	strncpy(path, "C:\BREAK.BAS", 13);
}

#endif
