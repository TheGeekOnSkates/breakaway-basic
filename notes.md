# To-do's for version 0.2

* Fix the bugg(z? Could just be one now)
* Update the docs

# Buggz! :D

* When a system command runs in program mode, it seems to stop (see "TEST"); not to mention, look at run.c - there's a run_system, but also a run_sys - not sure if it should be that way
* I noticed too that lowercase cd doesn't seem to be working consistently - could be related to the previous issue.
	**EDIT:** Pretty sure it is related; look at my "TEST" script.  If I comment out line 10, line 20 ("pwd") runs but then stops.  If I then comment out line 20, line 30 (cd ../) runs, and the program stops.  This doesn't make a whole lot of sense, but I'm sure it's a slight'n'stupid.  Gotta be some ridonkulously subtle son-of-a-bug hiding in plain site.  Someday I'll attack it with a fresh brain, lure it out of its tiny hidey-hold and squash the sucker. :D


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
