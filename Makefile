all:
	clear && gcc ./*.c ./os-dependent/*.c -obreakaway-basic -lm -lreadline || exit 1
	./breakaway-basic

debug:
	clear && gcc ./*.c ./os-dependent/*.c -obreakaway-basic -lm -lreadline -Wall || exit 1
