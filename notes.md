# To-do's for version 0.2

* Update the docs - releases have "known issues" after all
* Keep swatting at the buggz.  Eventually I'll catch one. :D
* May as well keep adding fun features :)


# Buggz! :D

* See math.c on why I currently have to replace functions _after_ replacing variables.  Unlike the next one, this bug makes perfect sense (all variables are letters A-Z, all BASIC functions are made up of those letters, so ROWS() becomes 0000() if I call replace_vars first.)
* And yes, the dreaded cd/system mystery-bug I've been struggleshooting for weeks now... When a system command runs in program mode, it seems to stop (see "TEST"); not to mention, look at run.c - there's a run_system, but also a run_sys - not sure if it should be that way.  I noticed too that lowercase cd doesn't seem to be working consistently - could be related to the previous issue.
	**EDIT:** Pretty sure it is related; look at my "TEST" script.  If I comment out line 10, line 20 ("pwd") runs but then stops.  If I then comment out line 20, line 30 (cd ../) runs, and the program stops.  This doesn't make a whole lot of sense, but I'm sure it's a slight'n'stupid.  Gotta be some ridonkulously subtle son-of-a-bug hiding in plain site.  Someday I'll attack it with a fresh brain, lure it out of its tiny hidey-hold and squash the sucker. :D
	**EDIT 2:** Extended notes below.  This nuisance is hands down one of the most slippery bugs I've ever fought.

## Okay, it's tracy-trace time............... :P

* So like all programs, it starts in main().
* Main kicks it off to parse().
* Parse can go to either:
	- set_line (program mode, which is what "TEST" uses), or
		But set_line just copies the program into memory; it doesn't actually run anything.
	- run (both modes mode, if is_statement returns true), OR
		This runs BASIC statements, which can include both run_sys and run_system.
	- run_system (direct mode, if is_statement returns false)
		Here, there is yet another problem: For {reasons}, just running cd ../ works from HERE (my project folder) but not when Breakaway BASIC is run from ./.bashrc; this stooooopid CD bug!  What the puck!  #pucksucker

So I think we can rule out run_sys - it works fine.  Like, all the time.
I think I can also count out run_cd; again, it seems rock-solid.
The lowercase cd is flaky, unpredictable, being reliable when I need it to break and breaking when I think it's done.  So that is definitely one component of this particular gorilla-bug.
The bigger issue seems to be with pwd though; it's like it hangs in program mode; I can run it by itself and it's fine; I can run SYS "pwd" and it's fine.  So this one will have to remain a mystery, possibly till my Lord comes back and shows me my ID10T error.  Then we can have a good laugh together and move on. :)






-----------------------------------------------------------------------------------------------------------------------

# Road map to version 1.0

* Aliases - that was really cool on the old version
* Support for special characters like "▄" in ASC
* Set up LET so I can just do i.e. X = 7 (make sure to call is_variable and all that first, to prevent the issue I described before [equals signs in commands])
* Add support for parens again
* And if I'm going _there_, may as well add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Variables with names longer than 1 character
* Variables ending in $ being strings
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
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
