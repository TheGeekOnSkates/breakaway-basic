# Breakaway BASIC User's Manual

## Command Reference

### BG number

Set the text background color.  This varies from one terminal to the next and from one system to the next.

### BLINK ON (or OFF)

Turns text blinking mode on or off

### BOLD ON (or OFF)

Turns bright/bold color on or off

### CLEAR or CLS

Clears the screen (assuming your terminal supports ANSI escape codes).

### CONT or CONTINUE

Runs the your program from wherever it left off

### END

Tells the interpreter it has reached the end of your program.  I'd like to say it "exits" your program, but that might be confused with EXIT below (which is not the same thing).  I think you get the idea. :)

### ESC string

Since escape codes vary from one terminal to the other, this prints the escape character (0x1B in hex, 27 decimal, or "\033" in... octal?) followed by whatever you type.  So for example, you could do:

`ESC [34m`

To make the text blue.  Of course we do include some more user-friendly ways to do stuff (i.e. BG, FG, REVERSE, BLINK, and MOVE), but if there's one I didn't add (or yours works different from mine) you can use ESC to print it.

### EXIT

Exits Breakaway BASIC.  Unlike Bash, C, and other languages there are no "exit codes."  If it exits with anything other than zero, it's because the OS said so.

### FAINT ON (or OFF)

Turns text "faint mode" on or off.  Note that some terminal documentation may call this "dim", but DIM is planned to be a keyword in this BASIC (as it is in most) so I went with FAINT.

### FG number

Set the text foreground color.  This varies from one terminal to the next and from one system to the next.

### GOTO line or GO TO line

Goes to a line number, like most BASICs have

### GOSUB line or GO SUB line

Similar to GOTO except that it when it finds a RETURN, it picks up where it left off.  Again, most BASICs have this.  See RETURN for more info.

### ITALIC ON (or OFF)

Turns text italic mode on or off

### LIST [line number [ - line number]]

Lists the contents of your program.  Examples:

* `LIST` shows you your entire program.
* `LIST 30` shows you just line 30.
* `LIST 40-70` shows just lines 40-70

### LOAD file

Loads a file.  Unlike other BASICs, there's no need to use quotes.  So you can just do i.e. `LOAD myfile.bas` or `LOAD ../path/to/my/file.bas`.

### MOVE x y

Moves the cursor to column x, row y.  This is different from other terminal control systems you may have used (which usually do it as row, then column, or y then x).  This is on purpose - as fun and retro as it is to have it backwards like that, more programmers today are familiar with x-y coordinates.

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

### RESET

Resets the terminal's color settings to the default

### RETURN

Moves the program just past where it was last time GOSUB was called.  For example:

```
10 GOSUB 100
20 SYS echo "Done."
99 END
100 CLEAR
110 RETURN
```

GOSUB will move it to line 100, which will clear the screen.  Then line 110 will tell it to go back to where it was before (so line 11).  Then it hits line 20 and prints "Done."

### REVERSE ON (or OFF)

Turns the terminal's "reverse mode" on

### RESET

Resets all terminal settings to the default.  Note that it doesn't clear any text (colored, blinking, reversed or otherwise) that was put there before - call CLEAR if you want a "blank slate".

### RUN

Runs the your program from the beginning

### SAVE file

Saves the current program to a file.  Like LOAD, don't use quotes around the file name.  Just do i.e. `SAVE myfile.bas` or `SAVE /path/to/my/file.bas` without them.  Note also that the file extension doesn't even have to be ".bas" - it can be ".txt" or anything you like.  Even no extension at all.

### SYS

Runs a system command or external program.

### UNDERLINE ON (or OFF)

Turns text underline mode on or off

