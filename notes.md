# To-do's for version 0.2

* Use is_keyword to make the syntax-checker a bit smarter - if I type `MOVE X` that's a syntax error, not a system command.
* Use is_keyword in is_var if possible
* MOVE UP/DOWN/LEFT/RIGHT
* I kinda like the idea of ROW() and COLUMN() to get cursor position - there's gotta be a way to do it in the "termios" API (or the "ioctl" API... lol where do the kernel folks come up with this cryptic shorthand?) :D
* Support for special characters like "▄" in ASC
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
* POKE X Y character (right now it takes 4 lines to do this - put CHARACTER at position X, Y)
* PEEK(X, Y) - get character at that position.  On the other hand, what if I made the memory stack bigger?  Then we could do not only screen "RAM" but also color "RAM" and use the rest for storing data.  Might be nice to have an extra 64K (or 128K or whatever) just for extra data.
* Aliases
* Auto-run files
* Keep swatting at the buggz.  Eventually I'll catch one. :D
* Update the docs
* Random thought: Do I really need parse()?  Its code could be added to run(), cuz it's not really a separate step anymore.


# Buggz! :D

* See math.c on why I currently have to replace functions _after_ replacing variables.  Unlike the next one, this bug makes perfect sense (all variables are letters A-Z, all BASIC functions are made up of those letters, so ROWS() becomes 0000() if I call replace_vars first.)






-----------------------------------------------------------------------------------------------------------------------

# Road map to version 1.0

## Stuff I'll probably procrastinate longer - 0.4 (maybe), lol

* GET (may need to add BLOCK ON/OFF to make that work tho)
* Add support for parens again
* And if I'm going _there_, may as well add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Variables with names longer than 1 character
* Variables ending in $ being strings
* Something like my old CLEAR HISTORY
* also, a way to not add repeats to history

## Giant leaps forward that will probably end up in me calling it a 1.0

* FOR <expr> TO <expr> STEP <expression>
* NEXT (can't have FOR without it) :)
* Arrays
* _maybe_ WHILE / LOOP (not WEND or END WHILE like other BASICs)



------------------------------------------------------------------------------------------------------------

# How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
