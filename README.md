# Breakaway BASIC

## Overview

Breakaway BASIC is a shell for Linux (and maybe someday, DOS and other systems) inspired by the 8-bit BASICs of the 1970s and 80s.  Its design was meant to be easier than other shells for practical automation, but also just fun to play with.  It could be used to create games, or it could be used to write scripts that actually do useful stuff.

It gets its name from hockey, of course (look at my nickname if you don't get why that's so obvious, lol).  A "breakaway" is one of the most exciting things you could see at a hockey game.  It's when a player manages to get past all the opposing team's defenders, so it's just him/her vs. the goalie.  Breakaways are rare, but they're always described as fast, cool, and sometimes game-changing - all things I would like this BASIC to be. :)

## Quick Start

If you're on an x86-based Linux distro, you don't need to build Breakaway BASIC (if you are on something else, please see "building" below).  There's an executable file already compiled; you might need to give it permission to run though:

`sudo chmod +x ./breakaway-basic`

When you run it, you'll see a title screen and a ridiculous number of "bytes free" (this is more a joke, a nod to Commodore BASIC, which has a tremendous influence on this BASIC).  From here you can type any of the commands below.  For example, one thing that was common in the 80s was to write something like this:

```
10 PRINT "BREAKAWAY! ";
20 GOTO 10
RUN
```

Before we go any further, it's worth mentioning that this BASIC, like the ones that inspired it, have two "modes":
1. "Program mode": If a line of code starts with a line number, that line is saved to your program.
2. "Direct mode": If you don't start with a line number, the code runs immediately.

If you type (or paste) this code into Breakaway BASIC, the word "BREAKAWAY!" will fill the screen, in a crazy wavy pattern, non-stop, until you press the Escape key.  This is the kind of goofy trick that makes BASIC fun.

