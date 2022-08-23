I think I have is_chr working; but now I need to actually replace the character.
Also, lowercase cd is not working yet (maybe don't call run_cd)


# To-do's for version 0.2

* ROW() and COLUMN() to get the current cursor position
* ASC(<character>)
* CHR$(<number>)
* Add support for parens again (might be necessaryto make ASC and CHR work)
* And if I'm going _there_, may as well add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Update the docs

# Known issues

* Fix the bug in "LAUGH" (syntax error in 20??)
* In the Escape shortcut, fix the "BREAK" line; for example, in the classic
	10 PRINT "BREAKAWAY!  ";
	20 GOTO 10
  When I hit Escape, it says "BREAK IN 11" or "IN 15" or wherever - get it to point to the last actual line that ran.


-----------------------------------------------------------------------------------------------------------------------

# Thoughts / plans for version 0.3

* Aliases - that was really cool on the old version
* Variables with names longer than 1 character
* Variables ending in $ being strings
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)

# If I make it to version 1.0

* Set up LET so I can just do i.e. X = 7 (debating about this, cuz what if users want to run a command like ./my-script name="some file"?  The quotes make it hard to use `SYS`, and the = means it would be treated like a `LET`... maybe this should wait till after I have string-expressions and CHR$ and all that. :)
* FOR <expr> TO <expr> STEP <expression>
* NEXT (can't have FOR without it) :)
* Variables with parens being arrays
* Sound (technically possible with SYS "play somesound.wav" but a built-in API would be nice).



------------------------------------------------------------------------------------------------------------

# How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
