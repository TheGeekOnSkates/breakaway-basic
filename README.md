# Breakaway BASIC

## Overview

Breakaway BASIC is a shell for Linux (and maybe someday, DOS and other systems) inspired by the 8-bit BASICs of the 1970s and 80s.

## Language reference

### BG <expression>

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

### CD <string>

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
40 IF N <> 7 THEN END
50 PRINT "YOU GUESSED IT!  7!"
```

### ESC <string>

Prints an ANSI escape code followed by whatever text you put in the string.  In fact, this is what `FG`, `BG`, `CLEAR`, `RESET`, `BLINK`, etc. use.  So if Breakaway BASIC doesn't have an instruction for an escape code you want to use, you can use it with the `ESC` instruction.  For example:

```
10 REM THIS IS EQUIVALENT TO "BG 4"
20 ESC "[34m"
```

### EXIT

Exits Breakaway BASIC.

### FG <expression>

Sets the foreground color (text color).  See the `BG` instruction for more info (a list of colors, and also how to use it).  Here's another example:

```
```

### GOSUB <expression>

### GOTO <expression>

### HIDDEN ON/OFF

### IF <conditions> THEN <number or statement>

### INPUT <variable>

### ITALIC ON/OFF

### LET <variable> = <expression>

### LIST [<number>[ - <number>]]

### LOAD <string>

### MOVE <number> <number>

### NEW

### PRINT <expression>[, <expression>...]

### REM <comment>

A comment is like a note to yourself, so you know what your code is doing if you come back to it after a long time away.  For example:

```
10 REM 4 IS THE COLOR CODE FOR BLUE
20 BG BLUE
30 CLEAR
```



### RESET

### RETURN

### REVERSE ON/OFF

### RUN

### SAVE <string>

### SYS <string>

### UNDERLINE ON/OFF
