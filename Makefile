all:
	clear && g++ ./*.cpp -obreakaway-basic -Wall -Wextra || exit 1
	clear && ./breakaway-basic