Now for what makes this BASIC practical: system commands.  So first off, there is an SYS command.  For example, to bring up a list of files (assuming you're on Linux), you can do:

`SYS "ls -la"`

But the SYS command isn't the only way.  Anything that is not recognized as a Breakaway BASIC instruction is interpreted as a system command.  For example, you can do:

```
10 REM This demonstrates automating a journal writing process
20 cd /path/to/my/journal
30 date > journal.md
40 nano journal.md
```

You can save this code to a file, and then load it later.  If you use the extension ".bas" (which this BASIC doesn't require) you might also get some nice syntax highlighting in text editors, if you prefer to write your programs in that instead of entering the code into Breakaway BASIC directly.

## Building

For now, the only supported build target is Linux, and the only library I use is GNU readline.  To install it on Debian-based systems, run:

```
sudo apt-get install libreadline-dev
```

Alternatively, you can remove this dependency by going to os/Linux.c and getting rid of the readline stuff.  Delete the #includes and replace readline and add_history with fgets or something like that.


## Change log

### 0.3

* Added an optional auto-run file, to run a set of instructions on startup
* Added the `ALIAS` instruction
* Made the `LET` keyword optional (you can just do i.e. `X = 42` now).
* Bugfixes in `LIST`, `GOTO`, and lowercase `CD`
* Code changes "under the hood" that are different enough from 0.2 to mention.

### 0.2

* Tried to set up "normal" `CD` (normal meaning like other shells).  So both `CD "wherever"` AND `cd wherever` work.
* Added the `CURSOR ON/OFF` instruction
* Set up the Linux version to use GNU readline, including history
* Set up the Escape key to stop running the current program
* Added the `ASC("{character}")` instruction to get the ASCII character codes (like in Commodore BASICs); note that for now it's just ASCII; Unicode characters like "▄" are not supported yet.
* Added the `CONT` instruction to continue the program (pick up where it left off)
* Added the `ROWS()` and `COLUMNS()` functions for getting the terminal size
* Added the `RC()` function to get the return value of the last `SYS` instruction
* Added the `FRE()` function (like Commodore BASICs) - not important at all, but it's fun. :)

### 0.1

The first release was just a superset of "Tiny BASIC", the main additions being things like ASCII art functions and LOAD/SAVE.


==============================================================================

## Language reference

### ASC({character})

Gets the ASCII character code that corresponds to the character you typed.  For example, running `PRINT ASC("A")` would print 65 (the ASCII character code for the letter "A").

**NOTE:** For now, it's just ASCII (no Unicode).  However, this is something I plan to fix in a future update.  And that's where things really get interesting (and helpful).  Try printing `CHR$(9604)` and seeing what happens. :)

### ALIAS {string} = {string}

Aliases are kind of like a "create-your-own instruction".  To keep Breakaway BASIC as portable as possible, there are somet hings it just shouldn't have to do.  For example, in my work on this project, I would find it very easy to do something like this:

```
ALIAS "FILES" = "ls -la"
ALIAS "EDIT" = "nano"
ALIAS "DELETE" = "rm"
```

But let's say we port Breakaway BASIC to Windows someday; rather than compiling a bunch of extra (not to mention OS-dependent) code, I can just do:

```
ALIAS "FILES" = "dir"
ALIAS "EDIT" = "notepad"
ALIAS "DELETE" = "del"
```

And now with a lot less work, you can do this:

```
10 EDIT TEMP.TXT
20 FILES
30 DEL TEMP.TXT
40 FILES
```

When you `RUN` it, you will get more or less the same behavior (line 10 opens your text editor of choice, line 20 brings up a file listing, line 30 deletes the file you just wrote, and line 40 shows the updated file listing).

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

**NOTE:** You can also use lowercase cd, like you would in other shells (DOS, Bash etc).  For example, you can do `cd /path/to/wherever` or `cd ./wherever` like you're probably used to.

### CLEAR

Clears the screen.  This is used by a bunch of other examples (for instance, `BG`) so there's no need to repeat it here.

### CONT

Continues the program from where it left off.  So for example, if you have the program:

```
10 PRINT "BREAKAWAY ";
20 PRINT "BASIC ";
30 PRINT "IS ";
40 PRINT "AWESOME!"
```

And you hit Escape while it was on line 10, it would print "BASIC IS AWESOME!" (since it already ran line 10)

### COLUMNS()

Gets the number of columns of characters in your terminal, for terminals that support that feature.  For example:

```
PRINT COLUMNS(), "COLUMNS BY", ROWS(), "ROWS"
```

Should give you the dimensions of your terminal in characters.

### CURSOR ON/OFF

Shows or hides the blinking cursor on terminals that support it.  For example, this little program hides both the cursor and the text you type, kind of like when you're entering a password:

```
10 CURSOR OFF
20 PRINT "ENTER YOUR 4-DIGIT PIN:"
30 HIDDEN ON
40 INPUT X
50 HIDDEN OFF
60 CURSOR ON
70 PRINT "YOU TYPED: ",X
```

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

### FRE()

Prints the number of bytes free; not particularly useful or important on a modern system, but Commodore BASIC does it so I figured it would be a fun feature to have just cuz. :)

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

To exit this loop, press the Escape key.

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
10 LET X = 42
20 PRINT X
```

It will print 42.  Note that the `LET` keyword is optional (you can just do i.e. `10 X = 42`).

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

### RC()

Gets the return code of the last `SYS` call or system call in program mode.  This is usually zero, so checking if it's not may be useful for troubleshooting. For example:

```
10 SYS "ls"
20 IF RC() <> 0 THEN GOTO 50
30 PRINT "IT WORKED"
40 END
50 PRINT "COMMAND FAILED."
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

### ROWS()

Gets the number of rows of characters in your terminal, for terminals that support that feature.  For example:

```
PRINT COLUMNS(), "COLUMNS BY", ROWS(), "ROWS"
```

Should give you the dimensions of your terminal in characters.

### RUN

Runs your program.  To stop running, press the Escape key.

### SAVE {string}

Saves your program to a file (the string is the file name).

### SYS {string}

Runs a system command.  For example:

```
10 REM LIST STUFF IN THE CURRENT FOLDER
20 CLEAR
30 SYS "ls -la"
```

The return value of the system call will be saved for later use by the `RC()` function.

### UNDERLINE ON/OFF

Turns underline text on/off

```
10 UNDERLINE ON
20 PRINT "THIS WILL BE UNDERLINED."
30 UNDERLINE OFF
40 PRINT "THIS WON'T."
```
