# To-do's for version 0.2

* Update the docs - I'm at the point of just calling it a "known issue" and saying the puck with it.  Really, really, really, really not worth the aggravation!  This isn't fun anymore.  If I ever get paid to maintain this project, I will gladly burn countless hours tracing and tracking and speculating and guessing and praying until someday my God shows me the solution... but maaaaaaaaaan...... Goo.  Ber.  Ly.  What a mega-goob!  Ultra-goob!  There's gotta be some reeeeeeeeeeeeally low-level explanation, something so insanely close to the kernel that only my Lord and Mr. Linus understand.  Maybe someday I'll research how Bash does it.  It doesn't seem to just be with CD.  It also seems to be with pwd and other system commands.  I think this is one of those things that will somehow, someday, just "naturally" solve itself.  Like if I build a way to combine strings, then I could just do SYS "ls" + CHR$(32) + "-la" and so passing characters to SYS commands will be kind of a non-issue.  The language itself - the part that doesn't rely on OS-dependent code - is working just fine.  Duh heck widdit. :P

# Buggz! :D

* See Line 33 (or was it 333) of math.c
* When a system command runs in program mode, it seems to stop (see "TEST"); not to mention, look at run.c - there's a run_system, but also a run_sys - not sure if it should be that way
* I noticed too that lowercase cd doesn't seem to be working consistently - could be related to the previous issue.
	**EDIT:** Pretty sure it is related; look at my "TEST" script.  If I comment out line 10, line 20 ("pwd") runs but then stops.  If I then comment out line 20, line 30 (cd ../) runs, and the program stops.  This doesn't make a whole lot of sense, but I'm sure it's a slight'n'stupid.  Gotta be some ridonkulously subtle son-of-a-bug hiding in plain site.  Someday I'll attack it with a fresh brain, lure it out of its tiny hidey-hold and squash the sucker. :D

## Okay, it's tracy-trace time...............

* So like all programs, it starts in main().
* Main kicks it off to parse().
* Parse can go to either:
	- set_line (program mode, which is what "TEST" uses), or
		But set_line just copies the program into memory; it doesn't actually run anything.
	- run (both modes mode, if is_statement returns true), OR
		This runs BASIC statements, which can include both run_sys and run_system.
	- run_system (direct mode, if is_statement returns false)
		Here, there is yet another problem: For {reasons}, just running cd ../ works from HERE (my project folder) but not when Breakaway BASIC is run from ./.bashrc; this stooooopid CD bug!  What the puck!  #pucksucker








-----------------------------------------------------------------------------------------------------------------------

# Road map to version 1.0

* ASC(<character>)
* FRE() - like on Commodore BASIC
* Add support for parens again
* And if I'm going _there_, may as well add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Aliases - that was really cool on the old version
* Variables with names longer than 1 character
* Variables ending in $ being strings
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
* Set up LET so I can just do i.e. X = 7 (make sure to call is_variable and all that first, to prevent the issue I described before [equals signs in commands])
* FOR <expr> TO <expr> STEP <expression>
* NEXT (can't have FOR without it) :)
* GET (may need to add BLOCK ON/OFF to make that work tho)
* Variables with parens being arrays
* POKE X Y character (right now it takes 4 lines to do this - put CHARACTER at position X, Y)
* PEEK(X, Y) - get character at that position.  On the other hand, what if I made the memory stack bigger?  Then we could do not only screen "RAM" but also color "RAM" and use the rest for storing data.  Might be nice to have an extra 64K (or 128K or whatever) just for extra data.



------------------------------------------------------------------------------------------------------------

# How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
