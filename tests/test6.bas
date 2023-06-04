1 REM TEST 6: Demonstrates the problem with infinite loops; this program
2 REM makes the screen flash like crazy (and it's greased lightning! :D)
3 REM but the only way to exit is to close the kill the process
10 printf "\e[40m"
11 clear
20 printf "\e[41m"
21 clear
30 printf "\e[42m"
31 clear
40 printf "\e[43m"
41 clear
50 printf "\e[44m"
51 clear
60 printf "\e[45m"
61 clear
70 printf "\e[46m"
71 clear
80 printf "\e[47m"
81 clear
90 printf "\e[48m"
91 clear
100 printf "\e[49m"
101 clear
110 goto 10

