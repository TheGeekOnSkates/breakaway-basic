#ifndef _ANSI_H
#define _ANSI_H

#define ANSI_CLEAR() printf("\x1b[1;1H\x1b[J")

#define ANSI_BOLD_ON() printf("\x1b[1m")
#define ANSI_BOLD_OFF() printf("\x1b[2m")

#define ANSI_RED() printf("\x1b[31m")
#define ANSI_GREEN() printf("\x1b[32m")
#define ANSI_YELLOW() printf("\x1b[33m")
#define ANSI_BLUE() printf("\x1b[34m")
#define ANSI_MAGENTA() printf("\x1b[35m")
#define ANSI_CYAN() printf("\x1b[36m")
#define ANSI_WHITE() printf("\x1b[37m")
#define ANSI_RED_BG() printf("\x1b[41m")
#define ANSI_GREEN_BG() printf("\x1b[42m")
#define ANSI_YELLOW_BG() printf("\x1b[43m")
#define ANSI_BLUE_BG() printf("\x1b[44m")
#define ANSI_MAGENTA_BG() printf("\x1b[45m")
#define ANSI_CYAN_BG() printf("\x1b[46m")
#define ANSI_WHITE_BG() printf("\x1b[47m")

#endif
