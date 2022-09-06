# To-do's for version 0.3

* Finish support for "string expressions" - what I mean is, "something like" + " this" + STR$(whatever the character code for "." is)
	- Add an is_string_function function (lol) - returns true for things like CHR$, TAB, etc. which return strings
	- In is_print, replace is_function with is_string_function
	- Fix the bug at the top of the "buggz" list
	- Once combine_strings works for PRINT, get it to work in PROMPT
	- Then, same deal for SYS
* Add support for case-insensitive commands (see issue #1 on GitHub)
* Once that's done, I'd say update the docs and call 0.3 done - it's already *way* better than 0.2!

# Buggz! :D

* If I do PRINT CHR$({number}) + "STRING", it works; if I print "STRING" + CHR$(number), the CHR$ part gets clipped off.  Note this is true whether we're talking special characters or ASCII
* See math.c on why I currently have to replace functions _after_ replacing variables.  Unlike the next one, this bug makes perfect sense (all variables are letters A-Z, all BASIC functions are made up of those letters, so ROWS() becomes 0000() if I call replace_vars first.)
* Looking at other BASICs, I notice mine doesn't show the prompt nearly often enough; like if I do "10 PRINT whatever" I get no prompt, but anything else in direct mode gives me a prompt.  Maybe give that a closer look (take the prompts out of run_program and put them back in main or something)





-----------------------------------------------------------------------------------------------------------------------

# Road map to version 1.0

## Fun stuff I'll add when I get in the mood, just cuz it's awesome

* SPC({number}) like the C64 has
* I was researching the whole "get cursor position with termios" thing when I found this:
	http://dtelnet.sourceforge.net/shkeys.c
  Apparently, you can get (and even SET) *mouse support!*  If I can find out how that works; I could add instructions like MOUSE ON/OFF, MOUSEX() and MOUSEY() to get the position, CLICKX() and CLICKY() to get the last clicked position, ON CLICK GOTO... no, that's too far. :D
* If I go there... and I might cuz it's awesome... why not use the Linux *joystick* library?!  There's a joystick.h I used years ago that would totally work for that.


## On the to-do list for 0.4

* Variables with names longer than 1 character
* Variables ending in $ being strings
* MOVE UP/DOWN/LEFT/RIGHT/HOME/END - or maybe just MOVE X Y TRUE
* I kinda like the idea of ROW() and COLUMN() to get cursor position
* Support for special characters like "▄" in ASC
* POKE X Y character (right now it takes 4 lines to do this - put CHARACTER at position X, Y)
* PEEK(X, Y) - get character at that position.  On the other hand, what if I made the memory stack bigger?  Then we could do not only screen "RAM" but also color "RAM" and use the rest for storing data.  Might be nice to have an extra 64K (or 128K or whatever) just for extra data.
	**EDIT:** The more I think about this, the more I'm thinking it should be more like other BASICs, POKE {address} {value} and PEEK({address}) - that way addresses > the total character cells can be used to set *colors* on specific cells rather than *characters* :)
* Now that I'm using is_keyword in is_var, address that bug in math.c
* GET (may need to add BLOCK ON/OFF to make that work tho)
* Add support for parens again
* And when I going *there*, may as well add in all my other mathing work - meaningless functions like ABS, ATN, COS, TAN, ETC, ETC, ETC, that some people will appreciate.
* Something like my old CLEAR HISTORY
* also, a way to not add repeats to history


## Giant leaps forward that will probably end up in me calling it a 1.0

* FOR <expr> TO <expr> STEP <expression>
* NEXT (can't have FOR without it) :)
* Arrays
* _maybe_ WHILE / LOOP (not WEND or END WHILE like other BASICs)
* Advanced file I/O (OPEN, CLOSE, PRINT#, INPUT# etc.)


------------------------------------------------------------------------------------------------------------

# How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
