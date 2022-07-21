# TO-DO'S

For RENUMBER:

* Get it to also check for strings that contain GOSUB and GOTO, and replace those line numbers with the new ones (that's gonna be a big job lol)

Readline-related stuff:

* Try going beyond BUFFER_MAX and see what happens; might need to fix some things.
	**EDIT:** I think this is not an issue - I use strncpy, not strcpy, unless I know I'm under the limit.  So next commit delete this message. :)
* Figure out how to clear readline history, and add a command for it (and maybe a command to _list_ history too, maybe even turn it on/off).

On IF:

* Write a function to check if a string starts and ends with quotation marks (maybe a QuotesMatch similar to ParensMatch
* Using that, back in RunIF, get the left and right sides and try these functions on them; see how that works out.
	**NOTE:** This is tricker than it sounds; for one thing, AND/OR/NOT throws a monkey-wrench into the whole idea.  I think this will be a char-by-char analysis, not using functions like the ones in validation.c... at least, maybe not yet...)

# KNOWN ISSUES

* Aliases can override keywords (I created one called TEST, then tried to TEST a variable lol... add an IsKeyword function and fix that).
* Also, idk if I want NEW to delete aliases; I have a script I wrote (not in this folder) that adds a bunch of them, but every time I load a different program, they get deleted.


-----------------------------------------------------------------------------------------------

In xterm, whenever I type a line > 80 chars, it somehow gets separated/cut off.  For example, if I do:

git commit -m "some message that goes to the next line because it's greater than 80 characters long..."

Git only sees the first 80 chars.  Also, if you don't give it a closing quote (which Git is normally fine with) you get an error.  Not sure what to do about that apart from changing my Git config to use nano :)

**NOTE:** Does readline fix this?  Find out.


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
