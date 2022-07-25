TO-DO'S

--------------------------------------------------------------------------------

# High-level: To call this a release (to push to the master branch)

* Finish RENUMBER
* Finish variables
* Finish IF
* If possible, finish GET (the only thing I'd need it for isn't working, no obvious reason, might not be possible?)
* Add PRINT



--------------------------------------------------------------------------------

# For variables:

## Rework the value-setting part

For example, right now if I did:

LET X = 7
X = X + 3
TEST X

I would get "X + 3" (minus the quotes) when it should give me "10".

## Add name- and type-checking

* Up till version 2022.07.24.0, I could do crazy stuff like this:

=!SOMEVAR* = A string but not in quotes

This isn't particularly bad, cuz then I could do stuff like:

10 FILES = ls -la
20 FILES /path/to/whatever

But this BASIC has aliases now; I think what I might end up doing (for cases where I need to mix variables and commands) would be to do i.e.

10 OPTIONS = "-la"
20 "ls " + OPTIONS + " /path/to/whatever"

Which means checking for type mismatches, doing CombineStrings etc. like my old one did.

--------------------------------------------------------------------------------

# For PRINT

Yes, I think it's finally time to add that command.  Once the variable stuff is done, it'll nice to not have to use echo for everything (cuz not all systems will have it, though idk which - Haiku or BSDs maybe?  Even DOS did... idk).

1. Add a check for it to Interpret()
2. Have it run the eval functions on only the code not in quotes; for example:
	PRINT "7 + 3 = " 7 + 3
	It should print 7 + 3 = 10
3. Have it build and print the string.

--------------------------------------------------------------------------------

# For GET:

Get loops like this to work:

10 GET KEY
20 IF KEY = -1 THEN 10
30 TEST KEY

I've confirmed that the issue is not with variables; setting variables is fixed.  I think what might be happening is getchar is called, and then blocking is immediately turned back on.  idk, still working on it

--------------------------------------------------------------------------------

# For RENUMBER

Finish getting it to renumber references

* Debug the test I have in place for THEN.  It seems to work (when I run LIST it shows what I want), but then RUNning it causes segfaults (because {reasons}).  I really need to do a CRASH-course on core dumps. :D
* Once I can RUN my renumbered program without crashing it, factor in ELSE.  Right now, it would get erased (but that's okay cuz I'm still tinkering with the strategy - usually segfaults are a sign of an ID10T error, so THEN may take serious time to fully discover what stupid thing I did, lol).
* Then do it for GOTO/GO TO/GOSUB/GO SUB

--------------------------------------------------------------------------------

# On IF:

* If an if-statement fails, and there is no ELSE, it segfaults (what the).
* Move more of the branches into if.c - that function is getting huge
* Still like the idea of a function to check if a string starts and ends with quotation marks (maybe a QuotesMatch similar to ParensMatch


--------------------------------------------------------------------------------

# KNOWN ISSUES I'M WILLING TO OVERLOOK :)

From what I read about readline's history, getting the history list creates variables that need to be freed; however, actually doing that as the Stack Overflow post suggested leads to memory errors (double frees, linked list corrupt or something, etc.).  So there is probably (?) a memory leak there.  But I've been all over the web looking for docs on readline and haven't found them yet, so obscure SO posts are all I have to go on.  Not worth fighting with for a fun project. :)

-----------------------------------------------------------------------------------------------

# FEATURES TO BE ADDED

* PROMPT string (so instead of "READY." users could have "Ok" like on the Tandy M-100, or "]" like on the Apple ][ etc.)
* As I create/change BASIC commands, keep updating the docs.
* Add PUT x y character
* Add COLOR x y color, or maybe COLORS x y fg bg
* Environment variables like ~ (looks like on Linux, the "getenv" function works for this)
* Arrays
* FOR
* Advanced file I/O: OPEN and CLOSE, GET# and INPUT#, PRINT#, CLEAR# etc.
* __MAYBE__ an auto-run file (kinda like a config file, but not really... think autoexec.bat in DOS :D)

And by the time I get here, idk what else I could possibley need/want.  I can write aliases for things like speech (i.e. `ALIAS SAY SYS easpeak `), sound, and things like listing files.  And if I'm using this with a screen reader, the screen reader will automatically speak stuff as I PRINT it anyway... now 3D sound is a bit tricky, but IMO that's a different project entirely.  And if I write that program, I can make aliases for that in Breakaway BASIC too :)
