#include "main.h"

#if BUILD_TARGET == DOS

void NewLine() {
	printf("\r\n");
}

#else

void NewLine() {
	printf("\n");
}

#endif
