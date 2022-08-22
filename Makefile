linux:
	clear && gcc ./*.c ./os/*.c -obreakaway-basic -Wall -lm -lreadline || exit 1
	./breakaway-basic

debug:
	clear && gcc ./*.c ./os/*.c -obreakaway-basic -Wall -g -lm -lreadline || exit 1
