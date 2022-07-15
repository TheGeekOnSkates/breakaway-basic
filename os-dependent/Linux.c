#include "../main.h"

#ifdef Linux

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void SetBlocking(bool setting) {
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	if (!setting) {
		t.c_lflag &= ~ICANON;
		t.c_lflag &= ~ECHO;
	}
	else {
		t.c_lflag |= ICANON;
		t.c_lflag |= ECHO;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void NewLine() {
	printf("\n");
}

void GetKey(int *c) {
	//read(0, c, 1);
	*c = getchar();
}



#endif
