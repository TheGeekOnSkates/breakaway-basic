# Breakaway BASIC

## Overview

Breakaway BASIC is a shell for Linux (and maybe someday, DOS and other systems) inspired by the 8-bit BASICs of the 1970s and 80s.  Its design was meant to be simpler than other shells (yes, I'm cmparing it to Bash again, lol), fully functional for scripting but also just fun to play with.  It could be used to create games, or it could be used to write scripts that actually do useful stuff.

It gets its name from hockey, of course (look at my nickname if you don't get why that's so obvious, lol).  A "breakaway" is one of the most exciting things you could see at a hockey game.  It's when a player manages to get past all the opposing team's defenders, so it's just him/her vs. the goalie.  Breakaways are rare, but they're always described as fast, cool, and sometimes game-changing - all things I would like this BASIC to be. :)

## Change log

### 0.1

The first release was just a superset of "Tiny BASIC", the main additions being things like ASCII art functions and LOAD/SAVE.


==============================================================================

## Language reference

### BG {expression}

Sets the background color, if your terminal supports that (most do)).  After you run it, any text you type will have the background color you set.  One cool thing you can do is use this to set the background color of the entire screen.  For example:

```
10 BG 4
20 CLEAR
```

For both this and the `FG` command, the colors on most terminals are:

0. Black or dark gray
1. Red
2. Green
3. Yellow
4. Blue
5. Magenta
6. Cyan
7. White

### BLINK ON/OFF

Turns blinking text on/off.  When it's on, any text you type will blink like the cursor.  For example:

```
10 BLINK ON
20 PRINT "THIS TEXT WILL BLINK."
30 BLINK OFF
40 PRINT "THIS TEXT WILL NOT."
```

### BOLD ON/OFF

Turns bold text on or off.  For example:

```
10 BOLD ON
20 PRINT "THIS TEXT WILL BE BOLD."
30 BOLD OFF
40 PRINT "THIS TEXT WILL NOT."
```

### CD {string}

Changes the folder you're working in (most systems call this the "working directory").  Note that this is the _only_ way to change directory in Breakaway BASIC.  Here's how it works:

`CD "wherever"`

### CLEAR

Clears the screen.  This is used by a bunch of other examples (for instance, `BG`) so there's no need to repeat it here.

### END

Ends the program.  For example:

```
10 CLEAR  
20 PRINT "GUESS A NUMBER:  ";
30 INPUT N
40 IF N {} 7 THEN END
50 PRINT "YOU GUESSED IT!  7!"
```

### ESC {string}

Prints an ANSI escape code followed by whatever text you put in the string.  In fact, this is what `FG`, `BG`, `CLEAR`, `RESET`, `BLINK`, etc. use.  So if Breakaway BASIC doesn't have an instruction for an escape code you want to use, you can use it with the `ESC` instruction.  For example:

```
10 REM THIS IS EQUIVALENT TO "BG 4"
20 ESC "[34m"
```

### EXIT

Exits Breakaway BASIC.

### FG {expression}

Sets the foreground color (text color).  See the `BG` instruction for more info (a list of colors, and also how to use it).  Here's another example:

```
10 CLEAR
20 FG 4
30 PRINT "BREAKAWAY ";
40 FG 3
50 PRINT "BASIC"
60 RESET
```

### GOSUB {expression}

Jumps to a line number, and doesn't go back from there until it finds a `RETURN` instruction.  For example:

```
10 PRINT "BEFORE GOSUB"
20 GOSUB 100
30 PRINT "AFTER GOSUB"
40 END
100 PRINT "SEE HOW IT SKIPPED TO LINE 100?"
110 RETURN
```

### GOTO {expression}

Jumps to a line number.  One classic example (and if you ever played with any BASIC I'm sure you've done it) is this:

```
10 PRINT "BREAKAWAY!  ";
20 GOTO 10
```

Note that for version 0.1, the only way to stop this infinite loop is to exit Breakaway BASIC.  This change will (Lord willing) be fixed in version 0.2. :)

### HIDDEN ON/OFF

