#include "../main.h"

#ifdef Linux

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

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

void NewLine() {
	printf("\n");
}

#endif
