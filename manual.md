# Breakaway BASIC User's Manual

## Command Reference

### CLEAR or CLS

Clears the screen (assuming your terminal supports ANSI escape codes).

### CONT or CONTINUE

Runs the your program from wherever it left off

### END

Tells the interpreter it has reached the end of your program.  I'd like to say it "exits" your program, but that might be confused with EXIT below (which is not the same thing).  I think you get the idea. :)

### EXIT

Exits Breakaway BASIC.  Unlike Bash, C, and other languages there are no "exit codes."  If it exits with anything other than zero, it's because the OS said so.

### LIST [line number [ - line number]]

Lists the contents of your program.  Examples:

* `LIST` shows you your entire program.
* `LIST 30` shows you just line 30.
* `LIST 40-70` shows just lines 40-70

### LOAD file

Loads a file.  Unlike other BASICs, there's no need to use quotes.  So you can just do i.e. `LOAD myfile.bas` or `LOAD ../path/to/my/file.bas`.

### NEW

Clears the contents of the program memory.  For example:

```
10 REM THIS COMMENT WILL GET ERASED BY "NEW"
READY.
LIST
10 REM THIS COMMENT WILL GET ERASED BY "NEW"

READY.

NEW

READY.
LIST

READY.
```

### REM [comment]

Comments are ignored by the interpreter.  They're a way for you to write notes in your code.

### RUN

Runs the your program from the beginning

### SAVE file

Saves the current program to a file.  Like LOAD, don't use quotes around the file name.  Just do i.e. `SAVE myfile.bas` or `SAVE /path/to/my/file.bas` without them.  Note also that the file extension doesn't even have to be ".bas" - it can be ".txt" or anything you like.  Even no extension at all.

### SYS

Runs a system command or external program.
