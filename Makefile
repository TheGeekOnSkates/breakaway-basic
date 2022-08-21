linux:
	clear && gcc ./*.c ./os/*.c -obreakaway-basic -Wall || exit 1
	./breakaway-basic

debug:
	clear && gcc ./*.c ./os/*.c -obreakaway-basic -Wall -g || exit 1
