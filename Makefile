all:
	clear && g++ ./*.cpp -obreakaway-basic -Wall -Wextra -lreadline || exit 1
	clear && ./breakaway-basic

no-readline:
	clear && g++ ./*.cpp -obreakaway-basic -Wall -Wextra || exit 1
	clear && ./breakaway-basic

