10 CLEAR
20 PRINT "1. Debug mode"
30 PRINT "2. Release mode"
40 INPUT M
50 IF M = 1 THEN 1000
60 IF M = 2 THEN 2000
999 END
1000 REM DEBUG MODE
1010 CLEAR
1020 gcc ./*.c ./os/*.c -obreakaway-basic -Wall -Wextra -g -lm -lreadline
1030 IF RC() <> 0 THEN END
1040 valgrind ./breakaway-basic
2000 REM RELEASE MODE
2010 gcc ./*.c ./os/*.c -obreakaway-basic -lm -lreadline
2020 IF RC() <> 0 THEN END
2030 ./breakaway-basic
