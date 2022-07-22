# TO-DO'S

For RENUMBER:

* Get it to also check for strings that contain GOSUB and GOTO, and replace those line numbers with the new ones (that's gonna be a big job lol)

Readline-related stuff:

* Figure out how to clear readline history, and add a command for it (and maybe a command to _list_ history too, maybe even turn it on/off).

On IF:

* If an if-statement fails, and there is no ELSE, it segfaults (what the).
* Move more of the branches into if.c - that function is getting huge
* Still like the idea of a function to check if a string starts and ends with quotation marks (maybe a QuotesMatch similar to ParensMatch

# KNOWN ISSUES

* It seems changing variables isn't working; look at tests/test6 - if I change lines 20 or 30 (the values to be compared in an IF-statement), it doesn't actually work correctly unless I do a NEW and then re-LOAD)
* Aliases can override keywords (I created one called TEST, then tried to TEST a variable lol... add an IsKeyword function and fix that).
* Also, idk if I want NEW to delete aliases; I have a script I wrote (not in this folder) that adds a bunch of them, but every time I load a different program, they get deleted.


-----------------------------------------------------------------------------------------------

# FEATURES TO BE ADDED

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
