all:
	clear && gcc ./*.c ./os-dependent/*.c -obreakaway-basic -lm -lncurses || exit 1
	./breakaway-basic

debug:
	clear && gcc ./*.c ./os-dependent/*.c -obreakaway-basic -lm -lncurses -Wall || exit 1
