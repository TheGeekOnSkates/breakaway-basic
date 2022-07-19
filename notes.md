# TO-DO'S

For RENUMBER:

* For some reason, renumbering by multiples of 10 is not working (but RENUMBER 5, RENUMBER 7 etc. are)
* Get it to also check for strings that contain GOSUB and GOTO, and replace those line numbers with the new ones (that's gonna be a big job lol)

For readline-related stuff:

1. Test all my instructions, to make sure they still work as expected.
2. Ditch all that code that strips out newline chars and test again.
3. Try going beyond BUFFER_MAX and see what happens; might need to fix some things.
4. Figure out how to clear readline history, and add a command for it (and maybe a command to _list_ history too, maybe even turn it on/off).

On IF:

* Keep trying to figure out that bug with PI (I think maybe it's because there was a ReplacePi function in math.h that I forgot about, lol).  Or maybe the above will fix it?
* Write a function to check if a string is a number (I think I have one in my library?)
* Write a function to check if a string starts and ends with quotation marks (maybe a QuotesMatch similar to ParensMatch
* Using that, back in RunIF, get the left and right sides and try these functions on them; see how that works out.
* Also, I found out aliases can override keyboards (I created one called TEST, then tried to TEST a variable lol... add an IsKeyword function and fix that).

# KNOWN ISSUES

There's a bug in ReplaceVariablesWithValues; if I do this:

LET PI = 3.14159
LET X = 7
LET Y = 3
IF X + Y < PI THEN 10

The if-statement works correctly:
IF 7 + 3 < 3.14159 THEN 10

But if I leave the spaces out of the equation:

IF X+Y<PI THEN 10
I get:
IF 7.14159+3.14159<3.14159 THEN 10

-----------------------------------------------------------------------------------------------

In xterm, whenever I type a line > 80 chars, it somehow gets separated/cut off.  For example, if I do:

git commit -m "some message that goes to the next line because it's greater than 80 characters long..."

Git only sees the first 80 chars.  Also, if you don't give it a closing quote (which Git is normally fine with) you get an error.  Not sure what to do about that apart from changing my Git config to use nano :)


-----------------------------------------------------------------------------------------------



# FEATURES TO BE ADDED

* RENUMBER (like I think it was the TI 99 4/A had)
* Type-checking on variables
* PROMPT string (so instead of "READY." users could have "Ok" like on the Tandy M-100, or "]" like on the Apple ][ etc.)
* As I create/change BASIC commands, keep updating the docs.
* Add PUT x y character
* Add COLOR x y color, or maybe COLORS x y fg bg
* Environment variables like ~
* Arrays
* GET
* Looping (FOR, _maybe_ WHILE)
* PRINT
* Advanced file I/O: OPEN and CLOSE, GET# and INPUT#, PRINT#, CLEAR# etc.
* __MAYBE__ an auto-run file (kinda like a config file, but not really... think autoexec.bat in DOS :D)
* Maybe a history like Bash has; not important, but it would be kinda nice.
* But that would also involve putting text into STDIN (and if I can do that I'd also want an EDIT command like the TI 99 4/A has)

And by the time I get here, idk what else I could possibley need/want.  I can write aliases for things like speech (i.e. `ALIAS SAY SYS easpeak `), sound, and things like listing files.  And if I'm using this with a screen reader, the screen reader will automatically speak stuff as I PRINT it anyway... now 3D sound is a bit tricky, but IMO that's a different project entirely.  And if I write that program, I can make aliases for that in Breakaway BASIC too :)
