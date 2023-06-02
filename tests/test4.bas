1 REM Test #4: nested GOSUBs
2 REM Also, you can change line 30 to RETURN to test user error :)
10 gosub 100
20 printf "Done.\n"
30 end
100 printf "In sub 1\n"
110 gosub 200
120 printf "back in sub 1\n"
130 return
200 printf "In sub 2\n"
210 gosub 300
220 printf "Back in sub 2\n"
230 return
300 printf "In sub 3\n"
310 gosub 400
320 printf "Back in sub 3\n"
330 return
400 printf "\e[1;33mSweet!  It works\e[0m\n"
410 return
