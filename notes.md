# To-do's for version 0.4

* Maybe play with that `COLOR` instruction idea (see below)
* Once that's done, I'd say update the docs and call 0.3 done - it's already *way* better than 0.2!

# Buggz! :D

1. I can't actually do LET I = -3; at first I thought this was a problem with my FOR/NEXT changes, but nope - even in old versions, negative variables crash the program.
2. I noticed that sometimes Breakaway BASIC crashes if system() returns a non-zero value.  For example, in my game, "The Great Gretscii", I use a build script instead of a Makefile.  If the build fails, BASIC crashes.  Ask around forums about this. :D

-----------------------------------------------------------------------------------------------------------------------

# Notes on the buggz

## LET X = -3 crashes

I've narrowed it down to line 612, eval_expr.  Not surprised there.  Advanced mathing is something I plan to address in the next update (something I tried to do in a different 0.4 branch, lol).  I think the solution will involve merging a lot of code from my old calculator app - which, in addition to fixing the bug, should also introduct a boatload of functions for math lovers - `COS` and `ATN` and all those other random ones that I have no idea how to use for any practical purpose whatso-flipping-ever. :D
But for now, I'm gonna let it go and just roll out 0.4 as-is.  It's a zero-point release, so it's "good enough".  And it has a bunch of fun features so why not? :)


-----------------------------------------------------------------------------------------------------------------------

# Road map to version 1.0

## On the to-do list for future 0.x releases

* I just saw an awesome idea from the 8-Bit Guy: His BASIC for the Commander X16 has `COLOR FG, BG` - like a 2-in-1.  Breakaway BASIC _needs_ that.  Saves a line of code. :D
* Add support for nested parens, variable-replacing etc.  It's a rabbit-hole that nearly brought this project to a halt, so no hurry.  See math.c on why I currently have to replace functions _after_ replacing variables.  Unlike the next one, this bug makes perfect sense (all variables are letters A-Z, all BASIC functions are made up of those letters, so ROWS() becomes 0000() if I call replace_vars first.)
* SPC({number}) like the C64 has
* STR$/LEFT$/RIGHT$/MID$! :)
* I was researching the whole "get cursor position with termios" thing when I found this:
	http://dtelnet.sourceforge.net/shkeys.c
  Apparently, you can get (and even SET) *mouse support!*  If I can find out how that works; I could add instructions like MOUSE ON/OFF, MOUSEX() and MOUSEY() to get the position, CLICKX() and CLICKY() to get the last clicked position, ON CLICK GOTO... no, that's too far. :D
* If I go there... and I might cuz it's awesome... why not use the Linux *joystick* library?!  There's a joystick.h I used years ago that would totally work for that.
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

* Arrays
* _maybe_ WHILE / LOOP (not WEND or END WHILE like other BASICs)
* Advanced file I/O (OPEN, CLOSE, PRINT#, INPUT# etc.)

## Crazy awesome ideas that fal into the "maybe someday" category

### Idea #1

@Dreadful over on Lunduke did some "wishful thinking" and I like where s/he is going with this:
FOR EACH fname IN DIR(somedir) : OPEN "I",#1,fname : DO LINE INPUT #1, S$ : IF INSTR(1,LCASE(S$),"error" ) > -1 THEN PRINT S$ : LOOP WHILE EOF(#1) > -1 : CLOSE #1 : NEXT fname

To make this work, I would have to have:

* Using colons as a delimiter, so I can have multiple instructions on one line (a thing I've been kinda wanting myself).  Commodore BASIC has that.  Most BASICs do.
* A `DIR()` function
* Some of the stuff I thought of as "advanced file I/O"
* And a `FOR EACH` statement
* Oh, and longer named variables (it would have to be fname$ but still, a thing I've been wanting to add myself)

### Idea #2

@Barry6502gs (also on Lunduke) said this:

My version of "Import" for BASIC with Line Numbers would Insert at "Here-Line-Number", and in theory Re-Numbers appropriately. 🤔 I'd probably put my "INCLUDE" at the bottom. Line numbers should not become a problem (because Auto-Re-Number)

in File "HappyHappy.BAS"
1001 REM Subroutine to Print "Happy"
1002 PRINT "Happy Happy Happy"
1003 RETURN

in File "FooBarBaz.BAS"
1001 REM Subroutine to Print "FooBar"
1002 PRINT "Foo Bar Baz"
1003 RETURN

in Main File
10 REM This is my Main File
20 GOSUB 1000
30 GOSUB 2000
40 END
50 REM Subroutine Modules Included Below
1000 INCLUDE "HappyHappy.BAS"
1010 REM Maybe Explain Something Here
2000 INCLUDE "FooBarBaz.BAS"
2010 REM Probably Need Warning Message If This Line Executes

PS: Are you giving yourself an "Auto-Number" or "Re-Number" Utility? (I think the TRS-80 had that capability.)
Afterthought: "LIST" Command - When "INCLUDE" exists, have a "Verbose" option which Expands the "Included Modules"

Wow, just... wow.  So much cool stuff to unpack here...

* Renumber is a thing I've been thinking about (he's right the M-100 has it)
* His idea of INCLUDE is more lika my INCLUDE and RUN. Totally doable and very cool.  Eliminates the risk of overwriting line numbers
	Thought: What if I do an INCLUDE that doesn't have line numbers?  Wouldn't that work like his?
	Idea: what about a RUN "file" - separate thing from INCLUDE... answer my first question first.


------------------------------------------------------------------------------------------------------------

# How to add new instructions

1. Define an is_* function for it
2. Add a check for it to is_statement
3. Add a check for it in RUN to make it do whatever it's supposed to do
