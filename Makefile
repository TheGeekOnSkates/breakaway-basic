all:
	clear && gcc ./*.c ./os-dependent/*.c -obreakaway-basic -lm || exit 1
	./breakaway-basic

