# Breakaway BASIC User's Manual

## Command Reference

### CONT or CONTINUE

Runs the your program from wherever it left off

### EXIT

Exits Breakaway BASIC.  Unlike Bash, C, and other languages there are no "exit codes."  If it exits with anything other than zero, it's because the OS said so.

### LIST [line number [ - line number]]

Lists the contents of your program.  Examples:

* `LIST` shows you your entire program.
* `LIST 30` shows you just line 30.
* `LIST 40-70` shows just lines 40-70

### REM [comment]

Comments are ignored by the interpreter.  They're a way for you to write notes in your code.

### RUN

Runs the your program from the beginning

### SYS

Runs a system command or external program.
