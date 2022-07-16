all:
	clear && gcc ./*.c ./os-dependent/*.c -obreakaway-basic -lm || exit 1
	./breakaway-basic

debug:
	clear && gcc ./*.c ./os-dependent/*.c -obreakaway-basic -lm -Wall || exit 1
