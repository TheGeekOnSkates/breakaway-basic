# To-do's for version 0.2

* Finish CHR$ - I think I have is_chr working; but now I need to actually replace the character.
* Fix the buggz :/
* Update the docs

# Buggz! :D

* I can't do MOVE COLUMNS() ROWS() - might also be a good idea to try MOVE 3 + 3 4... actually, just saying that, I kinda want to add a comma between X and Y.
* PRINT "     Leading spaces IN QUOTES get clipped.     ";
* Need to allow for system commands in program mode, such as:

	10 micro notes.md
	20 make

  Currently this would throw a syntax error (look at run_program.c).



-----------------------------------------------------------------------------------------------------------------------

# Road map to version 1.0

* ASC(<character>)
* Add support for parens again
* And if I'm going _there_, may as well add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Update the docs
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
* POKE X Y character (right now it takes 4 lines to do this - put CHARACTER at position X, Y)
* PEEK(X, Y) - get character at that position.  On the other hand, what if I made the memory stack bigger?  Then we could do not only screen "RAM" but also color "RAM" and use the rest for storing data.  Might be nice to have an extra 64K (or 128K or whatever) just for extra data.

## Pipe dreams for 2.0

* Sound (link SDL2 on Linux)
* Porting to DOS - not sure how sound would work, but everything else is diable
* Porting to Windows - by the time 1.0 is super-polished and super-fun, I would like to be able to use it for scripting at work. :)


------------------------------------------------------------------------------------------------------------

# How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
