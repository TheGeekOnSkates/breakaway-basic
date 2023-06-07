all:
	clear && g++ ./*.cpp -obreakaway-basic -Wall -Wextra -lreadline || exit 1
	./breakaway-basic && clear

no-readline:
	clear && g++ ./*.cpp -obreakaway-basic -Wall -Wextra || exit 1
	./breakaway-basic && clear

if-test:
	exit 123