This works kind of like invisible ink: whatever you type will not be shown if this is turned on.  For example:

```
10 PRINT "TYPE A NUMBER, AND I WILL READ YOUR MIND..."
20 HIDDEN ON
30 INPUT N
40 HIDDEN OFF
50 PRINT "THE NUMBER IS:", N
```

### IF {conditions} THEN {number or statement}

Checks if the condition is true, and if so, goes to the number or runs the statement.  For example:

```
10 INPUT A
20 IF A < 7 THEN PRINT "TOO SMALL"
30 IF A > 7 THEN PRINT "TOO BIG"
40 REM "<>" MEANS "NOT IS NOT EQUAL TO" LIKE IN OTHER BASICS
50 IF A <> 7 THEN 80
60 IF A = 7 THEN PRINT "YOU GUESSED IT."
70 END
80 PRINT "PLEASE TRY AGAIN."
```

### INPUT {variable}

Asks you to enter some information, and saves it to a variable.  For now (version 0.1), only numbers are supported.  For an example, see `IF` above.  For more info on variables, see `LET` below.

### ITALIC ON/OFF

Turns italics on or off on terminals that support it.  For example:

```
10 ITALIC ON
20 PRINT "THIS TEXT WILL BE IN ITALICS."
30 ITALIC OFF
40 PRINT "BUT THIS WON'T.""
```

### LET {variable} = {expression}

Sets a variable.  Variables (as of version 0.1) can only be capital letters, just one character (longer names are not yet supported).  For example:

```
```

### LIST [{number}[ - {number}]]

### LOAD {string}

### MOVE {number or variable} {number or variable}

Moves the cursor to the given coordinates.  The first number is the horizontal ("X") coordinate, and the second number is the vertical ("Y") coordinate.  For example:

```
10 REM MOVE THE CURSOR TO 30, 20
20 REM OR IF YOU LIKE, ROW 20, COLUMN 30
30 LET X = 30
40 LET Y = 20
50 MOVE X Y
```

### NEW

Clears the program memory and any variables you may have set, so you are left with a clean slate (a "new" program).

### PRINT {expression}[, {expression}...]

Prints (displays) data on the screen.  I've used it all through this reference, but here are some more examples:

```
10 PRINT "2 + 2 = ", 2+2
20 PRINT "CHECK THIS OUT - ";
30 PRINT "THE SEMICOLON AT THE END TELLS BASIC NOT TO DO A LINE BREAK."
40 PRINT "ENTER A NUMBER:  ";
50 INPUT N
60 PRINT N,"SQUARED = ", N * N
```

### REM {comment}

A comment is like a note to yourself, so you know what your code is doing if you come back to it after a long time away.  For example:

```
10 REM 4 IS THE COLOR CODE FOR BLUE
20 BG BLUE
30 CLEAR
```

### RESET

Resets the terminal's text output to its default setting, undoing commands like `BOLD`, `BLINK`, `FG`, `BG`, etc.  This way you can turn them all off without having to write a bunch of lines like `UNDERLINE OFF`, `REVERSE OFF` etc.

### RETURN

Goes to wherever the program left off after it found a `GOSUB` instruction ("returning" to where it was before).  See `GOSUB` for more info and an example.

### REVERSE ON/OFF

Turns reverse text on/off (so for example, on most terminals it will cause text output to be black on white, not white on black).

```
10 REVERSE ON
20 PRINT "THIS TEXT WILL BE REVERSED."
30 REVERSE OFF
40 PRINT "THIS WON'T."
```

### RUN

Runs your program.

### SAVE {string}

Saves your program to a file (the string is the file name).

### SYS {string}

Runs a system command.  For example:

```
10 REM LIST STUFF IN THE CURRENT FOLDER
20 CLEAR
30 SYS "ls -la"
```

### UNDERLINE ON/OFF

Turns underline text on/off

```
10 UNDERLINE ON
20 PRINT "THIS WILL BE UNDERLINED."
30 UNDERLINE OFF
40 PRINT "THIS WON'T."
```
