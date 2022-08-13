# Breakaway BASIC

## Overview

This idea started off as a fun experiment; let's see if I can create my own scripting language (and of course, what better than something super-old-school?  lol).  I wanted it to have a bunch of fun tools for creating ANSI graphics, 2D or even 3D sound, and to be fully screen-reader accessible (cuz sometimes I like to work eyes-free, not to mention it would be a great tool for building audio games).  I wanted it to be freed software, easy to pick up and fun for geeks like me who love the retro stuff.  But I also wanted it to be something I could actually use to get sh...tuff done.  It was fun, for awhile, but eventually collected dust as I got other ideas I was more interested in (distracted by) at the time. :)

But one day I got to tinkering with something else when I realized, Linux command-line scripting is HARD.  Its syntax is a mess, it's super-config-heavy, and it just... kinda stinks.  But then I discovered the difference between a "shell" and a "terminal"; turns out, there are lots of other shells out there.  There's one in particular that I really like, called "nushell" (they really need to capitalize that S cuz I keep wanting to type "nutshell" lol).  There's also a "cbmbasic" that is very nice, but it has some problems that make it less than ideal as a replacement for Bash.  Then there's zish and fish and lish and a bunch of other funny-sounding ones.  Basically, a shell is the main program that runs when you bring up a terminal/command prompt.  It's what you use to run other programs.

And then it hit me.  My old BASIC, with the right tweaks, would make a great (or at least fun) shell for Linux.  As of right now, my focus is mostly on Linux, but when I notice clearly OS-dependent code, I have a place for it.  It works similar to 8-bit BASICs, with line numbers and all that.

Also, for the curious: The name "Breakaway BASIC" has a double meaning.  For one thing, I'm kind of trying to "break away" from Bash.  But before that, the idea came from hockey.  A breakaway is one of the most exciting things that can happen in a game.  It's when a player gets past the other team's defense, a sort of duel between the player and the goalie.  Mano a mano.  Sometimes with the game on the line.  That's what I want my BASIC to be, like a player on a breakaway: fast, powerful, fun to watch, and just plain awesome. :)

## Command Reference

### ALIAS name = value

Aliases are a concept I borrowed from other shells; they're kind of like a "create-your-own instruction", which can come in really handy.  For example, if I run this code (on Linux):

ALIAS FILES = ls -la

I can then do this:

FILES /path/to/my/stuff

A couple notes here:

* For now, if you're going to use them as commands, don't enclose them in quotes.  This is something I hope to fix in future releases, but for now that's how it works.
* Aliases are not cleared by running LOAD or NEW.

### BG number

Set the text background color.  This varies from one terminal to the next and from one system to the next.

### BLINK ON (or OFF)

Turns text blinking mode on or off

### BOLD ON (or OFF)

Turns bright/bold color on or off

### CLEAR or CLS

Clears the screen (assuming your terminal supports ANSI escape codes).

### CLEAR ALIASES

Clears the list of aliases (undoes all ALIAS instructions)

### CLEAR HISTORY

Clears the command history

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

### HIDDEN ON (or OFF)

Turns hidden text (like you might see for a password) on or off

### ITALIC ON (or OFF)

Turns text italic mode on or off

### LET variable = value

Sets a variable (I'm kinda surprised BASICs used LET instead of SET, but it's a convention I won't break because people know it and BASIC is supposed to be, well, basic). :)

```
10 LET NAME = Wayne Gretzky
20 LET JERSEY = 99
30 LEAGUE = NHL
```

If you'll notice here, there are some HUGE differences from other basics:

* You don't need to put strings in quotes (you can, but the quotes would become part of the string).
* There is no type-checking.  If you like, you can use the $ and % characters like other BASICs do, and I suggest you do that just so you (and other users) know what the type should be.  But at the time of this writing, Breakaway BASIC doesn't enforce that.
* Also, like in other BASICs, the "LET" part is totally optional (see line 30)

Eventually, I would like to have it strip leading/trailing quotes off, and also do type-checking, but for now this is where we're at.

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

Clears the contents of the program memory, including all variables.  For example:

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

The only thing that is not deleted are any aliases you may have defined with the ALIAS keyword.

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

Runs a system command or external program.  Note that in early versions of Breakaway BASIC (before 2022.07.17.2), all system commands had to start with SYS.  Now, it's mainly in there for these (admittedly minimal) reasons:

* Backwards compatibility - not sure if anyone cloned or forked early versions, but it could have happened.
* Clarity - kind of like how in some BASICs the "LET" keyword is not required, but anyone who knows BASIC knows what it does).
* Cuz it's retro - Commodore's SYS command jumped to a place in memory (usually a machine code program), which is exactly what this does (well, it's what C's "system" function does anyway). :)

But Breakaway BASIC 2022.07.17.2 and later will assume any unrecognized command is a system command.  This way if you type "ls" instead of "SYS ls" it'll still work.  Before 2022.07.17.2 it just threw a syntax error.

### UNDERLINE ON (or OFF)

Turns text underline mode on or off


