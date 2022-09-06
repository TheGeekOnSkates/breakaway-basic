# To-do's for version 0.3

* Also, now that our title screen is totally customizable, add a PROMPT command; this way instead of "READY." with a newline a la Commodore, you can have "]" like an Apple ][, or "Ok" like a TRS-80 Model 100 etc. :)
* MOVE UP/DOWN/LEFT/RIGHT/HOME/END - or maybe just MOVE X Y TRUE
* I kinda like the idea of ROW() and COLUMN() to get cursor position
* Support for special characters like "▄" in ASC
* Support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
* When that's done, add support for case-insensitive commands (see issue #1 on GitHub)
* POKE X Y character (right now it takes 4 lines to do this - put CHARACTER at position X, Y)
* PEEK(X, Y) - get character at that position.  On the other hand, what if I made the memory stack bigger?  Then we could do not only screen "RAM" but also color "RAM" and use the rest for storing data.  Might be nice to have an extra 64K (or 128K or whatever) just for extra data.
* Now that I'm using is_keyword in is_var, address that bug in math.c
* Keep swatting at the buggz.  Eventually I'll catch one. :D
* Keep updating the docs as I go

# Buggz! :D

* See math.c on why I currently have to replace functions _after_ replacing variables.  Unlike the next one, this bug makes perfect sense (all variables are letters A-Z, all BASIC functions are made up of those letters, so ROWS() becomes 0000() if I call replace_vars first.)






-----------------------------------------------------------------------------------------------------------------------

# Road map to version 1.0

## Fun stuff I'll add when I get in the mood, just cuz it's awesome

* I was researching the whole "get cursor position with termios" thing when I found this:
	http://dtelnet.sourceforge.net/shkeys.c
  Apparently, you can get (and even SET) *mouse support!*  If I can find out how that works; I could add instructions like MOUSE ON/OFF, MOUSEX() and MOUSEY() to get the position, CLICKX() and CLICKY() to get the last clicked position, ON CLICK GOTO... no, that's too far. :D
* If I go there... and I might cuz it's awesome... why not use the Linux *joystick* library?!  There's a joystick.h I used years ago that would totally work for that.


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
* Files


------------------------------------------------------------------------------------------------------------

# How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
